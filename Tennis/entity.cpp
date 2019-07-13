#include "entity.h"

Entity::Entity(){

	visible = false;
	box.x = 0;
	box.y = 0;
}

Entity::Entity(SDL_Surface *image){

	this->image = image;
	visible = false;
	box.x = 0;
	box.y = 0;
	box.w = image->w;
	box.h = image->h;
	objectName = "Generic Object";
}

void Entity::SetName(std::string objectName){
	this->objectName = objectName;
}

std::string Entity::getName(){
	return objectName;
}

void Entity::SetVisible(bool flag){
	visible = flag;
}

bool Entity::isVisible(){
	return visible;
}

void Entity::SetX(float x){
	box.x = x;
}

void Entity::SetY(float y){
	box.y = y;
}

void Entity::SetW(int w){
	box.w = w;
}

void Entity::SetH(int h){
	box.h = h;
}

float Entity::getX(){
	return box.x;
}

float Entity::getY(){
	return box.y;
}

int Entity::getW(){
	return box.w;
}

int Entity::getH(){
	return box.h;
}

void Entity::Move(float xVel, float yVel){
	box.x += xVel;
	box.y += yVel;
}

void Entity::Render(SDL_Surface *dest){
	if (visible && image != nullptr){
		SDL_Rect temp;
		temp.x = box.x;
		temp.y = box.y;
		SDL_BlitSurface(image, NULL, dest, &temp);
	}
}

Entity::~Entity(){
	delete image;
}