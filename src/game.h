#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "food.h"
#include <chrono>

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  int poison_x=-1;
  int poison_y=-1;
  int apple_x=-1;
  int apple_y=-1;
  
  bool apple{false}; // Bool value for checking if apple is placed on map
  bool poison{false}; // Bool value for checking if apple is placed on map

  // auto start = std::chrono::steady_clock::now();
  std::chrono::time_point<std::chrono::steady_clock> start;

 private:
  Snake snake;
  Food food;
  
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  
  void Update();
};

#endif