#include "RoundRobinScheduler.h"

RoundRobinScheduler::RoundRobinScheduler(double quantum)
    : quantum(quantum)
{
}

double RoundRobinScheduler::dispatchNext(double currentTime)
{
    // Take the process at the front of the queue (classic FIFO for RR).
    Process* process = readyQueue.front();
    readyQueue.pop_front();

    // Record response time only the first time this process ever runs.
    if (process->getResponseTime() == -1)
    {
        process->setResponseTime(currentTime - process->getArrivalTime());
    }

    process->setState(ProcessState::RUNNING);

    // Run for the quantum, or for whatever is left if less than a full quantum.
    double runTime = (process->getRemainingTime() < quantum)
        ? process->getRemainingTime()
        : quantum;

    process->execute(runTime);
    double newTime = currentTime + runTime;

    if (process->isFinished())
    {
        process->setCompletionTime(newTime);
        process->setTurnaroundTime(newTime - process->getArrivalTime());
        process->setWaitingTime(process->getTurnaroundTime() - process->getBurstTime());
        process->setState(ProcessState::FINISHED);
    }
    else
    {
        // Didn't finish: goes back to the end of the line.
        process->setState(ProcessState::READY);
        readyQueue.push_back(process);
    }

    return newTime;
}
