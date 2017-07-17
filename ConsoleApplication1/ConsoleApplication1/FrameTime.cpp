#include "FrameTime.h"
#include <SDL2\SDL.h>

FrameTime::FrameTime(double firstFps)
{
	fps = firstFps;
}

void FrameTime::CalculateFPS()
{
	double totalFrameTime = 0;
	double averageFrameTime = 0;

	currentFrame = SDL_GetTicks();
	deltaTime = currentFrame - previousFrame;
	previousFrame = currentFrame;

	fpsArray[frameCount] = deltaTime;

	// calculating average fps
	if (frameCount >= (NUM_FRAME - 1))
	{
		for (int i = 0; i < NUM_FRAME; i++)
		{
			totalFrameTime += fpsArray[i];
		}
		averageFrameTime = totalFrameTime / NUM_FRAME;

		if (averageFrameTime > 0.0)
			fps = 1000.0 / averageFrameTime;
		else
			fps = 60.0;
	}

	if (frameCount >= (NUM_FRAME - 1))
		frameCount = 0;
	else
		frameCount++;
}
