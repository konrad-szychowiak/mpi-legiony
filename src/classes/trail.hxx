//
// Created by konrad on 18.04.2022.
//

#ifndef LEGIONY_TRAIL_HXX
#define LEGIONY_TRAIL_HXX


class Trail
{
private:
  int id;
  int maxThroughput;
public:
  Trail(int _id, int _size) : id(_id), maxThroughput(_size)
  {}

  static Trail *
  withMaxThroughput(int size)
  {
    static int nextId = 0;
    return new Trail(++nextId, size);
  }

  int getId()
  { return id; }

  int getMaxThroughput()
  { return maxThroughput; }

};


#endif //LEGIONY_TRAIL_HXX
