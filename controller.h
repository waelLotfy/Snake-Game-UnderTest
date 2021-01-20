#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include "gameObject.h"


class Controller : public GameObject
{
 public:

  void HandleInput(bool &running, Snake &snake) const;
      
  // typical behaviour methods
  void runThread();


 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif