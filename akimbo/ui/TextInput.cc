#include "TextInput.hh"
#include "../Core.hh"

namespace Akimbo::UI {

TextInput::TextInput(Font& font) : font(&font)
{
}

TextInput::TextInput() : font(&core->getDefaultFont())
{
}

void TextInput::onRender(Render& render)
{
	render.color(1.0f, 1.0f, 1.0f);
	render.text(text, *font, render.topLeft, render.radius * 2.0f, Akimbo::Render::TextMode::Scroll);
}

void TextInput::onKeyPress(char key)
{
	text += key;
	render();
}

void TextInput::onKeyPress(Key key)
{
	switch(key)
	{
		case Key::Return:
			if(onSubmit)
				onSubmit(text);

			if(clearOnSubmit)
				text.clear();
		break;

		case Key::Backspace:
			if(!text.empty())
				text.pop_back();
		break;

		default: return;
	}

	render();
}

}
