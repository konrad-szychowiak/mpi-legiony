//
// Created by konrad on 18.04.2022.
//

#ifndef LEGIONY_LAMPORT_CLOCK_HXX
#define LEGIONY_LAMPORT_CLOCK_HXX


class LamportClock
{
private:
  int counter;

  LamportClock(int beginning) : counter(beginning)
  {}

public:
  static LamportClock *
  startFrom(int beginning)
  {
    return new LamportClock(beginning);
  }

  LamportClock() : counter(0)
  {}

  int
  getTime()
  {
    return counter;
  }

  int
  increment()
  {
    ++counter;
    return getTime();
  }

  int
  synchronise(LamportClock *other)
  {
    int mine = this->getTime();
    int their = other->getTime();
    if (their > mine)
    { counter = their; }
    return getTime();
  }
};


#endif //LEGIONY_LAMPORT_CLOCK_HXX
