#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "header.h"
#include "getopt.h"

stack_data stack[STACKSIZE];
int stack_nextpos = 0; //次のプッシュ位置
int stack_count = 0;
int max_stack=0;

void stack_push(stack_data data) {
	if (stack_nextpos == STACKSIZE) {
		stack_nextpos = 0;
	}
	stack[stack_nextpos].winfo = data.winfo;
	stack[stack_nextpos].x = data.x;
	stack[stack_nextpos].y = data.y;
	stack_nextpos++;
	stack_count++;
	if (stack_count > STACKSIZE) {
		stack_count = STACKSIZE;
	}
	if(max_stack<stack_count){
        max_stack=stack_count;
	}
	return;
}

stack_data stack_pop() {
	int itempos = stack_nextpos - 1;

	if (stack_count <= 0) {
		error_out("スタックが空なのにpopしようとしました。");
	}
	if (itempos == -1){
        itempos = STACKSIZE - 1;
	}
	stack_nextpos--;
	if (stack_nextpos == -1){
        stack_nextpos = STACKSIZE - 1;
	}
	stack_count--;

	return stack[itempos];
}

void stack_clear() {
	stack_nextpos = 0;
	stack_count = 0;
}

