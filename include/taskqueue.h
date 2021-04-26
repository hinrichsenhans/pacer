#include <vector>
#include <mutex>

template<typename T>
class TaskQueue
{
public:
    typedef std::vector<T> TASKS;
    typedef std::lock_guard<std::mutex> LOCKER;

    void Add(T && task); //queue a single task
    void PopAll(TASKS & tasks); //thread to do the work swaps out the work
    void Terminate();

private:
    std::mutex mutex_;
    TASKS tasks_;
};