//
// Created by konrad on 18.04.2022.
//

#ifndef LEGIONY_RESPONDER_THREAD_HXX
#define LEGIONY_RESPONDER_THREAD_HXX

#include <iostream>
#include <unistd.h>
#include "../classes/process-info.hxx"

void
responderThread(ProcessInfo *process)
{
  std::cout << "Hi!\n";
  std::cout << "I am " << process->rank << " (out of " << process->networkSize << ")" << "\n";
  std::cout << "My legion is " << process->legion->getId() << ", and its size is " << process->legion->getSize()
            << "\n";

  sleep(1);
  std::cout << "[" << process->rank << "] status: " << process->status << "\n";

  sleep(1);
  std::cout << "[" << process->rank << "] status: " << process->status << "\n";

  process->wakeUp();

  sleep(1);
  std::cout << "[" << process->rank << "] status: " << process->status << "\n";

  sleep(1);
  std::cout << "[" << process->rank << "] status: " << process->status << "\n";
}

#endif //LEGIONY_RESPONDER_THREAD_HXX
