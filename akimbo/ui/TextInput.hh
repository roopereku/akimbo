#ifndef AKIMBO_UI_TEXT_INPUT_HH
#define AKIMBO_UI_TEXT_INPUT_HH

#include "Widget.hh"

#include <string>

namespace Akimbo::UI {

class TextInput : public Widget
{
public:
	TextInput(Core* core, const EdgeConstraints& edges, Font& font);

	void onRender(Render& render) override;
	void onKeyPress(char key) override;

private:
	std::string text;
	Font& font;
};

}

#endif
