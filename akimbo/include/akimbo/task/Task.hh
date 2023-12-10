#ifndef AKIMBO_TASK_TASK_HH
#define AKIMBO_TASK_TASK_HH

namespace akimbo
{

class Core;

class Task
{
public:
	/// Tries to invoke and finish the task.
	/// \param context The core that this task is being executed in.
	/// \return True if the task is finished.
	virtual bool tryFinish(Core& context) = 0;

protected:
	static double getDeltaTime(Core& context);
};

}

#endif
