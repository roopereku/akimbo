#ifndef AKIMBO_SDL_WINDOW_HH
#define AKIMBO_SDL_WINDOW_HH

#include <akimbo/Window.hh>
#include <akimbo/SDL/Renderer2D.hh>

#include <memory>

namespace Akimbo
{

namespace SDL
{

class Window : public Akimbo::Window
{
public:
	Window();
	~Window();

	Renderer& getRenderer() override
	{
		return renderer;
	}

private:
	SDL_Window* createWindow();
	void onUpdate() override;

	bool mouseHeld = false;
	bool mouseMoved = false;

	SDL_Window* window;
	Renderer2D renderer;
};

}

}

#endif
