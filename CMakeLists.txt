cmake_minimum_required(VERSION 3.17)
project(ants-vs-some-bees)

set(CMAKE_CXX_STANDARD 14)

add_executable(5 driver.cpp Game.cpp Game.h Unit/Unit.cpp Unit/Unit.h Unit/Ant/Ant.cpp Unit/Ant/Ant.h)