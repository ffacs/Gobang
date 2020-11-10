//
// Created by ffacs on 2020/11/10.
//

#ifndef GOBANG_DFS_H
#define GOBANG_DFS_H

#include "StateJudge.h"

MINMAX dfs(int dep,int y,int x,int col,int fun,const MINMAX& last) {
    Board[y][x]=col;
    MINMAX res={INF,-INF};
    if(fun==0) res.first=last.first;
    else res.second=last.second;
    if(dep==0) { Board[y][x]=0;return stateJudge(col); }
    for(int i=0;i<BOARD_SIZE;i++) {
        for(int j=0;j<BOARD_SIZE;j++) {
            if(Board[i][j]||!Energy[i][j])continue;
            if(fun==0) res.second=std::max(res.second,dfs(dep-1,i,j,col*-1,fun^1,res).first);
            else res.first=std::min(res.first,dfs(dep-1,i,j,col*-1,fun^1,res).second);
            if(res.first<res.second) goto ed;
        }
    }
    ed:
    Board[y][x]=0;
    return res;
}

void get_Energy() {
    memset(Energy,0,sizeof(Energy));
    for(int y=0;y<BOARD_SIZE;y++) {
        for(int x=0;x<BOARD_SIZE;x++) {
            if(Board[y][x]) continue;
            for(int i=y-SEARCH_RANGE;i<=y+SEARCH_RANGE;i++) {
                for(int j=x-SEARCH_RANGE;j<=x+SEARCH_RANGE;j++) {
                    if(i<0||j<0||i>=BOARD_SIZE||j>=BOARD_SIZE) continue;
                    if(Board[i][j]) Energy[y][x]++;
                }
            }
        }
    }
}

#endif //GOBANG_DFS_H
