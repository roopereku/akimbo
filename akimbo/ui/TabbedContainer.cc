#include "TabbedContainer.hh"

#include <random>
#include <cmath>

namespace Akimbo::UI
{

Container& TabbedContainer::tab(const std::string& name)
{
	// creating new container
	auto* temp = &add<Container>(left(), top(0.1f), right(), bottom());

	// calculate the width of button
	int tabsCount = tabs.size() + 1;
	int percentage = ceil(100.0f / tabsCount);

	// adjust constraints of existing buttons
	int x = 0;

	for(auto& tab : tabs)
	{
		//	Is this tab the same as what was previously selected
		if(tab.second == selected)
			tab.first->setBackgroundColor(0.0f, 0.0f, 0.0f, 0.6f);

		tab.first->setConstraints(left(x), top(), left(x + percentage), top(0.1f));
		x += percentage;
	}

	selected = temp;

	//	Create a new button and pair it with the new container
	auto* btn = &add<Button>(left(x), top(), left(x + percentage), top(0.1f));
	tabs.push_back(std::make_pair(btn, selected));

	selected->render();

	btn->setBackgroundColor(0.0f, 0.0f, 0.0f, 0.7f);
	btn->setText(name);

	// when the button is clicked the corresponding tab is visible
	btn->onClick = [this, temp]()
	{
		for(auto& tab : tabs)
		{
			//	Make the button for the previously selected tab brighter
			if(tab.second == selected)
			{
				tab.first->setBackgroundColor(0.0f, 0.0f, 0.0f, 0.6f);
				tab.first->render();
			}

			//	Make the button for the newly selected tab darker
			if(tab.second == temp)
			{
				tab.first->setBackgroundColor(0.0f, 0.0f, 0.0f, 0.7f);
				tab.first->render();
			}
		}

		selected = temp;
		selected->render();
	};

	return *selected;
}

void TabbedContainer::onRender(Render& render)
{
	if(selected)
		selected->draw(render);

	for(auto& tab : tabs)
		tab.first->draw(render);
}

Widget* TabbedContainer::isInside(Vec2& point, Vec2& where)
{
	//	The point isn't inside this container
	if(!Widget::isInside(point, where))
		return nullptr;

	if(selected)
	{
		//	Is the point inside the selected tab?
		Vec2 normalizedParent = point;
		Widget* result = selected->isInside(normalizedParent, where);

		if(result) return result;
	}

	for(auto& tab : tabs)
	{
		Vec2 normalizedParent = point;

		//	Is the point inside this button
		Widget* result = tab.first->isInside(normalizedParent, where);
		if(result) return result;
	}

	return this;
}

}
