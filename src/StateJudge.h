//
// Created by ffacs on 2020/11/8.
//

#ifndef GOBANG_STATEJUDGE_H
#define GOBANG_STATEJUDGE_H



#include <vector>
#include <cstring>

using std::vector;
#define SEARCH_RANGE 2
#define BOARD_SIZE 16
int Board[BOARD_SIZE][BOARD_SIZE];
int Energy[BOARD_SIZE][BOARD_SIZE];
using ll =long long;
using MINMAX=std::pair<ll,ll>;
const ll INF=2e18;
ll powerOf10[20]={1};

ll func_judge(const vector<int>& V,int col) {
    bool haveWhite=false,haveBlack=false;
    for(auto x:V) if(x==-1) haveWhite= true;else if(x==1) haveBlack= true;
    if(!(haveWhite^haveBlack)) return 0;
    int len=0,lm=1,cnt=0;
    for(auto x:V) {
        if(x==0) {if(len) lm*=len;len=0;}
        else len++,cnt++;
    }if(len) lm*=len;
    ll flag=1;
    if((col==1&&haveWhite) || (col==-1&&haveBlack) ) flag=-10;
    return flag*lm*powerOf10[cnt];
}

inline vector<int> rowChess(int y,int x) { //row judge
    vector<int> V(5);
    for(int i=0;i<5;i++) V[i]=Board[y+i][x];
    return V;
}

inline vector<int> colChess(int y,int x){ //column judge
    vector<int> V(5);
    for(int i=0;i<5;i++) V[i]=Board[y][x+i];
    return V;
}

inline vector<int> leftDiagonalChess(int y,int x){//left diagonal
    vector<int> V(5);
    for(int i=0;i<5;i++) V[i]=Board[y+i][x+i];
    return V;
}

inline vector<int> rightDiagonalChess(int y,int x){//right diagonal
    vector<int> V(5);
    for(int i=0;i<5;i++) V[i]=Board[y+i][x-i];
    return V;
}

MINMAX stateJudge(int col) {
    ll stateJudgement=0;
//    MINMAX res={INF,-INF};
    for(int i=0;i<BOARD_SIZE;i++) {
        for(int j=0;j<BOARD_SIZE;j++) {
            if(i+5<=BOARD_SIZE) stateJudgement+=func_judge(rowChess(i,j),col);
            if(j+5<=BOARD_SIZE) stateJudgement+=func_judge(colChess(i,j),col);
            if(i+5<=BOARD_SIZE&&j+5<=BOARD_SIZE) stateJudgement+=func_judge(leftDiagonalChess(i,j),col);
            if(i+5<=BOARD_SIZE&&j>=4) stateJudgement+=func_judge(rightDiagonalChess(i,j),col);

//            if(i+5<=BOARD_SIZE) stateJudgement=std::max(stateJudgement,func_judge(rowChess(i,j),col));
//            if(j+5<=BOARD_SIZE) stateJudgement=func_judge(colChess(i,j),col);
//            if(i+5<=BOARD_SIZE&&j+5<=BOARD_SIZE) stateJudgement+=func_judge(leftDiagonalChess(i,j),col);
//            if(i+5<=BOARD_SIZE&&j>=4) stateJudgement+=func_judge(rightDiagonalChess(i,j),col);
        }
    }
    return {stateJudgement,stateJudgement};
//    return res;
}


#endif //GOBANG_STATEJUDGE_H
