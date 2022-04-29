//
// Created by konrad on 29.04.22.
//

#ifndef LEGIONY_PROCESS_INFO_HXX
#define LEGIONY_PROCESS_INFO_HXX


#include <map>
#include "../helpers/status.hxx"
#include "legion.hxx"
#include "trail.hxx"
#include "lamport-clock.hxx"
#include "priority.hxx"


class ProcessInfo
{
public:
  int rank;
  int networkSize;
  Legion *legion = nullptr;
  Trail *trail = nullptr;
  LamportClock *time = nullptr;
  Priority *requestPriority;
  ProcessStatus status;
  int responsesCount = 0;
  std::map<int, int> responses;

  ProcessInfo(int mpiRank, int mpiNetworkSize, Legion *assignedLegion)
      : rank(mpiRank), networkSize(mpiNetworkSize)
  {
    this->legion = assignedLegion;
    this->time = new LamportClock();
  }
};

#endif //LEGIONY_PROCESS_INFO_HXX
