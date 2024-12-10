#pragma once
#include <string>

struct ApiCounters {
    int timeApiCalls;
    int temperatureApiCalls;
};

extern ApiCounters apiCounters;


std::string getCurrentTime();
std::string getCurrentTemperature();