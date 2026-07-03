#pragma once

#include <deque>
#include "Process.h"

/**
 * @class Scheduler
 * @brief Abstract base class defining the contract for any CPU scheduling
 *        algorithm used inside a single queue of the MLQ system.
 *
 * Responsibility: define WHAT any scheduler must be able to do
 * (add a process, check if there's work pending, dispatch the next one).
 * It does NOT define HOW dispatching decisions are made — that is left
 * to each concrete subclass (RoundRobinScheduler, PriorityScheduler).
 *
 * This enables polymorphism: MLQScheduler holds Scheduler* pointers and
 * treats all three queues uniformly, without knowing their internal logic.
 */
class Scheduler
{
protected:
    // Processes currently waiting in this queue, ready to run.
    // deque (not plain queue) is used because PriorityScheduler needs to
    // scan/reorder, not just pop from the front like RoundRobin does.
    std::deque<Process*> readyQueue;

public:
    virtual ~Scheduler() = default;

    // Adds a process to this queue's ready list.
    virtual void addProcess(Process* process);

    // True if there is at least one process ready to run in this queue.
    virtual bool hasProcessesReady() const;

    // Selects and runs the next process according to this scheduler's
    // algorithm, advancing the simulation clock as needed.
    // currentTime: the simulation clock at the moment of dispatch.
    // Returns the new simulation clock value after this dispatch.
    virtual double dispatchNext(double currentTime) = 0;
};
