#ifndef AKIMBO_UI_CONSOLE_HH
#define AKIMBO_UI_CONSOLE_HH

#include "Container.hh"
#include "TextInput.hh"
#include "Button.hh"
#include "Logger.hh"

#include <unordered_map>
#include <functional>

namespace Akimbo::UI {

class Console : public Container
{
public:
	Console();

	void execute(const std::string& cmd);
	std::function <void(const std::string&)>& command(const std::string& name);

	Logger& log;

private:
	std::unordered_map <std::string, std::function <void(const std::string&)>> commands;

	Button& submit;
	TextInput& input;
};

}

#endif
