using Azure.Data.Tables;
using Microsoft.Azure.Functions.Worker;
using Microsoft.Azure.Functions.Worker.Http;
using Microsoft.Extensions.Logging;
using System.Net;

namespace api.Functions;

public class GetTableData(ILogger<GetTableData> logger)
{
    [Function("GetTableData")]
    public async Task<HttpResponseData> Run(
        [HttpTrigger(AuthorizationLevel.Anonymous, "get", Route = "table/{tableName}/{partitionKey}/{rowKey}")] HttpRequestData req,
        string tableName,
        string partitionKey,
        string rowKey)
    {
        logger.LogInformation("Processing request to get table data from {TableName} with PartitionKey: {PartitionKey}, RowKey: {RowKey}",
            tableName, partitionKey, rowKey);

        var response = req.CreateResponse();

        try
        {
            var connectionString = Environment.GetEnvironmentVariable("AzureWebJobsStorage");
            if (string.IsNullOrEmpty(connectionString))
            {
                response.StatusCode = HttpStatusCode.InternalServerError;
                await response.WriteStringAsync("Azure Storage connection string not configured");
                return response;
            }

            var tableServiceClient = new TableServiceClient(connectionString);
            var tableClient = tableServiceClient.GetTableClient(tableName);

            // Try to get the entity directly - if table doesn't exist, it will throw
            var entity = await tableClient.GetEntityAsync<TableEntity>(partitionKey, rowKey);

            if (entity?.Value == null)
            {
                response.StatusCode = HttpStatusCode.NotFound;
                await response.WriteStringAsync($"Entity not found with PartitionKey: {partitionKey}, RowKey: {rowKey}");
                return response;
            }

            response.StatusCode = HttpStatusCode.OK;
            await response.WriteAsJsonAsync(new
            {
                tableName,
                partitionKey = entity.Value.PartitionKey,
                rowKey = entity.Value.RowKey,
                timestamp = entity.Value.Timestamp,
                properties = entity.Value.Keys.Where(k => k != "PartitionKey" && k != "RowKey" && k != "Timestamp")
                    .ToDictionary(k => k, k => entity.Value[k])
            });

            logger.LogInformation("Successfully retrieved entity from {TableName}", tableName);
        }
        catch (Azure.RequestFailedException ex) when (ex.Status == 404)
        {
            logger.LogWarning("Entity not found in {TableName} with PartitionKey: {PartitionKey}, RowKey: {RowKey}",
                tableName, partitionKey, rowKey);
            response.StatusCode = HttpStatusCode.NotFound;
            await response.WriteStringAsync($"Entity not found with PartitionKey: {partitionKey}, RowKey: {rowKey}");
        }
        catch (Exception ex)
        {
            logger.LogError(ex, "Error retrieving entity from {TableName}", tableName);
            response.StatusCode = HttpStatusCode.InternalServerError;
            await response.WriteStringAsync($"Error: {ex.Message}");
        }

        return response;
    }
}
