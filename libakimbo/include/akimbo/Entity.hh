#ifndef AKIMBO_ENTITY_HH
#define AKIMBO_ENTITY_HH

#include <akimbo/Property.hh>
#include <akimbo/task/Task.hh>
#include <akimbo/task/RepeatingTask.hh>

#include <vector>
#include <memory>

namespace akimbo
{

class Core;

class Entity : public std::enable_shared_from_this <Entity>
{
public:
	Entity()
	{
	}

	Entity& operator=(const Entity& rhs) = delete;
	Entity(const Entity& rhs) = delete;

	virtual bool isUpdating()
	{
		return false;
	}

	void executeTasks();

	// Property needs access to onPropertyChanged().
	friend class Property;

protected:
	virtual void onPropertyChanged(Property& property)
	{
	}

	template <typename Callback>
	void addRepeatingTask(Callback&& callback)
	{
		tasks.emplace_back(RepeatingTask <Callback>::make(std::move(callback)));
	}

	static Core& getCore();

private:
	std::vector <std::shared_ptr <Task>> tasks;
};

}

#endif
