#ifndef AKIMBO_CORE_HH
#define AKIMBO_CORE_HH

#include <akimbo/UpdatingEntity.hh>
#include <akimbo/ValueProperty.hh>

#include <vector>
#include <memory>

namespace akimbo
{

class Core : public UpdatingEntity
{
public:
	template <typename T>
	T& addUpdating(T* entity)
	{
		updatingEntities.emplace_back(entity);
		return static_cast <T&> (*updatingEntities.back());
	}

	void run();

	ValueProperty <bool> isRunning;

	friend class Entity;

protected:
	Core();
	virtual void onUpdate() override;

	std::vector <std::shared_ptr <UpdatingEntity>> updatingEntities;
};

}

#endif
