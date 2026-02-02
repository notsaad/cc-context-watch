cmake_minimum_required(VERSION 3.14)
project(cc-context-watch LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(json)

add_executable(cc-context-watch src/main.cpp)
target_link_libraries(cc-context-watch PRIVATE nlohmann_json::nlohmann_json)
