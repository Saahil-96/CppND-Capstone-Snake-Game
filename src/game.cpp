#include "game.h"
#include <iostream>
#include "SDL.h"
#include <chrono>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    controller.HandleInput(running, snake);     // Input, Update, Render - the main game loop.
    Update();
    renderer.Render(snake, food, apple_x, apple_y, poison_x, poison_y, apple, poison);

    frame_end = SDL_GetTicks();

    frame_count++; // Keep track of how long each loop through the input/update/render cycle takes.
    frame_duration = frame_end - frame_start;

    if (frame_end - title_timestamp >= 1000) // After every second, update the window title.
    {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    
    if((x>31)||(y>31)) // Make sure the food is not placed out of bounds
    {
      x = random_w(engine);
      y = random_h(engine);
    }
    if (!snake.SnakeCell(x, y)) // Check that the location is not occupied by a snake item before placing food.
    {
      food.loc.x = x;
      food.loc.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;
  
  snake.Update();
  
  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  auto end=std::chrono::steady_clock::now();

  if (apple_x==new_x && apple_y==new_y && apple==true) // Check if an apple is placed on the map and location of apple is reached 
  {
    snake.godmode=true; // Switch on godmode for the snake
    apple=false; 
    score++;
    apple_x=-1; // Avoid garbage value locations rendering apple on the map by mistake
    apple_y=-1;
    start=std::chrono::steady_clock::now();
  }

  else if(poison_x==new_x && poison_y==new_y && poison==true) // Check if poison is placed on the map and location of poison is reached 
  {
    if (snake.godmode) // In case the snake was in godmode from before, make it regular
        {
          snake.godmode=false; // Switch off god mode
        }
        else
        {
          snake.poisoned=true; // Switch on poisoned mode
          score=score/2;
          snake.speed*=2;
          start=std::chrono::steady_clock::now();
        }
    score++;
    poison=false;
    poison_x=-1; // Avoid garbage value locations rendering poison on the map by mistake
    poison_y=-1;
  }

  if (food.loc.x == new_x && food.loc.y == new_y) // Check if there's food over here
  {  
    apple=false; // In case food is eaten despite any special food, remove special foods automatically from map
    poison=false; 
    score++;
    if (((score%5)==0)&&(score!=0))
    {
      food.att=food.apple;
      PlaceFood(); // Generate and place apple when score is a multiple of 5 
      apple_x=food.loc.x;
      apple_y=food.loc.y;
      apple=true;
    }
    else if (((score%7)==0)&&(score!=0))
    {
      food.att=food.poison;
      PlaceFood(); // Generate and place poison when score is a multiple of 7 
      poison_x=food.loc.x;
      poison_y=food.loc.y;
      poison=true;
    }

    food.att=food.regular;
    PlaceFood();
    // std::cout<<"Score is "<<score<<" and snake size is "<< snake.size << " and snake modes are "<< snake.godmode<<snake.poisoned<<std::endl;
    
    snake.GrowBody(); // Grow snake and increase speed.
    if(!snake.godmode){snake.speed += 0.02;} // Do not increase speed when in godmode
  }

  if (snake.godmode||snake.poisoned)
  {
    if(std::chrono::duration_cast<std::chrono::seconds>(end-start).count()>=4) // Make sure that godmode or poisoned time lasts only 4 seconds
    {
      if(snake.godmode)
      {
       snake.godmode=false;
      }
      else
      {
       snake.speed/=2;
       snake.poisoned=false;
      }
    }
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }