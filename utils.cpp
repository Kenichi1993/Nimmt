#include <bits/stdc++.h>
using namespace std;

//手札を表示
void print_Hands(int turn, int N, vector<vector<int>> Hands){
  cout<<"Turn "<<turn<<endl;
  for(int i=0; i<N; i++){
    cout<<"PL"<<i+1<<"_hand: ";
    for(auto j:Hands.at(i)){
      cout<<j<<" ";
    }
    cout<<endl;
  }
}

//場を表示
void print_Field(int turn, int L, vector<vector<int>> Field){
  cout<<"----------------------"<<endl<<"Turn "<<turn<<endl;
  for(int i=0; i<L; i++){
    cout<<"Lane"<<i+1<<": ";
    for(auto j:Field.at(i)){
      cout<<j<<" ";
    }
    cout<<endl;
  }
  cout<<"----------------------"<<endl;
}

//点数を表示
void print_Scores(int N, vector<int> Scores){
  for(int i=0; i<N; i++){
    cout<<"PL"<<i+1<<": "<<Scores.at(i)<<" pts"<<endl;
  }
}

//勝者を表示
int print_Winner(int N, vector<int> Scores){
  int ret=0;
  for(int i=1;i<N;i++){
    if(Scores.at(i)<Scores.at(ret)) ret=i; //点数低いほうが勝ち。同点なら先手が勝ち
  }
  cout<<"Winner: PL"<<ret+1<<endl;
  return ret;
}
