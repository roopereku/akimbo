#ifndef AKIMBO_TASK_TASK_HH
#define AKIMBO_TASK_TASK_HH

namespace akimbo
{

class Task
{
public:
	// Tries to invoke and finish the task.
	// \return True if the task is finished.
	virtual bool tryFinish() = 0;
};

}

#endif
