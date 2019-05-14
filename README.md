# Tetris

An implementation (from scratch) of Tetris (https://en.wikipedia.org/wiki/Tetris) in C++. Visuals are done with OpenGL
(except for background image).

![screenshot](img/screenshot.png?raw=true)

Gameplay video: <https://youtu.be/yQIu5vZ5QbE>

*Background image: Free stock photo from https://www.pexels.com/search/background/*

*Music and sound effects: From https://freesound.org*

## Features:
* Music
* Sound effects
* Preview next 2 pieces
* Holding slot for one piece (for later use)
* Preview of where the current piece would land

## Keyboard controls:
* Move left: LEFT arrow
* Move right: RIGHT arrow
* Hard drop: Space bar
* Soft drop: DOWN arrow
* Rotate right: X or UP arrow
* Rotate left: Z
* Hold: SHIFT key

## Development requirements

* [GLFW 3.3](https://www.glfw.org)
* [Glad](https://github.com/Dav1dde/glad)
* [FreeImage 3.18.0](http://freeimage.sourceforge.net)
* [irrKlang 1.6.0](https://www.ambiera.com/irrklang/downloads.html)