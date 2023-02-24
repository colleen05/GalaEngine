# GalaEngine Roadmap
See the most recent version's progress [here](#version-030).

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
- [x] Add appropriate demos.


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
  - [ ] etc...
- [ ] AssetManager to have a `defaultTextureFilter` member.
- [ ] Layers and entities to have blend modes.
- [ ] Fully implement Window class functionality.

### Core features
- [ ] Shader class:
  - [ ] ``Shader::Compile(...)``: Load from vertex and fragment strings.
  - [ ] ``Shader::GetAttributes()``: Return all attributes.
  - [ ] ``Shader::Set<T>(...)``: Set attribute.
  - [ ] ``Shader::Get<T>(...)``: Get attribute.
  - [ ] ``Surface::UseShader(...)``: Set shader of surface.
- [ ] Multi-camera support:
  - [ ] `Camera` class to have a render target texture.
  - [ ] Scene to have a list of cameras and their on-screen placements.
- [ ] Fonts properly supported.
- [ ] Immediate-mode GUI (IMGUI).
- [ ] Loading scenes from resource files.

### Utilities
- [ ] 9-slicing (Surfaces).
- [ ] CompositeLayer (layers beneath will render to this layer. allows fragment shading).

### GalaMake
- [ ] Build scenes.
- [ ] Build fonts.
- [ ] Add "filter" option to textures.

### Tasks
- [ ] Document changes.
- [ ] Add appropriate demos.


## Version 0.4.0
### Core features
- [ ] Debug::Logger class.
- [ ] Timeline class.
- [ ] Path class.
- [ ] Particle system.
- [ ] Audio listener & emitter system.

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
  
### Tasks
- [ ] Document changes.
- [ ] Write in manual:
  - [ ] Downloading & Prerequisites
  - [ ] Engine Overview
  - [ ] Compiling a Project
  - [ ] Using GalaMake
  - [ ] Using Layers
  - [ ] Creating Entities
- [ ] Add appropriate demos.


## Version 0.5.0
### Core features
- [ ] Physics (via Box2D?)
- [ ] Scripting:
  - [ ] ``ScriptedGame`` and ``ScriptedEntity`` classes?
  - *To be determined...*

### Tasks
- [ ] Document changes.
- [ ] Write in manual:
  - [ ] Cameras
  - [ ] Surfaces & Drawing
  - [ ] Creating GUIs
  - [ ] Logging & Debugging
  - [ ] Timelines & Paths
  - [ ] Input System & Binding
  - [ ] Sound & Audio
  - [ ] Particles
  - [ ] Physics
- [ ] Add scripting section to manual.
- [ ] Add appropriate demos.
- [ ] Switch to a proper buildsystem.


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
