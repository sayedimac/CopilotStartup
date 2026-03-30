using api.Functions;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using Moq;

namespace test;

public class TableDataFunctionTests
{
    private readonly Mock<ILogger<TableDataFunction>> _loggerMock;
    private readonly TableDataFunction _function;

    public TableDataFunctionTests()
    {
        _loggerMock = new Mock<ILogger<TableDataFunction>>();
        _function = new TableDataFunction(_loggerMock.Object);
    }

    [Fact]
    public void GetTableData_ReturnsOkResult()
    {
        // Arrange
        var httpContext = new DefaultHttpContext();
        var request = httpContext.Request;
        var partitionKey = "partition1";
        var rowKey = "row1";

        // Act
        var result = _function.Run(request, partitionKey, rowKey);

        // Assert
        Assert.IsType<OkObjectResult>(result);
    }

    [Fact]
    public void GetTableData_ReturnsEntityWithCorrectPartitionKey()
    {
        // Arrange
        var httpContext = new DefaultHttpContext();
        var request = httpContext.Request;
        var partitionKey = "test-partition";
        var rowKey = "test-row";

        // Act
        var result = _function.Run(request, partitionKey, rowKey);

        // Assert
        var okResult = Assert.IsType<OkObjectResult>(result);
        Assert.NotNull(okResult.Value);
        
        var responseType = okResult.Value.GetType();
        var partitionKeyProperty = responseType.GetProperty("PartitionKey");
        Assert.NotNull(partitionKeyProperty);
        Assert.Equal("test-partition", partitionKeyProperty.GetValue(okResult.Value));
    }

    [Fact]
    public void GetTableData_ReturnsEntityWithCorrectRowKey()
    {
        // Arrange
        var httpContext = new DefaultHttpContext();
        var request = httpContext.Request;
        var partitionKey = "test-partition";
        var rowKey = "test-row";

        // Act
        var result = _function.Run(request, partitionKey, rowKey);

        // Assert
        var okResult = Assert.IsType<OkObjectResult>(result);
        Assert.NotNull(okResult.Value);
        
        var responseType = okResult.Value.GetType();
        var rowKeyProperty = responseType.GetProperty("RowKey");
        Assert.NotNull(rowKeyProperty);
        Assert.Equal("test-row", rowKeyProperty.GetValue(okResult.Value));
    }

    [Fact]
    public void GetTableData_ReturnsEntityWithData()
    {
        // Arrange
        var httpContext = new DefaultHttpContext();
        var request = httpContext.Request;
        var partitionKey = "partition";
        var rowKey = "row";

        // Act
        var result = _function.Run(request, partitionKey, rowKey);

        // Assert
        var okResult = Assert.IsType<OkObjectResult>(result);
        Assert.NotNull(okResult.Value);
        
        var responseType = okResult.Value.GetType();
        var dataProperty = responseType.GetProperty("Data");
        Assert.NotNull(dataProperty);
        Assert.NotNull(dataProperty.GetValue(okResult.Value));
    }

    [Fact]
    public void GetTableData_ReturnsEntityWithTimestamp()
    {
        // Arrange
        var httpContext = new DefaultHttpContext();
        var request = httpContext.Request;
        var partitionKey = "partition";
        var rowKey = "row";

        // Act
        var result = _function.Run(request, partitionKey, rowKey);

        // Assert
        var okResult = Assert.IsType<OkObjectResult>(result);
        Assert.NotNull(okResult.Value);
        
        var responseType = okResult.Value.GetType();
        var timestampProperty = responseType.GetProperty("Timestamp");
        Assert.NotNull(timestampProperty);
        
        var timestamp = timestampProperty.GetValue(okResult.Value);
        Assert.NotNull(timestamp);
        Assert.IsType<DateTime>(timestamp);
    }
}
