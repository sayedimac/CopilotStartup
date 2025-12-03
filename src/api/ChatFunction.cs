using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Azure.Functions.Worker;
using Microsoft.Extensions.Logging;
using System.Text.Json;

namespace Api;

public class ChatFunction
{
    private readonly ILogger<ChatFunction> _logger;

    public ChatFunction(ILogger<ChatFunction> logger)
    {
        _logger = logger;
    }

    [Function("chat")]
    public async Task<IActionResult> Run(
        [HttpTrigger(AuthorizationLevel.Anonymous, "post", Route = "chat")] HttpRequest req)
    {
        _logger.LogInformation("Chat function processed a request.");

        string requestBody = await new StreamReader(req.Body).ReadToEndAsync();
        
        if (string.IsNullOrEmpty(requestBody))
        {
            return new BadRequestObjectResult(new { error = "Message is required" });
        }

        var chatRequest = JsonSerializer.Deserialize<ChatRequest>(requestBody, new JsonSerializerOptions
        {
            PropertyNameCaseInsensitive = true
        });

        if (chatRequest == null || string.IsNullOrEmpty(chatRequest.Message))
        {
            return new BadRequestObjectResult(new { error = "Message is required" });
        }

        // Simple echo response for the MVP
        var response = new ChatResponse
        {
            Message = chatRequest.Message,
            Reply = $"You said: {chatRequest.Message}",
            Timestamp = DateTime.UtcNow
        };

        return new OkObjectResult(response);
    }
}

public class ChatRequest
{
    public string Message { get; set; } = string.Empty;
}

public class ChatResponse
{
    public string Message { get; set; } = string.Empty;
    public string Reply { get; set; } = string.Empty;
    public DateTime Timestamp { get; set; }
}
