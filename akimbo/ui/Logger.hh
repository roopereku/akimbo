#ifndef AKIMBO_UI_LOGGER_HH
#define AKIMBO_UI_LOGGER_HH

#include "Widget.hh"
#include "../Font.hh"

#include <string>
#include <vector>

namespace Akimbo::UI {

class Logger : public Widget
{
public:
	Logger(Core* core, const EdgeConstraints& edges, Font& font);

	void onRender(Frame& frame) override;
	void onResize(Vec2 resizeFactor) override;

	void addMessage(const std::string& msg);

private:
	float columns;
	float rows;

	std::vector <std::string> messages;
	Vec2 characterSize;
	Font& font;
};

}

#endif
