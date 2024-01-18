#include <bits/stdc++.h>
using namespace std;

#include "Player.cpp"

struct PLAYER1 : public PLAYER {

  int select_card(){
    int ret=hand.back();
    hand.pop_back();
    return ret;
  }

  int select_lane(){
    int ret=0;
    for (int j=1;j<field.size();j++){
      if(field.at(j).size()<field.at(ret).size()) ret=j;
    }
    return ret;
  }

};