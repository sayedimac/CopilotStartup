using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Azure.Functions.Worker;
using Microsoft.Extensions.Logging;

namespace api.Functions;

public class TableDataFunction
{
    private readonly ILogger<TableDataFunction> _logger;

    public TableDataFunction(ILogger<TableDataFunction> logger)
    {
        _logger = logger;
    }

    [Function("GetTableData")]
    public IActionResult Run(
        [HttpTrigger(AuthorizationLevel.Anonymous, "get", Route = "table/{partitionKey}/{rowKey}")] HttpRequest req,
        string partitionKey,
        string rowKey)
    {
        _logger.LogInformation("Reading table data with PartitionKey: {PartitionKey}, RowKey: {RowKey}", 
            partitionKey, rowKey);

        // In a real implementation, this would connect to Azure Table Storage
        // and retrieve the entity with the specified keys
        var entity = new
        {
            PartitionKey = partitionKey,
            RowKey = rowKey,
            Data = "Sample data",
            Timestamp = DateTime.UtcNow
        };

        return new OkObjectResult(entity);
    }
}
