#include "wincounter.h"
#include <sstream>
WinCounter::WinCounter() {}

std::string WinCounter::Results()
{
  std::stringstream ss;
  ss << "X wins: " << x_wins << ", O wins: " << zero_wins << ", draws: " << draws;
  x_wins = zero_wins = draws = 0;
  return ss.str();
}

void WinCounter::Worker(Stage st)
{
  switch (st) {
    case Stage::DRAW:
      ++draws;
      break;
    case Stage::WIN_X:
      ++x_wins;
      break;
    case Stage::WIN_0:
      ++zero_wins;
      break;
    default:
      break;
    }
}

