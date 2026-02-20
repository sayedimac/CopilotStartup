# CopilotStartup — Chatbot Template (Blazor WASM + .NET Functions)

## Purpose

Generic starter template for a chatbot web application:

- **Frontend**: Blazor WebAssembly (SPA) in `src/web` — .NET 10
- **Backend**: Azure Functions isolated worker in `src/api` — .NET 9
- **Hosting**: Azure Static Web Apps (the `/api` route is automatically routed to the Functions app)
- **Tests**: Playwright end-to-end tests in `tests/playwright`

The template ships with a simple echo bot. Replace the reply logic in `src/api/ChatFunction.cs`
with your preferred AI/LLM integration (e.g. Azure OpenAI, OpenAI, Semantic Kernel, etc.).

---

## Project layout

```
CopilotStartup/
├── src/
│   ├── web/          ← Blazor WASM chatbot frontend (.NET 10)
│   │   ├── Models/
│   │   ├── Pages/
│   │   └── Services/
│   └── api/          ← Azure Functions chat backend (.NET 9 isolated)
│       └── Models/
├── tests/
│   └── playwright/   ← Playwright API + UI tests (TypeScript)
├── .github/
│   ├── copilot-instructions.md
│   ├── instructions/
│   │   ├── web.instructions.md
│   │   └── api.instructions.md
│   ├── prompts/
│   │   └── add-llm-integration.prompt.md
│   └── workflows/
│       └── azure-static-web-apps.yml
├── CopilotStartup.sln
└── README.md
```

---

## Prerequisites

- .NET 10 SDK
- .NET 9 SDK (for the Functions project)
- Azure Functions Core Tools v4+
- Node.js 20+ (for Playwright tests)
- Git

---

## Local development

### Run the API

```bash
cd src/api
func start
# Functions will be available at http://localhost:7071/api/chat
```

### Run the web app

```bash
cd src/web
dotnet run
# App will be available at http://localhost:5000
```

Configure the web app to call the local API by setting `ApiBaseUrl` in
`wwwroot/appsettings.Development.json`:

```json
{
  "ApiBaseUrl": "http://localhost:7071"
}
```

### Run Playwright tests

```bash
# Install browsers once
cd tests/playwright
npx playwright install chromium

# Run all tests (requires both API and web running locally)
npm test

# Run only API tests
API_BASE_URL=http://localhost:7071 npx playwright test --grep "Chat API"
```

---

## GitHub Copilot features used

| Feature | Location |
|---|---|
| Repository-level instructions | `.github/copilot-instructions.md` |
| Folder-scoped instructions | `.github/instructions/*.instructions.md` |
| Reusable prompt file | `.github/prompts/add-llm-integration.prompt.md` |
| CI/CD workflow | `.github/workflows/azure-static-web-apps.yml` |

---

## GitHub Actions deployment

The workflow in `.github/workflows/azure-static-web-apps.yml` builds and deploys
to Azure Static Web Apps on every push to `main`.

**Required secret**: `AZURE_STATIC_WEB_APPS_API_TOKEN`

---

## Adding an LLM integration

Use the Copilot prompt in `.github/prompts/add-llm-integration.prompt.md` to guide
GitHub Copilot in replacing the echo reply with a real AI backend.

---

## Notes & best practices

- Keep `local.settings.json` out of source control — it may contain secrets.
- Add API keys and connection strings as environment variables / Azure app settings.
- The Blazor app reads `ApiBaseUrl` at runtime; this is empty in production (same-origin proxy).
- Prefer .NET isolated Functions for .NET 9/10 support.
- Add unit tests for the Functions using `Microsoft.Azure.Functions.Worker.Tests`.
