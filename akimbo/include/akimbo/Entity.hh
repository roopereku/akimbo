#ifndef AKIMBO_ENTITY_HH
#define AKIMBO_ENTITY_HH

#include <akimbo/Property.hh>
#include <akimbo/task/Task.hh>
#include <akimbo/task/RepeatingTask.hh>
#include <akimbo/task/TransitionTask.hh>

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

	/// Creates a new repeating task that repeats the given amount.
	/// \param callback The callback to call upon executing the task.
	/// \param repetitions How many times to repeat. Defaults to 0 (Repeat infinitely).
	template <typename Callback>
	void addRepeatingTask(Callback&& callback, unsigned repetitions = 0)
	{
		tasks.emplace_back(RepeatingTask <Callback>::make(std::move(callback), repetitions));
	}

	/// Creates a new repeating task that repeats the given amount.
	/// \param callback The callback to call upon executing the task.
	/// \param durationSeconds How long this TransitionTask should last for.
	template <typename Callback>
	void addTransitionTask(Callback&& callback, double durationSeconds)
	{
		tasks.emplace_back(TransitionTask <Callback>::make(std::move(callback), durationSeconds));
	}

	static Core& getCore();

private:
	std::vector <std::shared_ptr <Task>> tasks;
};

}

#endif
