#include "TextInput.hh"

namespace Akimbo::UI {

TextInput::TextInput(Font& font) : font(font)
{
}

void TextInput::onRender(Render& render)
{
	render.text(text, font, render.topLeft, render.radius * 2.0f);
}

void TextInput::onKeyPress(char key)
{
	text += key;
}

}
