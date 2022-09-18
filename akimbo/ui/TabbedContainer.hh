#ifndef AKIMBO_UI_TABBED_CONTAINER_HH
#define AKIMBO_UI_TABBED_CONTAINER_HH

#include "Container.hh"
#include "Button.hh"

namespace Akimbo::UI
{

class TabbedContainer : public Container
{
public:
	Container& tab(const std::string& name);

	void onRender(Render& render) override;
private:
	std::vector<std::pair<Button*, Container*>> tabs;
	Container* selected = nullptr;
	
};

};


#endif
