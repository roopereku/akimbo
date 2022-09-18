# Updating things

The `Core` class provides you with the function `update` which can be used to update things every frame

## Example
```cpp
class UpdateExample : public Akimbo::Core
{
public:
	void onUpdate(double delta) override
	{
		elapsed += delta;

		//	Only update things every second
		if(elapsed < 1.0)
			return;

		//	Increment the counter and call onRender() one time per second
		//	NOTE calling render() is important because without nothing new is rendered
		counter++;
		render();

		elapsed = 0.0;
	}

	void onRender(Akimbo::Render& render) override
	{
		render.color(0.5f, 0.5f, 0.5f);
		render.clear();

		//	Draw the value of the counter at the top left of the screen
		render.fitText(std::to_string(counter), getDefaultFont(),
						render.topLeft(), Vec2(0.4f, 0.4f));
	}

private:
	double elapsed = 0.0;
	unsigned counter = 0;
};
```
