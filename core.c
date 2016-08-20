#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "header.h"


node nodes[16][31];
int mouse_x=0;
int mouse_y=29;
int mouse_angle=90;
destination mouse_dest=Goal;
int mouse_runcount=0; //0で未初期化、n回目の走行でnにセットされてる
int flag_count=0;
bool center_checking=false; //１回めのゴールでゴール内を見て回ったかどうか
bool center_checked=false;
bool need_fix=false;
bool shortestpath_fixed=false;
const int reverse_direction[8]={1,0,3,2,6,7,4,5};

int max_cost;


void fukurokoji_remove(int x,int y){
    int count;
    fstack_data now;
    fstack_data temp;
    fstack_clear();
    temp.x=x;temp.y=y;
    fstack_push(temp); //最初のアイテムをプッシュ！

    while(fstack_count>0){
        now=fstack_pop();
        if(now.y%2==0){
            //右側を調べる
            count=0;
            if(nodes[now.x][now.y].winfo==Exist || nodes[now.x][now.y].delay_exist==true){
                count++;
            }
            if(now.x==14 || nodes[now.x+1][now.y].winfo==Exist || nodes[now.x+1][now.y].delay_exist==true){
                count++;
            }
            if(now.y==0 || nodes[now.x+1][now.y-1].winfo==Exist || nodes[now.x+1][now.y-1].delay_exist==true){
                count++;
            }
            if(now.y==30 || nodes[now.x+1][now.y+1].winfo==Exist || nodes[now.x+1][now.y+1].delay_exist==true){
                count++;
            }
            if(count==3){
                if(now.x!=14 && nodes[now.x+1][now.y].winfo!=Exist && nodes[now.x+1][now.y].delay_exist==false){
                    nodes[now.x+1][now.y].delay_exist=true;
                    temp.x=now.x+1;temp.y=now.y;
                    fstack_push(temp);
                }else if(now.y!=0 && nodes[now.x+1][now.y-1].winfo!=Exist && nodes[now.x+1][now.y-1].delay_exist==false){
                    nodes[now.x+1][now.y-1].delay_exist=true;
                    temp.x=now.x+1;temp.y=now.y-1;
                    fstack_push(temp);
                }else if(now.y!=30 && nodes[now.x+1][now.y+1].winfo!=Exist && nodes[now.x+1][now.y+1].delay_exist==false){
                    nodes[now.x+1][now.y+1].delay_exist=true;
                    temp.x=now.x+1;temp.y=now.y+1;
                    fstack_push(temp);
                }
            }

            //左側を調べる
            count=0;
            if(nodes[now.x][now.y].winfo==Exist || nodes[now.x][now.y].delay_exist==true){
                count++;
            }
            if(now.x==0 || nodes[now.x-1][now.y].winfo==Exist || nodes[now.x-1][now.y].delay_exist==true){
                count++;
            }
            if(now.y==0 || nodes[now.x][now.y-1].winfo==Exist || nodes[now.x][now.y-1].delay_exist==true){
                count++;
            }
            if(now.y==30 || nodes[now.x][now.y+1].winfo==Exist || nodes[now.x][now.y+1].delay_exist==true){
                count++;
            }
            if(count==3){
                if(now.x!=0 && nodes[now.x-1][now.y].winfo!=Exist && nodes[now.x-1][now.y].delay_exist==false){
                    nodes[now.x-1][now.y].delay_exist=true;
                    temp.x=now.x-1;temp.y=now.y;
                    fstack_push(temp);
                }else if(now.y!=0 && nodes[now.x][now.y-1].winfo!=Exist && nodes[now.x][now.y-1].delay_exist==false){
                    nodes[now.x][now.y-1].delay_exist=true;
                    temp.x=now.x;temp.y=now.y-1;
                    fstack_push(temp);
                }else if(now.y!=30 && nodes[now.x][now.y+1].winfo!=Exist && nodes[now.x][now.y+1].delay_exist==false){
                    nodes[now.x][now.y+1].delay_exist=true;
                    temp.x=now.x;temp.y=now.y+1;
                    fstack_push(temp);
                }
            }
        }else{
            //上側を調べる
            count=0;
            if(nodes[now.x][now.y].winfo==Exist || nodes[now.x][now.y].delay_exist==true){
                count++;
            }
            if(now.y==1 || nodes[now.x][now.y-2].winfo==Exist || nodes[now.x][now.y-2].delay_exist==true){
                count++;
            }
            if(now.x==0 || nodes[now.x-1][now.y-1].winfo==Exist || nodes[now.x-1][now.y-1].delay_exist==true){
                count++;
            }
            if(now.x==15 || nodes[now.x][now.y-1].winfo==Exist || nodes[now.x][now.y-1].delay_exist==true){
                count++;
            }
            if(count==3){
                if(now.y!=1 && nodes[now.x][now.y-2].winfo!=Exist && nodes[now.x][now.y-2].delay_exist==false){
                    nodes[now.x][now.y-2].delay_exist=true;
                    temp.x=now.x;temp.y=now.y-2;
                    fstack_push(temp);
                }else if(now.x!=0 && nodes[now.x-1][now.y-1].winfo!=Exist && nodes[now.x-1][now.y-1].delay_exist==false){
                    nodes[now.x-1][now.y-1].delay_exist=true;
                    temp.x=now.x-1;temp.y=now.y-1;
                    fstack_push(temp);
                }else if(now.x!=15 && nodes[now.x][now.y-1].winfo!=Exist && nodes[now.x][now.y-1].delay_exist==false){
                    nodes[now.x][now.y-1].delay_exist=true;
                    temp.x=now.x;temp.y=now.y-1;
                    fstack_push(temp);
                }
            }

            //下側を調べる
            count=0;
            if(nodes[now.x][now.y].winfo==Exist || nodes[now.x][now.y].delay_exist==true){
                count++;
            }
            if(now.y==29 || nodes[now.x][now.y+2].winfo==Exist || nodes[now.x][now.y+2].delay_exist==true){
                count++;
            }
            if(now.x==0 || nodes[now.x-1][now.y+1].winfo==Exist || nodes[now.x-1][now.y+1].delay_exist==true){
                count++;
            }
            if(now.x==15 || nodes[now.x][now.y+1].winfo==Exist || nodes[now.x][now.y+1].delay_exist==true){
                count++;
            }
            if(count==3){
                if(now.y!=29 && nodes[now.x][now.y+2].winfo!=Exist && nodes[now.x][now.y+2].delay_exist==false){
                    nodes[now.x][now.y+2].delay_exist=true;
                    temp.x=now.x;temp.y=now.y+2;
                    fstack_push(temp);
                }else if(now.x!=0 && nodes[now.x-1][now.y+1].winfo!=Exist && nodes[now.x-1][now.y+1].delay_exist==false){
                    nodes[now.x-1][now.y+1].delay_exist=true;
                    temp.x=now.x-1;temp.y=now.y+1;
                    fstack_push(temp);
                }else if(now.x!=15 && nodes[now.x][now.y+1].winfo!=Exist && nodes[now.x][now.y+1].delay_exist==false){
                    nodes[now.x][now.y+1].delay_exist=true;
                    temp.x=now.x;temp.y=now.y+1;
                    fstack_push(temp);
                }
            }

        }
    }

}

void infer_wall(int temp_x,int temp_y){
    //壁推論（柱からは少なくとも一つの壁が出ているということから）
	if(nodes[temp_x][temp_y].winfo==NoWall){
        if(temp_y%2==0){
            if(temp_y!=30){
                int no_count=0;
                if(nodes[temp_x][temp_y+1].winfo==NoWall){
                    no_count++;
                }
                if(nodes[temp_x+1][temp_y+1].winfo==NoWall){
                    no_count++;
                }
                if(nodes[temp_x][temp_y+2].winfo==NoWall){
                    no_count++;
                }
                if(no_count==2){
                    if(nodes[temp_x][temp_y+1].winfo==Unknown){
                        nodes[temp_x][temp_y+1].winfo=Exist;
                    }else if(nodes[temp_x+1][temp_y+1].winfo==Unknown){
                        nodes[temp_x+1][temp_y+1].winfo=Exist;
                    }else if(nodes[temp_x][temp_y+2].winfo==Unknown){
                        nodes[temp_x][temp_y+2].winfo=Exist;
                    }
                }
            }
            if(temp_y!=0){
                int no_count=0;
                if(nodes[temp_x+1][temp_y-1].winfo==NoWall){
                    no_count++;
                }
                if(nodes[temp_x][temp_y-1].winfo==NoWall){
                    no_count++;
                }
                if(nodes[temp_x][temp_y-2].winfo==NoWall){
                    no_count++;
                }
                if(no_count==2){
                    if(nodes[temp_x+1][temp_y-1].winfo==Unknown){
                        nodes[temp_x+1][temp_y-1].winfo=Exist;
                    }else if(nodes[temp_x][temp_y-1].winfo==Unknown){
                        nodes[temp_x][temp_y-1].winfo=Exist;
                    }else if(nodes[temp_x][temp_y-2].winfo==Unknown){
                        nodes[temp_x][temp_y-2].winfo=Exist;
                    }
                }
            }
        }

        if(temp_y%2==1){
            if(temp_x!=0){
                int no_count=0;
                if(nodes[temp_x-1][temp_y].winfo==NoWall){
                    no_count++;
                }
                if(nodes[temp_x-1][temp_y-1].winfo==NoWall){
                    no_count++;
                }
                if(nodes[temp_x-1][temp_y+1].winfo==NoWall){
                    no_count++;
                }
                if(no_count==2){
                    if(nodes[temp_x-1][temp_y].winfo==Unknown){
                        nodes[temp_x-1][temp_y].winfo=Exist;
                    }else if(nodes[temp_x-1][temp_y-1].winfo==Unknown){
                        nodes[temp_x-1][temp_y-1].winfo=Exist;
                    }else if(nodes[temp_x-1][temp_y+1].winfo==Unknown){
                        nodes[temp_x-1][temp_y+1].winfo=Exist;
                    }
                }
            }
            if(temp_x!=15){
                int no_count=0;
                if(nodes[temp_x+1][temp_y].winfo==NoWall){
                    no_count++;
                }
                if(nodes[temp_x][temp_y-1].winfo==NoWall){
                    no_count++;
                }
                if(nodes[temp_x][temp_y+1].winfo==NoWall){
                    no_count++;
                }
                if(no_count==2){
                    if(nodes[temp_x+1][temp_y].winfo==Unknown){
                        nodes[temp_x+1][temp_y].winfo=Exist;
                    }else if(nodes[temp_x][temp_y-1].winfo==Unknown){
                        nodes[temp_x][temp_y-1].winfo=Exist;
                    }else if(nodes[temp_x][temp_y+1].winfo==Unknown){
                        nodes[temp_x][temp_y+1].winfo=Exist;
                    }
                }
            }
        }
    }
}

//終わりのときはtrueを返します
bool nextstep(){
    int i;
    int *goal_result,*near;

    int sum_length=0,this_direction=-1; //連続検知用
	int virtual_x,virtual_y;
    bool exitflag=false;
    bool exitflag2=false;
    bool is_sensor_read=false;
    int start_array[3]={0,29,-1};


    if(mouse_runcount>=ENDCOUNT){
        return false; //rescue内で変更された時の検出のため
    }

    if(mouse_runcount==0){
        int x,y;
        //nodesの初期化はmain関数でなくてここで
        for (y=0;y<31;y++)
        {
            for(x=0;x<16;x++){
                nodes[x][y].flag=false;
                nodes[x][y].delay_exist=false;
            }
        }

        nodes[0][29].winfo=NoWall;
        nodes[0][30].winfo=Exist;

        nodes[7][14].winfo=NoWall;
        nodes[7][16].winfo=NoWall;
        nodes[7][15].winfo=NoWall;
        nodes[8][15].winfo=NoWall;


        //グローバル変数初期化
        mouse_x=0;
        mouse_y=29;
        mouse_angle=90;
        mouse_dest=Goal;
        mouse_runcount=0;
        flag_count=0;
        center_checking=false;
        need_fix=false;
        shortestpath_fixed=false;

        recalc();
        near=nearestflag();
        if(near==NULL){
            goal_result=dijkstra(0,29,GOALS,false);
            setroute(0,29,goal_result[0],goal_result[1],false);
        }else{
            setroute(0,29,near[0],near[1],false);

            drop_goal(near[0],near[1]);

        }
        mouse_runcount++;

        if(is_debug){
            printf("movestart\n");
            printf("start\n%d回目（行き）\n",(mouse_runcount+1)/2);
        }

        relay_half();
        runcost=0;
    }else if(mouse_dest==Start && mouse_x==0 && mouse_y==29){
        if(need_fix==true || mouse_runcount==2){
            fix_shortestpath();
            need_fix=false;
        }

        mouse_runcount++;

        if(is_debug){
            if(mouse_runcount!=ENDCOUNT){
                printf("start\n%d回目（行き）\n",(mouse_runcount+1)/2);
            }
        }

        printf("runcost\n%d\n",runcost);


        mouse_dest=Goal;
        relay_half();
        relay_turn((mouse_angle + 180) % 360);



        if(mouse_runcount==ENDCOUNT){
            return false;
        }

        relay_half();


        recalc();
        near=nearestflag();
        if(near==NULL){
            goal_result=dijkstra(0,29,GOALS,false);
            setroute(0,29,goal_result[0],goal_result[1],false);
        }else{
            setroute(0,29,near[0],near[1],false);
        }

        runcost=0;
    }else if(mouse_dest==Goal){
        bool isdest=false;

        for(i=0;*(GOALS+i)!=-1;i+=2){
            if(mouse_x==*(GOALS+i) && mouse_y==*(GOALS+i+1)){
                isdest=true;
                break;
            }
        }
        if (isdest==true && (center_checking==true || center_checked==true)){
            center_checking=false;
            center_checked=true;

            printf("runcost\n%d\n",runcost);

            mouse_runcount++;
            if(is_debug){
                printf("start\n%d回目（帰り）\n",mouse_runcount/2);
            }
            mouse_dest=Start;

            //is_shortest==true は移植時に削除
            if(mouse_runcount!=2 || is_shortest==true){
                //初回ゴール時はゴール内探査するから位置は気にしなくていい
                relay_half();
                relay_turn((mouse_angle + 180) % 360);
                relay_half();
            }

            if(need_fix==true){
                fix_shortestpath();
                need_fix=false;
            }
            recalc();
            near=nearestflag();
            if(near==NULL){
                goal_result=dijkstra(0,29,GOALS,false);
                if(goal_result[0]==mouse_x && goal_result[1]==mouse_y){
                    setroute(0,29,goal_result[0],goal_result[1],true);
                }else{
                    dijkstra(mouse_x,mouse_y,start_array,false);
                    setroute(mouse_x,mouse_y,0,29,false);
                }
            }else{
                setroute(mouse_x,mouse_y,near[0],near[1],false);
            }

            runcost=0;
        }else if(isdest==true && center_checked==false && center_checking==false){
            prepare_centercheck();
        }

    }




    switch (mouse_angle) {
		case 0:
			if (mouse_x + 1 <= 15 && mouse_y - 1 >= 1 && nodes[mouse_x + 1][ mouse_y - 1].winfo == Unknown) {
				nodes[mouse_x+1][mouse_y-1].winfo = relay_sense(2);
				fukurokoji_remove(mouse_x+1,mouse_y-1);
                infer_wall(mouse_x+1,mouse_y-1);
                is_sensor_read=true;
			}
			if (mouse_x + 1 <= 14 && nodes[mouse_x + 1][ mouse_y].winfo == Unknown) {
				nodes[mouse_x+1][mouse_y].winfo = relay_sense(0);
				fukurokoji_remove(mouse_x+1,mouse_y);
				infer_wall(mouse_x+1,mouse_y);
				is_sensor_read=true;
			}
			if (mouse_x + 1 <= 15 && mouse_y + 1 <= 29 && nodes[mouse_x + 1][ mouse_y + 1].winfo == Unknown) {
				nodes[mouse_x+1][mouse_y+1].winfo = relay_sense(3);
				fukurokoji_remove(mouse_x+1,mouse_y+1);
				infer_wall(mouse_x+1,mouse_y+1);
				is_sensor_read=true;
			}
			break;
		case 90:
			if (mouse_x - 1 >= 0 && mouse_y - 1 >= 0 && nodes[mouse_x - 1][ mouse_y - 1].winfo == Unknown) {
				nodes[mouse_x-1][mouse_y-1].winfo = relay_sense(2);
				fukurokoji_remove(mouse_x-1,mouse_y-1);
				infer_wall(mouse_x-1,mouse_y-1);
				is_sensor_read=true;
			}
			if (mouse_y - 1 >= 0 && mouse_x <= 14 && nodes[mouse_x][ mouse_y - 1].winfo ==Unknown) {
				nodes[mouse_x][mouse_y-1].winfo = relay_sense(3);
				fukurokoji_remove(mouse_x,mouse_y-1);
				infer_wall(mouse_x,mouse_y-1);
				is_sensor_read=true;
			}
			if (mouse_y - 2 >= 1 && nodes[mouse_x][ mouse_y - 2].winfo == Unknown) {
				nodes[mouse_x][mouse_y-2].winfo = relay_sense(0);
				fukurokoji_remove(mouse_x,mouse_y-2);
				infer_wall(mouse_x,mouse_y-2);
				is_sensor_read=true;
			}
			break;
		case 180:
			if (mouse_y - 1 >= 1 && nodes[mouse_x][ mouse_y - 1].winfo == Unknown) {
				nodes[mouse_x][mouse_y-1].winfo = relay_sense(3);
				fukurokoji_remove(mouse_x,mouse_y-1);
				infer_wall(mouse_x,mouse_y-1);
				is_sensor_read=true;
			}
			if (mouse_x - 1 >= 0 && nodes[mouse_x - 1][ mouse_y].winfo == Unknown) {
				nodes[mouse_x-1][mouse_y].winfo = relay_sense(0);
				fukurokoji_remove(mouse_x-1,mouse_y);
				infer_wall(mouse_x-1,mouse_y);
				is_sensor_read=true;
			}
			if (mouse_y + 1 <= 29 && nodes[mouse_x][ mouse_y + 1].winfo == Unknown) {
				nodes[mouse_x][mouse_y+1].winfo = relay_sense(2);
				fukurokoji_remove(mouse_x,mouse_y+1);
				infer_wall(mouse_x,mouse_y+1);
				is_sensor_read=true;
			}
			break;
		case 270:
			if (mouse_x - 1 >= 0 && mouse_y + 1 <= 30 && nodes[mouse_x - 1][ mouse_y + 1].winfo == Unknown) {
				nodes[mouse_x-1][mouse_y+1].winfo = relay_sense(3);
				fukurokoji_remove(mouse_x-1,mouse_y+1);
				infer_wall(mouse_x-1,mouse_y+1);
				is_sensor_read=true;
			}
			if (mouse_y + 1 <= 30 && mouse_x <= 14 && nodes[mouse_x][ mouse_y + 1].winfo == Unknown) {
				nodes[mouse_x][mouse_y+1].winfo = relay_sense(2);
				fukurokoji_remove(mouse_x,mouse_y+1);
				infer_wall(mouse_x,mouse_y+1);
				is_sensor_read=true;
			}
			if (mouse_y + 2 <= 29 && nodes[mouse_x][ mouse_y + 2].winfo == Unknown) {
				nodes[mouse_x][mouse_y+2].winfo = relay_sense(0);
				fukurokoji_remove(mouse_x,mouse_y+2);
				infer_wall(mouse_x,mouse_y+2);
				is_sensor_read=true;
			}
			break;
		default:
			error_out("想定外の値です。");
			break;
	}


    if(center_checking==false && shortestpath_fixed==false && is_sensor_read==true){
        //①の動作
        recalc();
        near=nearestflag();
        if(near==NULL){
            need_fix=true;
            if(mouse_dest==Start){
                dijkstra(mouse_x,mouse_y,start_array,false);
                setroute(mouse_x,mouse_y,0,29,false);
            }else{
                goal_result=dijkstra(mouse_x,mouse_y,GOALS,false);
                setroute(mouse_x,mouse_y,goal_result[0],goal_result[1],false);
            }
        }else{
            setroute(mouse_x,mouse_y,near[0],near[1],false);
            if(mouse_dest==Goal){
                drop_goal(near[0],near[1]);
            }
        }
    }else if(center_checking==false && shortestpath_fixed==false){
        //recalc()しない時でもnearestflag()は要る
        dijkstra(mouse_x,mouse_y,NULL,false);
        near=nearestflag();
        if(near==NULL){
            need_fix=true;
            if(mouse_dest==Start){
                dijkstra(mouse_x,mouse_y,start_array,false);
                setroute(mouse_x,mouse_y,0,29,false);
            }else{
                goal_result=dijkstra(mouse_x,mouse_y,GOALS,false);
                setroute(mouse_x,mouse_y,goal_result[0],goal_result[1],false);
            }
        }else{
            setroute(mouse_x,mouse_y,near[0],near[1],false);
            if(mouse_dest==Goal){
                drop_goal(near[0],near[1]);
            }
        }
    }


    //移動前に、前壁補正
    switch(mouse_angle){
    case 0:
        if(mouse_x==14 || nodes[mouse_x+1][mouse_y].winfo==Exist){
            ll_fwr();
        }
        break;
    case 90:
        if(mouse_y==1 || nodes[mouse_x][mouse_y-2].winfo==Exist){
            ll_fwr();
        }
        break;
    case 180:
        if(mouse_x==0 || nodes[mouse_x-1][mouse_y].winfo==Exist){
            ll_fwr();
        }
        break;
    case 270:
        if(mouse_y==29 || nodes[mouse_x][mouse_y+2].winfo==Exist){
            ll_fwr();
        }
        break;
    default:
		error_out("想定外の値です。");
		break;
    }

    //デバッグ情報出力
    inform_flag();
    inform_wall();

    //移動
	virtual_x=mouse_x;virtual_y=mouse_y;

	while(true){
        int now_direction = nodes[virtual_x][virtual_y].next_direction;

		if(this_direction==-1){
			this_direction=now_direction;
		}else if(this_direction!=now_direction){
			break;
		}

		switch (this_direction) {
			case 0:
				virtual_y-=1*2;
				break;
			case 1:
				virtual_y+=1*2;
				break;
			case 2:
				virtual_x-=1;
				break;
			case 3:
				virtual_x+=1;
				break;
			case 4:
			    if (virtual_y % 2 == 0) {
                    virtual_x++;
                    virtual_y--;
                } else {
                    virtual_y--;
                }
                break;
			case 5:
			    if (virtual_y % 2 == 0) {
                    virtual_y--;
                } else {
                    virtual_x--;
                    virtual_y--;
                }
                break;
			case 6:
			    if (virtual_y % 2 == 0) {
                    virtual_y++;
                } else {
                    virtual_x--;
                    virtual_y++;
                }
                break;
			case 7:
			    if (virtual_y % 2 == 0) {
                    virtual_x++;
                    virtual_y++;
                } else {
                    virtual_y++;
                }
				break;
			default:
				error_out("想定外の値です。");
				break;
		}

		if(nodes[virtual_x][virtual_y].winfo==Unknown){
            break;
		}else if(nodes[virtual_x][virtual_y].winfo==Exist){
		    recalc();
            near=nearestflag();
            if(near==NULL){
                if(mouse_dest==Start){
                    dijkstra(mouse_x,mouse_y,start_array,false);
                    setroute(mouse_x,mouse_y,0,29,false);
                }else{
                    goal_result=dijkstra(mouse_x,mouse_y,GOALS,false);
                    setroute(mouse_x,mouse_y,goal_result[0],goal_result[1],false);
                }
            }else{
                setroute(mouse_x,mouse_y,near[0],near[1],false);
            }
            return true;
		}

        if(mouse_runcount<=2){
            //最短が確定したら、壁見逃しなんでどーでもいいから、１往復目だけ実行！

            //https://www.evernote.com/shard/s184/sh/0e9a228e-cb0a-4ba1-9775-8d447c790041/aea599797ac5590f9c24c2c459b0a69f
            //のバグの解決（壁見逃し）
            switch (this_direction) {
                case 0:
                    if((virtual_x!=0 && nodes[virtual_x-1][virtual_y+1].winfo==Unknown) || (virtual_x!=15 && nodes[virtual_x][virtual_y+1].winfo==Unknown)){
                        exitflag2=true;
                    }
                    break;
                case 1:
                    if((virtual_x!=0 && nodes[virtual_x-1][virtual_y-1].winfo==Unknown) || (virtual_x!=15 && nodes[virtual_x][virtual_y-1].winfo==Unknown)){
                        exitflag2=true;
                    }
                    break;
                case 2:
                    if((virtual_y!=0 && nodes[virtual_x+1][virtual_y-1].winfo==Unknown) || (virtual_y!=30 && nodes[virtual_x+1][virtual_y+1].winfo==Unknown)){
                        exitflag2=true;
                    }
                    break;
                case 3:
                    if((virtual_y!=0 && nodes[virtual_x][virtual_y-1].winfo==Unknown) || (virtual_y!=30 && nodes[virtual_x][virtual_y+1].winfo==Unknown)){
                        exitflag2=true;
                    }
                    break;
                case 4:
                    if (virtual_y % 2 == 0) {
                        if((virtual_y!=0 && nodes[virtual_x][virtual_y-1].winfo==Unknown) || (virtual_x!=0 && nodes[virtual_x-1][virtual_y].winfo==Unknown)){
                            exitflag2=true;
                        }
                    } else {
                        if((virtual_x!=15 && nodes[virtual_x][virtual_y+1].winfo==Unknown) || (virtual_y!=29 && nodes[virtual_x][virtual_y+2].winfo==Unknown)){
                            exitflag2=true;
                        }
                    }
                    break;
                case 5:
                    if (virtual_y % 2 == 0) {
                        if((virtual_x!=14 && nodes[virtual_x+1][virtual_y].winfo==Unknown) || (virtual_y!=0 && nodes[virtual_x+1][virtual_y-1].winfo==Unknown)){
                            exitflag2=true;
                        }
                    } else {
                        if((virtual_x!=0 && nodes[virtual_x-1][virtual_y+1].winfo==Unknown) || (virtual_y!=29 && nodes[virtual_x][virtual_y+2].winfo==Unknown)){
                            exitflag2=true;
                        }
                    }
                    break;
                case 6:
                    if (virtual_y % 2 == 0) {
                        if((virtual_x!=14 && nodes[virtual_x+1][virtual_y].winfo==Unknown) || (virtual_y!=30 && nodes[virtual_x+1][virtual_y+1].winfo==Unknown)){
                            exitflag2=true;
                        }
                    } else {
                        if((virtual_x!=0 && nodes[virtual_x-1][virtual_y-1].winfo==Unknown) || (virtual_y!=1 && nodes[virtual_x][virtual_y-2].winfo==Unknown)){
                            exitflag2=true;
                        }
                    }
                    break;
                case 7:
                    if (virtual_y % 2 == 0) {
                        if((virtual_x!=0 && nodes[virtual_x-1][virtual_y].winfo==Unknown) || (virtual_y!=30 && nodes[virtual_x][virtual_y+1].winfo==Unknown)){
                            exitflag2=true;
                        }
                    } else {
                        if((virtual_x!=15 && nodes[virtual_x][virtual_y-1].winfo==Unknown) || (virtual_y!=1 && nodes[virtual_x][virtual_y-2].winfo==Unknown)){
                            exitflag2=true;
                        }
                    }
                    break;
                default:
                    error_out("想定外の値です。");
                    break;
            }
            if(exitflag2==true){
                break;
            }
        }


		sum_length++;

        if (mouse_dest == Goal) {
			for(i=0;*(GOALS+i)!=-1;i+=2){
                if(virtual_x==*(GOALS+i) && virtual_y==*(GOALS+i+1)){
                    exitflag=true;
                    break;
                }
            }
            if (exitflag) break;
		} else {
			if (virtual_x == 0 && virtual_y == 29) {
				break;
			}
		}
	}

	virtual_x=mouse_x;virtual_y=mouse_y;
    for(i=0;i<sum_length;i++){
        if(nodes[virtual_x][virtual_y].delay_exist==true){
            nodes[virtual_x][virtual_y].winfo=Exist;
            nodes[virtual_x][virtual_y].delay_exist=false;
        }

        switch (this_direction) {
            case 0:
                virtual_y-=1*2;
                break;
            case 1:
                virtual_y+=1*2;
                break;
            case 2:
                virtual_x-=1;
                break;
            case 3:
                virtual_x+=1;
                break;
            case 4:
                if (virtual_y % 2 == 0) {
                    virtual_x++;
                    virtual_y--;
                } else {
                    virtual_y--;
                }
                break;
            case 5:
                if (virtual_y % 2 == 0) {
                    virtual_y--;
                } else {
                    virtual_x--;
                    virtual_y--;
                }
                break;
            case 6:
                if (virtual_y % 2 == 0) {
                    virtual_y++;
                } else {
                    virtual_x--;
                    virtual_y++;
                }
                break;
            case 7:
                if (virtual_y % 2 == 0) {
                    virtual_x++;
                    virtual_y++;
                } else {
                    virtual_y++;
                }
                break;
            default:
                error_out("想定外の値です。");
                break;
        }


    }


    //移動開始！
	switch (this_direction) {
		case 0:
			relay_turn(90);
			relay_run(sum_length);
			runcost += sum_length==0 ? 0 : straightcost[sum_length - 1];
			break;
		case 1:
			relay_turn(270);
			relay_run(sum_length);
			runcost += sum_length==0 ? 0 : straightcost[sum_length - 1];
			break;
		case 2:
			relay_turn(180);
			relay_run(sum_length);
			runcost += sum_length==0 ? 0 : straightcost[sum_length - 1];
			break;
		case 3:
			relay_turn(0);
			relay_run(sum_length);
			runcost += sum_length==0 ? 0 : straightcost[sum_length - 1];
			break;
		case 4:
			relay_turn(mouse_y % 2 == 0 ? 0 : 90);
			relay_slalom(mouse_y % 2 == 0 ? 4 : 5, sum_length);
			runcost += sum_length==0 ? 0 : slalomcost[sum_length - 1];
			break;
		case 5:
			relay_turn(mouse_y % 2 == 0 ? 180 : 90);
			relay_slalom(mouse_y % 2 == 0 ? 6 : 7, sum_length);
			runcost += sum_length==0 ? 0 : slalomcost[sum_length - 1];
			break;
		case 6:
			relay_turn(mouse_y % 2 == 0 ? 180 : 270);
			relay_slalom(mouse_y % 2 == 0 ? 8 : 9, sum_length);
			runcost += sum_length==0 ? 0 : slalomcost[sum_length - 1];
			break;
		case 7:
			relay_turn(mouse_y % 2 == 0 ? 0 : 270);
			relay_slalom(mouse_y % 2 == 0 ? 10 : 11, sum_length);
			runcost += sum_length==0 ? 0 : slalomcost[sum_length - 1];
			break;
		default:
			error_out("想定外の値です。");
			break;
	}

    //内部座標における衝突チェック
    if (mouse_x < 0 || mouse_y < 0 || mouse_y > 30)
    {
        //外周の壁に衝突
        error_out("外周の壁に衝突");
    }
    else if (mouse_y % 2 == 0 && mouse_x > 14)
    {
        //外周の壁に衝突
        error_out("外周の壁に衝突");
    }
    else if (mouse_y % 2 == 1 && mouse_x > 15)
    {
        //外周の壁に衝突
        error_out("外周の壁に衝突");
    }
    else if (nodes[mouse_x][ mouse_y].winfo==Exist)
    {
        //内部の壁に衝突
        error_out("内部の壁に衝突");
    }

    return true;
}

void drop_goal(int destination_x,int destination_y){
    int now_x=mouse_x,now_y=mouse_y;
    int i;

    while(now_x!=destination_x || now_y!=destination_y){
        //周囲にゴールがないかどうかチェック
        if(now_y%2==0){
            if(now_x!=0 && nodes[now_x-1][now_y].winfo!=Exist){
                for(i=0;*(GOALS+i)!=-1;i+=2){
                    if(now_x-1==*(GOALS+i) && now_y==*(GOALS+i+1)){
                        nodes[now_x][now_y].next_direction=2;
                        return;
                    }
                }
            }
            if(now_x!=14 && nodes[now_x+1][now_y].winfo!=Exist){
                for(i=0;*(GOALS+i)!=-1;i+=2){
                    if(now_x+1==*(GOALS+i) && now_y==*(GOALS+i+1)){
                        nodes[now_x][now_y].next_direction=3;
                        return;
                    }
                }
            }
            if(now_y!=0 && nodes[now_x][now_y-1].winfo!=Exist){
                for(i=0;*(GOALS+i)!=-1;i+=2){
                    if(now_x==*(GOALS+i) && now_y-1==*(GOALS+i+1)){
                        nodes[now_x][now_y].next_direction=5;
                        return;
                    }
                }
            }
            if(now_y!=30 && nodes[now_x][now_y+1].winfo!=Exist){
                for(i=0;*(GOALS+i)!=-1;i+=2){
                    if(now_x==*(GOALS+i) && now_y+1==*(GOALS+i+1)){
                        nodes[now_x][now_y].next_direction=6;
                        return;
                    }
                }
            }
            if(now_y!=0 && nodes[now_x+1][now_y-1].winfo!=Exist){
                for(i=0;*(GOALS+i)!=-1;i+=2){
                    if(now_x+1==*(GOALS+i) && now_y-1==*(GOALS+i+1)){
                        nodes[now_x][now_y].next_direction=4;
                        return;
                    }
                }
            }
            if(now_y!=30 && nodes[now_x+1][now_y+1].winfo!=Exist){
                for(i=0;*(GOALS+i)!=-1;i+=2){
                    if(now_x+1==*(GOALS+i) && now_y+1==*(GOALS+i+1)){
                        nodes[now_x][now_y].next_direction=7;
                        return;
                    }
                }
            }
        }else{
            if(now_y!=1 && nodes[now_x][now_y-2].winfo!=Exist){
                for(i=0;*(GOALS+i)!=-1;i+=2){
                    if(now_x==*(GOALS+i) && now_y-2==*(GOALS+i+1)){
                        nodes[now_x][now_y].next_direction=0;
                        return;
                    }
                }
            }
            if(now_y!=29 && nodes[now_x][now_y+2].winfo!=Exist){
                for(i=0;*(GOALS+i)!=-1;i+=2){
                    if(now_x==*(GOALS+i) && now_y+2==*(GOALS+i+1)){
                        nodes[now_x][now_y].next_direction=1;
                        return;
                    }
                }
            }
            if(now_x!=0 && nodes[now_x-1][now_y-1].winfo!=Exist){
                for(i=0;*(GOALS+i)!=-1;i+=2){
                    if(now_x-1==*(GOALS+i) && now_y-1==*(GOALS+i+1)){
                        nodes[now_x][now_y].next_direction=5;
                        return;
                    }
                }
            }
            if(now_x!=0 && nodes[now_x-1][now_y+1].winfo!=Exist){
                for(i=0;*(GOALS+i)!=-1;i+=2){
                    if(now_x-1==*(GOALS+i) && now_y+1==*(GOALS+i+1)){
                        nodes[now_x][now_y].next_direction=6;
                        return;
                    }
                }
            }
            if(now_x!=15 && nodes[now_x][now_y-1].winfo!=Exist){
                for(i=0;*(GOALS+i)!=-1;i+=2){
                    if(now_x==*(GOALS+i) && now_y-1==*(GOALS+i+1)){
                        nodes[now_x][now_y].next_direction=4;
                        return;
                    }
                }
            }
            if(now_x!=15 && nodes[now_x][now_y+1].winfo!=Exist){
                for(i=0;*(GOALS+i)!=-1;i+=2){
                    if(now_x==*(GOALS+i) && now_y+1==*(GOALS+i+1)){
                        nodes[now_x][now_y].next_direction=7;
                        return;
                    }
                }
            }
        }

        switch(nodes[now_x][now_y].next_direction){
            case 0:
                now_y-=2;
                break;
            case 1:
                now_y+=2;
                break;
            case 2:
                now_x--;
                break;
            case 3:
                now_x++;
                break;
            case 4:
                if (now_y % 2 == 0) {
                    now_x++;
                    now_y--;
                } else {
                    now_y--;
                }
                break;
            case 5:
                if (now_y % 2 == 0) {
                    now_y--;
                } else {
                    now_x--;
                    now_y--;
                }
                break;
            case 6:
                if (now_y % 2 == 0) {
                    now_y++;
                } else {
                    now_x--;
                    now_y++;
                }
                break;
            case 7:
                if (now_y % 2 == 0) {
                    now_x++;
                    now_y++;
                } else {
                    now_y++;
                }
                break;
            default:
                error_out("想定外の値です。");
                break;
        }
    }
}

//destinationsは-1で終端！
//error_reportをtrueにしておくと、エラー時に何もせず返り値を座標(-1,-1)にして知らせます
int* dijkstra(int departure_x,int departure_y,const int *destinations,bool error_report) {
	int x, y,y2, now_x, now_y, tempcost;
	static int goal_result[2];
	bool exitflag=false;
	pqueue_data temp;
	int remain_flag;
	int nowcost;
	node *thisnode,*endofnode;
	const int *intptr;
	int initc;
    int initx,inity,range_x,range_y,xmax;//xmaxは空でないとわかった最終列

    remain_flag=flag_count;


	/*for (y=0;y<31;y++)
    {
        for(x=0;x<16;x++){
            //楽するため使わない要素にもセットしてる
            nodes[x][y].cost=USHRT_MAX;
            nodes[x][y].closed=false;

        }
    }*/

    endofnode=&(nodes[15][30]);
    thisnode=&(nodes[0][0]);
    thisnode--;
    do
    {
         //楽するため使わない要素にもセットしてる
         thisnode++;
         thisnode->cost=USHRT_MAX;
         thisnode->closed=false;

    }while(thisnode!=endofnode);

    //無駄な探索範囲を狭める
    initx=9;inity=12; //ギリギリ
    range_x=15;range_y=0;
    xmax=initx-1;
    for(y=inity;y>=0 && xmax!=15;y-=2){
    	for(x=0;x<=14;x++){
    		if(nodes[x][y].winfo!=Exist && xmax<x+1){
    			for(y2=y+1;y2<=30;y2+=2){
    				if(nodes[x+1][y2].winfo==Exist){
    					xmax++;
    					goto up;
    				}
    			}
    			range_x=x+1;range_y=y;
    			//printf("hit!\n");
    			goto dep;
    		}else if(nodes[x][y].winfo==Exist){
    			break;
    		}
    		up:;
    	}
    }
    dep:

	//スタート座標(最初は0.5前進する必要有)
	now_x = departure_x;
	now_y = departure_y;

	//一応キューをリセット
	pqueue_clear();

	nodes[now_x][ now_y].cost = 0;
	nodes[now_x][now_y].before_direction=9;//例外なので範囲外を指定

	while (true) {
        nowcost=nodes[now_x][now_y].cost;
		//上下方向
		if (now_y % 2 == 1) {
            temp.x=now_x;


            initc=now_y-2;
            for (y = initc;y>=range_y; y -= 2) {
                thisnode=&(nodes[now_x][y]);
                if (thisnode->winfo == Exist || y <= 0){
                    break;
                }
                if (thisnode->closed ==false) {
                    tempcost =
                            nowcost+ straightcost[((initc-y)>>1)];
                    assert_out(tempcost>=0);

                    if (thisnode->cost==USHRT_MAX) {
                        //temp.x = now_x;
                        temp.y = y;
                        temp.cost = tempcost;
                        pqueue_push(&temp);
                        thisnode->cost = tempcost;
                        thisnode->before_direction = 1;
                        thisnode->before_length = ((initc-y)>>1)+1;
                    }else if (thisnode->cost > tempcost) {
                        //temp.x = now_x;
                        temp.y = y;
                        temp.cost = tempcost;
                        pqueue_decrease(&temp);
                        thisnode->cost = tempcost;
                        thisnode->before_direction = 1;
                        thisnode->before_length = ((initc-y)>>1)+1;
                    }
                }
            }




            initc=now_y+2;
            for (y = initc;; y += 2) {
                thisnode=&(nodes[now_x][y]);
                if (thisnode->winfo == Exist || y > 29){
                    break;
                }
                if (thisnode->closed ==false) {
                    tempcost =
                            nowcost + straightcost[(y-initc)>>1];
                    assert_out(tempcost>=0);

                    if (thisnode->cost==USHRT_MAX) {
                        //temp.x = now_x;
                        temp.y = y;
                        temp.cost = tempcost;
                        pqueue_push(&temp);
                        thisnode->cost = tempcost;
                        thisnode->before_direction = 0;
                        thisnode->before_length = ((y-initc)>>1)+1;
                    }else if (thisnode->cost > tempcost) {
                        //temp.x = now_x;
                        temp.y = y;
                        temp.cost = tempcost;
                        pqueue_decrease(&temp);
                        thisnode->cost = tempcost;
                        thisnode->before_direction = 0;
                        thisnode->before_length = ((y-initc)>>1)+1;
                    }
                }
            }


		} else {
            temp.y=now_y;
            //左右方向


            initc=now_x-1;
            for (x = initc;; x--) {
                thisnode=&(nodes[x][now_y]);
                if (thisnode->winfo== Exist || x < 0){
                    break;
                }
                if (thisnode->closed ==false) {
                    tempcost =
                            nowcost + straightcost[initc-x];
                    assert_out(tempcost>=0);

                    if (thisnode->cost==USHRT_MAX) {
                        temp.x = x;
                        //temp.y = now_y;
                        temp.cost = tempcost;
                        pqueue_push(&temp);
                        thisnode->cost = tempcost;
                        thisnode->before_direction = 3;
                        thisnode->before_length = initc-x+1;

                    }else if (thisnode->cost > tempcost) {
                        temp.x = x;
                        //temp.y = now_y;
                        temp.cost = tempcost;
                        pqueue_decrease(&temp);
                        thisnode->cost = tempcost;
                        thisnode->before_direction = 3;
                        thisnode->before_length = initc-x+1;

                    }
                }
            }





            initc=now_x+1;
            for (x = now_x + 1;x<=range_x; x++) {
                thisnode=&(nodes[x][now_y]);
                if (thisnode->winfo == Exist || x > 14){
                    break;
                }
                if (thisnode->closed ==false) {
                    tempcost =
                            nowcost + straightcost[x-initc];
                    assert_out(tempcost>=0);
                    if (thisnode->cost==USHRT_MAX) {
                        temp.x = x;
                        //temp.y = now_y;
                        temp.cost = tempcost;
                        pqueue_push(&temp);
                        thisnode->cost = tempcost;
                        thisnode->before_direction = 2;
                        thisnode->before_length = x-initc+1;

                    }else if (thisnode->cost > tempcost) {
                        temp.x = x;
                        //temp.y = now_y;
                        temp.cost = tempcost;
                        pqueue_decrease(&temp);
                        thisnode->cost = tempcost;
                        thisnode->before_direction = 2;
                        thisnode->before_length = x-initc+1;

                    }
                }
            }

		}

		//右上方向
		initc=now_y-1;

        x = now_x;y=now_y;
        for (;;) {

            if (y % 2 == 0) {
                x++;
                y--;
            } else {
                y--;
            }
            if(x>range_x || y<range_y){
                	break;
                }
            thisnode=&(nodes[x][y]);
            if (thisnode->winfo == Exist || !(x <= ((y % 2 == 0) ? 14 : 15)) || !(y >= 0)){
                break;
            }
            if (thisnode->closed ==false) {
                tempcost =
                        nowcost + slalomcost[initc-y];
                assert_out(tempcost>=0);

                if (thisnode->cost==USHRT_MAX) {
                    temp.x = x;
                    temp.y = y;
                    temp.cost = tempcost;
                    pqueue_push(&temp);
                    thisnode->cost = tempcost;
                    thisnode->before_direction = 6;
                    thisnode->before_length = initc-y+1;

                }else if (thisnode->cost > tempcost) {
                    temp.x = x;
                    temp.y = y;
                    temp.cost = tempcost;
                    pqueue_decrease(&temp);
                    thisnode->cost = tempcost;
                    thisnode->before_direction = 6;
                    thisnode->before_length = initc-y+1;

                }
            }
        }



		//左上方向

        x = now_x;y=now_y;
        for (;;) {

            if (y % 2 == 0) {
                y--;
            } else {
                x--;
                y--;
            }
            if(y<range_y){
                	break;
                }
            thisnode=&(nodes[x][y]);
            if (thisnode->winfo == Exist || !(x >= 0) || !(y >= 0)){
                break;
            }
            if (thisnode->closed ==false) {
                tempcost =
                        nowcost + slalomcost[initc-y];
                assert_out(tempcost>=0);

                if (thisnode->cost==USHRT_MAX) {
                    temp.x = x;
                    temp.y = y;
                    temp.cost = tempcost;
                    pqueue_push(&temp);
                    thisnode->cost = tempcost;
                    thisnode->before_direction = 7;
                    thisnode->before_length =initc-y+1;

                }else if (thisnode->cost > tempcost) {
                    temp.x = x;
                    temp.y = y;
                    temp.cost = tempcost;
                    pqueue_decrease(&temp);
                    thisnode->cost = tempcost;
                    thisnode->before_direction = 7;
                    thisnode->before_length = initc-y+1;

                }
            }
        }


		//左下方向
		initc=now_y+1;

        x = now_x;y=now_y;
        for (;; ) {

            if (y % 2 == 0) {
                y++;
            } else {
                x--;
                y++;
            }
            thisnode=&(nodes[x][y]);
            if (thisnode->winfo == Exist || !(x >= 0) || !(y <= 30)){
                break;
            }
            if (thisnode->closed ==false) {
                tempcost =
                        nowcost + slalomcost[y-initc];
                assert_out(tempcost>=0);

                if (thisnode->cost==USHRT_MAX) {
                    temp.x = x;
                    temp.y = y;
                    temp.cost = tempcost;
                    pqueue_push(&temp);
                    thisnode->cost = tempcost;
                    thisnode->before_direction = 4;
                    thisnode->before_length = y-initc+1;

                }else if (thisnode->cost > tempcost) {
                    temp.x = x;
                    temp.y = y;
                    temp.cost = tempcost;
                    pqueue_decrease(&temp);
                    thisnode->cost = tempcost;
                    thisnode->before_direction = 4;
                    thisnode->before_length = y-initc+1;

                }
            }
        }


		//右下方向

        x = now_x;y=now_y;
        for (;;) {

            if (y % 2 == 0) {
                x++;
                y++;
            } else {
                y++;
            }
            if(x>range_x){
                	break;
                }
            thisnode=&(nodes[x][y]);
            if (thisnode->winfo == Exist || !(x <= ((y % 2 == 0) ? 14 : 15)) || !(y <= 30)){
                break;
            }
            if (thisnode->closed ==false) {
                tempcost =
                        nowcost + slalomcost[y-initc];
                assert_out(tempcost>=0);

                if (thisnode->cost==USHRT_MAX) {
                    temp.x = x;
                    temp.y = y;
                    temp.cost = tempcost;
                    pqueue_push(&temp);
                    thisnode->cost = tempcost;
                    thisnode->before_direction = 5;
                    thisnode->before_length = y-initc+1;

                }else if (thisnode->cost > tempcost) {
                    temp.x = x;
                    temp.y = y;
                    temp.cost = tempcost;
                    pqueue_decrease(&temp);
                    thisnode->cost = tempcost;
                    thisnode->before_direction = 5;
                    thisnode->before_length = y-initc+1;

                }
            }
        }


		nodes[now_x][now_y].closed=true;

		if(nodes[now_x][now_y].flag==true && destinations==NULL){
            remain_flag--;
		}
		if(remain_flag==0 && destinations==NULL){
            bool canbreak=true;
		    //ゴールまわりも全部見とかなあかん
            /*for(i=0;*(GOALS+i)!=-1;i+=2){
                if(nodes[*(GOALS+i)][*(GOALS+i+1)].winfo==NoWall && nodes[*(GOALS+i)][*(GOALS+i+1)].closed==false){
                    canbreak=false;
                    break;
                }
            }*/
            for(intptr=GOALS;*intptr!=-1;intptr+=2){
                if(nodes[*intptr][*(intptr+1)].winfo==NoWall && nodes[*intptr][*(intptr+1)].closed==false){
                    canbreak=false;
                    break;
                }
            }
            if(canbreak==true){
                break;
            }
        }

		//目的地についたら終了
		if(destinations!=NULL){
            /*for(i=0;*(destinations+i)!=-1;i+=2){
                if(now_x==*(destinations+i) && now_y==*(destinations+i+1)){
                    exitflag=true;
                    break;
                }
            }*/
            for(intptr=destinations;*intptr!=-1;intptr+=2){
                if(now_x==*intptr && now_y==*(intptr+1)){
                    exitflag=true;
                    break;
                }
            }
            if (exitflag) break;
		}

		if (pqueue_count[0] == 0 && pqueue_count[1] == 0 && pqueue_count[2] == 0 && pqueue_count[3] == 0) {
            if(error_report==false){
                break;
            }else{
                goal_result[0]=-1;goal_result[1]=-1;
                return goal_result;
            }
		}

		temp = pqueue_pop();

		now_x = temp.x;
		now_y = temp.y;
	}

	goal_result[0]=now_x;
	goal_result[1]=now_y;
	return goal_result;

}


void setflags(int departure_x, int departure_y, int destination_x, int destination_y){
    int now_x,now_y,i,x,y;
    int *goal_result;
    int inner_count;
    bool is_closeneed_map[64]; //多めに確保（サイズはいろいろなので）
    node *now_ptr;

    if(is_debug){
        printf("srouteinfo\n");
    }

    for (y=0;y<31;y++)
    {
        for(x=0;x<16;x++){
            //楽するため使わない要素にもセットしてる
            nodes[x][y].flag=false;
        }
    }
    flag_count=0;

    now_x=destination_x;
    now_y=destination_y;

    //目的地にも旗を
    if(nodes[destination_x][destination_y].winfo==Unknown){
        nodes[destination_x][destination_y].flag=true;
        nodes[destination_x][destination_y].subflag=false;
        flag_count++;
    }

    while(now_x!=departure_x || now_y!=departure_y){
        int now_len=nodes[now_x][now_y].before_length;
        int now_dir=nodes[now_x][now_y].before_direction;

        if(is_debug){
            printf("%d\n%d\n",now_x,now_y);
        }

        for(i=0;i<now_len;i++){
            switch(now_dir){
            case 0:
                now_y-=2;
                break;
            case 1:
                now_y+=2;
                break;
            case 2:
                now_x--;
                break;
            case 3:
                now_x++;
                break;
            case 4:
                if (now_y % 2 == 0) {
                    now_x++;
                    now_y--;
                } else {
                    now_y--;
                }
                break;
            case 5:
                if (now_y % 2 == 0) {
                    now_y--;
                } else {
                    now_x--;
                    now_y--;
                }
                break;
            case 6:
                if (now_y % 2 == 0) {
                    now_y++;
                } else {
                    now_x--;
                    now_y++;
                }
                break;
            case 7:
                if (now_y % 2 == 0) {
                    now_x++;
                    now_y++;
                } else {
                    now_y++;
                }
                break;
            default:
                error_out("想定外の値です。");
                break;
            }

            if(nodes[now_x][now_y].winfo==Unknown){
                nodes[now_x][now_y].flag=true;
                nodes[now_x][now_y].subflag=false;
                flag_count++;
            }
            if(is_debug){
                printf("%d\n%d\n",now_x,now_y);
            }
        }
    }

    if(is_debug){
        printf("-1\n");
    }

    int devide,trial,region;

    //-----補助旗の設置開始-----
    int start=(mouse_dest==Start?DEVIDE_START_TOSTART:DEVIDE_START_TOGOAL),end=(mouse_dest==Start?DEVIDE_END_TOSTART:DEVIDE_END_TOGOAL);
    int ems=(end-start>=0);
    if((mouse_dest==Start?REVERSE_TOSTART:REVERSE_TOGOAL)==0){
        for(devide=start;(ems)?(devide<=end):(devide>=end);devide+=((ems)?1:-1)){
            for(i=0;i<64;i++){
                is_closeneed_map[i]=true;
            }

            int d2=devide*devide;
            int mds=(mouse_dest==Start?TRIAL_TOSTART:TRIAL_TOGOAL);

            for(trial=0;trial<mds;trial++){
                for(region=0;region<d2;region++){
                    inner_count=0;
                    for (y=0;y<31;y++)
                    {
                        for(x=0;x<16;x++){
                            if((y%2==0&&x>=15)||(y%2==1&&x>=16)){
                                continue;
                            }

                            int rx1,ry1;
                            ry1=y/(31/devide);
                            if(y%2==0){
                                rx1=x/(15/devide);
                            }else{
                                rx1=x/(16/devide);
                            }
                            if(rx1>=devide){
                                rx1=devide-1;
                            }
                            if(ry1>=devide){
                                ry1=devide-1;
                            }

                            if(ry1*devide+rx1==region){
                                if(nodes[x][y].flag==true){
                                    nodes[x][y].winfo=Exist;
                                    inner_count++;
                                }
                            }
                        }
                    }

                    if(inner_count==0){
                        continue;
                    }

                    if(is_closeneed_map[region]==false){
                        goto skip;
                    }

                    goal_result=dijkstra(0,29,GOALS,true);

                    if(goal_result[0]!=-1){
                        now_x=goal_result[0];
                        now_y=goal_result[1];

                        //目的地にも旗を
                        if(nodes[goal_result[0]][goal_result[1]].flag==false && nodes[goal_result[0]][goal_result[1]].winfo==Unknown){
                            nodes[goal_result[0]][goal_result[1]].flag=true;
                            nodes[goal_result[0]][goal_result[1]].subflag=true;
                            flag_count++;
                        }
                        now_ptr=&(nodes[now_x][now_y]);
                        while(now_x!=0 || now_y!=29){

                            int now_len=now_ptr->before_length;
                            int now_dir=now_ptr->before_direction;

                            for(i=0;i<now_len;i++){
                                switch(now_dir){
                                case 0:
                                    now_y-=2;
                                    break;
                                case 1:
                                    now_y+=2;
                                    break;
                                case 2:
                                    now_x--;
                                    break;
                                case 3:
                                    now_x++;
                                    break;
                                case 4:
                                    if (now_y % 2 == 0) {
                                        now_x++;
                                        now_y--;
                                    } else {
                                        now_y--;
                                    }
                                    break;
                                case 5:
                                    if (now_y % 2 == 0) {
                                        now_y--;
                                    } else {
                                        now_x--;
                                        now_y--;
                                    }
                                    break;
                                case 6:
                                    if (now_y % 2 == 0) {
                                        now_y++;
                                    } else {
                                        now_x--;
                                        now_y++;
                                    }
                                    break;
                                case 7:
                                    if (now_y % 2 == 0) {
                                        now_x++;
                                        now_y++;
                                    } else {
                                        now_y++;
                                    }
                                    break;
                                default:
                                    error_out("想定外の値です。");
                                    break;
                                }
                                now_ptr=&(nodes[now_x][now_y]);
                                if(now_ptr->flag==false && now_ptr->winfo==Unknown){
                                    now_ptr->flag=true;
                                    now_ptr->subflag=true;
                                    flag_count++;
                                }
                            }
                        }
                    }else{
                        is_closeneed_map[region]=false;
                    }

        skip:
                    for (y=0;y<31;y++)
                    {
                        for(x=0;x<16;x++){
                            if(nodes[x][y].flag==true){
                                nodes[x][y].winfo=Unknown;
                            }
                        }
                    }
                }
            }
        }
    }else{
        int mds=(mouse_dest==Start?TRIAL_TOSTART:TRIAL_TOGOAL);
        for(trial=0;trial<mds;trial++){
            for(devide=start;(ems)?(devide<=end):(devide>=end);devide+=((ems)?1:-1)){
                for(i=0;i<64;i++){
                    is_closeneed_map[i]=true;
                }

                int d2=devide*devide;
                for(region=0;region<d2;region++){
                    inner_count=0;
                    for (y=0;y<31;y++)
                    {
                        for(x=0;x<16;x++){
                            if((y%2==0&&x>=15)||(y%2==1&&x>=16)){
                                continue;
                            }

                            int rx1,ry1;
                            ry1=y/(31/devide);
                            if(y%2==0){
                                rx1=x/(15/devide);
                            }else{
                                rx1=x/(16/devide);
                            }
                            if(rx1>=devide){
                                rx1=devide-1;
                            }
                            if(ry1>=devide){
                                ry1=devide-1;
                            }

                            if(ry1*devide+rx1==region){
                                if(nodes[x][y].flag==true){
                                    nodes[x][y].winfo=Exist;
                                    inner_count++;
                                }
                            }
                        }
                    }

                    if(inner_count==0){
                        continue;
                    }

                    if(is_closeneed_map[region]==false){
                        goto skip2;
                    }

                    goal_result=dijkstra(0,29,GOALS,true);

                    if(goal_result[0]!=-1){
                        now_x=goal_result[0];
                        now_y=goal_result[1];

                        //目的地にも旗を
                        if(nodes[goal_result[0]][goal_result[1]].flag==false && nodes[goal_result[0]][goal_result[1]].winfo==Unknown){
                            nodes[goal_result[0]][goal_result[1]].flag=true;
                            nodes[goal_result[0]][goal_result[1]].subflag=true;
                            flag_count++;
                        }

                        now_ptr=&(nodes[now_x][now_y]);
                        while(now_x!=0 || now_y!=29){

                            int now_len=now_ptr->before_length;
                            int now_dir=now_ptr->before_direction;

                            for(i=0;i<now_len;i++){
                                switch(now_dir){
                                case 0:
                                    now_y-=2;
                                    break;
                                case 1:
                                    now_y+=2;
                                    break;
                                case 2:
                                    now_x--;
                                    break;
                                case 3:
                                    now_x++;
                                    break;
                                case 4:
                                    if (now_y % 2 == 0) {
                                        now_x++;
                                        now_y--;
                                    } else {
                                        now_y--;
                                    }
                                    break;
                                case 5:
                                    if (now_y % 2 == 0) {
                                        now_y--;
                                    } else {
                                        now_x--;
                                        now_y--;
                                    }
                                    break;
                                case 6:
                                    if (now_y % 2 == 0) {
                                        now_y++;
                                    } else {
                                        now_x--;
                                        now_y++;
                                    }
                                    break;
                                case 7:
                                    if (now_y % 2 == 0) {
                                        now_x++;
                                        now_y++;
                                    } else {
                                        now_y++;
                                    }
                                    break;
                                default:
                                    error_out("想定外の値です。");
                                    break;
                                }
                                now_ptr=&(nodes[now_x][now_y]);
                                if(now_ptr->flag==false && now_ptr->winfo==Unknown){
                                    now_ptr->flag=true;
                                    now_ptr->subflag=true;
                                    flag_count++;
                                }
                            }
                        }
                    }else{
                        is_closeneed_map[region]=false;
                    }

        skip2:
                    for (y=0;y<31;y++)
                    {
                        for(x=0;x<16;x++){
                            if(nodes[x][y].flag==true){
                                nodes[x][y].winfo=Unknown;
                            }
                        }
                    }
                }
            }
        }

    }

    return;
}

int* nearestflag(){
    int x,y,i;
    int mincost,minx=-1,miny=-1;
    int remain_flag=flag_count;
    int min_lookback=INT_MAX,minx_lb=-1,miny_lb=-1;
    int good_destdist;
    int min_goal=INT_MAX,minx_g=-1,miny_g=-1;
    bool nonsubflag_exist=false;
    static int result[3];

    //非subflagがあるか事前チェック
    for (y=0;y<=30 ;y+=2 )
    {
        for (x=0;x<=14 ;x++ )
        {
            if(remain_flag==0){
                goto phase1;
            }
            if(nodes[x][y].flag==true){
                if(nodes[x][y].subflag==false){
                    nonsubflag_exist=true;
                }
                remain_flag--;
            }
        }
    }

    for (y=1;y<=30 ;y+=2 )
    {
        for (x=0;x<=15 ;x++ )
        {
            if(remain_flag==0){
                goto phase1;
            }
            if(nodes[x][y].flag==true){
                if(nodes[x][y].subflag==false){
                    nonsubflag_exist=true;
                }
                remain_flag--;
            }
        }
    }

phase1:

    if(nonsubflag_exist==false){
        return NULL;
    }


    //ゴール優先のチェック
    if(mouse_dest==Goal){
        for(i=0;*(GOALS+i)!=-1;i+=2){
            if(nodes[*(GOALS+i)][*(GOALS+i+1)].flag==true){
                if(nodes[*(GOALS+i)][*(GOALS+i+1)].cost<min_goal){
                    min_goal=nodes[*(GOALS+i)][*(GOALS+i+1)].cost;
                    minx_g=*(GOALS+i); miny_g=*(GOALS+i+1);
                }
            }
        }
        if(GOGOAL_LIMIT!=255 && min_goal>GOGOAL_LIMIT){
            min_goal=INT_MAX;
        }
        if(min_goal!=INT_MAX){
            goto end;
        }
    }

    if(true){
        remain_flag=flag_count;
        for (y=0;y<=30 ;y+=2 )
        {
            for (x=0;x<=14 ;x++ )
            {
                if(remain_flag==0){
                    goto phase3;
                }
                if(nodes[x][y].flag==true){
                    if(nodes[x][y].subflag==false){
                        nonsubflag_exist=true;
                    }
                    remain_flag--;
                    if(fillalgorithm(x,y)<=LOOKBACK_LIMITSIZE && nodes[x][y].cost<min_lookback){
                        min_lookback=nodes[x][y].cost;
                        minx_lb=x; miny_lb=y;
                    }
                }
            }
        }

        for (y=1;y<=30 ;y+=2 )
        {
            for (x=0;x<=15 ;x++ )
            {
                if(remain_flag==0){
                    goto phase3;
                }
                if(nodes[x][y].flag==true){
                    if(nodes[x][y].subflag==false){
                        nonsubflag_exist=true;
                    }
                    remain_flag--;
                    if(fillalgorithm(x,y)<=LOOKBACK_LIMITSIZE && nodes[x][y].cost<min_lookback){
                        min_lookback=nodes[x][y].cost;
                        minx_lb=x; miny_lb=y;
                    }
                }
            }
        }



    }

phase3:
    if(min_lookback>LOOKBACK_LIMITDISTANCE){
        min_lookback=INT_MAX;
    }

    if(min_lookback==INT_MAX){
        if(mouse_dest==Start){
            good_destdist=INT_MIN;
        }else{
            good_destdist=INT_MAX;
        }

        mincost=INT_MAX;

        //mincostを前もって求めておく
        for (y=0;y<31;y++)
        {
            for(x=0;x<16;x++){
                if((y%2==0&&x>=15)||(y%2==1&&x>=16)){
                    continue;
                }

                if(nodes[x][y].flag==true){
                    if(nodes[x][y].cost<mincost){
                        mincost=nodes[x][y].cost;
                    }
                }
            }
        }



        remain_flag=flag_count;
        for (y=0;y<=30 ;y+=2 )
        {
            for (x=0;x<=14 ;x++ )
            {
                if(remain_flag==0){
                    goto end;
                }
                if(nodes[x][y].flag==true){
                    if(nodes[x][y].subflag==false){
                        nonsubflag_exist=true;
                    }
                    remain_flag--;
                    if(PERMISSIBLE_RANGE==255 || nodes[x][y].cost<=mincost+PERMISSIBLE_RANGE){
                        if(mouse_dest==Start){
                            if(nodes[x][y].cost_fromdest>good_destdist){
                                minx=x;miny=y;
                                good_destdist=nodes[x][y].cost_fromdest;
                            }
                        }else{
                            if(nodes[x][y].cost_fromdest<good_destdist){
                                minx=x;miny=y;
                                good_destdist=nodes[x][y].cost_fromdest;
                            }
                        }
                    }
                }
            }
        }

        for (y=1;y<=30 ;y+=2 )
        {
            for (x=0;x<=15 ;x++ )
            {
                if(remain_flag==0){
                    goto end;
                }
                if(nodes[x][y].flag==true){
                    if(nodes[x][y].subflag==false){
                        nonsubflag_exist=true;
                    }
                    remain_flag--;
                    if(PERMISSIBLE_RANGE==255 || nodes[x][y].cost<=mincost+PERMISSIBLE_RANGE){
                        if(mouse_dest==Start){
                            if(nodes[x][y].cost_fromdest>good_destdist){
                                minx=x;miny=y;
                                good_destdist=nodes[x][y].cost_fromdest;
                            }
                        }else{
                            if(nodes[x][y].cost_fromdest<good_destdist){
                                minx=x;miny=y;
                                good_destdist=nodes[x][y].cost_fromdest;
                            }
                        }
                    }
                }
            }
        }
    }


end:
    if(min_goal!=INT_MAX){
        result[0]=minx_g;
        result[1]=miny_g;
        result[2]=-1;
        return result;
    }else if(min_lookback!=INT_MAX){
        result[0]=minx_lb;
        result[1]=miny_lb;
        result[2]=-1;
        return result;
    }else{
        result[0]=minx;
        result[1]=miny;
        result[2]=-1;
        return result;
    }

}



void setroute(int departure_x, int departure_y, int destination_x, int destination_y,bool reverse){
    int now_x,now_y,i;

    now_x=destination_x;
    now_y=destination_y;

    if(is_debug){
        printf("nrouteinfo\n");
    }

    while(now_x!=departure_x || now_y!=departure_y){
        int now_len=nodes[now_x][now_y].before_length;
        int now_dir=nodes[now_x][now_y].before_direction;

        if(is_debug){
            printf("%d\n%d\n",now_x,now_y);
        }

        if(reverse==true){
            nodes[now_x][now_y].next_direction=now_dir;
        }

        for(i=0;i<now_len;i++){
            switch(now_dir){
            case 0:
                now_y-=2;
                break;
            case 1:
                now_y+=2;
                break;
            case 2:
                now_x--;
                break;
            case 3:
                now_x++;
                break;
            case 4:
                if (now_y % 2 == 0) {
                    now_x++;
                    now_y--;
                } else {
                    now_y--;
                }
                break;
            case 5:
                if (now_y % 2 == 0) {
                    now_y--;
                } else {
                    now_x--;
                    now_y--;
                }
                break;
            case 6:
                if (now_y % 2 == 0) {
                    now_y++;
                } else {
                    now_x--;
                    now_y++;
                }
                break;
            case 7:
                if (now_y % 2 == 0) {
                    now_x++;
                    now_y++;
                } else {
                    now_y++;
                }
                break;
            default:
                error_out("想定外の値です。");
                break;
            }

            if(reverse==false){
                nodes[now_x][now_y].next_direction=reverse_direction[now_dir];
            }else{
                nodes[now_x][now_y].next_direction=now_dir;
            }
            if(is_debug){
                printf("%d\n%d\n",now_x,now_y);
            }
        }
    }
    if(is_debug){
        printf("-1\n");
    }
}


void relay_run(int length) {
	switch (mouse_angle) {
		case 0:
			mouse_x += length;
			break;
		case 90:
			mouse_y -= length * 2;
			break;
		case 180:
			mouse_x -= length;
			break;
		case 270:
			mouse_y += length * 2;
			break;
		default:
            error_out("想定外の値です...switch");
            break;
	}

	//lengthだけ進む制御プログラムをここに記述
	ll_straight(length);
}

void relay_half() {

	ll_half();
	return;
}

void relay_slalom(int direction, int length) {
	int i, now = direction;

	for (i = 0; i < length; i++) {
		switch (now) {
			case 4: //yが偶数
				mouse_angle = 90;
				mouse_x++;
				mouse_y--;
				ll_slalom(now);
				now = 5;

				break;
			case 5: //yが奇数
				mouse_angle = 0;
				mouse_y--;
				ll_slalom(now);
				now = 4;

				break;
			case 6:
				mouse_angle = 90;
				mouse_y--;
				ll_slalom(now);
				now = 7;

				break;
			case 7:
				mouse_angle = 180;
				mouse_x--;
				mouse_y--;
				ll_slalom(now);
				now = 6;

				break;
			case 8:
				mouse_angle = 270;
				mouse_y++;
				ll_slalom(now);
				now = 9;

				break;
			case 9:
				mouse_angle = 180;
				mouse_x--;
				mouse_y++;
				ll_slalom(now);
				now = 8;

				break;
			case 10:
				mouse_angle = 270;
				mouse_x++;
				mouse_y++;
				ll_slalom(now);
				now = 11;

				break;
			case 11:
				mouse_angle = 0;
				mouse_y++;
				ll_slalom(now);
				now = 10;

				break;
			default:
				error_out("想定外の値です...switch");
				break;
		}
	}
}

//希望の角度に、自動で回転角度を計算して回転します
int relay_turn(int a) {
	int before = mouse_angle;
	int temp = a - before;

	if (temp > 180) {
		temp = (360 - temp) * -1;
	}
	if (temp < -180) {
		temp += 360;
	}
	if (temp != 0) {
		//tempだけ回転する制御プログラムをここに書く
		ll_turn(temp);

		if(abs(temp)==180){
            runcost+=turn180cost;
		}
	}
	mouse_angle = a;
	assert_out(temp == 0 || abs(temp) == 90 || abs(temp) == 180);
	return temp;
}

//センサー番号を指定して壁の有無を読み取り
//0:前(1)　1:前(2)　 2:左 　3:右
//NoWall or exist を返す
wallinfo relay_sense(int sensor_no) {
	wallinfo ret;
	int watchx, watchy;

	switch (mouse_angle) {
		case 0:
			switch (sensor_no) {
				case 0:
				case 1:
					watchx = mouse_x + 1;
					watchy = mouse_y;
					break;
				case 2:
					watchx = mouse_x + 1;
					watchy = mouse_y - 1;
					break;
				case 3:
					watchx = mouse_x + 1;
					watchy = mouse_y + 1;
					break;
				default:
                    error_out("想定外の値です...switch");
                    break;
			}
			break;
		case 90:
			switch (sensor_no) {
				case 0:
				case 1:
					watchx = mouse_x;
					watchy = mouse_y - 2;
					break;
				case 2:
					watchx = mouse_x - 1;
					watchy = mouse_y - 1;
					break;
				case 3:
					watchx = mouse_x;
					watchy = mouse_y - 1;
					break;
				default:
                    error_out("想定外の値です...switch");
                    break;
			}
			break;
		case 180:
			switch (sensor_no) {
				case 0:
				case 1:
					watchx = mouse_x - 1;
					watchy = mouse_y;
					break;
				case 2:
					watchx = mouse_x;
					watchy = mouse_y + 1;
					break;
				case 3:
					watchx = mouse_x;
					watchy = mouse_y - 1;
					break;
				default:
                    error_out("想定外の値です...switch");
                    break;
			}
			break;
		case 270:
			switch (sensor_no) {
				case 0:
				case 1:
					watchx = mouse_x;
					watchy = mouse_y + 2;
					break;
				case 2:
					watchx = mouse_x;
					watchy = mouse_y + 1;
					break;
				case 3:
					watchx = mouse_x - 1;
					watchy = mouse_y + 1;
					break;
				default:
                    error_out("想定外の値です...switch");
                    break;
			}
			break;
		default:
			error_out("斜め状態でセンサー読み取りをしようとしました。");
			return Exist;
			break;
	}

	ret = loadedmeiro[watchx][watchy].winfo;

	assert_out(ret == Exist || ret == NoWall);

	return ret;
}

void prepare_centercheck(){
    int x,y;
    int pattern[5]; //マウス位置、中央上下左右のnext_directionにセットするもの

    for (y=0;y<31;y++)
    {
        for(x=0;x<16;x++){
            //楽するため使わない要素にもセットしてる
            nodes[x][y].flag=false;
        }
    }
    flag_count=0;

    if(mouse_x==7 && mouse_y==13){
        pattern[0]=1;pattern[1]=5;pattern[2]=4;pattern[3]=7;pattern[4]=5;

    }else if(mouse_x==8 && mouse_y==13){
        pattern[0]=1;pattern[1]=4;pattern[2]=5;pattern[3]=4;pattern[4]=6;

    }else if(mouse_x==6 && mouse_y==14){
        pattern[0]=3;pattern[1]=7;pattern[2]=5;pattern[3]=5;pattern[4]=6;

    }else if(mouse_x==8 && mouse_y==14){
        pattern[0]=2;pattern[1]=6;pattern[2]=4;pattern[3]=7;pattern[4]=4;

    }else if(mouse_x==6 && mouse_y==16){
        pattern[0]=3;pattern[1]=6;pattern[2]=4;pattern[3]=6;pattern[4]=5;

    }else if(mouse_x==8 && mouse_y==16){
        pattern[0]=2;pattern[1]=7;pattern[2]=5;pattern[3]=4;pattern[4]=7;

    }else if(mouse_x==7 && mouse_y==17){
        pattern[0]=0;pattern[1]=7;pattern[2]=6;pattern[3]=4;pattern[4]=6;

    }else if(mouse_x==8 && mouse_y==17){
        pattern[0]=0;pattern[1]=6;pattern[2]=7;pattern[3]=7;pattern[4]=5;

    }

    nodes[mouse_x][mouse_y].next_direction=pattern[0];
    nodes[7][14].next_direction=pattern[1];
    nodes[7][16].next_direction=pattern[2];
    nodes[7][15].next_direction=pattern[3];
    nodes[8][15].next_direction=pattern[4];

    center_checking=true;

    return;
}

//未探索の場所を探索済みにしてしまう（最短経路固定のため）
void fix_shortestpath(){
    int x,y;
    for(y=0;y<31;y++){
        for(x=0;x<16;x++){
            if(nodes[x][y].winfo==Unknown){
                nodes[x][y].winfo=Exist;
            }
        }
    }
    shortestpath_fixed=true;
    return;
}


int fillalgorithm(int flag_x,int flag_y){
	fstack_data set,read;
	int x,y,rx,ry;
	int count=0;

	if(nodes[flag_x][flag_y].flag==false){
        return 0;
	}

	for (y=0;y<31;y++)
    {
        for(x=0;x<16;x++){
            nodes[x][y].marked=false;
        }
    }
	fstack_clear();
	//最初の基準点をプッシュ
	set.x=flag_x; set.y=flag_y;
	fstack_push(set);
	count++;

	while(fstack_count>0){
		read=fstack_pop();
		rx=read.x;ry=read.y;

        //近くに旗がないか探す！
        if(ry%2==0){
            if(rx-1>=0 && nodes[rx-1][ry].flag==true){
                if(nodes[rx-1][ry].marked==false){
                    nodes[rx-1][ry].marked=true;
                    set.x=rx-1; set.y=ry;
                    fstack_push(set);
                    count++;
                }
            }
            if(rx+1<=14 && nodes[rx+1][ry].flag==true){
                if(nodes[rx+1][ry].marked==false){
                    nodes[rx+1][ry].marked=true;
                    set.x=rx+1; set.y=ry;
                    fstack_push(set);
                    count++;
                }
            }

            if(ry-1>=0 && rx>=0 && nodes[rx][ry-1].flag==true){
                if(nodes[rx][ry-1].marked==false){
                    nodes[rx][ry-1].marked=true;
                    set.x=rx; set.y=ry-1;
                    fstack_push(set);
                    count++;
                }
            }
            if(ry-1>=0 && rx+1<=15 && nodes[rx+1][ry-1].flag==true){
                if(nodes[rx+1][ry-1].marked==false){
                    nodes[rx+1][ry-1].marked=true;
                    set.x=rx+1; set.y=ry-1;
                    fstack_push(set);
                    count++;
                }
            }
            if(ry+1<=30 && rx>=0 && nodes[rx][ry+1].flag==true){
                if(nodes[rx][ry+1].marked==false){
                    nodes[rx][ry+1].marked=true;
                    set.x=rx; set.y=ry+1;
                    fstack_push(set);
                    count++;
                }
            }
            if(ry+1<=30 && rx+1<=15 && nodes[rx+1][ry+1].flag==true){
                if(nodes[rx+1][ry+1].marked==false){
                    nodes[rx+1][ry+1].marked=true;
                    set.x=rx+1; set.y=ry+1;
                    fstack_push(set);
                    count++;
                }
            }
        }else{
            if(ry-2>=0 && nodes[rx][ry-2].flag==true){
                if(nodes[rx][ry-2].marked==false){
                    nodes[rx][ry-2].marked=true;
                    set.x=rx; set.y=ry-2;
                    fstack_push(set);
                    count++;
                }
            }
            if(ry+2<=30 && nodes[rx][ry+2].flag==true){
                if(nodes[rx][ry+2].marked==false){
                    nodes[rx][ry+2].marked=true;
                    set.x=rx; set.y=ry+2;
                    fstack_push(set);
                    count++;
                }
            }

            if(ry-1>=0 && rx<=14 && nodes[rx][ry-1].flag==true){
                if(nodes[rx][ry-1].marked==false){
                    nodes[rx][ry-1].marked=true;
                    set.x=rx; set.y=ry-1;
                    fstack_push(set);
                    count++;
                }
            }
            if(ry-1>=0 && rx-1>=0 && nodes[rx-1][ry-1].flag==true){
                if(nodes[rx-1][ry-1].marked==false){
                    nodes[rx-1][ry-1].marked=true;
                    set.x=rx-1; set.y=ry-1;
                    fstack_push(set);
                    count++;
                }
            }
            if(ry+1<=30 && rx<=14 && nodes[rx][ry+1].flag==true){
                if(nodes[rx][ry+1].marked==false){
                    nodes[rx][ry+1].marked=true;
                    set.x=rx; set.y=ry+1;
                    fstack_push(set);
                    count++;
                }
            }
            if(ry+1<=30 && rx-1>=0 && nodes[rx-1][ry+1].flag==true){
                if(nodes[rx-1][ry+1].marked==false){
                    nodes[rx-1][ry+1].marked=true;
                    set.x=rx-1; set.y=ry+1;
                    fstack_push(set);
                    count++;
                }
            }
        }

	}

	return count;

}

void recalc(){
    int *goal_result;
    int x,y;
    int gx,gy;//保存しとかないとsetflagsで失われる
    goal_result=dijkstra(0,29,GOALS,false);
    gx=goal_result[0]; gy=goal_result[1];
    setflags(0,29,goal_result[0],goal_result[1]);
    if(mouse_dest==Start){
        dijkstra(0,29,NULL,false);
    }else{
        dijkstra(gx,gy,NULL,false);
    }

    for (y=0;y<31;y++)
    {
        for(x=0;x<16;x++){
            nodes[x][y].cost_fromdest=nodes[x][y].cost;
        }
    }
    dijkstra(mouse_x,mouse_y,NULL,false);

    return;
}
