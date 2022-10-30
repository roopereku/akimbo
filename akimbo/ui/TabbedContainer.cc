#include "TabbedContainer.hh"

#include <random>
#include <cmath>

namespace Akimbo::UI
{

void TabbedContainer::create(Widget* widget, const std::string& name)
{
	// calculate the width of button
	int tabsCount = tabs.size() + 1;
	int percentage = ceil(100.0f / tabsCount);

	float titleAlpha = titleTransparency;
	int x = 0;

	//	Adjust the constraints of previous titles so that the new one fits
	for(auto& tab : tabs)
	{
		//	If we're automatically focusing the new tab, unhighlight the old selected title
		if(autoFocusTabs && tab.second == selected)
			tab.first->setBackgroundColor(0.0f, 0.0f, 0.0f, titleTransparency);

		tab.first->setConstraints(left(x), top(), left(x + percentage), top(0.1f));
		x += percentage;
	}

	//	Create a new button and pair it with the new container
	auto* btn = &add<Button>(left(x), top(), left(x + percentage), top(0.1f));
	tabs.push_back(std::make_pair(btn, widget));

	//	If we added the first tab or want to automatically focus new tabs, focus the tab
	if(tabs.size() == 1 || autoFocusTabs)
	{
		titleAlpha += 0.1f;

		selected = widget;
		selected->render();
	}

	btn->setBackgroundColor(0.0f, 0.0f, 0.0f, titleAlpha);
	btn->setText(name);

	// when the button is clicked the corresponding tab is visible
	btn->onClick = [this, widget]()
	{
		for(auto& tab : tabs)
		{
			//	Make the button for the previously selected tab brighter
			if(tab.second == selected)
				tab.first->setBackgroundColor(0.0f, 0.0f, 0.0f, titleTransparency);

			//	Make the button for the newly selected tab darker
			if(tab.second == widget)
				tab.first->setBackgroundColor(0.0f, 0.0f, 0.0f, titleTransparency + 0.1f);
		}

		selected = widget;
		selected->render();
	};
}

void TabbedContainer::onRender(Render& render)
{
	if(selected)
		selected->draw(render);

	for(auto& tab : tabs)
		tab.first->draw(render);
}

void TabbedContainer::setTitleTransparency(float alpha)
{
	titleTransparency = alpha;

	for(auto& tab : tabs)
	{
		float a = titleTransparency + (tab.second == selected) * 0.1f;
		tab.first->setBackgroundColor(0.0f, 0.0f, 0.0f, a);
	}
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
