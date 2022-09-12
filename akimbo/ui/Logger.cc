#include "Logger.hh"
#include "../Debug.hh"

#include <cmath>

namespace Akimbo::UI {

Logger::Logger(Font& font) : font(font)
{
}

void Logger::onRender(Render& render)
{
	render.color(0.5f, 0.0f, 0.0f);
	render.clear();

	float entryHeight = (render.radius.y * 2) / rows;
	render.color(1.0f, 1.0f, 1.0f);

	for(size_t i = 0; i < messages.size(); i++)
	{
		float y = render.topLeft.y - (entryHeight * i);
		render.text(messages[i], font, Vec2(render.topLeft.x, y), Vec2(render.radius.x * 2, entryHeight));
	}
}

void Logger::setRows(unsigned amount)
{
	rows = amount;
	render();
}

void Logger::onMouseClick(Vec2 at, int button)
{
	(void)button;
	(void)at;

	addMessage("Logger clicked");
}

void Logger::addMessage(const std::string& msg)
{
	messages.push_back(msg);
	render();
}

}
