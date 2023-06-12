#ifndef AKIMBO_UI_SPLIT_CONTAINER_HH
#define AKIMBO_UI_SPLIT_CONTAINER_HH

#include <akimbo/ui/Container.hh>

namespace Akimbo
{

namespace UI
{

enum class Split
{
	Horizontally,
	Vertically,
};

class SplitContainer : public Container
{
public:
	SplitContainer(Split direction) : direction(direction)
	{
	}

	void setMaximumSize(Widget& widget, int pixels);

protected:
	virtual void prepare(Widget& widget) override;

private:
	void adjustChildren() override;
	void onRender(Render2D& render) override;

	Split direction;
};

class HorizontallySplitContainer : public SplitContainer
{
public:
	HorizontallySplitContainer() : SplitContainer(Split::Horizontally)
	{
	}
};

class VerticallySplitContainer : public SplitContainer
{
public:
	VerticallySplitContainer() : SplitContainer(Split::Vertically)
	{
	}
};

}

}

#endif
