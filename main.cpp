#include "p1_library.hpp"
#include "stats.cpp"
#include <fstream>
#include <iostream>

using namespace std;

int main() {

  Team football("roster.txt");

  football.read("ALL_SPRING_TEAM.txt", "team");
  football.read("ALL_SPRING_SKELLY.txt", "skelly");

  football.show_team("snaps.csv");
}