#include "Label.hh"
#include "../Core.hh"

namespace Akimbo::UI {

Label::Label(Font& font) : font(&font)
{
}

Label::Label() : font(&core->getDefaultFont())
{
}

void Label::onRender(Render& render)
{
	render.text(text, *font, render.topLeft, render.radius * 2.0f);
}

void Label::setText(const std::string& str)
{
	text = str;
}

}
