#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {

  if (SDL_Init(SDL_INIT_VIDEO) < 0) { // Initialize SDL
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED); // Create renderer
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const snake, Food const &food, int apple_x, int apple_y, int poison_x, int poison_y, bool apple, bool poison) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);  // Clear screen
  SDL_RenderClear(sdl_renderer);

  if(apple)   // If apple should exist somewhere on map
  {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x1E, 0xFF, 0xFF); //Render apple
    block.x = apple_x * block.w;
    block.y = apple_y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  } 

  else if(poison) // If poison should exist somewhere on map
  {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);//Render poison
    block.x = poison_x * block.w;
    block.y = poison_y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }
  
  if(food.att==food.regular) 
  {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF); //Render regular food
    block.x = food.loc.x * block.w;
    block.y = food.loc.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF); //Render snake's body
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  if(snake.godmode)
  {SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x1E, 0xFF, 0xFF);} //Render godmode body
  else if(snake.poisoned)
  {SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);} //Render poisoned body
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
   }

  block.x = static_cast<int>(snake.head_x) * block.w; // Render snake's head
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  SDL_RenderPresent(sdl_renderer); // Update Screen
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
