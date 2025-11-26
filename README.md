# CopilotTest

A minimal Blazor WebAssembly application with .NET 8 Azure Functions backend.

## Project Structure

```
CopilotTest/
├── src/
│   ├── web/           # Blazor WebAssembly app (frontend)
│   └── api/           # Azure Functions (backend)
├── CopilotTest.sln    # Solution file
└── README.md
```

## Prerequisites

- [.NET 8 SDK](https://dotnet.microsoft.com/download/dotnet/8.0)
- [Azure Functions Core Tools v4+](https://learn.microsoft.com/azure/azure-functions/functions-run-local) (optional, for local function debugging)
- Git
- Visual Studio Code or Visual Studio (optional)

## Getting Started

### Build the Solution

```bash
dotnet build
```

### Run the Blazor Web App

```bash
dotnet run --project src/web
```

The web app will be available at `http://localhost:5000` (or the URL shown in the console).

### Run the Azure Functions (API)

If you have Azure Functions Core Tools installed:

```bash
cd src/api
func start
```

Or run directly with .NET:

```bash
dotnet run --project src/api
```

## Development

### Add New Azure Function

To add a new HTTP trigger function, create a new class in `src/api`:

```csharp
using Microsoft.Azure.Functions.Worker;
using Microsoft.Azure.Functions.Worker.Http;
using Microsoft.Extensions.Logging;

namespace api
{
    public class MyFunction
    {
        private readonly ILogger _logger;

        public MyFunction(ILoggerFactory loggerFactory)
        {
            _logger = loggerFactory.CreateLogger<MyFunction>();
        }

        [Function("MyFunction")]
        public HttpResponseData Run([HttpTrigger(AuthorizationLevel.Anonymous, "get", "post")] HttpRequestData req)
        {
            _logger.LogInformation("C# HTTP trigger function processed a request.");

            var response = req.CreateResponse(System.Net.HttpStatusCode.OK);
            response.Headers.Add("Content-Type", "text/plain; charset=utf-8");
            response.WriteString("Welcome to Azure Functions!");

            return response;
        }
    }
}
```

### Configuration

- **Web app settings**: `src/web/wwwroot/appsettings.json`
- **API local settings**: `src/api/local.settings.json`
- **API host configuration**: `src/api/host.json`

## Deployment

This project is configured for deployment to Azure Static Web Apps. See `.github/workflows/` for CI/CD configuration.

## Learn More

- [Blazor WebAssembly Documentation](https://learn.microsoft.com/aspnet/core/blazor/)
- [Azure Functions Documentation](https://learn.microsoft.com/azure/azure-functions/)
- [Azure Static Web Apps Documentation](https://learn.microsoft.com/azure/static-web-apps/)
