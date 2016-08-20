#ifndef HEADER_MAIN
#define HEADER_MAIN

//定数
#define FSTACKSIZE 200
#define PQUEUESIZE 480

#define ENDCOUNT 11

//列挙体
typedef enum{false=0,true=1} bool;
typedef enum{Unknown=0,NoWall=1,Exist=2} wallinfo;
typedef enum{Start=0,Goal=1} destination;

//構造体
typedef struct {
    unsigned short cost;
    unsigned short cost_fromdest; //目的地からの距離をセットしておく
    unsigned int before_length:5;
    unsigned int before_direction:3;
    unsigned int next_direction:3;
    unsigned int flag:1;
    unsigned int subflag:1;
    unsigned int closed:1;
    unsigned int marked:1; //補助旗の場合はsubflag==true
    unsigned int delay_exist:1; //“壁有”をセットするのを遅らせます（マウスがいるところをexistにできないから）
    unsigned int winfo:2;
} node;


typedef struct {
    unsigned char x;
    unsigned char y;
} fstack_data;

typedef struct {
    unsigned short cost;
    unsigned char x;
    unsigned char y;
} pqueue_data;


//main.c
extern bool is_shortest;

//pqueue.c
void pqueue_clear();
void pqueue_push(const pqueue_data *x);
pqueue_data pqueue_pop();
void pqueue_decrease(const pqueue_data *target);
extern int pqueue_count[];


//fstack.c
void fstack_push(fstack_data data);
fstack_data fstack_pop();
void fstack_clear();
extern int fstack_count;

//core.c
int extracost(int begin_x,int begin_y,int direction,const int *dest);
extern bool center_checked;
extern node nodes[16][31];
void recalc();
bool nextstep();
int* dijkstra(int departure_x,int departure_y,const int *destinations,bool error_report);
void setflags(int departure_x, int departure_y, int destination_x, int destination_y);
int* nearestflag();
void setroute(int departure_x, int departure_y, int destination_x, int destination_y,bool reverse);
void drop_goal(int destination_x,int destination_y);
void relay_run(int length);
void relay_half();
void relay_slalom(int direction, int length);
int relay_turn(int a);
wallinfo relay_sense(int sensor_no);
void infer_wall(int temp_x,int temp_y);
void prepare_centercheck();
void fix_shortestpath();
bool is_otherflagexist(int flag_x,int flag_y);
int fillalgorithm(int flag_x,int flag_y);
void fukurokoji_remove(int x,int y);

extern int mouse_x;
extern int mouse_y;
extern int mouse_angle;
extern int mouse_runcount;
extern int flag_count;
extern bool shortestpath_fixed;
extern destination mouse_dest;

#define assert_out(b)	\
{if(!(b)){printf("error\n%s\n%d\n%s\n", __FILE__, __LINE__,#b); exit(-1); }}

#define error_out(str)	\
{printf("error\n%s\n%d\n%s\n", __FILE__, __LINE__,str); exit(-1); }

//lowlevel.c
void ll_straight(int length);
void ll_half();
void ll_slalom(int direction);
void ll_turn(int angle);
wallinfo ll_sense(int sensor_no);
void ll_fwr();

//utility.c
void load_meiro(char *filename);
extern node loadedmeiro[16][31];

//test.c
extern int runcost;

//const.c
extern int straightcost[];
extern int slalomcost[];
extern const int GOALS[];
extern int turn180cost;
extern int DEVIDE_START_TOSTART,DEVIDE_END_TOSTART,TRIAL_TOSTART,REVERSE_TOSTART;
extern int DEVIDE_START_TOGOAL,DEVIDE_END_TOGOAL,TRIAL_TOGOAL,REVERSE_TOGOAL;
extern int LOOKBACK_LIMITSIZE,LOOKBACK_LIMITDISTANCE,GOGOAL_LIMIT,PERMISSIBLE_RANGE;

//debug.h
void inform_flag();
void inform_wall();
void inform_message(char *msg);
extern bool is_debug;



extern int max_fstack;
extern int max_pqueue;
extern int max_cost;

#endif
