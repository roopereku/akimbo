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
	Logger(Font& font);
	Logger();

	void onRender(Render& render) override;
	void onMouseClick(Vec2 at, int button) override;

	void addMessage(const std::string& msg, Vec3 color = Vec3(1.0f, 1.0f, 1.0f));
	void setRows(unsigned amount);

private:
	unsigned rows = 20;
	std::vector <std::pair <std::string, Vec3>> messages;
	Font* font;
};

}

#endif
