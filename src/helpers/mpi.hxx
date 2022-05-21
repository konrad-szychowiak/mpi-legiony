//
// Created by konrad on 21.05.22.
//

#ifndef LEGIONY_MPI_HXX
#define LEGIONY_MPI_HXX

#include "../classes/priority.hxx"

#define MSG_QUESTION 1000
#define MSG_ANSWER 2000

namespace message
{
  struct MSGContent
  {
    int time;
    int rank;
    int trailIndex;
    int trailUsage;
  };

  MSGContent placeholderMessage = {0, 0, 0, 0};

  int size = sizeof(MSGContent) / sizeof(int);

  MSGContent question(int time, int rank, int trail)
  {
    MSGContent msg = {time, rank, trail, 0};
    return msg;
  };

  MSGContent answer(int time, int rank, int trail, int usage)
  {
    MSGContent msg = {time, rank, trail, usage};
    return msg;
  };
}


#endif //LEGIONY_MPI_HXX
