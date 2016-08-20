#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

bool is_debug;


//旗情報をシミュレータ用に出力します
void inform_flag(){
    int x,y;

    if(!is_debug){
        return;
    }

    printf("flaginfo\n");
    for (y=0;y<31;y++)
    {
        for(x=0;x<16;x++){
            if((y%2==0&&x>=15)||(y%2==1&&x>=16)){
                continue;
            }
            if(nodes[x][y].flag==true){
                printf("True\n");
            }else{
                printf("False\n");
            }
        }
    }
}

//壁未探索情報をシミュレータ用に出力します
void inform_wall(){
    int x,y;

    if(!is_debug){
        return;
    }

    printf("wallinfo\n");
    for (y=0;y<31;y++)
    {
        for(x=0;x<16;x++){
            if((y%2==0&&x>=15)||(y%2==1&&x>=16)){
                continue;
            }

            switch(nodes[x][y].winfo){
            case Unknown:
                printf("0\n");
                break;
            case NoWall:
                printf("1\n");
                break;
            case Exist:
                printf("2\n");
                break;
            default:
                error_out("error;default!");
                break;
            }
        }
    }
}

void inform_message(char *msg){
    if(!is_debug){
        return;
    }
    printf("msg\n%s\n",msg);
    return;
}
