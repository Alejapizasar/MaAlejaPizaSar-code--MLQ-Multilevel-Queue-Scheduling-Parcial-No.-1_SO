#include <iostream>
#include <filesystem>
#include "FileManager.h"
#include "MLQScheduler.h"
#include "Metrics.h"

namespace fs = std::filesystem;

int main()
{
    const std::string inputDir = "input";
    const std::string outputDir = "output";

    if (!fs::exists(inputDir) || !fs::is_directory(inputDir))
    {
        std::cerr << "Error: no existe la carpeta de entrada '" << inputDir << "'." << std::endl;
        return 1;
    }

    fs::create_directories(outputDir);

    int filesProcessed = 0;

    for (const auto& entry : fs::directory_iterator(inputDir))
    {
        if (!entry.is_regular_file() || entry.path().extension() != ".txt")
        {
            continue;
        }

        std::string inputPath = entry.path().string();
        std::string baseName = entry.path().stem().string(); // filename without extension
        std::string outputPath = outputDir + "/" + baseName + "_result.txt";

        std::cout << "Procesando: " << inputPath << " ..." << std::endl;

        try
        {
            std::vector<Process> processes = FileManager::readProcesses(inputPath);

            if (processes.empty())
            {
                std::cerr << "  Advertencia: '" << inputPath << "' no contiene procesos validos. Se omite." << std::endl;
                continue;
            }

            MLQScheduler mlq(processes);
            mlq.run();

            AverageMetrics averages = Metrics::calculateAverages(processes);

            FileManager::writeResults(
                outputPath,
                processes,
                averages.waitingTime,
                averages.completionTime,
                averages.responseTime,
                averages.turnaroundTime
            );

            std::cout << "  -> Resultado escrito en: " << outputPath << std::endl;
            std::cout << Metrics::formatReport(processes, averages) << std::endl;

            filesProcessed++;
        }
        catch (const std::exception& e)
        {
            std::cerr << "  Error procesando '" << inputPath << "': " << e.what() << std::endl;
        }
    }

    if (filesProcessed == 0)
    {
        std::cerr << "No se proceso ningun archivo .txt en '" << inputDir << "'." << std::endl;
        return 1;
    }

    std::cout << "Listo. " << filesProcessed << " archivo(s) procesado(s) correctamente." << std::endl;
    return 0;
}
