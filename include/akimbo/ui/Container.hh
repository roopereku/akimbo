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
	void onMouseClick(Vec2 at) override;
	bool onMouseDrag(Vec2 at) override;

	struct Child
	{
		Child(Widget& widget) : widget(widget)
		{
		}

		bool isPointInside(Vec2 at);

		Vec2 position;
		Vec2 size;

		Widget& widget;

		float maxSize;
	};

	virtual void prepare(Child& child)=0;
	Widget& addChild(Widget& widget);

	std::vector <Child> children;
};

}

}

#endif
