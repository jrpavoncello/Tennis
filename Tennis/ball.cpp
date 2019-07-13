#include "ball.h"

Ball::Ball(float xVel, float yVel){
	this->xVel = xVel;
	this->yVel = yVel;
	defaultXVel = xVel;
	defaultYVel = yVel;
	Object = new Entity(SDL_LoadBMP("ball.bmp"));
	Object->SetVisible(true);
	Object->SetX(395);
	Object->SetY(295);
	Object->SetName("Ball");
}

void Ball::SetDefaultXVel(float xVel){
	defaultXVel = xVel;
}
void Ball::SetDefaultYVel(float yVel){
	defaultYVel = yVel;
}
float Ball::getDefaultXVel(){
	return defaultXVel;
}
float Ball::getDefaultYVel(){
	return defaultYVel;
}

void Ball::CollidedWithPaddle(){
	xVel *= -1;
}

void Ball::CollidedWithWall(){
	yVel *= -1;
}

float Ball::getXVel(){
	return xVel;
}

void Ball::SetXVel(float xVel){
	this->xVel = xVel;
}

float Ball::getYVel(){
	return yVel;
}

void Ball::SetYVel(float yVel){
	this->yVel = yVel;
}


Ball::~Ball(){
	delete Object;
}