#ifndef AKIMBO_UI_TEXT_INPUT_HH
#define AKIMBO_UI_TEXT_INPUT_HH

#include "Widget.hh"

#include <functional>
#include <string>

namespace Akimbo::UI {

class TextInput : public Widget
{
public:
	TextInput(Font& font);
	TextInput();

	void onRender(Render& render) override;

	void onKeyPress(char key) override;
	void onKeyPress(Key key) override;

	bool clearOnSubmit = true;
	std::function <void(const std::string&)> onSubmit;

	const std::string& getValue() { return text; }
	void clear();

private:
	std::string text;
	Font* font;
};

}

#endif
