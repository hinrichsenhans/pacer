#include "pacer.h"

class PacerWorker;

class PacerServer
{
public:
    PacerServer();

    void Startup();
    void Shutdown();

    void Start(Pacer::TimelineId id);
    void Start(Pacer::TimelineId id, Pacer::Timestamp time);
    void Jam(Pacer::TimelineId id, Pacer::Timestamp time);
    void Resume(Pacer::TimelineId id);
    void Stop(Pacer::TimelineId id);
    void Pause(Pacer::TimelineId id);

private:
    PacerWorker * workerThread_ = nullptr;
};