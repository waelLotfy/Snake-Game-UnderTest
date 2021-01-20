#include "gameObject.h"
#include <iostream>


//std::mutex GameObject::_mtx;


GameObject::GameObject()
{
   
}
/*
GameObject::~GameObject()
{
    // set up thread barrier before this object is destroyed
    std::for_each(threads.begin(), threads.end(), [](std::thread &t) {
        t.join();
    });
}
*/