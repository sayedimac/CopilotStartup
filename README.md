# CopilotStartup - Blazor WASM + Azure Functions (.NET 10)

A modern, minimal starter template for building cloud-native applications with Blazor WebAssembly and Azure Functions, leveraging the latest .NET 10 features and best practices.

## 🚀 Features

- **Blazor WebAssembly** with .NET 10 - Modern, component-based UI framework
- **Azure Functions** (.NET 10 Isolated) - Serverless backend APIs
- **Azure Storage Integration** - Built-in blob and table storage support
- **Modern C# 13** - Latest language features and performance improvements
- **Minimal APIs** - Clean, efficient function implementations
- **Primary Constructors** - Simplified dependency injection in functions
- **Top-level Statements** - Concise program startup

## 📋 Prerequisites

- [.NET 10 SDK](https://dotnet.microsoft.com/download/dotnet/10.0)
- [Azure Functions Core Tools v4+](https://docs.microsoft.com/azure/azure-functions/functions-run-local)
- [Visual Studio 2022](https://visualstudio.microsoft.com/) or [VS Code](https://code.visualstudio.com/)
- [Azure Storage Emulator](https://docs.microsoft.com/azure/storage/common/storage-use-emulator) or Azure Storage Account

## 🏗️ Project Structure

```
CopilotStartup/
├── src/
│   ├── web/              # Blazor WebAssembly client application
│   │   ├── Pages/        # Razor pages/components
│   │   ├── Layout/       # Application layout components
│   │   └── wwwroot/      # Static assets
│   │
│   └── api/              # Azure Functions backend
│       ├── Functions/    # HTTP trigger functions
│       │   ├── GetBlobs.cs       # List blobs from storage
│       │   └── GetTableData.cs   # Query table storage
│       ├── Program.cs    # Function app startup
│       └── host.json     # Function host configuration
│
└── CopilotStartup.sln    # Solution file

## 🛠️ Getting Started

### Clone and Build

```bash
git clone <repository-url>
cd CopilotStartup
dotnet restore
dotnet build
```

### Run Locally

#### Option 1: Run Both Projects Separately

**Terminal 1 - Blazor Web App:**
```bash
cd src/web
dotnet run
```

**Terminal 2 - Azure Functions:**
```bash
cd src/api
func start
# Or use: dotnet run
```

#### Option 2: Use Visual Studio
Open `CopilotStartup.sln` and set both projects as startup projects (right-click solution → Properties → Multiple startup projects).

### Configure Azure Storage

1. For local development, use Azure Storage Emulator or Azurite:
   ```bash
   # Install Azurite
   npm install -g azurite
   
   # Start Azurite
   azurite --silent --location c:\azurite --debug c:\azurite\debug.log
   ```

2. Update `src/api/local.settings.json`:
   ```json
   {
     "IsEncrypted": false,
     "Values": {
       "AzureWebJobsStorage": "UseDevelopmentStorage=true",
       "FUNCTIONS_WORKER_RUNTIME": "dotnet-isolated"
     }
   }
   ```

3. For Azure deployment, set the connection string:
   ```json
   {
     "Values": {
       "AzureWebJobsStorage": "DefaultEndpointsProtocol=https;AccountName=<account>;AccountKey=<key>;EndpointSuffix=core.windows.net"
     }
   }
   ```

## 📡 API Endpoints

### Get Blobs
```
GET /api/blobs/{containerName}
```
Lists all blobs in the specified container.

**Example Response:**
```json
{
  "containerName": "test-container",
  "blobCount": 5,
  "blobs": ["file1.txt", "file2.jpg", "file3.pdf"]
}
```

### Get Table Data
```
GET /api/table/{tableName}/{partitionKey}/{rowKey}
```
Retrieves a specific entity from Azure Table Storage.

**Example Response:**
```json
{
  "tableName": "TestTable",
  "partitionKey": "partition1",
  "rowKey": "row1",
  "timestamp": "2026-01-23T10:00:00Z",
  "properties": {
    "Name": "John Doe",
    "Email": "john@example.com"
  }
}
```

## 🎯 Key .NET 10 Features Used

### 1. Primary Constructors
Functions use C# 12's primary constructors for cleaner dependency injection:
```csharp
public class GetBlobs(ILogger<GetBlobs> logger)
{
    [Function("GetBlobs")]
    public async Task<HttpResponseData> Run(...)
    {
        logger.LogInformation("...");
    }
}
```

### 2. Top-level Statements
Simplified program startup in both Blazor and Functions projects.

### 3. Implicit Usings
Reduced boilerplate with globally imported namespaces.

### 4. Nullable Reference Types
Enhanced null safety throughout the codebase.

### 5. Modern Async/Await Patterns
Efficient asynchronous operations with latest best practices.

## 🚢 Deployment

### Azure Static Web Apps

1. Create an Azure Static Web App in the Azure Portal
2. Configure GitHub Actions workflow (see `.github/workflows/azure-static-web-apps.yml`)
3. Set the deployment token in GitHub repository secrets as `AZURE_STATIC_WEB_APPS_API_TOKEN`
4. Push to main branch to trigger deployment

### Manual Deployment

**Blazor Web App:**
```bash
cd src/web
dotnet publish -c Release -o ./publish
# Deploy contents of ./publish/wwwroot to your hosting provider
```

**Azure Functions:**
```bash
cd src/api
func azure functionapp publish <function-app-name>
```

## 📚 Learn More

- [.NET 10 What's New](https://docs.microsoft.com/dotnet/core/whats-new/dotnet-10)
- [Blazor WebAssembly](https://docs.microsoft.com/aspnet/core/blazor)
- [Azure Functions](https://docs.microsoft.com/azure/azure-functions)
- [Azure Storage](https://docs.microsoft.com/azure/storage)
- [C# 13 Language Features](https://docs.microsoft.com/dotnet/csharp/whats-new/csharp-13)

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## 📄 License

This project is licensed under the MIT License.

## 💡 Tips

- Use Azure Storage Explorer for easier management of storage resources
- Enable Application Insights for production monitoring
- Consider using Azure Key Vault for sensitive configuration
- Leverage .NET 10's performance improvements for optimal application speed
