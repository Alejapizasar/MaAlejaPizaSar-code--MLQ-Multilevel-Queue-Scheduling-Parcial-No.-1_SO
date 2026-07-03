#include "Metrics.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>

AverageMetrics Metrics::calculateAverages(const std::vector<Process>& processes)
{
    if (processes.empty())
    {
        throw std::runtime_error("No hay procesos para calcular metricas.");
    }

    double wtSum = 0.0;
    double ctSum = 0.0;
    double rtSum = 0.0;
    double tatSum = 0.0;

    for (const Process& p : processes)
    {
        wtSum += p.getWaitingTime();
        ctSum += p.getCompletionTime();
        rtSum += p.getResponseTime();
        tatSum += p.getTurnaroundTime();
    }

    double n = static_cast<double>(processes.size());

    AverageMetrics averages;
    averages.waitingTime = wtSum / n;
    averages.completionTime = ctSum / n;
    averages.responseTime = rtSum / n;
    averages.turnaroundTime = tatSum / n;

    return averages;
}

std::string Metrics::formatReport(
    const std::vector<Process>& processes,
    const AverageMetrics& averages
)
{
    std::ostringstream report;
    report << std::fixed << std::setprecision(2);

    report << "=== Reporte de Planificacion MLQ ===\n\n";
    report << "Etiqueta\tBT\tAT\tQ\tPr\tWT\tCT\tRT\tTAT\n";

    for (const Process& p : processes)
    {
        report << p.getLabel() << "\t"
                << p.getBurstTime() << "\t"
                << p.getArrivalTime() << "\t"
                << p.getQueue() << "\t"
                << p.getPriority() << "\t"
                << p.getWaitingTime() << "\t"
                << p.getCompletionTime() << "\t"
                << p.getResponseTime() << "\t"
                << p.getTurnaroundTime() << "\n";
    }

    report << "\n";
    report << "WT promedio:  " << averages.waitingTime << "\n";
    report << "CT promedio:  " << averages.completionTime << "\n";
    report << "RT promedio:  " << averages.responseTime << "\n";
    report << "TAT promedio: " << averages.turnaroundTime << "\n";

    return report.str();
}
