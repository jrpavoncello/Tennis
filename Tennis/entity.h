#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <string>
#include "SDL.h"
#include "SDL_main.h"

class Entity{

	private:
		SDL_Surface *image;
		SDL_Rect box;
		bool visible;
		std::string objectName;
		
	public:
		Entity();
		Entity(SDL_Surface *image);
		void SetName(std::string);
		std::string getName();
		void SetVisible(bool flag);
		bool isVisible();
		void SetX(float x);
		void SetY(float y);
		void SetW(int w);
		void SetH(int h);
		float getX();
		float getY();
		int getW();
		int getH();
		virtual void Render(SDL_Surface *dest);
		void Move(float xVel, float yVel);
		~Entity();
};

#endif //ENTITY_H