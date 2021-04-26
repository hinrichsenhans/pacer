#include "pacerserver.h"
#include "pacerworker.h"
#include "taskqueue.h"

struct ServerTask
{
    enum class Type
    {
        kClientPing,
        kTimelineStart,
        kTimelinePause,
        kTimelineJam,
    };

    Type t;
    Pacer::TimelineId id;
    Pacer::Timestamp timelineTime;
    Pacer::Timestamp referenceTime;
};

class ServerWorker : PacerWorker
{
public:
    void AddEvent(ServerTask&& task)
    {
        queue_.Add(std::move(task));
    }

    void ProcessClientPing(const ServerTask& /*task*/) {}
    void ProcessTimelineChange(const ServerTask& /*task*/) {}
    
    void Tick() override
    {
        TaskQueue<ServerTask>::TASKS list;
        queue_.PopAll(list);
        for (ServerTask& task : list)
        {
            switch (task.t)
            {
            case ServerTask::Type::kClientPing:
                ProcessClientPing(task);
                break;
            case ServerTask::Type::kTimelineJam:
            case ServerTask::Type::kTimelinePause:
            case ServerTask::Type::kTimelineStart:
                ProcessTimelineChange(task);
                break;
            default:
                break;
            }
        }
    }

private:
    TaskQueue<ServerTask> queue_;
};