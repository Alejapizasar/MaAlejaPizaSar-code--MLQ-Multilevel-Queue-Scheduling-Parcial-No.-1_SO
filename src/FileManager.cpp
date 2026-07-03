#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

std::string FileManager::trim(const std::string& text)
{
    size_t start = text.find_first_not_of(" \t\r\n");
    if (start == std::string::npos)
    {
        return "";
    }
    size_t end = text.find_last_not_of(" \t\r\n");
    return text.substr(start, end - start + 1);
}

std::vector<std::string> FileManager::split(const std::string& text, char delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream ss(text);
    std::string token;

    while (std::getline(ss, token, delimiter))
    {
        tokens.push_back(trim(token));
    }

    return tokens;
}

std::vector<Process> FileManager::readProcesses(const std::string& inputPath)
{
    std::ifstream file(inputPath);
    if (!file.is_open())
    {
        throw std::runtime_error("No se pudo abrir el archivo de entrada: " + inputPath);
    }

    std::vector<Process> processes;
    std::string line;

    while (std::getline(file, line))
    {
        std::string cleanLine = trim(line);

        // Skip empty lines and comments.
        if (cleanLine.empty() || cleanLine[0] == '#')
        {
            continue;
        }

        std::vector<std::string> fields = split(cleanLine, ';');

        if (fields.size() != 5)
        {
            // Malformed line: skip it rather than crashing the whole run.
            continue;
        }

        std::string label = fields[0];
        double burstTime = std::stod(fields[1]);
        double arrivalTime = std::stod(fields[2]);
        int queue = std::stoi(fields[3]);
        int priority = std::stoi(fields[4]);

        processes.emplace_back(label, burstTime, arrivalTime, queue, priority);
    }

    file.close();
    return processes;
}

void FileManager::writeResults(
    const std::string& outputPath,
    const std::vector<Process>& processes,
    double wtAverage,
    double ctAverage,
    double rtAverage,
    double tatAverage
)
{
    std::ofstream file(outputPath);
    if (!file.is_open())
    {
        throw std::runtime_error("No se pudo crear el archivo de salida: " + outputPath);
    }

    file << std::fixed << std::setprecision(2);

    for (const Process& p : processes)
    {
        file << p.getLabel() << ";"
              << p.getBurstTime() << ";"
              << p.getArrivalTime() << ";"
              << p.getQueue() << ";"
              << p.getPriority() << ";"
              << p.getWaitingTime() << ";"
              << p.getCompletionTime() << ";"
              << p.getResponseTime() << ";"
              << p.getTurnaroundTime() << "\n";
    }

    file << "\n";
    file << "WT promedio: " << wtAverage << "\n";
    file << "CT promedio: " << ctAverage << "\n";
    file << "RT promedio: " << rtAverage << "\n";
    file << "TAT promedio: " << tatAverage << "\n";

    file.close();
}
