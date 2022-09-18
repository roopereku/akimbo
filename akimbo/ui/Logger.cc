#include "Logger.hh"
#include "../Core.hh"
#include "../Debug.hh"

#include <cmath>

namespace Akimbo::UI {

Logger::Logger(Font& font) : font(&font)
{
}

Logger::Logger() : font(&core->getDefaultFont())
{
}

void Logger::onRender(Render& render)
{
	render.color(0.5f, 0.5f, 0.0f);
	render.clear();

	float entryHeight = (render.radius.y * 2) / rows;
	render.color(1.0f, 1.0f, 1.0f);

	Vec2 position = render.topLeft;

	for(size_t i = 0; i < messages.size(); i++)
	{
		Vec2 size = render.text(messages[i], *font, position, Vec2(render.radius.x * 2, entryHeight), render.wrapText);
		position.y += size.y;
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
