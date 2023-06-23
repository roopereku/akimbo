#ifndef AKIMBO_SDL_WINDOW_HH
#define AKIMBO_SDL_WINDOW_HH

#include <akimbo/Window.hh>
#include <akimbo/SDL/Renderer2D.hh>

namespace Akimbo::SDL
{

class Window : public Akimbo::Window
{
public:
	Window();
	~Window();

private:
	Renderer& getRenderer() override
	{
		return renderer;
	}

	void onContentSet() override;

	SDL_Window* createWindow();
	void onUpdate() override;

	bool mouseHeld = false;
	bool mouseMoved = false;

	SDL_Window* window;
	Renderer2D renderer;
};

}

#endif
