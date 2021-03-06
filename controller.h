#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include "gameObject.h"

/*New Feature Added : A thread for handling the inpit control for the snake*/
class Controller : public GameObject , public std::enable_shared_from_this<Controller>
{
 
 public:
  void HandleInput(bool &running/*, std::shared_ptr<Snake> snake*/) const;
      
  // typical behaviour methods
  void runThread() override; /*New Feature Added : A thread for handling the inpit control for the snake*/
  
  /*New Feature Added : A thread for handling the inpit control for the snake*/
  /* This method is used as a thread for checking if there is input for controlling the snake. */
  void controlInput() ; 

  void setSnake(std::shared_ptr<Snake> s); /*To get the snake from the controller*/ /*New Feature Added : A thread for handling the inpit control for the snake*/
  void setTargetFrameDuration(std::size_t t); /*To get the target_frame_duration from the controller*/ /*New Feature Added : A thread for handling the inpit control for the snake*/
  void setRunning(bool /*&*/r );
  bool getRunning();
  
  // miscellaneous
  std::shared_ptr<Controller> get_shared_this() { return shared_from_this(); }
  
  
 private:
  void ChangeDirection(/*std::shared_ptr<Snake> snake,*/ Snake::Direction input,
                       Snake::Direction opposite) const;
  std::shared_ptr<Snake> snake;/*New Feature Added : A thread for handling the inpit control for the snake*/
  std::size_t target_frame_duration;/*New Feature Added : A thread for handling the inpit control for the snake*/
  /*mutable*/ bool running ; /*New Feature Added : A thread for handling the inpit control for the snake*/

  mutable std::mutex _mtxRunning;  /*New Feature Added : A thread for handling the inpit control for the snake*/ // To be used in the constant function for locking the shared resource. 
  
  
};

#endif