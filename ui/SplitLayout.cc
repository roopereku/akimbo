#include <akimbo/ui/SplitLayout.hh>
#include <akimbo/ui/Root.hh>
#include <akimbo/Core.hh>

namespace akimbo::UI
{

SplitLayout& SplitLayout::add(Direction direction)
{
	return getCore().addUpdating(new SplitLayout(direction));
}

SplitLayout& SplitLayout::addVertical()
{
	return add(Direction::Vertical);
}

SplitLayout& SplitLayout::addHorizontal()
{
	return add(Direction::Horizontal);
}

Root& SplitLayout::addRoot(Direction direction)
{
	auto& layout = SplitLayout::add(direction);
	auto& root = Root::add(layout);

	return root;
}

void SplitLayout::onRender(Renderer2D& render)
{
	Widget::onRender(render);
}

void SplitLayout::onChildAdded()
{
}

}
