cmake_minimum_required(VERSION 3.21)
project(DiorDo)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
include_directories(src/FCFS)
include_directories(logging)

add_executable(test_DiorDo
        src/FCFS/FcfsScheduler.cpp
        src/FCFS/FcfsScheduler.h
        src/Dispatcher.cpp
        src/Dispatcher.h
        src/SchedulerBase.h
        src/Task.h
        logging/logging.h
        test/test_DiorDo.cpp src/SchedulerNonPreemptive.h)

add_executable(test_Task
        src/FCFS/FcfsScheduler.cpp
        src/FCFS/FcfsScheduler.h
        src/Dispatcher.cpp
        src/Dispatcher.h
        src/SchedulerBase.h
        src/Task.h
        logging/logging.h
        test/test_Task.cpp)

target_link_libraries(test_DiorDo pthread)
target_link_libraries(test_Task pthread)