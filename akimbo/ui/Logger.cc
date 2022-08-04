#include "Logger.hh"
#include "../Debug.hh"

#include <cmath>

namespace Akimbo::UI {

Logger::Logger(Font& font) : font(font)
{
	columns = 20;
	onResize(Vec2());
}

void Logger::onRender(Render& render)
{
	Vec2 currentPosition = render.topLeft;

	for(size_t y = scroll; y < messages.size() && y < scroll + visibleRows; y++)
	{
		std::string& msg = messages[y];
		for(size_t x = 0; x < static_cast <size_t> (columns) && x < msg.length(); x++)
		{
			render.character(msg[x], font, currentPosition, characterSize);
			currentPosition.x += characterSize.x;
		}

		currentPosition.y += characterSize.y;
		currentPosition.x = render.topLeft.x;
	}
}

void Logger::setColumns(unsigned amount)
{
	columns = amount;
	onResize(Vec2());
}


void Logger::onResize(Vec2)
{
	/*
	//	How wide is one character to fit n amount of them next to each other		
	characterSize.x = size.x / columns;
	characterSize.y = characterSize.x;

	//	How many rows are visible?
	visibleRows = size.y / characterSize.y;

	//	Are all of the messages visible?
	if(messages.size() - visibleRows >= messages.size())
		scroll = 0;

	//	If all are not visible, focus on the few before the last one
	else scroll = messages.size() - visibleRows;
	*/
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

	if(messages.size() >= visibleRows)
	{
		DBG_LOG("Scroll %u -> %u", scroll, scroll + 1);
		scroll++;
	}
}

}
