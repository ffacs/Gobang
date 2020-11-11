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
ll powerOf10[20]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
const int DIRCTION=8;
int Xdirction[]={1,1,1,0,-1,-1,-1,0};
int Ydirction[]={-1,0,1,1,1,0,-1,-1};


ll func_judge(const int* V,int col) {
    bool haveWhite=false,haveBlack=false;
    for(int i=0;i<5;i++) if(V[i]==-1) haveWhite= true;else if(V[i]==1) haveBlack= true;
    if(!(haveWhite^haveBlack)) return 0;
    int len=0,lm=1,cnt=0;
    for(int i=0;i<5;i++) {
        if(V[i]==0) {if(len) lm*=len;len=0;}
        else len++,cnt++;
    }if(len) lm*=len;
    ll flag=1;
    if((col==1&&haveWhite) || (col==-1&&haveBlack) ) flag=-10;
    return flag*lm*powerOf10[cnt];
}

int isGameOver() {
    for(int d=0;d<DIRCTION/2;d++) {
        for(int i=0;i<BOARD_SIZE;i++) {
            if(i+4*Ydirction[d]<0||i+4*Ydirction[d]>=BOARD_SIZE) continue;
            for(int j=0;j<BOARD_SIZE;j++) {
                if(j+4*Xdirction[d]<0||j+4*Xdirction[d]>=BOARD_SIZE) continue;
                int V[5];for(int k=0;k<5;k++) V[k]=Board[i+k*Ydirction[d]][j+k*Xdirction[d]];
                if(V[0]==0) {continue;}for(int k=1;k<5;k++) if(V[k]!=V[0]) continue;
                return V[0];
            }
        }
    }
    return 0;
}

MINMAX stateJudge(int col) {
    ll stateJudgement=0;
    for(int d=0;d<DIRCTION;d++) {
        for(int i=0;i<BOARD_SIZE;i++) {
            if(i+4*Ydirction[d]<0||i+4*Ydirction[d]>=BOARD_SIZE) continue;
            for(int j=0;j<BOARD_SIZE;j++) {
                if(j+4*Xdirction[d]<0||j+4*Xdirction[d]>=BOARD_SIZE) continue;
                int V[5];for(int k=0;k<5;k++) V[k]=Board[i+k*Ydirction[d]][j+k*Xdirction[d]];
                ll nowStatus=func_judge(V,col);
                stateJudgement+=nowStatus;
            }
        }
    }
    return {stateJudgement,stateJudgement};
}

#endif //GOBANG_STATEJUDGE_H
