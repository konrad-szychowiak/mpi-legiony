//
// Created by konrad on 18.04.2022.
//

#ifndef LEGIONY_MAIN_THREAD_HXX
#define LEGIONY_MAIN_THREAD_HXX

#include <random>
#include <functional>
#include <chrono>
#include <array>
#include <unistd.h>
#include <mpi.h>

#include "../classes/trail.hxx"
#include "../helpers/status.hxx"
#include "../classes/process-info.hxx"
#include "../config.hpp"
#include "../helpers/mpi.hxx"

void mainThread(ProcessInfo *process)
{
  std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> distribution(0, (const int) sizeof(trails) / sizeof(Trail) - 1);
  auto randomTrailId = [&distribution, &generator]
  { return distribution(generator); };


  while (true)
  {
    for (int i = 1; i < process->networkSize; i++)
    {
      int otherNodeIndex = (process->rank + i) % process->networkSize;
      process->responses.erase(otherNodeIndex);
      process->responses.insert(std::pair<int, int>(otherNodeIndex, -1));
    }

    auto trailIndex = randomTrailId();
    auto trail = trails[trailIndex];
    process->trail = trail;
    process->requestPriority = Priority::from(process->time, process->rank);
    process->responseCount = 0;

    printf("\033[32m[r%d:t%d:s%d]\033[0m New life!\n",
           process->rank, process->time->getTime(), process->status
    );

    printf("\033[32m[r%d:t%d:s%d]\033[0m Selected trail is %d with max throughput %d\n",
           process->rank, process->time->getTime(), process->status,
           trail->getId(),
           trail->getMaxThroughput()
    );

    process->status = ProcessStatus::IN_LOCAL;
    sleep(randomTrailId());


    process->status = ProcessStatus::CONCURRING;
    // todo: proces.odpowiedzi[nadawca] <- undefined

    auto question = message::question(
        process->requestPriority->time,
        process->requestPriority->rank,
        trailIndex
    );

    lock(&process->responseCtl);
    process->time->increment();
    for (int i = 1; i < process->networkSize; i++)
    {
      int otherNodeIndex = (process->rank + i) % process->networkSize;
      printf("\033[36m[r%d:t%d:s%d >>> r%d]\033[0m Informing about exit and free resources\n",
             process->rank, process->time->getTime(), process->status, otherNodeIndex
      );
      MPI_Send(&question, message::size, MPI_INT, otherNodeIndex, MSG_QUESTION, MPI_COMM_WORLD);
    }
    unlock(&process->responseCtl);

    // wait for go-signal
    process->sleep();
    // wake up

    process->status = ProcessStatus::IN_CRITICAL;
    sleep(randomTrailId());


    auto resourceFreed = message::answer(
        process->requestPriority->time,
        process->requestPriority->rank,
        trailIndex,
        0
    );

    lock(&process->responseCtl);
    process->time->increment();
    for (int i = 1; i < process->networkSize; i++)
    {
      int otherNodeIndex = (process->rank + i) % process->networkSize;
      MPI_Send(&resourceFreed, message::size, MPI_INT, otherNodeIndex, MSG_ANSWER, MPI_COMM_WORLD);
    }
    unlock(&process->responseCtl);
    // sprzątamy po sobie
//    process->trail = nullptr;
  }
// end while
}

#endif //LEGIONY_MAIN_THREAD_HXX
