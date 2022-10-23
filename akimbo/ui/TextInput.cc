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
	render.text(text, *font, view.topLeft, view.radius * 2.0f, Akimbo::Render::TextMode::Scroll);
}

void TextInput::onKeyPress(char key)
{
	text += key;
	render();
}

void TextInput::onKeyPress(Key key)
{
	//	No point in doing anything if there's no text
	if(text.empty())
		return;

	switch(key)
	{
		case Key::Return:
			if(onSubmit)
				onSubmit(text);

			if(clearOnSubmit)
				text.clear();
		break;

		case Key::Backspace:
			text.pop_back();
		break;

		default: return;
	}

	render();
}

void TextInput::clear()
{
	text.clear();
	render();
}

}
