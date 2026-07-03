#include "MLQScheduler.h"
#include <algorithm>

MLQScheduler::MLQScheduler(std::vector<Process>& processes)
    : cola1(3.0),
      cola2(5.0),
      systemClock(0.0)
{
    // Collect pointers to all processes (we never copy Process objects,
    // just reference the ones that live in the caller's vector).
    for (Process& p : processes)
    {
        pendingArrivals.push_back(&p);
    }

    // Sort by arrival time. stable_sort preserves the original relative
    // order (i.e. order of appearance in the input file) for processes
    // that share the same arrivalTime, which is our tie-break convention.
    std::stable_sort(
        pendingArrivals.begin(),
        pendingArrivals.end(),
        [](Process* a, Process* b) {
            return a->getArrivalTime() < b->getArrivalTime();
        }
    );
}

void MLQScheduler::releaseArrivals(double currentTime)
{
    while (!pendingArrivals.empty() &&
           pendingArrivals.front()->getArrivalTime() <= currentTime)
    {
        Process* process = pendingArrivals.front();
        pendingArrivals.erase(pendingArrivals.begin());

        process->setState(ProcessState::READY);

        switch (process->getQueue())
        {
            case 1:
                cola1.addProcess(process);
                break;
            case 2:
                cola2.addProcess(process);
                break;
            case 3:
                cola3.addProcess(process);
                break;
        }
    }
}

double MLQScheduler::getNextArrivalTime() const
{
    return pendingArrivals.front()->getArrivalTime();
}

void MLQScheduler::run()
{
    releaseArrivals(systemClock);

    while (cola1.hasProcessesReady() ||
           cola2.hasProcessesReady() ||
           cola3.hasProcessesReady() ||
           !pendingArrivals.empty())
    {
        if (cola1.hasProcessesReady())
        {
            systemClock = cola1.dispatchNext(systemClock);
        }
        else if (cola2.hasProcessesReady())
        {
            systemClock = cola2.dispatchNext(systemClock);
        }
        else if (cola3.hasProcessesReady())
        {
            systemClock = cola3.dispatchNext(systemClock);
        }
        else
        {
            // All three queues are empty, but processes still haven't
            // arrived. Jump the clock forward instead of simulating idle time.
            systemClock = getNextArrivalTime();
        }

        releaseArrivals(systemClock);
    }
}
