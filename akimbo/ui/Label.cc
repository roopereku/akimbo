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
	render.color(1.0f, 1.0f, 1.0f, 1.0f);
	render.centerText(text, *font, view.topLeft, view.radius * 2.0f, align);
}

void Label::setText(const std::string& str)
{
	text = str;
	render();
}

void Label::setAlign(TextAlign align)
{
	this->align = align;
	render();
}

}
