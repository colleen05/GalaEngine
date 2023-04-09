# GalaEngine Roadmap
**NOTE:** See the most recent version's progress [here](#version-030).

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
- [x] Improved Window functionality.

### Tasks
- [x] Refactor: Properly use const, and references.
- [x] Optimise: Container optimisations.
- [x] Add appropriate demos.


## Version 0.3.0
### Updates
- [x] Add Entity context members: `sceneWidth`, `sceneHeight`, `sceneEntities`, and `sceneLayers`.
- [x] InputManager allows for direct checking:
  - [x] Direct keyboard key checking.
  - [x] Direct gamepad buttons and axis checking.
  - [x] Get mouse wheel deltas.
- [ ] `Colour.hpp` to contain BlendModes.
- [ ] Layers and entities to have blend modes.
- [x] Fully implement Window class functionality.
  - [x] Set fullscreen explicitly (`Window::SetFullscreen(bool fullscreen)`).
  - [x] Get and set the following properties: resizable, undecorated, hidden, and topmost.
  - [x] Support multiple scaling options: `Contain`, `Stretch`, `IntegerScale`.
  - [x] Support window surface filtering (nearest neighbour or bilinear).
  - [x] Set icon and minimum size.
  - [x] ``Window::Centre()``: Centre window on screen.
  - [x] ``Window::GetMousePosition()``: Get proper mouse position (in surface-space).
- [x] Game class to support F11 for fullscreen toggle.
- [x] Textures and sprites have texture filters.

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

### Utilities
- [x] Math utility functions. 
- [x] 9-slicing (Surfaces).
- [ ] CompositeLayer (layers beneath will render to this layer. allows fragment shading).

### Gres
- [x] Load 9-slices.
- [x] Load fonts.
- [x] Add "filter" option to textures and sprites.

### Tasks
- [ ] Document changes.
- [ ] Add appropriate demos.


## Version 0.4.0
### Updates
- [ ] Window background.

### Core features
- [ ] Debug::Logger class.
- [ ] Timeline class.
- [ ] Path class.
- [ ] Particle system.
- [ ] Audio listener & emitter system.
- [ ] Scene loading from files.

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
- [ ] Rewrite GalaMake.
- [ ] Document changes.
- [ ] Write in manual:
  - [ ] Downloading & Prerequisites
  - [ ] Engine Overview
  - [ ] Compiling a Project
  - [ ] Using GalaMake
  - [ ] Using Layers
  - [ ] Creating Entities
- [ ] Add appropriate demos.

### Gres
- [ ] Implement scene loading from .gres.


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
