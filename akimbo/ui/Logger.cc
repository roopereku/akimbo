#include "Logger.hh"
#include "../Debug.hh"

namespace Akimbo::UI {

Logger::Logger(Core* core, const EdgeConstraints& edges, Font& font)
	: Widget(core, edges), font(font)
{
	columns = 20;
	rows = 10;

	characterSize = size / Vec2(columns, rows);
}

void Logger::onRender(Frame& frame)
{
	Vec2 currentPosition = position;

	for(size_t y = 0; y < static_cast <size_t> (rows) && y < messages.size(); y++)
	{
		for(size_t x = 0; x < static_cast <size_t> (columns) && x < messages[y].length(); x++)
		{
			frame.drawCharacter(messages[y][x], font, currentPosition, characterSize);
			currentPosition.x += characterSize.x;
		}

		currentPosition.y += characterSize.y;
		currentPosition.x = position.x;
	}
}

void Logger::onResize(Vec2 resizeFactor)
{
	//	To keep the text size the same, just resize rows and columns
	columns /= resizeFactor.x;
	rows /= resizeFactor.y;
}

void Logger::onMouseClick(Vec2 at, int button)
{
	addMessage("Logger clicked");
}

void Logger::addMessage(const std::string& msg)
{
	messages.push_back(msg);
}

}
