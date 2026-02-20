namespace CopilotStartup.Api.Models;

public class ChatResponse
{
    public string Reply { get; set; } = string.Empty;
    public string ConversationId { get; set; } = string.Empty;
    public DateTimeOffset Timestamp { get; set; } = DateTimeOffset.UtcNow;
}
