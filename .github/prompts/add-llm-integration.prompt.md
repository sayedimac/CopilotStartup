---
mode: edit
description: Replace the echo-bot reply in ChatFunction.cs with a real LLM integration
---

Update `src/api/ChatFunction.cs` to replace the echo reply with a call to an LLM API.

## Requirements

1. Read the LLM API key from an environment variable (e.g. `OPENAI_API_KEY` or `AZURE_OPENAI_API_KEY`).
2. Use the `conversationId` to maintain conversation context across multiple turns.
3. Return the LLM's response text as the `Reply` field in the `ChatResponse`.
4. Handle API errors gracefully — return HTTP 502 with an error message if the LLM call fails.
5. Do not hard-code any API keys or endpoints.

## Integration options

Choose **one** of the following:

### Option A — Azure OpenAI (recommended for Azure deployments)

- NuGet package: `Azure.AI.OpenAI`
- Environment variables needed:
  - `AZURE_OPENAI_ENDPOINT` — your Azure OpenAI resource endpoint
  - `AZURE_OPENAI_API_KEY` — your API key
  - `AZURE_OPENAI_DEPLOYMENT` — the deployment name (e.g. `gpt-4o`)

### Option B — OpenAI

- NuGet package: `OpenAI`
- Environment variables needed:
  - `OPENAI_API_KEY`
  - `OPENAI_MODEL` (e.g. `gpt-4o-mini`)

### Option C — Semantic Kernel

- NuGet package: `Microsoft.SemanticKernel`
- Wire up the kernel in `Program.cs` and inject it into `ChatFunction`.

## Example skeleton (Azure OpenAI)

```csharp
// In Program.cs — register the client
services.AddSingleton(sp =>
{
    var endpoint = new Uri(Environment.GetEnvironmentVariable("AZURE_OPENAI_ENDPOINT")!);
    var credential = new AzureKeyCredential(Environment.GetEnvironmentVariable("AZURE_OPENAI_API_KEY")!);
    return new AzureOpenAIClient(endpoint, credential);
});

// In ChatFunction.cs — inject and call
var chatClient = _openAIClient.GetChatClient(Environment.GetEnvironmentVariable("AZURE_OPENAI_DEPLOYMENT"));
var completion = await chatClient.CompleteChatAsync(
    [new UserChatMessage(chatRequest.Message)]);
var reply = completion.Value.Content[0].Text;
```

## Tests

After integrating, run the Playwright API tests to verify end-to-end behaviour:

```bash
cd tests/playwright
API_BASE_URL=http://localhost:7071 npx playwright test "Chat API"
```
