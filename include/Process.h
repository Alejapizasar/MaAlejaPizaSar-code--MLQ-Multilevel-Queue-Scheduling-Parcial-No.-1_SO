#pragma once

#include <string>

enum class ProcessState
{
    NEW,
    READY,
    RUNNING,
    FINISHED
};

class Process
{
private:
    std::string label;
    double burstTime;
    double remainingTime;
    double arrivalTime;
    int queue;
    int priority;

    double waitingTime;
    double completionTime;
    double responseTime;
    double turnaroundTime;

    ProcessState state;

public:
    Process(
        const std::string& label,
        double burstTime,
        double arrivalTime,
        int queue,
        int priority
    );

    const std::string& getLabel() const;

    double getBurstTime() const;
    double getRemainingTime() const;
    double getArrivalTime() const;
    int getQueue() const;
    int getPriority() const;

    double getWaitingTime() const;
    double getCompletionTime() const;
    double getResponseTime() const;
    double getTurnaroundTime() const;

    ProcessState getState() const;

    void setRemainingTime(double remainingTime);
    void setWaitingTime(double waitingTime);
    void setCompletionTime(double completionTime);
    void setResponseTime(double responseTime);
    void setTurnaroundTime(double turnaroundTime);
    void setState(ProcessState state);

    void execute(double timeSlice);

    bool isFinished() const;

    void reset();
};
