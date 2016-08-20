#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "header.h"
#include "getopt.h"

void ll_straight(int length) {
    if(!is_debug){
        return;
    }

	printf("straight\n");
	printf("%d\n",length);
	return;
}

void ll_half() {
    if(!is_debug){
        return;
    }

	printf("half\n");
	return;
}

void ll_slalom(int direction) {
    if(!is_debug){
        return;
    }

	printf("slalom\n");
	printf("%d\n",direction);
	return;
}

void ll_turn(int angle) {
    if(!is_debug){
        return;
    }

	printf("turn\n");
	printf("%d\n",angle);
	return;
}

wallinfo ll_sense(int sensor_no) {
	//algorithm.c�ł́A����͌Ă΂�Ȃ����ƂɂȂ��Ă���B�v
	//algorithm.c��ҏW���ăZ���T�[�ǂݎ��ɂ��̊֐����g���悤�ɂ��Ȃ��Ƃ����Ȃ��B
	return Exist;
}

//�O�Ǖ␳�̂���
void ll_fwr(){
    if(!is_debug){
        return;
    }

    printf("fwr\n");
    return;
}
