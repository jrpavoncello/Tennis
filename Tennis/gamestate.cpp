#include "gamestate.h"

GameState::GameState(){
	run = true;
	score[0] = 0;
	score[1] = 0;
	ticks = 0;
	gameInProgress = false;
	paused = false;
	roundEnd = true;
	pointStart = false;
	Key = SDL_GetKeyState(NULL);
	//Screen resolution
	screen = SDL_SetVideoMode(800,600,32,SDL_DOUBLEBUF|SDL_HWSURFACE);
}

bool GameState::isColliding(Entity &Player, Entity &Ball){
	return ((Player.getX() + Player.getW() > Ball.getX()) && 
		(Player.getX() < Ball.getX() + Ball.getW()) && 
		(Player.getY() + Player.getH() > Ball.getY()) && 
		(Player.getY() < Ball.getY() + Ball.getH())) ? true : false;
}

bool GameState::isTopWallColliding(Entity &Object){

	return Object.getY() < 0 ? true : false;
}

bool GameState::isBottomWallColliding(Entity &Object){

	return Object.getY() + Object.getH() > 600 ? true : false;
}

bool GameState::isGoalColliding(Entity &Object, int wall){
	
	if(wall == 0){
		return Object.getX() > 800 ? true : false;
	}
	else{
		if(wall == 1){
			return Object.getX() + Object.getW() < 0 ? true : false;
		}
	}
	return false;
}

GameState::~GameState(){
	delete Key;
}