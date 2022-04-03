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

# 03.04.2022

I neglected the project a bit due to devoting time to other development aspects.
After 5 months I decided to complete project with basic assumptions. 
This project is not the best example of making some educational project, but for me is a way to improve my knowledge about C++ language (pointers, classes, functions) and develop my algorithmical skills and way of thinking outside the box. 
I tried to write this code with some basics principles compatible with clean coding rules. 
The fact that I want to finish this project almost immediately, there are some lines of codes which could be written in better way.

The list of implemented functionalities in this version:
- There is added settings and scoreboard menu.
- There is added music in main menu (all are free stock music).
- In settings player can choose music volume and main controller (keyboard, joystick, mouse).
- In scoreboard player can see 3 best scores from text file.
- In main game in corner is presenting score counter.
- By using "Esc" key in gameplay mode, it is possible to pause game.
- From pause state player can choose continuation of game or exit whole application.

The list of lacks which be implemented in last update:
- Possibility to save new best score in text file.
- Due to lack of time and willingness to deal with other projects, I am not planning to implement a additional objects like score modificator or movement speeds modificator cause it would have similar mechanic to collision with obstacles (pipes) or making different language version.

Some list of insights about actual code:
- There are some bugs in code like back from settings option and highlight incorrect button until you move the mouse. All mouse moves and actions are treated like events and game notice event when user press some key, or move mouse. Only key control in game should be treated like event, mouse control should not be implemented by sf::Events class from SFML library. Lack of time cause, that I will not try to repair this functionality.
- There are some useless lines of code (commented sequences or non-used lines which were created for some tests).

After looking at some other projects made using SFML library, my projects looks like really amateur and ugly 2D project without animation, which should not be presented in repository, but it is my first project with simple game theme and I wanted to develop my skills in programming. In future I will try to program PLCs or embedded systems and focusing on develop my knowledge about process control algorithms.
