namespace CopilotStartup.Web.Models;

public class ChatMessage
{
    public string Text { get; set; } = string.Empty;
    public bool IsUser { get; set; }
    public DateTimeOffset Timestamp { get; set; } = DateTimeOffset.UtcNow;
}

public class ChatRequest
{
    public string Message { get; set; } = string.Empty;
    public string? ConversationId { get; set; }
}

public class ChatResponse
{
    public string Reply { get; set; } = string.Empty;
    public string ConversationId { get; set; } = string.Empty;
    public DateTimeOffset Timestamp { get; set; }
}
