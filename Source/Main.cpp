#include "Application.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

int main(int argc, char *argv[])
{
	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
	int exitCode = 0;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 
		|| IMG_Init(IMG_INIT_PNG) == 0 
		|| Mix_Init(MIX_INIT_MID) == 0 
		|| Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1
		|| TTF_Init() == -1)
		exitCode = 1;
	else
	{
		Application{}.run();
	}

	SDL_Quit();
	IMG_Quit();
	Mix_Quit();
	Mix_CloseAudio();
	TTF_Quit();

	return exitCode;
}