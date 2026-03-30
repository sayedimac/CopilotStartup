using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Azure.Functions.Worker;
using Microsoft.Extensions.Logging;

namespace api.Functions;

public class BlobListFunction
{
    private readonly ILogger<BlobListFunction> _logger;

    public BlobListFunction(ILogger<BlobListFunction> logger)
    {
        _logger = logger;
    }

    [Function("ListBlobs")]
    public IActionResult Run(
        [HttpTrigger(AuthorizationLevel.Anonymous, "get", Route = "blobs/{containerName}")] HttpRequest req,
        string containerName)
    {
        _logger.LogInformation("Listing blobs in container: {ContainerName}", containerName);

        // In a real implementation, this would connect to Azure Storage
        // and list blobs from the specified container
        var blobs = new[]
        {
            new { Name = "sample-blob-1.txt", Size = 1024L },
            new { Name = "sample-blob-2.txt", Size = 2048L }
        };

        return new OkObjectResult(new { ContainerName = containerName, Blobs = blobs });
    }
}
