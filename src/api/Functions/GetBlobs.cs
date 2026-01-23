using Azure.Storage.Blobs;
using Microsoft.Azure.Functions.Worker;
using Microsoft.Azure.Functions.Worker.Http;
using Microsoft.Extensions.Logging;
using System.Net;

namespace api.Functions;

public class GetBlobs(ILogger<GetBlobs> logger)
{
    [Function("GetBlobs")]
    public async Task<HttpResponseData> Run(
        [HttpTrigger(AuthorizationLevel.Anonymous, "get", Route = "blobs/{containerName}")] HttpRequestData req,
        string containerName)
    {
        logger.LogInformation("Processing request to list blobs in container: {ContainerName}", containerName);

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

            var blobServiceClient = new BlobServiceClient(connectionString);
            var containerClient = blobServiceClient.GetBlobContainerClient(containerName);

            if (!await containerClient.ExistsAsync())
            {
                response.StatusCode = HttpStatusCode.NotFound;
                await response.WriteStringAsync($"Container '{containerName}' not found");
                return response;
            }

            var blobs = new List<string>();
            await foreach (var blobItem in containerClient.GetBlobsAsync())
            {
                blobs.Add(blobItem.Name);
            }

            response.StatusCode = HttpStatusCode.OK;
            await response.WriteAsJsonAsync(new
            {
                containerName,
                blobCount = blobs.Count,
                blobs
            });

            logger.LogInformation("Successfully listed {Count} blobs from container {ContainerName}", blobs.Count, containerName);
        }
        catch (Exception ex)
        {
            logger.LogError(ex, "Error listing blobs from container {ContainerName}", containerName);
            response.StatusCode = HttpStatusCode.InternalServerError;
            await response.WriteStringAsync($"Error: {ex.Message}");
        }

        return response;
    }
}
