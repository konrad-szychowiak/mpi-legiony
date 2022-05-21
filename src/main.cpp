#include <mpi.h>
#include <iostream>
#include "threads/main.thread.hxx"
#include "config.hpp"
#include "threads/responder.thread.hxx"

using namespace std;

// todo: sending mutex

/**
 * todo: should start both threads
 * @return
 */
int
main(int argc, char **argv)
{
//  MPI_Init(&argc, &argv);

  int size, rank, given;
  Thread responderThreadHandle;

  MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &given);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);


  auto processInfo = new ProcessInfo(rank, size, legions[rank]);

  pthread_create(&responderThreadHandle, NULL,
                 reinterpret_cast<void *(*)(void *)>(responderThread),
                 processInfo);

  mainThread(processInfo);

  pthread_join(responderThreadHandle, NULL);
  MPI_Finalize();
  return 0;
}

