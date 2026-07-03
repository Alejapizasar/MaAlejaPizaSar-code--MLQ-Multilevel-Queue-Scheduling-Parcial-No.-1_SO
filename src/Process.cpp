#include "Process.h"

Process::Process(
    const std::string& label,
    double burstTime,
    double arrivalTime,
    int queue,
    int priority
)
    : label(label),
        burstTime(burstTime),
        remainingTime(burstTime),
        arrivalTime(arrivalTime),
        queue(queue),
        priority(priority),
        waitingTime(0),
        completionTime(0),
        responseTime(-1),
        turnaroundTime(0),
        state(ProcessState::NEW)
{
}

// --- Getters ---

const std::string& Process::getLabel() const
{
    return label;
}

double Process::getBurstTime() const
{
    return burstTime;
}

double Process::getRemainingTime() const
{
    return remainingTime;
}

double Process::getArrivalTime() const
{
    return arrivalTime;
}

int Process::getQueue() const
{
    return queue;
}

int Process::getPriority() const
{
    return priority;
}

double Process::getWaitingTime() const
{
    return waitingTime;
}

double Process::getCompletionTime() const
{
    return completionTime;
}

double Process::getResponseTime() const
{
    return responseTime;
}

double Process::getTurnaroundTime() const
{
    return turnaroundTime;
}

ProcessState Process::getState() const
{
    return state;
}

// --- Setters ---

void Process::setRemainingTime(double remainingTime)
{
    this->remainingTime = remainingTime;
}

void Process::setWaitingTime(double waitingTime)
{
    this->waitingTime = waitingTime;
}

void Process::setCompletionTime(double completionTime)
{
    this->completionTime = completionTime;
}

void Process::setResponseTime(double responseTime)
{
    this->responseTime = responseTime;
}

void Process::setTurnaroundTime(double turnaroundTime)
{
    this->turnaroundTime = turnaroundTime;
}

void Process::setState(ProcessState state)
{
    this->state = state;
}

// --- Behavior ---

void Process::execute(double timeSlice)
{
    remainingTime -= timeSlice;

    if (remainingTime < 0)
    {
        remainingTime = 0;
    }
}

bool Process::isFinished() const
{
    return remainingTime <= 0;
}

void Process::reset()
{
    remainingTime = burstTime;
    waitingTime = 0;
    completionTime = 0;
    responseTime = -1;
    turnaroundTime = 0;
    state = ProcessState::NEW;
}