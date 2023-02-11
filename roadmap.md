# GalaEngine Roadmap
## Version 0.1.0
### Core features & base classes
- [x] Game class.
- [x] Entity.
- [x] Scene.
- [x] Layer & Layers: Background, Entity, Tiles (Per-layer only).
- [x] Surfaces & drawing.
- [x] Tilesets & Tilemaps (Graphically).
- [x] Colours.
- [x] Sprites.
- [x] Window managing (Window creation & surface).
- [x] Simple camera.
			
## Version 0.2.0
### Core features
- [x] Asset managing (Load files by path w/ resource path, auto unloading).
- [x] Tilesets should have a flags field (example: for collision).
- [x] Bindable input tags & multiple inputs -> single action (Ex: E Key and LMB both being 'use').
- [x] AudioController (Sound loading, playing, and status-getting).
- [x] Window class supports fully implements raylib functionality.

### Tasks
- [x] Refactor: Properly use const, and references.
- [x] Optimise: Container optimisations.
- [ ] Add appropriate demos.


## Version 0.3.0
### Updates
- [ ] Add Entity context members: `sceneWidth`, `sceneHeight`, `sceneEntities`, and `sceneLayers`.
- [ ] InputManager allows for direct checking:
  - [ ] `bool InputManager::IsKeyPressed(...)`: Has key just been pressed?
  - [ ] `bool InputManager::IsKeyDown(...)`: Is key currently down?
  - [ ] `bool InputManager::IsKeyReleased(...)`: Has key just been released?
  - [ ] `bool InputManager::IsMousePressed(...)`: Has mouse button just been pressed?
  - [ ] `bool InputManager::IsMouseDown(...)`: Is mouse button currently down?
  - [ ] `bool InputManager::IsMouseReleased(...)`: Is mouse button currently down?
  - [ ] `Vector2 InputManager::GetMouseWheel()`: Get mouse scroll vector.
  - [ ] `bool InputManager::IsGamepadPressed(...)`: Has gamepad button just been pressed?
  - [ ] `bool InputManager::IsGamepadDown(...)`: Is gamepad button currently down?
  - [ ] `bool InputManager::IsGamepadReleased(...)`: Has gamepad button just been released?
- [ ] Better camera system (render to target texture).
- [ ] AssetManager to have a `defaultTextureFilter` member.

### Core features
- [ ] Shader class:
  - [ ] ``Shader::Compile(...)``: Load from vertex and fragment strings.
  - [ ] ``Shader::GetAttributes()``: Return all attributes.
  - [ ] ``Shader::Set<T>(...)``: Set attribute.
  - [ ] ``Shader::Get<T>(...)``: Get attribute.
  - [ ] ``Surface::UseShader(...)``: Set shader of surface.
- [ ] Immediate-mode GUI (IMGUI).
- [ ] Audio listener & emitter system:
- [ ] Loading scenes from resource files.

### Utilities
- [ ] 9-slicing (Surfaces).
- [ ] SurfaceLayer (layer with just a surface).
- [ ] CompositeLayer (layers beneath will render to this layer. allows fragment shading).


### GalaMake
- [ ] Build scenes.
- [ ] Add "filter" option to textures.

### Tasks
- [ ] Document changes.
- [ ] Add appropriate demos.


## Version 0.4.0
### Core features
- [ ] Debug::Logger class.
- [ ] Timeline class.
- [ ] Path class.
- [ ] Networking.
- [ ] Particle system.

### Utilities
- [ ] OS interaction:
  - `GetPlatformString()`: Returns name of OS.
  - `GetPlatformType()`: Returns platform type enum.
  - `GetPlatformLanguage()`: Returns the language of the OS.
  - `ShowMessageBox(...)`: Show a message box.
  - `ShowOptionBox(...)`: Show a message box with two options, return the selected option.
  - `ShowQuestionBox(...)`: Show a message box with input field, return the entered text.
  - `FileSelector(...)`: Show a file selection window, return path of selected file.
  - `PushNotification(...)`: Send a notification to the user.
- [ ] Collision detection.

### Tasks
- [ ] Document changes.
- [ ] Complete manual.
- [ ] Add appropriate demos.


## Version 0.5.0
### Core features
- [ ] Scripting:
  - [ ] ``ScriptedGame`` and ``ScriptedEntity`` classes?
  - *To be determined...*


## Version 1.0.0
### Editor
- [ ] Game info editing.
- [ ] Asset creation.
- [ ] Asset browser.
- [ ] Tileset creator.
- [ ] Sprite creator.
- [ ] Entity creator.

#### Scene editing
- [ ] Overview
- [ ] Manage layers
- [ ] Place entities

### Tasks
- [ ] Document editor in manual.
