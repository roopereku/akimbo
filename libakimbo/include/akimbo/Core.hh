#ifndef AKIMBO_CORE_HH
#define AKIMBO_CORE_HH

#include <akimbo/Entity.hh>
#include <akimbo/ValueProperty.hh>

#include <vector>
#include <memory>
#include <chrono>

namespace akimbo
{

class Core : public Entity
{
public:
	template <typename T>
	T& add(T* entity)
	{
		entities.emplace_back(entity);
		return static_cast <T&> (*entities.back());
	}

	double getDeltaTime();
	void run();

	ValueProperty <bool> isRunning;

	// Grant access to the Core constructor.
	friend Core& Entity::getCore();

protected:
	Core();

private:
	std::chrono::duration <double> deltaTime;
	std::vector <std::shared_ptr <Entity>> entities;
};

}

#endif
