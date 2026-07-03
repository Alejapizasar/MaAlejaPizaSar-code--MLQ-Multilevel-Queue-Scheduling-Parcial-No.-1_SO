#pragma once

#include "Scheduler.h"

/**
 * @class PriorityScheduler
 * @brief Concrete Scheduler implementing non-preemptive Priority Scheduling.
 *
 * Responsibility: among all processes ready in this queue, dispatch the
 * one with the highest priority (5 = highest, 1 = lowest). Once dispatched,
 * it runs to completion without being interrupted (non-preemptive) — there
 * is no quantum and no re-enqueueing.
 *
 * Tie-break rule: if two processes share the same priority, the one that
 * arrived earlier (or was inserted first, in case of an exact tie) wins.
 */
class PriorityScheduler : public Scheduler
{
public:
    double dispatchNext(double currentTime) override;
};
