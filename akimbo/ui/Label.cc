#include "Label.hh"

namespace Akimbo::UI {

Label::Label(Core* core, const EdgeConstraints& edges, Font& font)
	: Widget(core, edges), font(font)
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
