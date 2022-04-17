#ifndef AKIMBO_UI_LABEL_HH
#define AKIMBO_UI_LABEL_HH

#include "Widget.hh"

#include <string>

namespace Akimbo::UI {

class Label : public Widget
{
public:
	Label(Core* core, const EdgeConstraints& edges, Font& font);

	void onRender(Frame& frame);
	void setText(const std::string& str);

private:
	std::string text;
	Font& font;
};

}

#endif
