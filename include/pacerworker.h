#include <QThread>

class PacerWorker : QThread
{
    Q_OBJECT
public:
    PacerWorker() = default;

    void Stop() { m_run = false; }
    bool IsRunning() const;

    virtual void Tick() = 0;

private:
    void run() override;

    bool m_run = true;
};
