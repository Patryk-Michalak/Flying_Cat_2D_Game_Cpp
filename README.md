# Flying_Cat_2D_Game_Cpp

Educational project of simple 2D game inspired by Flappy Bird but with different control of motion

Game will be made in C++ using SFML library in Eclipse IDE.

Basic functionalities, which I will try to implement:
- Main menu of the game with options: Play, Settings, Scoreboard, Exit.
- The player should choose the type of control (keyboard, mouse, joystick).
- There will be a scoreboard with some highscores, taken from a text file.
- The main goal of the game is to avoid the obstacles generated similar to Flappy Bird project.
- There will be additional objects, which modifies the score counter, change movement speed or end the game.
- The game will allow you to pause.
- Objects in game will have their own graphics.

Additional plans:
- Choose in settings the language of the game (English, Polish).

This information included in this file may change.

# 06.11.2021

First version of flying cat. As of today implemented:
- Simple image intro.
- Main menu with play and exit options.
- Main menu is controlled only by mouse.
- In gameplay implemented only control object (cat) and obstacles (pipes).
- Cat is controlled only by keyboard (WSAD).
- There is collision detection (cat hitting the pipe results as game over).
- After hitting the obstacle, game immediately show main menu.

There are exist some bugs like no speed reset when starting a new game.
