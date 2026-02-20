using System.Net;
using System.Text.Json;
using CopilotStartup.Api.Models;
using Microsoft.Azure.Functions.Worker;
using Microsoft.Azure.Functions.Worker.Http;
using Microsoft.Extensions.Logging;

namespace CopilotStartup.Api;

public class ChatFunction
{
    private readonly ILogger<ChatFunction> _logger;

    public ChatFunction(ILogger<ChatFunction> logger)
    {
        _logger = logger;
    }

    [Function("chat")]
    public async Task<HttpResponseData> Chat(
        [HttpTrigger(AuthorizationLevel.Anonymous, "post", Route = "chat")] HttpRequestData req)
    {
        _logger.LogInformation("Chat function received a request.");

        ChatRequest? chatRequest;
        try
        {
            chatRequest = await JsonSerializer.DeserializeAsync<ChatRequest>(
                req.Body,
                new JsonSerializerOptions { PropertyNameCaseInsensitive = true });
        }
        catch (JsonException ex)
        {
            _logger.LogWarning(ex, "Invalid JSON in chat request body.");
            var badRequest = req.CreateResponse(HttpStatusCode.BadRequest);
            await badRequest.WriteStringAsync("Invalid request body.");
            return badRequest;
        }

        if (chatRequest is null || string.IsNullOrWhiteSpace(chatRequest.Message))
        {
            var badRequest = req.CreateResponse(HttpStatusCode.BadRequest);
            await badRequest.WriteStringAsync("Message is required.");
            return badRequest;
        }

        var conversationId = chatRequest.ConversationId ?? Guid.NewGuid().ToString();

        // Replace this echo reply with your preferred AI/LLM integration.
        var reply = $"You said: {chatRequest.Message}";

        var response = req.CreateResponse(HttpStatusCode.OK);
        response.Headers.Add("Content-Type", "application/json");
        await response.WriteStringAsync(JsonSerializer.Serialize(new ChatResponse
        {
            Reply = reply,
            ConversationId = conversationId
        }));

        return response;
    }
}
