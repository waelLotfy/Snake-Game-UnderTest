#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <thread>
#include <mutex>


class GameObject {
 public:
    // constructor / desctructor
    GameObject();
   // ~GameObject();

    
    // typical behaviour methods
    virtual void runThread(){};

  
 protected: 
  
    //std::vector<std::thread> threads; // holds all threads that have been launched within this object
    //static std::mutex _mtx;           // mutex shared by all traffic objects for protecting cout 

  
 private:
  
};

#endif