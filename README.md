# CStell Engine SFML

2D game engine written in C++ and SFML.
This is just small project to learn more about Game Development, how Game Engine work under the hood and C++

WARNING this project wasn't made with the focus of compatibity and protability, this is more like exploration and experiment. Just cloning the repository will not make it work out of box, you will need to manually link all libraries.

### Table of content

- [Features](#features)
- [CStell Editor](#cstell-editor)
- [Drag and Drop](#drag-and-drop-entity)
- [Operation at Runtime](#Operation-at-Runtime)
- [Axis Aligned Bounding Box (AABB) Collision](#Axis-Aligned-Bounding-Box-(AABB)-Collision)
- [Saving the Scene](#Saving-the-Scene)
- [External](#external)

### Features

- Written in C++ and SFML
- ECS Architecture
- Own Physics Engine
- Save/Load Support using YAML
- Editor Interface using ImGui
- Content Browser using ImGui FileDialog
- Simple Sprite Sheet Animation Support

### CStell Editor

Dockable menu UI is made with the help of ImGui

https://github.com/VedantS-32/ConstellationEngineSFML/assets/122535961/03add6be-e3e8-4cab-ada3-862b06149ad8

### Drag and Drop Entity

Tracking and Truncating mouse position while entity is selected

https://github.com/VedantS-32/ConstellationEngineSFML/assets/122535961/82adfc9c-7d15-488a-b3bd-9e55a5db82ef

### Operations at Runtime

https://github.com/VedantS-32/ConstellationEngineSFML/assets/122535961/7fa866f1-d637-4f34-9dd0-3f6046063810

Pretty cool right?

- Adding Entity

- Adding Component

- Changing Sprite

### Axis Aligned Bounding Box (AABB) Collision

A simple AABB detection and resolution

https://github.com/VedantS-32/ConstellationEngineSFML/assets/122535961/7681b06c-ccf8-449e-93ce-321e5a615b3c

### Saving the Scene

Serializer/Deserializer using YAML file

{{< embedVideo "CStellSaveLoad" "/CStellEngineSFML/CStell_SaveLoad.mp4">}}

### External

- An excellent resource for learning C++ and introduction to game programming [LinkToPlaylist](https://youtube.com/playlist?list=PL_xRyXins848nDj2v-TJYahzvs-XW9sVV&si=Ob8yquaC4f9_B_Q6)

- Sprite Asset used [SunnyLand](https://ansimuz.itch.io/sunny-land-pixel-game-art) by [Ansimuz](https://itch.io/profile/ansimuz)

Thank You for Reading!
