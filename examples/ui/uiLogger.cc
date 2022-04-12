#include "akimbo/akimbo/Core.hh"
#include "akimbo/akimbo/ui/Logger.hh"

class SwitchExample : public Akimbo::Core
{
public:
	SwitchExample()
	{
		//	You have to decide what font to use, so let's load it here
		Akimbo::Font& loggerFont = loadFont("/path/to/font");

		//	Create a logger that fills up most of the window
		auto& loggerObject = uiRoot.add <Akimbo::UI::Logger> (
			uiRoot.left(0.1f, false),
			uiRoot.top(0.1f, false),
			uiRoot.right(-0.1f, false),
			uiRoot.bottom(-0.1f, false),

			//	The font to be used is passed after the constraints
			loggerFont
		);

		/*	Akimbo::UI::Logger has a function called addMessage()
		 *	which as you guessed, adds a message to the logger */
		loggerObject.addMessage("This is a message");
		loggerObject.addMessage("This is another message");
	}

private:
};