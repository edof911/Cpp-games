#include <set>
#include <map>
#include <list>
#include <queue>
#include <stack>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <vector>
#include <string>
#include <bitset>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <numeric>
#include <complex>
#include <sstream>
#include <regex>
#include <fstream>
#include <iomanip>
#include <cassert>
#include <iostream>
#include <iterator>
#include <algorithm>
using namespace std;
using ll = long long;
using VL=vector<ll>;

#define rep(i, n) for(int i = 0;i < n;i++)
#define repr(i, n) for(int i = n;i >= 0;i--)
#define FOR(i, m, n) for(int i = m;i < n;i++)
const long long INF =  999999999;


const int row_size=5,col_size=8;
char grid[row_size][col_size];

pair<int,int> t(char c){
  switch(c){
    case 'a':
      return pair<int,int>(0,-1);
    case 's':
      return pair<int,int>(0,1);
    case 'w':
      return pair<int,int>(-1,0);
    case 'z':
      return pair<int,int>(1,0);
  }
  return pair<int,int>(0,0);
}

//壁に行っていないか
bool wall(int x,int y,int dx, int dy){
  return (0<x+dx && x+dx<row_size-1 && 0<y+dy && y+dy<col_size-1);
}

//二つの荷物を同時に押していないか
bool twobag(int x,int y,int dx,int dy){
  if((grid[x+dx][y+dy]=='o' ) && (grid[x+2*dx][y+2*dy]=='o' || grid[x+2*dx][y+2*dy]=='O')){
    return false;
  }
  else return true;
}

//壁に向かって荷物を押していないか
bool wallbag(int x,int y,int dx,int dy){
  if((grid[x+dx][y+dy]=='o' ) && (grid[x+2*dx][y+2*dy]=='#' || grid[x+2*dx][y+2*dy]=='#')){
    return false;
  }
  else return true;
}

//すでに置いた荷物を押していないか
bool compbag(int x,int y,int dx,int dy){
  if(grid[x+dx][y+dy]=='O'){
    return false;
  }
  else return true;
}

//上記4つを全て満たしているか
bool canmove(int x,int y, int dx,int dy){
  return (wall(x,y,dx,dy) && twobag(x,y,dx,dy) && wallbag(x,y,dx,dy) && compbag(x,y,dx,dy));
}

//荷物が動いたところにあった場合動かす(実際に荷物が動かせるかはcanmoveで判定済み)
bool movebag(int x,int y,int dx,int dy){
  if(grid[x+dx][y+dy]=='o'){
    grid[x+dx][y+dy]=' ';
    if(grid[x+2*dx][y+2*dy]=='.'){
      grid[x+2*dx][y+2*dy]='O';
      return true;
    }
    else {
      grid[x+2*dx][y+2*dy]='o';
      return false;
    }
  }
  else return false;
}


//全部戻す。
void restart(int& px,int& py){
  for(int i=0;i<row_size;i++){
    for(int j=0;j<col_size;j++){
      if(i==0 || i==row_size-1 || j==0 || j==col_size-1){
        grid[i][j]='#';
      }
      else{
        grid[i][j]=' ';
      }
    }
  }

  grid[1][2]=grid[1][3]='.';
  grid[2][2]=grid[2][3]='o';

  //初期位置
  px=1,py=5;
  grid[px][py]='p';

}


int main(){
  vector<pair<int,int> > bag,goal;
  pair<int,int> Pos;

  for(int i=0;i<row_size;i++){
    for(int j=0;j<col_size;j++){
      if(i==0 || i==row_size-1 || j==0 || j==col_size-1){
        grid[i][j]='#';
      }
      else{
        grid[i][j]=' ';
      }
    }
  }

  grid[1][2]=grid[1][3]='.';
  grid[2][2]=grid[2][3]='o';

  //初期位置
  int px=1,py=5;
  grid[px][py]='p';
  //運んだ荷物の数
  int comp=0;
  while(true){
    for(int i=0;i<row_size;i++){
      for(int j=0;j<col_size;j++){
        cout<<grid[i][j];
      }
      cout<<endl;
    }
    cout<<"a:left s:right w:up z:down r:restart"<<endl;

    cout<<"comp:"<<comp<<endl;

    if(comp==2){
      cout<<"You've Done!"<<endl;
      break;
    }

    char c;
    cin >>c;

    if(c=='r'){
      cout<<"こんな簡単なゲームもできないわけぇ？"<<endl;
      restart(px,py);
      comp=0;
      continue;
    }
    pair<int,int> np=t(c);
    int nx=np.first,ny=np.second;
    if(canmove(px,py,nx,ny)){
      cout<<comp<<endl;
      comp+=movebag(px,py,nx,ny) ? 1 : 0;
      cout<<comp<<endl;
      //現在地がゴール地点でそこから動く
      if(grid[px][py]=='P'){
        grid[px][py]='.';
      }

      //現在地スペース
      if(grid[px][py]=='p'){
        grid[px][py]=' ';
      }

      //行き先がゴール地点
      if(grid[px+nx][py+ny]=='.'){
        grid[px+nx][py+ny]='P';
      }

      //スペースに入った(荷物を運んだ場合も目の前はスペースにしてある)
      if(grid[px+nx][py+ny]==' '){
        grid[px+nx][py+ny]='p';

      }

      px+=nx,py+=ny;
    }
    else{
      cout<<"移動できません。"<<endl;
    }

  }

}
