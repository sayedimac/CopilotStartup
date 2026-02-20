# CopilotStartup — Chatbot Template

A production-ready starter template for a chatbot web application built with:

- **Frontend**: [Blazor WebAssembly](https://learn.microsoft.com/aspnet/core/blazor/) (.NET 10)
- **Backend**: [Azure Functions](https://learn.microsoft.com/azure/azure-functions/) isolated worker (.NET 9)
- **Hosting**: [Azure Static Web Apps](https://learn.microsoft.com/azure/static-web-apps/)
- **Tests**: [Playwright](https://playwright.dev/) end-to-end tests (TypeScript)

The template ships with a simple echo bot. **Replace the reply logic** in
`src/api/ChatFunction.cs` with your preferred AI/LLM integration.

## Quick start

### Prerequisites

- [.NET 10 SDK](https://dotnet.microsoft.com/download/dotnet/10.0)
- [.NET 9 SDK](https://dotnet.microsoft.com/download/dotnet/9.0) (for Functions)
- [Azure Functions Core Tools v4](https://learn.microsoft.com/azure/azure-functions/functions-run-local)
- [Node.js 20+](https://nodejs.org/) (for Playwright tests)

### Run locally

**1. Start the API**

```bash
cd src/api
func start
# → http://localhost:7071/api/chat
```

**2. Start the web app** (in a new terminal)

```bash
cd src/web
dotnet run
# → http://localhost:5000
```

**3. Run Playwright tests** (in a new terminal, with both API and web running)

```bash
cd tests/playwright
npm install
npx playwright install chromium
npm test
```

## Project structure

```
src/
  web/          ← Blazor WASM chatbot (.NET 10)
  api/          ← Azure Functions chat endpoint (.NET 9)
tests/
  playwright/   ← End-to-end tests
.github/
  copilot-instructions.md     ← Repo-level Copilot context
  instructions/               ← Folder-scoped Copilot instructions
  prompts/                    ← Reusable Copilot prompt files
  workflows/                  ← GitHub Actions CI/CD
```

## Adding an LLM

Open the prompt file in Copilot Chat to get guided integration:

```
.github/prompts/add-llm-integration.prompt.md
```

This prompt supports Azure OpenAI, OpenAI, and Semantic Kernel.

## Deploy to Azure Static Web Apps

1. Create an Azure Static Web App in the Azure Portal.
2. Copy the deployment token and add it as a repository secret: `AZURE_STATIC_WEB_APPS_API_TOKEN`.
3. Push to `main` — the GitHub Actions workflow handles build and deploy automatically.

## GitHub Copilot features

| Feature | File |
|---|---|
| Repository instructions | `.github/copilot-instructions.md` |
| `src/web` context | `.github/instructions/web.instructions.md` |
| `src/api` context | `.github/instructions/api.instructions.md` |
| LLM integration prompt | `.github/prompts/add-llm-integration.prompt.md` |

## Contributing

This is a template repository. Fork it and customise as needed.
