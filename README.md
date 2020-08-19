# CPPND: Capstone Snake Game Example

The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## Current Features

In this game, the starter code allows the user to use the SDL Library to simulate and play the classic snake game. The snake is allowed to roam outside of the game window only to come in from the opposite end and increases speed whenever it eats some food and dies whenever it touches it's own body. The game also makes sure it keeps a consistent frame rate based on the user PC by constantly checking and readjusting.

## Main Aim

To give new features to the game and allow for use of concurrency as well as smart pointers.

## Keywords

SDL Library, Cmake, C++, Gaming, Simulation

## File descriptions

### Controller.h/.cpp -
Access the controller attributes of SDL

### Main.h/.cpp -
Run the main code

### Renderer.h/cpp -
Render the whole environment for the game at each iteration

### Game.h/cpp -
Runs the game and updates screen using render each iteration and checks if snake has eaten food while regularly checking if snake is alive.

### Snake.h/cpp
Give attributes to the object snake and update it's head, body and make sure the snake does not eat itself
