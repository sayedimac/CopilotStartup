using System.Net.Http.Json;
using CopilotStartup.Web.Models;

namespace CopilotStartup.Web.Services;

public class ChatService
{
    private readonly HttpClient _httpClient;

    public ChatService(HttpClient httpClient)
    {
        _httpClient = httpClient;
    }

    public async Task<ChatResponse?> SendMessageAsync(ChatRequest request)
    {
        var response = await _httpClient.PostAsJsonAsync("api/chat", request);
        response.EnsureSuccessStatusCode();
        return await response.Content.ReadFromJsonAsync<ChatResponse>();
    }
}
