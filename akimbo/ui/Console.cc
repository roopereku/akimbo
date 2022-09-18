#include "Console.hh"

namespace Akimbo::UI {

const float gap = 0.02f;

Console::Console() : Container(),
	log(add <Logger> (left(gap), top(gap), right(gap), bottom(0.15f))),
	submit(add <Button> (log.right(-0.3f), log.bottom(gap), log.right(), bottom(gap))),
	input(add <TextInput> (log.left(), submit.top(), submit.left(gap), submit.bottom() ))
{
	log.setBackgroundColor(0.0f, 0.0f, 0.0f, 0.7f);
	input.setBackgroundColor(0.0f, 0.0f, 0.0f, 0.7f);
	submit.setBackgroundColor(0.0f, 0.0f, 0.0f, 0.7f);

	submit.setText("Submit");

	input.onSubmit = [this](const std::string& str)
	{
		execute(str);
	};

	submit.onClick = [this]()
	{
		if(input.getValue().empty())
			return;

		execute(input.getValue());
		input.clear();
	};
}

void Console::execute(const std::string& cmd)
{
	size_t separator = cmd.find(' ');

	std::string name;
	std::string value;

	//	Is there a value?
	if(separator != std::string::npos)
	{
		//	Separate the name and the value
		name = std::string(cmd.begin(), cmd.begin() + separator);
		value = std::string(cmd.begin() + separator + 1, cmd.end());
	}

	else name = cmd;

	//	Does the command exist?
	auto entry = commands.find(name);

	//	The command doesn't exist
	if(entry == commands.end())
	{
		log.addMessage("Invalid command: " + name, Vec3(1.0f, 0.0f, 0.0f));
		return;
	}

	//	Call the callback
	entry->second(value);
}

std::function <void(const std::string&)>& Console::command(const std::string& name)
{
	return commands[name];
}

}
