#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

struct PLAYER3{
  int turn;
  vector<vector<int>> field;
  vector<int> score;

  vector<int> hand;

  int select_card(){
    //sort(hand.begin(),hand.end());
    //reverse(hand.begin(),hand.end());
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