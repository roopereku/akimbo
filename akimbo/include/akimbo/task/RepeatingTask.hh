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
	/// Invokes the repeating task.
	/// \param context The core that this task is being executed in.
	/// \return True if all repetitions are done.
	bool tryFinish(Core&) final override
	{
		callback();
		invoked++;

		// If repetitions is above 0, don't finish until all repetitions are done.
		// If repetitions is 0, false is returned to indicate that the task is not finished.
		return repetitions && invoked >= repetitions;
	}

	/// Creates a new repeating task that repeats the given amount.
	/// \param callback The callback to call upon calling tryFinish().
	/// \param repetitions How many times to repeat. Defaults to 0 (Repeat infinitely).
	/// \return shared_ptr containing the repeating task.
	static std::shared_ptr <Task> make(Callback&& callback, unsigned repetitions = 0)
	{
		return std::shared_ptr <Task> (new RepeatingTask(std::move(callback), repetitions));
	}

private:
	RepeatingTask(Callback&& callback, unsigned repetitions)
		: callback(std::move(callback)), repetitions(repetitions)
	{
	}

	Callback callback;

	unsigned repetitions;
	unsigned invoked = 0;
};

}

#endif
