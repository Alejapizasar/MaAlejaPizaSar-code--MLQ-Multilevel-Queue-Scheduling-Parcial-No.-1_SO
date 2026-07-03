#include "Scheduler.h"

void Scheduler::addProcess(Process* process)
{
    readyQueue.push_back(process);
}

bool Scheduler::hasProcessesReady() const
{
    return !readyQueue.empty();
}
