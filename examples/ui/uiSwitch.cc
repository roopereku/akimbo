#include "akimbo/akimbo/Core.hh"
#include "akimbo/akimbo/ui/Switch.hh"

class SwitchExample : public Akimbo::Core
{
public:
	SwitchExample()
	{
		//	Create a switch at the very center of the screen
		auto& switchObject = ui.add <Akimbo::UI::Switch> (
			ui.left(50).then(-0.2f),
			ui.top(50).then(-0.2f),
			ui.right(50).then(-0.2f),
			ui.bottom(50).then(-0.2f)
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
