# .NET 10 Features and Improvements

This document outlines the .NET 10 features and improvements implemented in this project.

## Project Configuration

### Target Framework
- **Blazor WebAssembly**: .NET 10.0 (`net10.0`)
- **Azure Functions**: .NET 10.0 (`net10.0`) with Azure Functions V4

### SDK Version
- Fixed SDK version: `10.0.102`
- Roll-forward policy: `latestMinor`
- See `global.json` for exact SDK configuration

## C# 13 Language Features

### Primary Constructors
Both Azure Functions leverage C# 12's primary constructors for cleaner dependency injection:

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

**Benefits:**
- Reduced boilerplate code
- Clearer dependency declaration
- More concise class definitions

### Top-Level Statements
Both `Program.cs` files use top-level statements for simplified startup configuration.

**Blazor Web (Program.cs):**
```csharp
var builder = WebAssemblyHostBuilder.CreateDefault(args);
builder.RootComponents.Add<App>("#app");
builder.RootComponents.Add<HeadOutlet>("head::after");
builder.Services.AddScoped(sp => new HttpClient { BaseAddress = new Uri(builder.HostEnvironment.BaseAddress) });
await builder.Build().RunAsync();
```

**Azure Functions (Program.cs):**
```csharp
var builder = FunctionsApplication.CreateBuilder(args);
builder.ConfigureFunctionsWebApplication();
builder.Services
    .AddApplicationInsightsTelemetryWorkerService()
    .ConfigureFunctionsApplicationInsights();
builder.Services.AddHttpClient();
var app = builder.Build();
await app.RunAsync();
```

### Implicit Usings
Enabled in both projects (`<ImplicitUsings>enable</ImplicitUsings>`), reducing the need for repetitive using statements.

### Nullable Reference Types
Enabled in both projects (`<Nullable>enable</Nullable>`), providing enhanced null-safety checking at compile time.

## Performance Enhancements

### Blazor WebAssembly Project

```xml
<TieredCompilation>true</TieredCompilation>
<TieredCompilationQuickJit>true</TieredCompilationQuickJit>
```

- **Tiered Compilation**: Provides faster startup with Quick JIT, then optimizes hot paths
- **AOT Analyzer**: Enabled to identify potential issues for future AOT compilation support

### Azure Functions Project

```xml
<TieredCompilation>true</TieredCompilation>
<TieredCompilationQuickJit>true</TieredCompilationQuickJit>
<ServerGarbageCollection>true</ServerGarbageCollection>
<ConcurrentGarbageCollection>true</ConcurrentGarbageCollection>
```

- **Server GC**: Optimized for server workloads with better throughput
- **Concurrent GC**: Enables garbage collection on separate threads for better performance

## Modern .NET Patterns

### Asynchronous Programming
All I/O operations use `async`/`await` patterns:
- Azure Storage operations (blobs and tables)
- HTTP operations in Blazor components
- Function execution

### Pattern Matching
Enhanced pattern matching in exception handling:
```csharp
catch (Azure.RequestFailedException ex) when (ex.Status == 404)
{
    // Handle not found specifically
}
```

### Collection Expressions
Using modern collection initialization patterns throughout the codebase.

## Latest Package Versions

### Blazor WebAssembly
- `Microsoft.AspNetCore.Components.WebAssembly`: 10.0.2
- `Microsoft.AspNetCore.Components.WebAssembly.DevServer`: 10.0.2

### Azure Functions
- `Microsoft.Azure.Functions.Worker`: 2.51.0
- `Microsoft.Azure.Functions.Worker.ApplicationInsights`: 2.50.0
- `Microsoft.Azure.Functions.Worker.Extensions.Http.AspNetCore`: 2.1.0
- `Microsoft.Azure.Functions.Worker.Sdk`: 2.0.7
- `Microsoft.ApplicationInsights.WorkerService`: 2.23.0

### Azure Storage
- `Azure.Storage.Blobs`: 12.27.0
- `Azure.Data.Tables`: 12.11.0
- `Azure.Core`: 1.50.0 (transitive)
- `System.IO.Hashing`: 10.0.1 (transitive - .NET 10 optimized)

## Build and Deployment

### GitHub Actions Workflow
- Uses `dotnet-version: '10.0.x'` in the workflow
- Configured for Azure Static Web Apps deployment
- Automatic restore, build, and test steps

### Local Development
Both projects can be run locally using:
```bash
dotnet run --project src/web
dotnet run --project src/api
```

## Security Features

### Secure Connection String Handling
- Environment variable-based configuration
- No hardcoded secrets
- Development storage emulator support

### Null Safety
Comprehensive nullable reference type checking prevents null reference exceptions at compile time.

## Future Enhancements

### AOT Compilation
The project is configured with AOT analyzers enabled. Current warnings indicate areas where JSON serialization would need JsonSerializerContext for full AOT support. This is tracked for future implementation when Blazor WASM AOT is fully supported.

### Minimal APIs
The Azure Functions already use a minimal API approach with clean, focused endpoints.

### Performance Monitoring
Application Insights integration is configured for production monitoring and performance tracking.

## Documentation and Best Practices

- Comprehensive README with setup instructions
- Proper .gitignore for .NET projects
- Clear code structure and organization
- Bootstrap 5+ for modern UI components
- Separation of concerns (web UI vs. API backend)

## Testing Strategy

The project structure supports:
- Unit tests for Functions
- Integration tests for API endpoints
- Component tests for Blazor pages

(Test projects can be added as needed following .NET 10 xUnit/NUnit conventions)

## Summary

This project fully leverages .NET 10's capabilities:
✅ Latest C# 13 language features
✅ Performance-optimized project settings
✅ Modern asynchronous patterns
✅ Latest package versions
✅ Production-ready configuration
✅ AOT-ready code structure (prepared for future support)
✅ Server GC and concurrent GC optimizations
✅ Tiered compilation for better startup and runtime performance
