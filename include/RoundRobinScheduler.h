#pragma once

#include "Scheduler.h"

/**
 * @class RoundRobinScheduler
 * @brief Concrete Scheduler implementing Round Robin with a fixed quantum.
 *
 * Responsibility: dispatch the process at the front of the ready queue,
 * run it for at most `quantum` time units, and re-enqueue it at the back
 * if it didn't finish. The same class is reused for Queue 1 (quantum=3)
 * and Queue 2 (quantum=5) by simply constructing it with different values.
 */
class RoundRobinScheduler : public Scheduler
{
private:
    double quantum;

public:
    explicit RoundRobinScheduler(double quantum);

    double dispatchNext(double currentTime) override;
};
