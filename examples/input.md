# User input

The `Core` class provides you with some functions to handle user input

## Mouse input

To handle mouse clicks you can override the `onMouseClick` function. For an example
```cpp
class MouseExample : public Akimbo::Core
{
public:
	void onMouseClick(Vec2 at, int button) override
	{
		//	FIXME the button variable does nothing yet
		boxAt = at;
	}
	
	void onRender(Akimbo::Render& render) override
	{
		//	Render a box where the user clicks
		render.color(1.0f, 0.0f, 0.0f),
		render.box(boxAt, Vec2(0.2f, 0.2f), true);
	}

private:
	Vec2 boxAt;
};
```

## Keyboard input

To handle mouse clicks you can override the `onKeyPress` function. For an example

```cpp
#include <string>

class MouseExample : public Akimbo::Core
{
public:
	//	Handle characters
	void onKeyPress(char c) override
	{
		text += c;

		//	NOTE Remember to call render() to show the changes
		render();
	}

	//	Handle other key presses
	void onKeyPress(Akimbo::Key other) override
	{
		//	If backspace is pressed, remove the last character
		if(other == Akimbo::Key::Backspace && !text.empty())
		{
			text.pop_back();

			//	NOTE Remember to call render() to show the changes
			render();
		}
	}
	
	void onRender(Akimbo::Render& render) override
	{
		//	Render the text variable
		render.color(1.0f, 0.0f, 0.0f),
		render.fitText(text, getDefaultFont(), render.topLeft(), render.radius());
	}

private:
	std::string text;
};
```
