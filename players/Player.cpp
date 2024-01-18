#include <bits/stdc++.h>
using namespace std;

struct PLAYER{
    int turn;
    vector<vector<int>> field;
    vector<int> score;

    vector<int> hand;

    virtual int select_card(){
        //function for select card
        return 0;
    }
    virtual int select_lane(){
        //function for select lane
        return 0;
    }
};