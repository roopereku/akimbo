#include <akimbo/ui/Button.hh>

namespace Akimbo
{

namespace UI
{

void Button::onMouseClick(Vec2)
{
	if(onClick)
		onClick(*this);
}

}

}
