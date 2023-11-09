#ifndef AKIMBO_UI_ROOT_HH
#define AKIMBO_UI_ROOT_HH

#include <akimbo/Window.hh>

namespace akimbo::UI
{

class Root : public Window::Content
{
public:
	static Root& add();

private:
	void onRender(Renderer2D& render) final override;
};

}

#endif
