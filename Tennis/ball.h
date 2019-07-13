#ifndef BALL_H
#define BALL_H
#include "entity.h"

class Ball{

private:
	float xVel;
	float yVel;
	float defaultXVel;
	float defaultYVel;
public:
	Ball(float xVel, float yVel);
	void CollidedWithPaddle();
	void CollidedWithWall();
	void SetDefaultXVel(float xVel);
	void SetDefaultYVel(float yVel);
	float getDefaultXVel();
	float getDefaultYVel();
	void SetXVel(float xVel);
	float getXVel();
	void SetYVel(float yVel);
	float getYVel();
	Entity *Object;
	~Ball();
};

#endif //BALL_H