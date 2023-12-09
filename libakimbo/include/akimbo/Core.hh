#ifndef AKIMBO_CORE_HH
#define AKIMBO_CORE_HH

#include <akimbo/Entity.hh>
#include <akimbo/ValueProperty.hh>

#include <vector>
#include <memory>

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

	void run();

	ValueProperty <bool> isRunning;

	friend class Entity;

protected:
	Core();

	std::vector <std::shared_ptr <Entity>> entities;
};

}

#endif
