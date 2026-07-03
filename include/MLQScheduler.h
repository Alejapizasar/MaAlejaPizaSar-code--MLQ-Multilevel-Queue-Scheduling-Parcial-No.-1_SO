#pragma once

#include <vector>
#include "RoundRobinScheduler.h"
#include "PriorityScheduler.h"

/**
 * @class MLQScheduler
 * @brief Coordinates the three queues of the Multilevel Queue algorithm,
 *        enforcing strict priority between them and managing the system clock.
 *
 * Responsibility: decide WHICH queue dispatches next (Queue 1 > Queue 2 >
 * Queue 3, strictly), and handle processes that arrive at different times.
 * It does NOT implement any dispatching logic itself — that is delegated
 * to RoundRobinScheduler / PriorityScheduler (composition).
 */
class MLQScheduler
{
private:
    RoundRobinScheduler cola1;   // Queue 1: Round Robin, quantum = 3
    RoundRobinScheduler cola2;   // Queue 2: Round Robin, quantum = 5
    PriorityScheduler cola3;     // Queue 3: Priority Scheduling

    // Processes that haven't "arrived" yet, sorted by arrivalTime.
    // stable_sort preserves original relative order on arrivalTime ties.
    std::vector<Process*> pendingArrivals;

    double systemClock;

    // Moves any process whose arrivalTime <= currentTime from
    // pendingArrivals into its corresponding queue (1, 2 or 3).
    void releaseArrivals(double currentTime);

    // Returns the arrivalTime of the next process that hasn't arrived yet.
    // Precondition: pendingArrivals is not empty.
    double getNextArrivalTime() const;

public:
    // Receives the full list of processes to schedule (owned externally,
    // e.g. by FileManager / main.cpp). MLQScheduler only holds pointers
    // into it, it does not copy or own the Process objects.
    explicit MLQScheduler(std::vector<Process>& processes);

    // Runs the full simulation until every process has finished.
    // After this returns, each Process has its metrics
    // (WT, CT, RT, TAT) already calculated.
    void run();
};
