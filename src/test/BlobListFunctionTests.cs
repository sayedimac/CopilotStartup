using api.Functions;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using Moq;

namespace test;

public class BlobListFunctionTests
{
    private readonly Mock<ILogger<BlobListFunction>> _loggerMock;
    private readonly BlobListFunction _function;

    public BlobListFunctionTests()
    {
        _loggerMock = new Mock<ILogger<BlobListFunction>>();
        _function = new BlobListFunction(_loggerMock.Object);
    }

    [Fact]
    public void ListBlobs_ReturnsOkResult()
    {
        // Arrange
        var httpContext = new DefaultHttpContext();
        var request = httpContext.Request;
        var containerName = "test-container";

        // Act
        var result = _function.Run(request, containerName);

        // Assert
        var okResult = Assert.IsType<OkObjectResult>(result);
        Assert.NotNull(okResult.Value);
    }

    [Fact]
    public void ListBlobs_ReturnsContainerNameInResponse()
    {
        // Arrange
        var httpContext = new DefaultHttpContext();
        var request = httpContext.Request;
        var containerName = "my-container";

        // Act
        var result = _function.Run(request, containerName);

        // Assert
        var okResult = Assert.IsType<OkObjectResult>(result);
        Assert.NotNull(okResult.Value);
        
        var responseType = okResult.Value.GetType();
        var containerNameProperty = responseType.GetProperty("ContainerName");
        Assert.NotNull(containerNameProperty);
        Assert.Equal("my-container", containerNameProperty.GetValue(okResult.Value));
    }

    [Fact]
    public void ListBlobs_ReturnsBlobsArray()
    {
        // Arrange
        var httpContext = new DefaultHttpContext();
        var request = httpContext.Request;
        var containerName = "test-container";

        // Act
        var result = _function.Run(request, containerName);

        // Assert
        var okResult = Assert.IsType<OkObjectResult>(result);
        Assert.NotNull(okResult.Value);
        
        var responseType = okResult.Value.GetType();
        var blobsProperty = responseType.GetProperty("Blobs");
        Assert.NotNull(blobsProperty);
        
        var blobs = blobsProperty.GetValue(okResult.Value) as System.Collections.IEnumerable;
        Assert.NotNull(blobs);
    }
}
