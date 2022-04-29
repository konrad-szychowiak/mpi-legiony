//
// Created by konrad on 18.04.2022.
//

#ifndef LEGIONY_LEGION_HXX
#define LEGIONY_LEGION_HXX

class Legion
{
private:
  int id;
  int size;
public:
  Legion(int _id, int _size) : id(_id), size(_size)
  {}

  static Legion *
  withSize(int size)
  {
    static int nextId = 0;
    return new Legion(++nextId, size);
  }

  int getId()
  { return id; }

  int getSize()
  { return size; }
};

#endif //LEGIONY_LEGION_HXX
