cmake_minimum_required(VERSION 3.21)
project(DiorDo)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
include_directories(src/FCFS)

add_executable(DiorDo
        src/FCFS/FcfsScheduler.cpp
        src/FCFS/FcfsScheduler.h
        src/Dispatcher.cpp
        src/Dispatcher.h
        src/Scheduler.h
        src/Task.h
        logging/logging.h
        test/DiorDo_test.cpp)

target_link_libraries(DiorDo pthread)