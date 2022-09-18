# Rendering

Rendering can be done through any function that has `Akimbo::Render& render` as a parameter.
The `Render` class has a bunch of functions which can be used to draw things

### Example
```cpp
void onRender(Akimbo::Render& render) override
{
	//	Set the color as gray and clear the screen
	render.color(0.5f, 0.5f, 0.5f);
	render.clear();

	//	Draw a red filled rectangle that takes up half of the screen
	render.color(1.0f, 0.0f, 0.0f);
	render.box(render.topLeft, render.radius * Vec2(1.0f, 2.0f), true);

	//	Fit a string with 3 rows on the lower right corner of the screen
	render.color(1.0f, 1.0f, 1.0f);
	render.fitText("This is\na string that has\n3 rows!", getDefaultFont(),
					render.center, render.radius);
}
```
### Positioning

The `Render` class tells you exactly where some key positions are including

- `render.topLeft`
- `render.topRight`
- `render.bottomLeft`
- `render.bottomRight`
- `render.center`

There also is `render.radius` which tells you how large the screen is (1/4th of the screen).
To find out how large the entire screen is do `render.radius * 2.0f`
