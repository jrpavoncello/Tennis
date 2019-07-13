#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "entity.h"

class GameState{

	public:
		GameState();
		~GameState();
		SDL_Surface *screen;
		int score[2];
		int ticks;
		bool run;
		bool gameInProgress;
		bool paused;
		bool roundEnd;
		bool pointStart;
		SDL_Event event;
		Uint8 *Key;
		bool isColliding(Entity &Player, Entity &Ball);
		bool isTopWallColliding(Entity &Object);
		bool isBottomWallColliding(Entity &Object);
		bool isGoalColliding(Entity &Object, int wall);
};

#endif //GAMESTATE_H