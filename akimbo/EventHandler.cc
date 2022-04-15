#include "EventHandler.hh"
#include "Debug.hh"

#include <SDL2/SDL.h>

namespace Akimbo {

void EventHandler::toggleTextInput()
{
	textInput = !textInput;

	if(textInput)
		SDL_StartTextInput();

	else SDL_StopTextInput();
}

void EventHandler::update()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_KEYDOWN:
			break;

			case SDL_TEXTINPUT:
			break;

			case SDL_WINDOWEVENT:
			{
				switch(event.window.event)
				{
					/*	If a resize happens, we don't wan't to stretch the image
					 *	but adjust the camera radius so that the image remains the same size */
					case SDL_WINDOWEVENT_RESIZED:
					{
						if(onWindowResize)
						{
							Vec2i newSize(event.window.data1, event.window.data2);
							onWindowResize(newSize);
						}

						break;
					}
				}

				break;
			}

			case SDL_QUIT:
				if(onWindowClose)
					onWindowClose();
			break;

			case SDL_MOUSEBUTTONDOWN:
				if(onMouseClick)
					onMouseClick(Vec2i(event.button.x, event.button.y), 1);
			break;
		}
	}
}

}
