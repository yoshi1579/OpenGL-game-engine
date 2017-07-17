
#ifndef WINDOW_H
#define WINDOW_H

#include<iostream>
#include <string.h>
#include <SDL2\SDL.h>
#include "camera.h"
#include <time.h>

using namespace std;

class Window
{
public:
	Window(int width, int height, const string title);

	bool GetbClosed();
	void SwapBuffer(Camera* camera, Player* player);
	friend time_t GetCurrentTime();
	float GetFrameTime();
	~Window();


private:
	SDL_Window* window;
	SDL_GLContext glContext;
	bool bClosed;
	float delta;
	long lastTime;
};

#endif // !WINDOW_H