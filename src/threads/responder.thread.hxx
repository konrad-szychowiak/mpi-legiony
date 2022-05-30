//
// Created by konrad on 18.04.2022.
//

#ifndef LEGIONY_RESPONDER_THREAD_HXX
#define LEGIONY_RESPONDER_THREAD_HXX

#include <iostream>
#include <unistd.h>
#include <mpi.h>

#include "../classes/process-info.hxx"
#include "../helpers/mpi.hxx"

void
handleQuestion(message::MSGContent *question, ProcessInfo *process)
{
  int declaredUsage = 0;
  printf("\033[34m[r%d:t%d:s%d <<< r%d:t%d:question]\033[0m Asked about %d, mine is %d\n",
         process->rank, process->time->getTime(), process->status, question->rank, question->time,
         question->trailIndex + 1,
         process->trail->getId()
  );

  bool isAboutMyTrail = process->trail != nullptr && process->trail->getId() == question->trailIndex + 1;

  if (process->status == ProcessStatus::IN_LOCAL)
  {
    declaredUsage = 0;
    // printf("\033[37m[r%d:t%d:s%d:usage]\033[0m I'm in local; usage = %d\n",
    //        process->rank, process->time->getTime(), process->status, declaredUsage
    // );
  }

  if (process->status == ProcessStatus::IN_CRITICAL)
  {
    declaredUsage = isAboutMyTrail ? process->legion->getSize() : 0;
    // printf("\033[37m[r%d:t%d:s%d:usage]\033[0m I'm in Critical; usage = %d\n",
    //        process->rank, process->time->getTime(), process->status, declaredUsage
    // );
  }

  if (process->status == ProcessStatus::CONCURRING)
  {
    if (!isAboutMyTrail)
    { declaredUsage = 0; }
    else
    {
      if (process->requestPriority->time == question->time)
      {
        declaredUsage = process->rank < question->rank
                        ? process->legion->getSize()
                        : 0;
      }
      else if (process->requestPriority->time < question->time)
      { declaredUsage = process->legion->getSize(); }
      else
      { declaredUsage = 0; }
    }
    // printf("\033[37m[r%d:t%d:s%d:usage]\033[0m I'm also concurring; usage = %d\n",
    //        process->rank, process->time->getTime(), process->status, declaredUsage
    // );
  }

  auto answer = message::answer(
      process->time->getTime(),
      process->rank,
      question->trailIndex,
      declaredUsage
  );

  lock(&process->responseCtl);
  process->time->increment();
  printf("\033[35m[r%d:t%d:s%d >>> r:%d]\033[0m My usage of %d is %d\n",
         process->rank, process->time->getTime(), process->status, question->rank,
         question->trailIndex + 1,
         declaredUsage
  );
  MPI_Send(&answer, message::size, MPI_INT, question->rank, MSG_ANSWER, MPI_COMM_WORLD);
  unlock(&process->responseCtl);
}

void
handleAnswer(message::MSGContent *answer, ProcessInfo *process)
{
  printf("\033[33m[r%d:t%d:s%d <<< r%d:t%d:answer]\033[0m Their usage of %d is %d\n",
         process->rank, process->time->getTime(), process->status, answer->rank, answer->time,
         answer->trailIndex + 1,
         answer->trailUsage
  );

  if (process->trail == nullptr)
  { return; }

  if (process->status != ProcessStatus::CONCURRING)
  { return; }

  if (answer->trailIndex + 1 != process->trail->getId())
  { return; }

  if (process->responses.at(answer->rank) == -1)
  { process->responseCount++; }

  process->responses.erase(answer->rank);
  process->responses.insert(std::pair<int, int>(answer->rank, answer->trailUsage));

  if (process->responseCount == process->networkSize - 1)
  {
    int currentUsage = 0;

    for (auto x: process->responses)
    {
      currentUsage += x.second;
    }

    if (process->legion->getSize() <= process->trail->getMaxThroughput() - currentUsage)
    {
      printf("\033[32m[r%d:t%d:s%d]\033[0m Entering trail %d with my %d legionaries, %d of %d was being used\n",
             process->rank, process->time->getTime(), process->status,
             answer->trailIndex + 1,
             process->legion->getSize(),
             currentUsage,
             process->trail->getMaxThroughput()
      );
      process->wakeUp();
      return;
    }
    printf("\033[31m[r%d:t%d:s%d]\033[0m CANNOT enter trail %d with my %d legionaries, %d of %d was being used\n",
           process->rank, process->time->getTime(), process->status,
           answer->trailIndex + 1,
           process->legion->getSize(),
           currentUsage,
           process->trail->getMaxThroughput()
    );
  }
}

void
responderThread(ProcessInfo *process)
{
  // printf("\033[32m[r%d:t%d:s%d]\033[0m Selected legion is %d with size %d\n",
  //        process->rank, process->time->getTime(), process->status,
  //        process->legion->getId(),
  //        process->legion->getSize()
  // );

  while (true)
//  for (int i = 0; i < 3; i++)
//  if (process->rank == 1)
  {
    message::MSGContent message = message::placeholderMessage;
    MPI_Status status;

    MPI_Recv(&message, message::size, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    int time = message.time;
    auto receivedTime = LamportClock::startFrom(time);
    process->time->synchronise(receivedTime);
    delete receivedTime;

    switch (status.MPI_TAG)
    {
      case MSG_QUESTION:
        handleQuestion(&message, process);
        break;

      case MSG_ANSWER:
        handleAnswer(&message, process);
        break;
    }
  }
}

#endif //LEGIONY_RESPONDER_THREAD_HXX
