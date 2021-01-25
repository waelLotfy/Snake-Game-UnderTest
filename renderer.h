#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include "gameObject.h"
#include <memory>

/*New Feature Added : A thread for handling the rendering*/
class Renderer : public GameObject
{
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(/*std::shared_ptr<Snake> const snake, SDL_Point const &food*/);
  void UpdateWindowTitle(int score, int fps);
  
  // typical behaviour methods
  void runThread() override; /*New Feature Added : A thread for handling the rendering*/
  
  void setFood(SDL_Point /*const &*/f) ;/*New Feature Added : A thread for handling the rendering*/
  void setSnake(std::shared_ptr<Snake>     s) ;/*New Feature Added : A thread for handling the rendering*/

  void setRunning(bool r);
  bool getRunning();
 private:
  //SDL_Window *sdl_window;
  std::shared_ptr<SDL_Window> sdl_window;     /*Memory Mngt : feature no .2*/
  //SDL_Renderer *sdl_renderer;
  std::shared_ptr<SDL_Renderer> sdl_renderer; /*Memory Mngt : feature no .2*/

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
  
  std::shared_ptr<Snake>     snake;   /*New Feature Added : A thread for handling the rendering*/
  SDL_Point  food; /*New Feature Added : A thread for handling the rendering*/
  bool running{true} ;
  std::mutex _mtxRunningRender;  /*To be used for locking the running flag*/
  
};

#endif