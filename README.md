# Tic Tac Toe

<img href="logo.png" />

The purpose of this project was to make a game start to finish that was fully implemented using OpenGL and SDL2. I wanted to write everything from scratch rather than using a pre-existing game engine such as Unity or Unreal because I wanted to practice architecting my own systems and wanted to become a well-versed game engine developer. Morever, I wanted to apply fundamental knowledge about shaders, vertex data, user input, and UI. I chose Tic Tac Toe because the rules were simple and I could focus on writing the graphics related code. 

## Description

An in-depth paragraph about your project and overview of use.

As mentioned before, this project makes use of OpenGL and SDL2. The GLM library was used to perform matrix operations and the stb library was utilized to load images. One important goal of this project was to structure the code in a way that made sense for the game. Often times, people do projects and overcomplicated software systems when in reality the goal of the software should be to accomplish a task. An example of this in this project was the fact that I stored the vertex buffers related to the cross and circle pieces in global state. This was a fair tradeoff because although the global state would increase in size, it is known ahead of time that there are very few shapes in the game. Therefore, there is no need for a larger system to handle an arbitrary number of shapes. I was also able to use the FreeType library and add text to the game which then allowed for button and scene transitions. Once again, I made the choice to encapsulate the concept of scenes in a simple enum since there were only 2 scenes, the title scene and the game scene. Overall, I am proud of what I learned from this project and I think this is an excellent stepping stone for future projects, whether it be 2D and 3D.

## Getting Started

### Dependencies

* This program should run on all Windows Operating systems assuming the game is installed using the installer.

### Installing

* How/where to download your program
* Any modifications needed to be made to files/folders

<a href="TicTacToe_Installer.exe" download>Installer for the Game</a>

### Executing program

* How to run the program
* Step-by-step bullets
```
code blocks for commands
```

## License

This project is licensed under the [NAME HERE] License - see the LICENSE.md file for details

## Acknowledgments

Inspiration, code snippets, etc.
* [awesome-readme](https://github.com/matiassingers/awesome-readme)
* [PurpleBooth](https://gist.github.com/PurpleBooth/109311bb0361f32d87a2)
* [dbader](https://github.com/dbader/readme-template)
* [zenorocha](https://gist.github.com/zenorocha/4526327)
* [fvcproductions](https://gist.github.com/fvcproductions/1bfc2d4aecb01a834b46)