#include "TextInput.hh"

namespace Akimbo::UI {

TextInput::TextInput(Core* core, const EdgeConstraints& edges, Font& font) : Widget(core, edges), font(font)
{
}

void TextInput::onRender(Frame& frame)
{
	frame.drawText(text, font, position, size);
}

void TextInput::onKeyPress(char key)
{
	text += key;
}

}
