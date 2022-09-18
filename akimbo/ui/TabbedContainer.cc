#include "TabbedContainer.hh"

#include <random>
#include <cmath>

namespace Akimbo::UI
{

Container& TabbedContainer::tab(const std::string& name)
{
	// creating new container
	auto* temp = &add<Container>(left(), top(0.1f), right(), bottom());
	selected = temp;

	// TODO remove this
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(0.0f, 1.0f);

	selected->setBackgroundColor(dist(gen), dist(gen), dist(gen));

	// calculate the width of button
	int tabsCount = tabs.size() + 1;
	int percentage = ceil(100.0f / tabsCount);

	// adjust constraints of existing buttons
	int x = 0;
	for(auto& tab : tabs)
	{
		tab.first->setConstraints(left(x), top(), left(x + percentage), top(0.1f));
		x += percentage;	
	}

	// create new button
	auto* btn = &add<Button>(left(x), top(), left(x + percentage), top(0.1f));

	btn->setBackgroundColor(dist(gen), dist(gen), dist(gen));
	btn->setText(name);

	// when the button is clicked the corresponding tab is visible
	btn->onClick = [this, temp]()
	{
		selected = temp;
		render();
	};
	
	render();
	tabs.push_back(std::make_pair(btn, selected));

	return *selected;
}


void TabbedContainer::onRender(Render& render)
{
	if(selected)
		selected->draw(render);

	for(auto& tab : tabs)
	{
		tab.first->draw(render);
	}
}




}
