cmake_minimum_required(VERSION 3.27)
project(Producer_consumer_problem)

set(CMAKE_CXX_STANDARD 17)

add_executable(Producer_consumer_problem main.cpp
        BlockingQueue.hpp
        Consumer.hpp
        Producer.hpp
        Task.hpp
        utilities/UniqueIDGenerator.hpp
        utilities/SafeCout.hpp)
