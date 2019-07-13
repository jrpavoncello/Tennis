#include "entity.h"
#include "timer.h"
#include "text.h"
#include "gamestate.h"
#include "ball.h"
#include <random>
#include <time.h>

int main(int argc, char* args[]){
	
	GameState *Game = new GameState();
	//Start SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
		Game->run = false;
		return -1;
	}
	if(TTF_Init() < 0)
		return 1;

	//SDL Init Vars
	SDL_WM_SetCaption("Tennis", NULL);
	Timer fps;
	TTF_Font *gameStartFont = TTF_OpenFont("text.ttf", 21);
	SDL_Color gameStartColor = {255, 255, 255};
	Text *text1 = new Text("", gameStartColor, gameStartFont);
	void Start(GameState &Game, Entity &P1, Entity &P2, Ball &TennisBall, Text &Text);

	Entity *Player1 = new Entity(SDL_LoadBMP("paddle.bmp"));
	Player1->SetVisible(true);
	Player1->SetY(285);
	Player1->SetName("Player1");

	Entity *Player2 = new Entity(SDL_LoadBMP("paddle.bmp"));
	Player2->SetVisible(true);
	Player2->SetX(790);
	Player2->SetY(285);
	Player2->SetName("Player2");

	Ball *TennisBall = new Ball(10, 5);

	//Game Loop Vars
	stringstream gameInfo[2];
	stringstream pauseInfo;
	string score1 = "" + Game->score[0];
	string score2 = "" + Game->score[1];
	gameInfo[0] << "Press Space to begin, Escape to exit!";
	gameInfo[1] << "Player 1 use W and S, Player 2 use Up Arrow and Down Arrow.";
	pauseInfo << "Are you sure you want to quit? (Y/N)";

	while(Game->run){

		//Start ticks
		fps.Start();
		//Update Screen Black
		SDL_FillRect(Game->screen, 0, 0);
		
		if(!Game->gameInProgress && !Game->paused){
			text1->updateText(gameInfo[0].str());
			text1->render(160,10,Game->screen);
			text1->updateText(gameInfo[1].str());
			text1->render(40,40,Game->screen);
		}
		if(Game->paused){
			text1->updateText(pauseInfo.str());
			text1->render(200,300,Game->screen);
		}

		Start(*Game, *Player1, *Player2, *TennisBall, *text1);
		
		//Render objects
		Player1->Render(Game->screen);
		Player2->Render(Game->screen);
		TennisBall->Object->Render(Game->screen);

		if(SDL_Flip(Game->screen) < 0){
			return -1;
		}
		if(fps.get_ticks()<1000/30)
			SDL_Delay((1000/30)-fps.get_ticks());
	}
	
	TTF_Quit();
	SDL_Quit();

	return 0;
}

void Start(GameState &Game, Entity &P1, Entity &P2, Ball &TennisBall, Text &Text){

	if(!Game.paused){
		Game.ticks++;
		if(Game.ticks%30 == 0){
			TennisBall.getXVel() >= 0 ? TennisBall.SetXVel(TennisBall.getXVel() + 0.5f) : TennisBall.SetXVel(TennisBall.getXVel() - 0.5f);
			TennisBall.getYVel() >= 0 ? TennisBall.SetYVel(TennisBall.getYVel() + 0.5f) : TennisBall.SetYVel(TennisBall.getYVel() - 0.5f);\
		}
	}

	if(Game.gameInProgress){
		stringstream score1;
		score1 << "Player 1: " << Game.score[0];
		stringstream score2;
		score2 << "Player 2: " << Game.score[1];
		Text.updateText(score2.str());
		Text.render(13,40,Game.screen);
		Text.updateText(score1.str());
		Text.render(660,40,Game.screen);
	}

	if(Game.roundEnd){
		TennisBall.Object->SetX(395);
		TennisBall.Object->SetY(295);
		srand(time(NULL));
		int i = rand() % 2;
		if(i == 0){
			if(Game.score[0] >= Game.score[1]){
				TennisBall.SetXVel(TennisBall.getDefaultXVel());
				TennisBall.SetYVel(TennisBall.getDefaultYVel());
			}
			else{
				TennisBall.SetXVel(-TennisBall.getDefaultXVel());
				TennisBall.SetYVel(TennisBall.getDefaultYVel());
			}
		}
		else{
			if(i == 1){
				if(Game.score[0] >= Game.score[1]){
					TennisBall.SetXVel(TennisBall.getDefaultXVel());
					TennisBall.SetYVel(-TennisBall.getDefaultYVel());
				}
				else{
					TennisBall.SetXVel(-TennisBall.getDefaultXVel());
					TennisBall.SetYVel(-TennisBall.getDefaultYVel());
				}
			}
		}
	}
	else{
		if(!Game.paused){
			TennisBall.Object->Move(TennisBall.getXVel(), TennisBall.getYVel());
		}
	}

	while(SDL_PollEvent(&Game.event)){

		if(Game.event.type == SDL_QUIT){
			Game.run = false;
			return;
		}
		
		Game.Key = SDL_GetKeyState(NULL);
		if(Game.Key[SDLK_SPACE] && !Game.paused){
			Game.roundEnd = false;
			Game.gameInProgress = true;
		}
		if(Game.Key[SDLK_ESCAPE]){
			if(!Game.paused){
				Game.paused = true;
			}
		}
		if(Game.paused){
			if(Game.Key[SDLK_y]){
				Game.gameInProgress = false;
				Game.run = false;
				return;
			}
			if(Game.Key[SDLK_n]){
				Game.paused = false;
			}
		}
	}

	if(Game.gameInProgress && !Game.paused){

		if(Game.isColliding(P1, *TennisBall.Object)){
			TennisBall.CollidedWithPaddle();
		}

		if(Game.isColliding(P2, *TennisBall.Object)){
			TennisBall.CollidedWithPaddle();
		}

		if(Game.isTopWallColliding(*TennisBall.Object)){
			TennisBall.CollidedWithWall();
		}
		else{
			if(Game.isBottomWallColliding(*TennisBall.Object)){
				TennisBall.CollidedWithWall();
			}
		}

		if(Game.isGoalColliding(*TennisBall.Object, 0)){
			Game.score[1]++;
			Game.roundEnd = true;
		}

		if(Game.isGoalColliding(*TennisBall.Object, 1)){
			Game.score[0]++;
			Game.roundEnd = true;
		}

		if(Game.Key[SDLK_UP]){
			if(!Game.isTopWallColliding(P2)){
				P2.Move(0, -10);
			}
		}
		if(Game.Key[SDLK_DOWN]){
			if(!Game.isBottomWallColliding(P2)){
				P2.Move(0, 10);
			}
		}

		if(Game.Key[SDLK_w]){
			if(!Game.isTopWallColliding(P1)){
				P1.Move(0, -10);
			}
		}
		if(Game.Key[SDLK_s]){
			if(!Game.isBottomWallColliding(P1)){
				P1.Move(0, 10);
			}
		}
	}
}