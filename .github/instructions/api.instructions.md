---
applyTo: "src/api"
---

- This is a C# (.NET 9, isolated worker model) Azure Functions app
- It exposes a single HTTP-triggered function: `POST /api/chat`
- The function accepts a JSON body of `{ message: string, conversationId?: string }`
- It returns a JSON body of `{ reply: string, conversationId: string, timestamp: string }`
- `conversationId` is a GUID generated on the first turn and echoed back on subsequent turns
- The default `reply` is a simple echo — **replace the reply logic** with your preferred AI/LLM integration
- No Azure Storage, Cosmos DB, or other cloud service is required out of the box
- Configuration (e.g. AI API keys) should be read from environment variables / application settings
- `local.settings.json` is used for local development only and must not be committed with real secrets
- CORS is set to `*` in `local.settings.json` to allow the Blazor dev server to call the API locally
