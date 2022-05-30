cmake_minimum_required(VERSION 3.17)
project(legiony)

set(CMAKE_CXX_STANDARD 20)

add_executable(legiony src/main.cpp src/threads/main.thread.hxx src/threads/responder.thread.hxx src/config.hpp src/classes/legion.hxx src/classes/trail.hxx src/classes/lamport-clock.hxx src/classes/priority.hxx src/helpers/status.hxx src/classes/process-info.hxx src/helpers/pthread.hxx src/helpers/mpi.hxx)
