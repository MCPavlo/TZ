cmake_minimum_required(VERSION 3.30)
project(SquareTZ)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 REQUIRED system window graphics network)
find_package(CURL REQUIRED)
find_package(JsonCpp REQUIRED)

add_executable(SquareTZ
        src/main.cpp
        src/square.cpp
        src/api.cpp
        src/utils.cpp
)

target_include_directories(SquareTZ PUBLIC
        include
        ${SFML_INCLUDE_DIR}
        ${CURL_INCLUDE_DIR}
        ${JsonCpp_INCLUDE_DIR}
)

target_link_libraries(SquareTZ
        sfml-main
        sfml-system
        sfml-window
        sfml-graphics
        sfml-network
        sfml-audio
        JsonCpp::JsonCpp
        CURL::libcurl
)