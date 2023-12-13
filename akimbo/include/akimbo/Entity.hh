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

	// Property needs access to onPropertyChanged().
	friend class Property;

protected:
	virtual void onPropertyChanged(Property& property);

	/// Adds a new task. Internally calls Core::addTask.
	/// \param task The task to be added.
	void addTask(std::shared_ptr <Task>&& task);

	/// Creates a new repeating task that repeats the given amount.
	/// \param callback The callback to call upon executing the task.
	/// \param repetitions How many times to repeat. Defaults to 0 (Repeat infinitely).
	template <typename Callback>
	void addRepeatingTask(Callback&& callback, unsigned repetitions = 0)
	{
		addTask(RepeatingTask <Callback>::make(std::move(callback), repetitions));
	}

	/// Creates a new repeating task that repeats the given amount.
	/// \param callback The callback to call upon executing the task.
	/// \param durationSeconds How long this TransitionTask should last for.
	template <typename Callback>
	void addTransitionTask(Callback&& callback, double durationSeconds)
	{
		addTask(TransitionTask <Callback>::make(std::move(callback), durationSeconds));
	}

	static Core& getCore();
};

}

#endif
