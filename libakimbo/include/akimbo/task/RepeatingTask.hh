#ifndef AKIMBO_TASK_REPEATING_TASK_HH
#define AKIMBO_TASK_REPEATING_TASK_HH

#include <akimbo/task/Task.hh>

#include <memory>

namespace akimbo
{

template <typename Callback>
class RepeatingTask : public Task
{
public:
	// Invokes the repeating task.
	// \return Always false as a repeating task is never finished.
	bool tryFinish() final override
	{
		callback();
		return false;
	}

	// Creates a new repeating task.
	// \param callback The callback to call upon calling tryFinish().
	// \return shared_ptr containing the repeating task.
	static std::shared_ptr <Task> make(Callback&& callback)
	{
		return std::shared_ptr <Task> (new RepeatingTask(std::move(callback)));
	}

private:
	RepeatingTask(Callback&& callback) : callback(std::move(callback))
	{
	}

	Callback callback;
};

}

#endif
