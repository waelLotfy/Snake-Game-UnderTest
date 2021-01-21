#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::getSnake(std::shared_ptr<Snake> s) /*To get the sanke from the controller*/
{
  snake = s;
}

void Controller::getTargetFrameDuration(std::size_t t) /*To get the target_frame_duration from the controller*/
{
  target_frame_duration = t ;
}
void Controller::getRunning(bool &r )
{
  running = r ;
}

void Controller::runThread()
{
  // launch control input function in a thread
  threads.emplace_back(std::thread(&Controller::controlInput, this));
}

void Controller::controlInput() 
{
  std::unique_lock<std::mutex> lck(_mtx); //make lock before using the shared objects SDL and snake
  Uint32 title_timestamp = SDL_GetTicks();
  std::cout<< "running flag is " << running << std::endl;
  lck.unlock();
  
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  //int frame_count = 0;
  //bool running = true;

  while (running) {
    
    // sleep at every iteration to reduce CPU usage
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    std::unique_lock<std::mutex> lck(_mtx); //make lock before using the shared objects SDL and snake
    frame_start = SDL_GetTicks();
    Controller::HandleInput(running/*, snake*/);
    frame_end = SDL_GetTicks();
    lck.unlock();
    
    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    /*frame_count++;*/
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    /*if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }*/

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate. to be removed .
    if (frame_duration < target_frame_duration) {
      std::unique_lock<std::mutex> lck(_mtx); //make lock before using the SDL function
      SDL_Delay(target_frame_duration - frame_duration);
      lck.unlock();
    }
  }

}


void Controller::ChangeDirection(/*std::shared_ptr<Snake> snake, */Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake->getDirection() != opposite || snake->getSize() == 1) snake->setDirection(input);
  return;
}

void Controller::HandleInput(bool &running/*, std::shared_ptr<Snake> snake*/) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      
      std::unique_lock<std::mutex> lck(_mtx); //make lock before using the shared objects SDL and snake
      running = false;
      std::cout<< "running flag due to SDL_QUIT is " << running << std::endl;
      lck.unlock();
  
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(/*snake,*/ Snake::Direction::kUp,
                          Snake::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(/*snake,*/ Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(/*snake,*/ Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(/*snake,*/ Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;
      }
    }
  }
}