#ifndef AKIMBO_TASK_TRANSITION_TASK_HH
#define AKIMBO_TASK_TRANSITION_TASK_HH

#include <akimbo/task/Task.hh>

#include <memory>
#include <cstdio>

namespace akimbo
{

template <typename Callback>
class TransitionTask : public Task
{
public:
	/// Invokes the repeating task.
	/// \param context The core that this task is being executed in.
	/// \return True if all repetitions are done.
	bool tryFinish(Core& context) final override
	{
		timeSpent += getDeltaTime(context);
		float progress = timeSpent / durationSeconds;

		progress = progress > 1.0f ? 1.0f : progress;
		callback(progress);

		return timeSpent > durationSeconds;
	}

	/// Creates a new a new transition task that spans over the given duration.
	/// \param callback The callback to invoke upon task execution.
	/// \param durationSeconds How long this TransitionTask should last for.
	/// \return shared_ptr containing the transition task.
	static std::shared_ptr <Task> make(Callback&& callback, double durationSeconds)
	{
		return std::shared_ptr <Task> (new TransitionTask(std::move(callback), durationSeconds));
	}

private:
	TransitionTask(Callback&& callback, double durationSeconds)
		: callback(std::move(callback)), durationSeconds(durationSeconds)
	{
	}

	Callback callback;

	double durationSeconds;
	double timeSpent = 0.0;
};

}

#endif
