#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  head_x = fmod(head_x + grid_width, grid_width); // Wrap the Snake around to the beginning if going off of the screen.
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {

  body.push_back(prev_head_cell);   // Add previous head location to vector

  if (!growing) 
  {
    body.erase(body.begin()); // Remove the tail from the vector.
  } 
  else 
  {
    growing = false;
    size++;
  }

  for (auto const &item : body) // Check if the snake has died
  {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      if(!godmode){alive = false;} // Snake can only die if not in godmode
    }
  }
}

void Snake::GrowBody() { if(!godmode){growing = true;} }

bool Snake::SnakeCell(int x, int y) // Check if cell is occupied by snake.
{  
  if (godmode)
  {
    return false; // Make sure that snake cannot destroy itself when in godmode
  }
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}