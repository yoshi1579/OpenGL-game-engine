
#include "Window.h"
#include <GL\glew.h>
#include "Player.h"

const Uint8* keyState;
Uint32 mouseState;

Window::Window(int width, int height, const string title)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow(title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_OPENGL);
	if (window == NULL)
	{
		printf("Failed to open window\n");
		exit(-1);
	}

	glContext = SDL_GL_CreateContext(window);

	GLenum status = glewInit();
	if (status != GLEW_OK)
	{
	cerr << "Failed to initialize OpenGl" << endl;
	exit(-1);
	}

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	lastTime = GetCurrentTime();
	bClosed = false;
}

float Window::GetFrameTime()
{
	return delta;
}

Window::~Window()
{
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Window::SwapBuffer(Camera* camera, Player* player)
{
	int mouseX = 0;
	int mouseY = 0;
	long currentTime = GetCurrentTime();
	delta = (currentTime - lastTime) / 1000;	//conver to second
	lastTime = currentTime;

	SDL_GL_SwapWindow(window);

	SDL_Event e;
	
	while (SDL_PollEvent(&e))
	{
		keyState = SDL_GetKeyboardState(NULL);

		// input for player movement
		if (keyState[SDL_SCANCODE_W])
			player->SetSpeed(RUN_SPEED);
		else if (keyState[SDL_SCANCODE_S])
			player->SetSpeed(-RUN_SPEED);


		if (keyState[SDL_SCANCODE_A])
			player->SetCurrentTurnSpeed(TURN_SPEED);
		else if (keyState[SDL_SCANCODE_D])
			player->SetCurrentTurnSpeed(-TURN_SPEED);

		if (keyState[SDL_SCANCODE_SPACE])
		{
			if (!player->GetIsInAir())
			{
				player->SetUpwardSpeed(JUMP_POWER);
				player->SetIsInAir(true);
			}
		}

		// input for camera movement
		//if (e.type == SDL_MOUSEBUTTONDOWN)
		//{
			/*
			// change pitch
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				camera->IncreasePitch(e.button.y);
			}
			// change yaw
			else if (e.button.button == SDL_BUTTON_RIGHT)
			{
				camera->IncreaseYaw(e.button.x);
			}
			*/

			if (SDL_GetMouseState(&mouseX, &mouseY)&SDL_BUTTON_LMASK)
			{
				camera->IncreasePitch(mouseY - 300);
			}
			else if (SDL_GetMouseState(&mouseX, &mouseY)& SDL_BUTTON_RMASK)
			{
				camera->IncreaseYaw(mouseX - 400);
			}
		//}
		/*
		if (SDL_GetMouseState(&mouseX, &mouseY)&SDL_BUTTON(1))
		{
			camera->IncreasePitch(mouseY);
		}
		else if (SDL_GetMouseState(&mouseX, &mouseY)&SDL_BUTTON(0))
		{
			camera->IncreaseYaw(mouseX);
		}
		*/
	}

	if (!keyState[SDL_SCANCODE_W] && !keyState[SDL_SCANCODE_S])
		player->SetSpeed(0);
	if (!keyState[SDL_SCANCODE_A] && !keyState[SDL_SCANCODE_D])
		player->SetCurrentTurnSpeed(0);

}


bool Window::GetbClosed()
{
	return bClosed;
}

time_t GetCurrentTime()
{
	return time(NULL) * 1000;	// (ms)
}

