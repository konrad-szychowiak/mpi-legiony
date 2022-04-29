//
// Created by konrad on 18.04.2022.
//

#ifndef LEGIONY_MAIN_THREAD_HXX
#define LEGIONY_MAIN_THREAD_HXX

#include <random>
#include <functional>
#include <chrono>
#include "../helpers/status.hxx"
#include "../classes/process-info.hxx"
#include "../config.hpp"

void mainThread(ProcessInfo *process)
{
  std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> distribution(0, (const int) std::size(trails) - 1);
  auto randomTrailId = [&distribution, &generator]
  { return distribution(generator); };
  auto randomTrail = [&randomTrailId]()
  { return trails[randomTrailId()]; };


  std::cout << "Hi!\n";
  std::cout << "I am " << process->rank << " (out of " << process->networkSize << ")" << "\n";
  std::cout << "My legion is " << process->legion->getId() << ", and its size is " << process->legion->getSize()
            << "\n";

// begin while
  {
    process->status = ProcessStatus::IN_LOCAL;
//    wait

    process->status = ProcessStatus::CONCURRING;
    // todo: proces.odpowiedzi[nadawca] <- undefined
    // proces.ileZabranychOdpowiedzi <- 0
    // save priority
    // proces.wybrany_trakt <- losowy trakt ze zbioru T
    auto trail = randomTrail();
    process->trail = trail;
    process->requestPriority = Priority::from(process->time, process->rank);
    process->responsesCount = 0;
    std::cout << "selected trail is: " << trail->getId() << " with " << trail->getMaxThroughput() << "\n";

    // sleep on var

    // wake up
    process->status = ProcessStatus::IN_CRITICAL;

  }
// end while
}

#endif //LEGIONY_MAIN_THREAD_HXX
