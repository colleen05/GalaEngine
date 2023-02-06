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
- [ ] InputManager allows for direct key-checking.
- [ ] Entity tags & selecting.
- [ ] Audio listener & emitter system.
- [ ] Better camera system (render to target texture).

### Core features
- [ ] SceneVars.
- [ ] Collision detection.
- [ ] Shader class.
- [ ] Immediate-mode GUI (IMGUI).
- [ ] Loading scenes from resource files.

### Utilities
- [ ] 9-slicing (Surfaces).
- [ ] Particle system.
- [ ] GUILayer.
- [ ] CompositeLayer (layers beneath will render to this layer. allows fragment shading).

### Tasks
- [ ] Document changes.
- [ ] Add appropriate demos.


## Version 0.4.0
### Core features
- [ ] DebugInfo class.
- [ ] Timeline class.
- [ ] Path class.
- [ ] Networking.

### Tasks
- [ ] Document changes.
- [ ] Complete manual.
- [ ] Add appropriate demos.


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
