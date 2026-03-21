cmake_minimum_required(VERSION 3.28)
project(Silnik2D LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(Silnik2D src/main.cpp)
target_compile_features(Silnik2D PRIVATE cxx_std_17)
target_link_libraries(Silnik2D PRIVATE
	SFML::Graphics
	SFML::Window
	SFML::System
	SFML::Audio
	SFML::Network
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Silnik2D)