#include "timer.h"

Timer::Timer(){

    //Initialize the variables
    startticks = 0;
    pausedticks = 0;
    paused = false;
    started = false;
}

void Timer::Start(){

    //Start the timer
    started = true;

    //Unpause the timer
    paused = false;

    //Get the current clock time
    startticks = SDL_GetTicks();
}

void Timer::Stop(){

    //Stop the timer
    started = false;

    //Unpause the timer
    paused = false;
}

void Timer::Pause(){

    //If the timer is running and isn't already paused
    if(( started == true) && (paused == false)){

        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        pausedticks = SDL_GetTicks() - startticks;
    }
}

void Timer::Unpause(){

    //If the timer is paused
    if( paused == true ){

        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        startticks = SDL_GetTicks() - pausedticks;

        //Reset the paused ticks
        pausedticks = 0;
    }
}

int Timer::get_ticks(){

	//If the timer is running
    if( started == true ){

        //If the timer is paused
        if( paused == true ){

            //Return the number of ticks when the timer was paused
            return pausedticks;
        }

        else{

            //Return the current time minus the start time
            return SDL_GetTicks() - startticks;
        }
    }

    //If the timer isn't running
    return 0;
}

bool Timer::is_started(){

    return started;
}

bool Timer::is_paused(){

    return paused;
}