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

	void onRender(Render& render) override;
	void onResize(Vec2 resizeFactor) override;
	void onMouseClick(Vec2 at, int button) override;

	void addMessage(const std::string& msg);
	void setColumns(unsigned amount);

private:
	float columns;
	unsigned visibleRows = 0;
	unsigned scroll = 0;

	std::vector <std::string> messages;
	Vec2 characterSize;
	Font& font;
};

}

#endif
