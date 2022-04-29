#include <iostream>
#include "threads/main.thread.hxx"
#include "config.hpp"
#include <stdlib.h>

using namespace std;

// todo: sending mutex

/**
 * todo: should start both threads
 * @return
 */
int main()
{
  srand(time(NULL));
  auto processInfo = new ProcessInfo(0, 0, legions[0]);

  mainThread(processInfo);

  return 0;
}

