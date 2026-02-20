---
applyTo: "src/web"
---

- This is a .NET 10 Blazor WebAssembly standalone app
- It presents a chatbot interface where users type messages that are sent to the Azure Functions backend
- The `ChatService` in `Services/ChatService.cs` calls `POST /api/chat` with a `ChatRequest` payload
- Messages and bot replies are stored in a list of `ChatMessage` objects rendered in `Pages/Home.razor`
- Conversation identity is maintained across turns via a `conversationId` returned by the API
- The send button and Enter key both trigger message dispatch
- A typing indicator is shown while awaiting a response
- Error messages from the API are displayed inline below the chat window
- All HTTP calls use the scoped `HttpClient` whose `BaseAddress` is the app's origin
  (in Azure Static Web Apps the `/api` route is automatically proxied to the Functions backend)
- Keep UI components in `Pages/`, shared models in `Models/`, and HTTP services in `Services/`
