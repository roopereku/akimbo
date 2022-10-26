#ifndef AKIMBO_UI_LABEL_HH
#define AKIMBO_UI_LABEL_HH

#include "Widget.hh"

#include <string>

namespace Akimbo::UI {

class Label : public Widget
{
public:
	Label(Font& font);
	Label();

	void onRender(Render& render);
	void setText(const std::string& str);

	void setAlign(TextAlign align);

private:
	TextAlign align = TextAlign::Left;

	std::string text;
	Font* font;
};

}

#endif
