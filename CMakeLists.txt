cmake_minimum_required(VERSION 3.17)
project(ants-vs-some-bees)

set(CMAKE_CXX_STANDARD 14)

add_executable(AvSB driver.cpp Game.cpp Game.h Unit/Unit.cpp Unit/Unit.h Unit/Ant/Ant.cpp Unit/Ant/Ant.h Unit/Ant/Thrower.cpp Unit/Ant/Thrower.h ActionType.h Space.cpp Space.h Unit/Bee/Bee.cpp Unit/Bee/Bee.h Unit/Ant/Ninja.cpp Unit/Ant/Ninja.h Unit/Bee/BasicBee.cpp Unit/Bee/BasicBee.h Unit/Ant/Bodyguard.cpp Unit/Ant/Bodyguard.h)