#include <iostream>
#include "src/StateJudge.h"
#include "src/dfs.h"
#include <unistd.h>

using namespace std;


long long Y_chosen,X_chosen,maxJudgement;

void get_XY1(int col) {
    Y_chosen=BOARD_SIZE/2-1;X_chosen=BOARD_SIZE/2-1;maxJudgement=-2e18;
    get_Energy();
    for(int i=0;i<BOARD_SIZE;i++) {
        for(int j=0;j<BOARD_SIZE;j++) {
            if(Board[i][j]||!Energy[i][j]) continue;
            MINMAX nowJudgement=dfs(2,i,j,col,0,MINMAX{INF,-INF});
            if(nowJudgement.second>maxJudgement) {
                Y_chosen=i;X_chosen=j;maxJudgement=nowJudgement.second;
            }
        }
    }
}

void get_XY2(int col) {
    Y_chosen=BOARD_SIZE/2-1;X_chosen=BOARD_SIZE/2-1;maxJudgement=-2e18;
    get_Energy();
    for(int i=BOARD_SIZE-1;i>=0;i--) {
        for(int j=BOARD_SIZE-1;j>=0;j--) {
            if(Board[i][j]||!Energy[i][j]) continue;
            MINMAX nowJudgement=dfs(2,i,j,col,0,MINMAX{INF,-INF});
            if(nowJudgement.second>maxJudgement) {
                Y_chosen=i;X_chosen=j;maxJudgement=nowJudgement.second;
            }
        }
    }
}

void (*get_XY[2])(int)={get_XY1,get_XY2};

void print_board() {
    for(int i=0;i<BOARD_SIZE;i++) {
        for(int j=0;j<BOARD_SIZE;j++) {
            if(Board[i][j]==1) cout<<"* ";
            else if(Board[i][j]==-1) cout<<"+ ";
            else cout<<". ";
        }cout<<endl;
    }cout<<endl;
}

void selfplay() {
    for(int i=0;i<100;i++) {

        sleep(1);

        if(rand()%2) get_XY1(1);
        else get_XY2(1);
        Board[Y_chosen][X_chosen]=1;
        print_board();

        sleep(1);
        if(rand()%2) get_XY2(-1);
        else get_XY2(-1);
//        cout<<Y_chosen<<' '<<X_chosen<<endl;
        Board[Y_chosen][X_chosen]=-1;
        print_board();
    }
}
int main() {
    srand(time(nullptr));
    for(int i=1;i<20;i++) powerOf10[i]=powerOf10[i-1]*10;

//    selfplay();


    int black=0,white=0;
    for(auto & i : Board)
        for(int & j : i){
            cin>>j;
            if(j==1) black++;
            else if(j==-1) white++;
        }
    if(black==white) get_XY[rand()%2](1);
    else  get_XY[rand()%2](-1);

    cout<<Y_chosen<<' '<<X_chosen<<endl;

    return 0;
}
