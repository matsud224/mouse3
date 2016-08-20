/*
プライオリティーキューを４分割し、キューの操作にかかる時間を短縮
*/

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "header.h"


pqueue_data pqueue[4][130];
int pqueue_count[4];
int max_pqueue=0;

void pqueue_clear() {
	pqueue_count[0] = 0;
	pqueue_count[1] = 0;
	pqueue_count[2] = 0;
	pqueue_count[3] = 0;
}

//あふれたときはfalse
void pqueue_push(const pqueue_data *target) {
	int tx=target->x,ty=target->y,tc=target->cost;
	int queue_id=((tx%2)?0:2)+((ty%2)?0:1);
	int i = pqueue_count[queue_id];
	pqueue_count[queue_id]++;
    pqueue_data *selected=pqueue[queue_id];

	if (i >= 130) {
		//pqueueがあふれた
		error_out("プライオリティキューが溢れました。");
	}

	while (i > 0) {
        int p = (i - 1) / 2;
            if (selected[p].cost <= tc){
                break;
            }
		selected[i] = selected[p];
		i = p;
	}

	selected[i].x = tx;
	selected[i].y = ty;
	selected[i].cost = tc;

	if(max_pqueue<pqueue_count[queue_id]){
        max_pqueue=pqueue_count[queue_id];
	}
	if(max_cost<tc)
    {
        max_cost=tc;
    }

    //printf("push:%d,%d(%d)\n",tx,ty,tc);

	return;
}

//Generally speaking, the word "Karaage" have only meaning as food. But it is special in butchi.
pqueue_data pqueue_pop() {
	pqueue_data ret;
	pqueue_data x;
	int xcost;
	int a, b;
	int min_c=INT_MAX,min_id=0; //4つのキューのうち最小の要素を持つキューの番号
	int i;
	pqueue_data *selected;

	if(pqueue_count[0]>0 && pqueue[0][0].cost<min_c){
        min_c=pqueue[0][0].cost;
        min_id=0;
    }
    if(pqueue_count[1]>0 && pqueue[1][0].cost<min_c){
        min_c=pqueue[1][0].cost;
        min_id=1;
    }
    if(pqueue_count[2]>0 && pqueue[2][0].cost<min_c){
        min_c=pqueue[2][0].cost;
        min_id=2;
    }
    if(pqueue_count[3]>0 && pqueue[3][0].cost<min_c){
        min_c=pqueue[3][0].cost;
        min_id=3;
    }

    selected=pqueue[min_id];
	ret = selected[0];

	x = selected[pqueue_count[min_id] - 1];
	xcost=x.cost;
	pqueue_count[min_id]--;

	i = 0;
	while (i * 2 + 1 < pqueue_count[min_id]) {
		a = i * 2 + 1;
		b = i * 2 + 2;
		if (b < pqueue_count[min_id] && selected[b].cost < selected[a].cost){
            a = b;
        }
        if (selected[a].cost >= xcost){
            break;
        }
		selected[i] = selected[a];
		i = a;
	}
	selected[i] = x;

	//printf("pop:%d,%d(%d)\n",ret.x,ret.y,ret.cost);

	return ret;
}

//キューに既に追加したもののコストが小さくなったときそれをキューにも反映させます。
//存在しないものを変更しようとするとバグります
void pqueue_decrease(const pqueue_data *target) {
	int tx=target->x,ty=target->y,tc=target->cost;
	int queue_id=((tx%2)?0:2)+((ty%2)?0:1);
	int i,p;
    pqueue_data *selected=pqueue[queue_id];

	//探索を行います
	for (i = pqueue_count[queue_id]-1; i >=0; i--) {
		if (selected[i].y == ty && selected[i].x == tx) {
			break;
		}
	}


	while (i > 0) {
        p = (i - 1) / 2;
        if (selected[p].cost <= tc) break;

		selected[i] = selected[p];
		i = p;
	}

	selected[i].x = tx;
	selected[i].y = ty;
	selected[i].cost = tc;


    //printf("dec:%d,%d(%d)\n",tx,ty,tc);

	return;

}
