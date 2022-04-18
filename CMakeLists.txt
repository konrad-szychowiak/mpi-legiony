cmake_minimum_required(VERSION 3.21)
project(legiony)

set(CMAKE_CXX_STANDARD 20)

add_executable(legiony src/main.cpp src/threads/main.thread.cxx src/threads/main.thread.hxx src/threads/responder.thread.cxx src/threads/responder.thread.hxx src/process.cxx src/process.hxx src/config.hpp src/classes/legion.cxx src/classes/legion.hxx src/classes/trail.cxx src/classes/trail.hxx src/classes/lamport-clock.cxx src/classes/lamport-clock.hxx src/classes/priority.cxx src/classes/priority.hxx)
