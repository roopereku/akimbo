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
	void setContent(WindowContent2D& content);
	virtual Renderer& getRenderer() = 0;

protected:
	virtual void onContentSet() = 0;

	void renderContent(Renderer& renderer);	

	void contentMouseDrag(Vec2i at); 
	void contentMouseClick(Vec2i at); 
	void contentResize(Vec2i size); 

private:
	enum class ContentType
	{
		Content2D
	};

	ContentType contentType;
	WindowContentBase* content = nullptr;
};

};

#endif
