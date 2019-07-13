#ifndef TIMER_H
#define TIMER_H

#include "SDL.h"

//The timer
class Timer{

    private:

		//The clock time when the timer started
		int startticks;

		//The ticks stored when the timer was paused
		int pausedticks;

		//The timer status
		bool paused;
		bool started;

		public:

		//Initializes variables
		Timer();

		//The various clock actions
		void Start();
		void Stop();
		void Pause();
		void Unpause();

		//Gets the timer's time
		int get_ticks();

		//Checks the status of the timer
		bool is_started();
		bool is_paused();
};

#endif //TIMER_H