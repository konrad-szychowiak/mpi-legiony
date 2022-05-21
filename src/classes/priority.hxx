//
// Created by konrad on 18.04.2022.
//

#ifndef LEGIONY_PRIORITY_HXX
#define LEGIONY_PRIORITY_HXX


#include "lamport-clock.hxx"

class Priority
{
//private:
public:
  int time;
  int rank;

//public:
  Priority(int _time, int _rank) : time(_time), rank(_rank)
  {}

  static Priority *
  from(LamportClock *lc, int rank)
  {
    return new Priority(lc->getTime(), rank);
  };
};


#endif //LEGIONY_PRIORITY_HXX
