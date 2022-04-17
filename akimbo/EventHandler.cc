#include "EventHandler.hh"
#include "Debug.hh"

#include <SDL2/SDL.h>

namespace Akimbo {

EventHandler::EventHandler()
{
	SDL_StartTextInput();
}

void EventHandler::update()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_KEYDOWN:
				//	TODO handle key states
			break;

			case SDL_TEXTINPUT:
				//	TODO support unicode
				if(onKeyPress)
					onKeyPress(event.text.text[0]);
			break;

			case SDL_WINDOWEVENT:
			{
				switch(event.window.event)
				{
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
