#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "header.h"
#include "getopt.h"


//�o�H���o�ŃG���[�ƂȂ������̏���
void rescue_dijkstra(){
    inform_message("dijkstra���Ɍo�H��������܂���ł���");

    //���Ԃ�mouse_runcount==1�̎������Ă΂�Ȃ��i���S�[���ɒ�������o�H�͂P�͌����邩��j

    //�ǂ��g�Ȃ��h�Ƃ����ǂ��g����h�Ɗ��Ⴂ������
    //���o�H���Ȃ��Ȃ���
    int x,y;
    for(y=0;y<31;y++){
        for(x=0;x<16;x++){
            nodes[x][y].winfo=Unknown;
            nodes[x][y].flag=false;
        }
    }

    flag_count=0;

    nodes[0][29].winfo=NoWall;
    nodes[0][30].winfo=Exist;

    nodes[7][14].winfo=NoWall;
    nodes[7][16].winfo=NoWall;
    nodes[7][15].winfo=NoWall;
    nodes[8][15].winfo=NoWall;

    nodes[mouse_x][mouse_y].winfo=NoWall;

    return;
}

//��~�{�^���������ꂽ���̏���
void rescue_button_pushed(){
    stack_data sd;
    int *near;

    //�}�E�X�̓����������Z�b�g
    mouse_x=0;
    mouse_y=29;
    mouse_angle=90;
    mouse_dest=Goal;
    if(mouse_runcount%2==0){
        endcount-=2;
        mouse_runcount-=1;
    }else{
        endcount-=2;
    }

    if(shortestpath_fixed==false){
        while(stack_count>0){
            sd=stack_pop();
            nodes[sd.x][sd.y].winfo=Unknown;
        }
    }

    recalc();
    near=nearestflag();
    if(near==NULL){
        int *goal_result;
        goal_result=dijkstra(mouse_x,mouse_y,GOALS,false);
        setroute(0,29,goal_result[0],goal_result[1],false);
    }else{
        setroute(0,29,near[0],near[1],false);
        if(shortestpath_fixed==false && mouse_dest==Goal){
            drop_goal(near[0],near[1]);
        }
    }

    is_idle=true;
}

//�{�^����������čĊJ����Ƃ��ɌĂяo��.
void restart_button(){
    runcost=0;
    ll_half();
    is_idle=false;
    return;
}
