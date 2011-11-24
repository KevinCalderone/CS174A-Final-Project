Final Project Description
CS 174A

Arash Sepasi
Kevin Calderone
Ryan Harris

======================================
Project Description
======================================

	We created a survival shooter game that we specified in our initial project proposal.  The player moves around the environment avoiding and shooting monsters that are constantly spawning and chasing the player.  Crates also spawn randomly on that map that will upgrade your weapon for a short period of time.

	The external libraries that we used for this project were glut, glext and fmod.  The dll files for these libraries are included in the executable directory.  The project files are setup for Visual Studio 2010 Express.

======================================
Controls
======================================

asdw - Move the character
j - Turn the character counter-clockwise
l - Turn the character clockwise
space - Toggle firing
p - Pause the game
m - Mute sounds

======================================
Team Overview
======================================

Kevin
	Graphics Engine
Ash
	Collision Detection
	Game Logic
Ryan
	HUD Display
	Game Logic

======================================
Advanced Topic: Collision Detection
======================================

	For the advanced topic, we implemented collision detection for many parts of our game.  There is detection between the monsters to make sure that they don’t clump up as they are chasing the player.  There monsters also collide with the trees and path around them correctly.  There is also the collision between the bullets and the monsters, as well as the monsters with the player. The collision detection was implemented with oriented bounding boxes, as well as circles.  All of the collision was dealt with in 2d since our game takes place on a flat surface.

======================================
Notable Graphics Features and Other Advanced Topics
======================================

Frame Buffer Object Rendering
Bloom Lighting
Keyframe Animation
Normal Mapping
Environment Mapping
Faked Depth of Field Blur
Phong Lighting
Point Lights
Directional Light
Day/Night cycle for directional light
Diffuse Textures
Alpha Testing/Blending
Color Correction
OBJ Model Parser
BMP Texture Loader

======================================
Challenges/Comments
======================================

	This project was a lot more fun than the other assignments since we were allowed to choose what we were working on.  

The project repository is available online here:
https://github.com/Bovinedragon/CS174A-Final-Project