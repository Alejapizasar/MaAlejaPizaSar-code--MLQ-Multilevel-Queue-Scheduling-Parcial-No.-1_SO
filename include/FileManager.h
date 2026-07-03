#pragma once

#include <string>
#include <vector>
#include "Process.h"

/**
 * @class FileManager
 * @brief Handles all file I/O: reading process definitions from an input
 *        file, and writing scheduling results to an output file.
 *
 * Responsibility: isolate ALL file reading/writing in one place. If the
 * input/output format ever changes, only this class needs to change.
 * Stateless utility class (all methods static) since no instance data
 * needs to persist between calls.
 */
class FileManager
{
public:
    // Reads process definitions from a text file with the format:
    //   Label;BurstTime;ArrivalTime;Queue;Priority
    // Ignores empty lines, lines starting with '#', and surrounding whitespace.
    static std::vector<Process> readProcesses(const std::string& inputPath);

    // Writes the final results (one row per process, plus averages) to a
    // text file. Averages are passed in already calculated (by Metrics),
    // keeping FileManager decoupled from how they are computed.
    static void writeResults(
        const std::string& outputPath,
        const std::vector<Process>& processes,
        double wtAverage,
        double ctAverage,
        double rtAverage,
        double tatAverage
    );

private:
    // Removes leading/trailing whitespace from a string.
    static std::string trim(const std::string& text);

    // Splits a string by a delimiter character into a vector of tokens.
    static std::vector<std::string> split(const std::string& text, char delimiter);
};
