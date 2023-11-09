#ifndef AKIMBO_UI_ROOT_HH
#define AKIMBO_UI_ROOT_HH

#include <akimbo/Window.hh>
#include <akimbo/ui/Layout.hh>
#include <akimbo/EntityProperty.hh>

namespace akimbo::UI
{

class Layout;

class Root : public Window::Content
{
public:
	~Root();

	static Root& add(Layout& layout);
	operator Layout&();

	template <typename T>
	T& child(T& widget)
	{
		return layout.child(widget);
	}

private:
	Root(Layout& layout);
	void onRender(Renderer2D& render) final override;

	Layout& layout;
};

}

#endif
