#ifndef AKIMBO_UI_ROOT_HH
#define AKIMBO_UI_ROOT_HH

#include <akimbo/WindowContent.hh>

namespace akimbo::UI
{

class Root : public WindowContent
{
public:
	static Root& add();

private:
	void onRender(Renderer2D& render) final override;
};

}

#endif
