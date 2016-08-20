#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "header.h"
#include "getopt.h"

fstack_data fstack[FSTACKSIZE];
int fpos = 0; //���̃v�b�V���ʒu
int fstack_count = 0;
int max_fstack=0;

void fstack_push(fstack_data data) {
	if (fpos == FSTACKSIZE) {
		fpos = 0;
	}
	fstack[fpos].x = data.x;
	fstack[fpos].y = data.y;
	fpos++;
	fstack_count++;
	if (fstack_count > FSTACKSIZE) {
		fstack_count = FSTACKSIZE;
	}
	if(max_fstack<fstack_count){
        max_fstack=fstack_count;
	}
	return;
}

fstack_data fstack_pop() {
	int itempos = fpos - 1;

	if (fstack_count <= 0) {
		error_out("f�X�^�b�N����Ȃ̂�pop���悤�Ƃ��܂����B");
	}
	if (itempos == -1){
        itempos = FSTACKSIZE - 1;
	}
	fpos--;
	if (fpos == -1){
        fpos = FSTACKSIZE - 1;
	}
	fstack_count--;

	return fstack[itempos];
}

void fstack_clear() {
	fpos = 0;
	fstack_count = 0;
}

