#ifndef AKIMBO_UI_CONTAINER_BASE_HH
#define AKIMBO_UI_CONTAINER_BASE_HH

#include <akimbo/ui/Widget.hh>
#include <akimbo/Vector2.hh>
#include <akimbo/Core.hh>

#include <vector>

namespace Akimbo
{

namespace UI
{

class Container : public Widget
{
public:
	template <typename T, typename... Args>
	T& add(Args&&... args)
	{
		return static_cast <T&>
			(addChild(getCore().add <T> (std::forward <Args> (args)...)));
	}

	void onUpdate() final override
	{
		render();
	}

protected:
	virtual bool onMouseClick(Vec2i at) override;
	virtual bool onMouseDrag(Vec2i at) override;

	void onResize(Vec2i size) override;

	struct Child
	{
		Child(Widget& widget) : widget(widget)
		{
		}

		bool isPointInside(Vec2i at);

		Vec2i position;
		Vec2i size;

		Widget& widget;

		int maxSize;
	};

	virtual void prepare(Widget& widget) = 0;
	virtual void adjustChildren() = 0;

	Widget& addChild(Widget& widget);

	std::vector <Child> children;
	Vec2i size;
};

}

}

#endif
