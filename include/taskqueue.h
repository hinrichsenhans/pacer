#include <vector>
#include <mutex>

template<typename T>
class TaskQueue
{
public:
    typedef std::vector<T> TASKS;
    typedef std::lock_guard<std::mutex> LOCKER;

    void Add(T&& task)
    {
        LOCKER lock(mutex_);
        tasks_.emplace_back(task);
    }

    void PopAll(TASKS& tasks)
    {
        LOCKER lock(mutex_);
        tasks.swap(tasks_);
    }

    void Terminate()
    {
        LOCKER lock(mutex_);
        tasks_.clear();
    }

private:
    std::mutex mutex_;
    TASKS tasks_;
};