#pragma once

#include <string>
#include <vector>
#include "Process.h"

/**
 * @struct AverageMetrics
 * @brief Groups the four average metrics together, so they can be passed
 *        around as a single value instead of four loose doubles.
 */
struct AverageMetrics
{
    double waitingTime;
    double completionTime;
    double responseTime;
    double turnaroundTime;
};

/**
 * @class Metrics
 * @brief Calculates aggregate statistics over a set of already-scheduled
 *        processes, and formats them for display.
 *
 * Responsibility: turn a vector<Process> (with metrics already computed
 * by the schedulers) into summary statistics. Does not know anything
 * about scheduling algorithms or file I/O.
 */
class Metrics
{
public:
    // Calculates the average WT, CT, RT and TAT across all processes.
    static AverageMetrics calculateAverages(const std::vector<Process>& processes);

    // Produces a human-readable summary report (for console output,
    // logs, or embedding in documentation).
    static std::string formatReport(
        const std::vector<Process>& processes,
        const AverageMetrics& averages
    );
};
