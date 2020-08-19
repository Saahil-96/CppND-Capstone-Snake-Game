#ifndef FOOD_H
#define FOOD_H

#include <random>
#include "SDL.h"

class Food{
public:
    enum type{regular, apple, poison};
    type att;
    Food(){att=regular;} // By default all food is regular food
    Food(type t):att(t) // Overloaded constructor to allow definition of type of food at object creation
    {
        if (att==regular)
            {
                _uptime=0; 
            } 
        else if((att==apple)||(att==poison))
            {
                _uptime=5; // Time for prompt to stay up (To be implemented in a later release)
            }
    }

    SDL_Point loc; // Location of food
    int Uptime(){ return _uptime;} // Getter function

private:
int _uptime;
};

#endif