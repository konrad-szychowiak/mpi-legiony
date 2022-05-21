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
#include "../classes/trail.hxx"
#include "../helpers/status.hxx"
#include "../classes/process-info.hxx"
#include "../config.hpp"

void mainThread(ProcessInfo *process)
{
  std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> distribution(0, (const int) sizeof(trails) / sizeof(Trail) - 1);
  auto randomTrailId = [&distribution, &generator]
  { return distribution(generator); };
  auto randomTrail = [&randomTrailId]()
  { return trails[randomTrailId()]; };


// begin while
  {
    process->status = ProcessStatus::IN_LOCAL;
    sleep(1);

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


    process->sleep();


    // wake up
    process->status = ProcessStatus::IN_CRITICAL;
    sleep(1);

  }
// end while
}

#endif //LEGIONY_MAIN_THREAD_HXX
