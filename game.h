#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include <memory>
#include <future>
#include "gameObject.h"


class Game : public GameObject
{
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller /*const*/ &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

  // typical behaviour methods
  void runThread() override; /*New Feature Added : A thread for handling the update.*/

 private:
  //Snake snake;
  std::shared_ptr<Snake> snake;
  SDL_Point food;
  //std::size_t game_target_frame_duration;/*New Feature Added : A thread for handling the update*/
  //bool running;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void PlaceInitialFood();
  void Update();
  void UpdateGame();
};

#endif