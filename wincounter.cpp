#include "wincounter.h"
#include <sstream>
WinCounter::WinCounter() {}

std::string WinCounter::results()
{
  std::stringstream ss;
  ss << "X wins: " << xWins << ", O wins: " << zeroWins << ", draws: " << draws;
  xWins = zeroWins = draws = 0;
  return ss.str();
}

void WinCounter::worker(Stage st)
{
  switch (st) {
    case Stage::DRAW:
      ++draws;
      break;
    case Stage::WINX:
      ++xWins;
      break;
    case Stage::WIN0:
      ++zeroWins;
      break;
    default:
      break;
    }
}

