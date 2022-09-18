# Akimbo

Akimbo is a general purpose framework for making games and other applications

## Getting started

- Install SDL2 and GLEW
- `git clone https://github.com/Geckospaniel/akimbo.git`
- `cd akimbo; git submodule update --init`
- Add this to your `CMakeLists.txt`
	```cmake
	include_directories(akimbo)
	add_subdirectory(akimbo)
	add_executable(MyProject main.cc)
	target_link_libraries(MyProject akimbo)
	```
- Add this to your `main.cpp`
```cpp
#include <akimbo/Core.hh>

class Program : public Akimbo::Core
{
public:
	void onRender(Akimbo::Render& render) override
	{
		render.color(0.5f, 0.5f, 0.5f);
		render.clear();
	}
};

int main()
{
	Program p;
	p.start();
}
```
## Examples

[Updating things](./examples/update.md)
[Rendering](./examples/render.md)
[Input handling](./examples/input.md)
