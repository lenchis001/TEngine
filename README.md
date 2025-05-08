# TEngine

**TEngine** is a fast, easy-to-integrate, and cross-platform game engine.

## Components

### Audio
- Supports 3D audio based on OpenAL.

### Network
- Enables HTTP requests and WebSocket client connections.

### Rendering
- Provides OpenGL-based rendering.

### Plugins
- Modular plugin system for extending functionality.
- Includes built-in plugins for:
  - **Image Loading**: Supports BMP and PNG formats.
  - **Mesh Loading**: Supports OBJ and GLTF formats.

## Supported Platforms
- **Windows**
- **macOS**
- **Linux** (tested on Ubuntu)
- **Android**  
  *(iOS support will be added in the future)*

## Modular Architecture
- **Dynamic Plugin Loading**: Plugins are dynamically loaded at runtime, enabling flexible and extensible functionality.
- **Cross-Platform Compatibility**: Shared libraries are used for plugins, ensuring compatibility across supported platforms.