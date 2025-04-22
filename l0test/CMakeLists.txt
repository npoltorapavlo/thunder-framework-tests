cmake_minimum_required(VERSION 3.14)

project(l0test)

set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)
FetchContent_MakeAvailable(googletest)

find_package(Thunder NAMES WPEFramework Thunder)
find_package(${NAMESPACE}Core REQUIRED)

add_executable(${PROJECT_NAME}
        Module.cpp
        JsonTest.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        gmock_main
        ${NAMESPACE}Core::${NAMESPACE}Core
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
