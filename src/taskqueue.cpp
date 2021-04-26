#include "taskqueue.h"

template <typename T>
void TaskQueue<T>::Add(T && task)
{
    LOCKER lock(mutex_);
    tasks_.emplace_back(task);
}

template <typename T>
void TaskQueue<T>::PopAll(TASKS & tasks)
{
    LOCKER lock(mutex_);
    tasks.swap(tasks_);
}

template <typename T>
void TaskQueue<T>::Terminate()
{
    LOCKER lock(mutex_);
    tasks_.clear();
}