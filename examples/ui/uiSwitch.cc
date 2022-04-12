#include "akimbo/akimbo/Core.hh"
#include "akimbo/akimbo/ui/Switch.hh"

class SwitchExample : public Akimbo::Core
{
public:
	SwitchExample()
	{
		//	Create a switch at the very center of the screen
		auto& switchObject = uiRoot.add <Akimbo::UI::Switch> (
			uiRoot.left(0.5f, true).then(-0.2f, false),
			uiRoot.top(0.5f, true).then(-0.2f, false),
			uiRoot.left(0.5f, true).then(+0.2f, false),
			uiRoot.top(0.5f, true).then(+0.2f, false)
		);

		/*	Akimbo::UI::Switch has a callback variable called onSwitch
		 *	which can be overridden. Every time the switch
		 *	is flicked, this callback will be called */
		switchObject.onSwitch = [](bool on)
		{
			//	Do something if the switch is at the "on" position
			if(on) {}

			//	Do something if the switch is at the "off" position
			else {}
		};
	}

private:
};
