#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <thread>
#include <mutex>


class GameObject {
 public:
    // constructor / desctructor
    GameObject();
    ~GameObject();

    
    // typical behaviour methods
    virtual void runThread()=0;
  
 protected: 
  
    std::vector<std::thread> threads;  // holds all threads that have been launched within this object
    static std::mutex _mtxSnake;       // mutex shared by all game objects for protecting the shared snake
    static std::mutex _mtxFood;        // mutex shared by all game objects for protecting the shared food
    static std::mutex _mtxCout;        // mutex shared by all game objects for protecting the shared cout
    static std::mutex _mtxSDL;         // mutex shared by all game objects for protecting the shared SDL
  
 private:
  
};

#endif