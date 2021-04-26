#include "pacerworker.h"

void PacerWorker::run()
{
    m_run = true;
    while(m_run)
    {
        Tick();
        msleep(1);
    }
    quit();
}