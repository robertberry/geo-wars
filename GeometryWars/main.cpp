#include <cstdlib>

#include "Game.h"

int main(int argc, char* argv[]) {
  srand(time(NULL));
  Game game;
  game.run();
  return 0;
}
