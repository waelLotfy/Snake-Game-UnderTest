#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : engine(dev()),
      random_w(2, static_cast<int>(grid_width) ),
      random_h(2, static_cast<int>(grid_height)) {
        
  snake = std::make_shared<Snake> (grid_width, grid_height) ;
  PlaceFood();
}
void Game::Run(Controller /*const*/ &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  
  /*New Feature Added : A thread for handling the input control for the snake*/
  controller.setSnake(snake); 
  controller.setTargetFrameDuration(target_frame_duration); 
  controller.setRunning(running);/*to be optimized*/
  controller.runThread();
  
  /*New Feature Added : A thread for handling the rendering*/
   renderer.setSnake(snake);
   renderer.setFood(food);
   renderer.runThread();
  
  /*New Feature Added : A thread for handling the update*/
  //game_target_frame_duration = target_frame_duration;
  //runThread();
  
  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    //controller.HandleInput(running, snake);  /*Original Code*/
    Update();
    //controller.setSnake(snake); /*Set the updated snake (New Feature Added : A thread for handling the input snake control)*/
    //renderer.setSnake(snake);/*Set the updated snake (New Feature Added : A thread for handling the rendering)*/
    renderer.setFood(food);  /*Set the updated food  (New Feature Added : A thread for handling the rendering)*/
    renderer.setRunning(running);
    //renderer.Render(/*snake, food*/);/*Original Code*/
    
    frame_end = SDL_GetTicks();
    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
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
    
    running = controller.getRunning();
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake->SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::runThread()
{
  // launch control input function in a thread
  //threads.emplace_back(std::thread(&Game::UpdateGame, this));
  
}
void Game::Update() {
  if (!snake->getAlive()) return;

  snake->Update();

  int new_x = static_cast<int>(snake->getHead_x());
  int new_y = static_cast<int>(snake->getHead_y());

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake->GrowBody();
    //snake.speed += 0.02;
    snake->incrementSpeed(0.02) ;
  }
}
void Game::UpdateGame() {
  
  //std::unique_lock<std::mutex> lck(_mtx); //make lock before using the shared objects SDL, food and snake
  //Uint32 title_timestamp = SDL_GetTicks();
  //lck.unlock();
  
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  //bool running = true;
  
  while (true/*running*/){
  // sleep at every iteration to reduce CPU usage
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
    
 // std::unique_lock<std::mutex> lck(_mtx); //make lock before using the shared objects SDL, food and snake
    
  //Start up a task using std::async which takes a reference to the method Controller::getDirectionStatus,
  //Then, wait for the data to be available before updating the game status.
    
  auto futureDirection = std::async(std::launch::deferred, &Snake::isSnakeDirectionChanged,snake);
  futureDirection.wait() ;
  futureDirection.get() ;

  std::cout<< "Start Game Updating " << std::endl;

  frame_start = SDL_GetTicks();
  if (!snake->getAlive()) return;

  snake->Update();

  int new_x = static_cast<int>(snake->getHead_x());
  int new_y = static_cast<int>(snake->getHead_y());

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake->GrowBody();
    //snake.speed += 0.02;
    snake->incrementSpeed(0.02) ;
  }
    ////////////
  
    frame_end = SDL_GetTicks();
    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    ////frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    /*if (frame_end - title_timestamp >= 1000) {
      //renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }*/

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < 10000/*game_target_frame_duration*/) {
      SDL_Delay(10000/*game_target_frame_duration*/ - frame_duration);
    }
    
    
  //lck.unlock();
  }//end while loop
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake->getSize(); }