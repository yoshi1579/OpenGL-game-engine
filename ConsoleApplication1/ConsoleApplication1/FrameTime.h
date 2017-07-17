#ifndef FRAMETIME_H
#define FRAMETIME_H


const int NUM_FRAME = 30;

class FrameTime
{
public:
	double fps;
	FrameTime(double fps);

	void CalculateFPS();
private:
	double deltaTime = 0;
	float currentFrame = 0;
	float previousFrame = 0;
	int frameCount = 0;
	double fpsArray[NUM_FRAME];
	
};
#endif // !FRAMETIME_H

