#ifndef AKIMBO_WINDOW_HH
#define AKIMBO_WINDOW_HH

#include <akimbo/Module.hh>
#include <akimbo/Vector2.hh>
#include <akimbo/Renderer.hh>
#include <akimbo/WindowContent.hh>

#include <memory>
#include <vector>

namespace Akimbo
{

class Window : public Module
{
public:
	void setContent(WindowContent& content);

protected:
	virtual void onContentSet() = 0;
	virtual Renderer& getRenderer() = 0;

	void renderContent();
	void contentMouseDrag(Vec2i at); 
	void contentMouseClick(Vec2i at); 
	void contentResize(Vec2i size); 

private:
	WindowContent* content = nullptr;
};

};

#endif
