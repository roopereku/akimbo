# Akimbo engine
Akimbo is an easy to use 2D game framework

## Usage
All that is needed to get started is to 
- create a class that inherits from `Akimbo::Core`
- implement `onRender()` and `onUpdate()`
- Call `Akimbo::Core::start()` in `main()`
```cpp
#include "akimbo/Core.hh"

class Game : public Akimbo::Core
{
public:
	void onRender(Akimbo::Frame& frame) override
	{
		frame.color(255, 255, 255);
		frame.drawLine(Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
	}

	void onUpdate(double delta)
	{
	}
private:
};

int main()
{
	Game g;
	g.start();
}
```
## Plans
- Support other libraries than SDL2
- Add an entity system
- Add basic physics
