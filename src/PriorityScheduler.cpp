#include "PriorityScheduler.h"
#include <algorithm>

double PriorityScheduler::dispatchNext(double currentTime)
{
    // Find the process with the highest priority.
    // Comparator uses strict '<' so that, on an exact tie (same priority),
    // std::max_element keeps the FIRST one found — which, since the queue
    // preserves insertion order, is the one that arrived/was enqueued first.
    auto it = std::max_element(
        readyQueue.begin(),
        readyQueue.end(),
        [](Process* a, Process* b) {
            return a->getPriority() < b->getPriority();
        }
    );

    Process* process = *it;
    readyQueue.erase(it);

    if (process->getResponseTime() == -1)
    {
        process->setResponseTime(currentTime - process->getArrivalTime());
    }

    process->setState(ProcessState::RUNNING);

    // Non-preemptive: run the FULL remaining burst in one go.
    double runTime = process->getRemainingTime();
    process->execute(runTime);
    double newTime = currentTime + runTime;

    // isFinished() will always be true here, since we ran the full
    // remaining time — Priority (non-preemptive) never partially runs.
    process->setCompletionTime(newTime);
    process->setTurnaroundTime(newTime - process->getArrivalTime());
    process->setWaitingTime(process->getTurnaroundTime() - process->getBurstTime());
    process->setState(ProcessState::FINISHED);

    return newTime;
}
