#include "p1_library.hpp"
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class Player {
private:
  const string number;
  const char position;
  int skelly_snap;
  int team_snap;

public:
  Player(const string &number)
      : number(number), position(' '), skelly_snap(0), team_snap(0) {}

  Player(const string &number, const char &pos)
      : number(number), position(pos), skelly_snap(0), team_snap(0) {}

  string get_number() const { return number; }

  char get_position() const { return position; }

  int get_skelly_snap() const { return skelly_snap; }

  int get_team_snap() const { return team_snap; }

  int get_total_snap() const { return (team_snap + skelly_snap); }

  void add_skelly_snap() { skelly_snap++; }

  void add_team_snap() { team_snap++; }

  void reset_snaps() {
    team_snap = 0;
    skelly_snap = 0;
  }
};

class Team {
private:
  vector<Player> team;

public:
  Team(string filename) { fill_roster(filename); }

  void clear_all() {
    for (int i = 0; i < team.size(); ++i) {
      team[i].reset_snaps();
    }
  }

  void add_player(const Player &player) { team.push_back(player); }

  bool on_team(const string &number) const {
    for (int i = 0; i < team.size(); i++) {
      if (number == team[i].get_number()) {
        return true;
      }
    }
    return false;
  }

  Player *find_player(const string &number) {
    for (int i = 0; i < team.size(); i++) {
      if (number == team[i].get_number()) {
        return &team[i];
      }
    }
    assert(true);
    return nullptr;
  }

  void fill_roster(string filename) {
    ifstream team_in(filename);
    if (!team_in.is_open()) {
      cout << "Error opening " << filename << "\n";
      exit(1);
    }

    string number = "";
    char position;
    while (team_in >> number >> position) {
      Player player(number, position);
      add_player(player);
    }
    team_in.close();
  }

  void read(string filename, string type) {
    ifstream read(filename);
    if (!read.is_open()) {
      cout << "Error opening " << filename << "\n";
      exit(1);
    }

    string number;
    while (read >> number) {
      Player *player = find_player(number);
      if (type == "skelly") {
        player->add_skelly_snap();
      } else {
        player->add_team_snap();
      }
    }
    read.close();
  }

  void show_team(const string &output_file) {
    ofstream of(output_file);
    for (int i = 0; i < team.size(); i++) {
      of << team[i].get_number() << ", " << team[i].get_skelly_snap() << ", "
         << team[i].get_team_snap() << ", " << team[i].get_total_snap() << endl;
    }
  }
};
