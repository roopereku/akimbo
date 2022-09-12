#include "Label.hh"

namespace Akimbo::UI {

Label::Label(Font& font)
	: font(font)
{
}

void Label::onRender(Render& render)
{
	render.text(text, font, render.topLeft, render.radius * 2.0f);
}

void Label::setText(const std::string& str)
{
	text = str;
}

}
