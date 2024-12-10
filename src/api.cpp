#include "api.h"
#include <curl/curl.h>
#include <json/json.h>
#include <string>




ApiCounters apiCounters = {0, 0};

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


std::string getCurrentTemperature() {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://api.openweathermap.org/data/2.5/weather?q=London,uk&appid=7d3179a5df486f0b8666d10ebc77ee0f&units=metric");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res == CURLE_OK) {
            Json::Value jsonData;
            Json::Reader reader;
            if (reader.parse(readBuffer, jsonData)) {
                apiCounters.temperatureApiCalls++; // Increment counter
                return std::to_string(jsonData["main"]["temp"].asFloat());
            }
        }
    }
    return "N/A";
}

std::string getCurrentTime() {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://timeapi.io/api/time/current/zone?timeZone=Europe%2FLondon");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res == CURLE_OK) {
            Json::Value jsonData;
            Json::Reader reader;
            if (reader.parse(readBuffer, jsonData)) {
                apiCounters.timeApiCalls++; // Increment counter
                int hour = jsonData["hour"].asInt();
                int minute = jsonData["minute"].asInt();
                int seconds = jsonData["seconds"].asInt();

                char buffer[128];
                snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d", hour, minute, seconds);
                return std::string(buffer);
            }
        }
    }

    return "N/A";
}