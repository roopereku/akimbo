#include <akimbo/ui/Button.hh>

namespace Akimbo::UI
{

bool Button::onMouseClick(Vec2i)
{
	if(onClick)
	{
		onClick(*this);
		return true;
	}

	return false;
}

}
