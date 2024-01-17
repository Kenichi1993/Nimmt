#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#include "Player1.cpp"
#include "Player2.cpp"
#include "Player3.cpp"

const int N=3; //プレイ人数
const int L=4; //レーンの数
int turn; //ターン数
vector<vector<int>> Field; //場の状態
vector<vector<int>> Hands; //手札の状態
vector<int> Scores; //各プレイヤーの得点
vector<int> Cards; //カード

//プレイヤー1のstructのインスタンス作成
PLAYER1 p1;
//プレイヤー2のstructのインスタンス作成
PLAYER2 p2;
//プレイヤー3のstructのインスタンス作成
PLAYER3 p3;

//初期化
void init(){

  //グローバル変数の初期化
  turn=0;
  Field=vector<vector<int>>(L, vector<int>()); 
  Hands=vector<vector<int>>(N,vector<int>());
  Scores=vector<int>(N,0);
  Cards=vector<int>(104);

  //1-104のカードを作成
  iota(Cards.begin(), Cards.end(), 1);

  //カードをシャッフル
  random_device get_rand_dev; // seedに乱数を指定
  mt19937 get_rand_mt( get_rand_dev() ); 
  shuffle(Cards.begin(), Cards.end(), get_rand_mt ); 

  //レーンにL枚配置&手札10枚ずつ配る
  for(int i=0; i<L; i++){
    Field.at(i).push_back(Cards.back());
    Cards.pop_back();
  }
  for(int i=0;i<N;i++){
    for(int j=0;j<10;j++){
      Hands.at(i).push_back(Cards.back());
      Cards.pop_back();
    }
  }

  //structのhand変数に初期の手札を代入
  p1.hand=Hands.at(0);
  p2.hand=Hands.at(1);
  p3.hand=Hands.at(2);

  
}

//手札を表示
void print_Hands(){
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
void print_Field(){
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
void print_Scores(){
  for(int i=0; i<N; i++){
    cout<<"PL"<<i+1<<": "<<Scores.at(i)<<" pts"<<endl;
  }
}

//勝者を表示
int print_Winner(){
  int ret=0;
  for(int i=1;i<N;i++){
    if(Scores.at(i)<Scores.at(ret)) ret=i; //点数低いほうが勝ち。同点なら先手が勝ち
  }
  cout<<"Winner: PL"<<ret+1<<endl;
  return ret;
}

//出したカードがどのレーンに置かれるか決める関数。どこにも置けない場合は-1を出力
int lane(int x){
  int ret=-1;
  int tmp=0;
  for (int i=0; i<L; i++){
    if(Field.at(i).back()<x&&tmp<Field.at(i).back()) {
      ret=i;
      tmp=Field.at(i).back();
    }
  }
  return ret;
}

//出されたカードの処理と得点計算。引数はプレイヤーが選んだ数字のvector(=choice)
void shori(vector<int> X){
  vector<pair<int,int>> Sort; //pair(出した数字, 出したプレイヤー)のvector
  for (int i=0; i<N; i++){
    Sort.push_back(make_pair(X.at(i),i));
  }
  sort(Sort.begin(),Sort.end());

  for (int i=0; i<N; i++){
    int n=Sort.at(i).first; //出したカードの数字
    int p=Sort.at(i).second; //出したプレイヤー
    int l=lane(n); //置かれるレーン番号

    //どこにも置けない場合、いずれかのレーンを回収後、出したカードを置く
    if(l==-1){
      int sl; //selected lane
      if(p==0) sl=p1.select_lane();
      else if(p==1) sl=p2.select_lane();
      else if(p==2) sl=p3.select_lane();

      Scores.at(p)+=Field.at(sl).size(); //点数計算
      Field.at(sl).clear();
      Field.at(sl).push_back(n);
    }
    //レーンのカードの枚数が6枚になる場合、そのレーンを回収後、出したカードを置く
    else if (Field.at(l).size()==5){
      Scores.at(p)+=Field.at(l).size(); //点数計算
      Field.at(l).clear();
      Field.at(l).push_back(n);
    }
    //問題なくカードを置ける場合
    else Field.at(l).push_back(n);
  }
}

void play(){

  vector<int> choice={}; //プレイヤーが出した数字を格納するvector
  
  //プレイヤー1のstructのメンバ変数に代入
  p1.turn=turn;
  p1.field=Field;
  p1.score=Scores;
  choice.push_back(p1.select_card()); //プレイヤー1が出す数字をchoiceに格納

  //プレイヤー2のstructのメンバ変数に代入
  p2.turn=turn;
  p2.field=Field;
  p2.score=Scores;
  choice.push_back(p2.select_card());//プレイヤー2が出す数字をchoiceに格納

  //プレイヤー3のstructのメンバ変数に代入
  p3.turn=turn;
  p3.field=Field;
  p3.score=Scores;
  choice.push_back(p3.select_card());//プレイヤー3が出す数字をchoiceに格納

  //choiceの表示
  cout<<"Choice: ";
  for(auto c:choice){
    cout<<c<<" ";
  }
  cout<<endl;
  
  //処理
  shori(choice);
  
  //手札の状態を更新
  Hands.at(0)=p1.hand;
  Hands.at(1)=p2.hand;
  Hands.at(2)=p3.hand;
}


signed main(){

  int M=1; //ゲームの繰り返し数
  vector<int> Scores_Sum(N,0); //累計の点数
  vector<int> Win_Sum(N,0);

  for(int k=0;k<M;k++){

    //初期化
    init();

    //初期状態の表示
    print_Field();
    print_Hands();

    //1ゲームを実行（全10ターン）
    for (int i=0;i<10;i++){
      turn++;
      play();
    }

    print_Scores(); //点数表示
    for(int i=0;i<N;i++){
      Scores_Sum.at(i) += Scores.at(i); //累計点数に加算
    }
    Win_Sum.at(print_Winner())++; //勝者表示
  }

  //累計点数表示&累計勝利数表示
  for(int i=0;i<N;i++){
    cout<<"PL"<<i+1<<": "<<Scores_Sum.at(i)<<" pts, "<<Win_Sum.at(i)<<" wins"<<endl;
  }
}