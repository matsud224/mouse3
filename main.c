#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "header.h"
#include "getopt.h"


bool is_shortest=false;//���H���������Ƀ��[�h������ԁi���H�����łɒm���Ă�j�Ƃ��ăX�^�[�g
bool is_eval=false; //�ꊇ�]�����[�h�i�t�@�C�����͓K���Łj

int main(int argc, char *argv[]) {
	int opt, i,x,y, argpos = 0;
	char *filename;
	char *meiropath;
	char meirofullpath[512];

    is_debug=true;

	opterr = 0; //getopt�ɂ��G���[�\���}��
	while ((opt = getopt(argc, argv, "sne")) != -1) {
		switch (opt) {
			case 's':
				is_shortest=true;
				break;
            case 'n':
                is_debug=false;
                break;
            case 'e':
                is_eval=true;
                break;
			default:
				error_out("�R�}���h���C���I�v�V�����Ɍ�肪����܂��B");
				break;
		}
	}

	argc -= optind;
	argv += optind;

	/*
	 argv[0] ... filename
	 argv[1]~ ...�p�����[�^
	 */
	filename = argv[0];
	argpos++;
	meiropath = getenv("MEIRO_PATH");
	if (meiropath == NULL) {
		error_out("���[�U�[���ϐ� MEIRO_PATH �����ݒ�ł��B");
	}

	//�p�����[�^�̃��[�h
	//�S���[�h���ʂ̂���
	//straightcost
	for (i = 0; i < 30; i++) {
		straightcost[i] = atoi(argv[argpos]);
		argpos++;
	}
	//slalomcost
	for (i = 0; i < 30; i++) {
		slalomcost[i] = atoi(argv[argpos]);
		argpos++;
	}

    turn180cost = atoi(argv[argpos]);
	argpos++;

    DEVIDE_START_TOSTART = atoi(argv[argpos]);
	argpos++;
	DEVIDE_END_TOSTART = atoi(argv[argpos]);
	argpos++;
	TRIAL_TOSTART = atoi(argv[argpos]);
	argpos++;
	REVERSE_TOSTART = atoi(argv[argpos]);
	argpos++;

	DEVIDE_START_TOGOAL = atoi(argv[argpos]);
	argpos++;
	DEVIDE_END_TOGOAL = atoi(argv[argpos]);
	argpos++;
	TRIAL_TOGOAL = atoi(argv[argpos]);
	argpos++;
	REVERSE_TOGOAL = atoi(argv[argpos]);
	argpos++;

	LOOKBACK_LIMITSIZE = atoi(argv[argpos]);
	argpos++;
	LOOKBACK_LIMITDISTANCE = atoi(argv[argpos]);
	argpos++;
	GOGOAL_LIMIT = atoi(argv[argpos]);
	argpos++;
	PERMISSIBLE_RANGE = atoi(argv[argpos]);
	argpos++;

    printf("msg\nmouse3 - type b\n");

    mouse_runcount=0;

    if(is_eval==true){
        DIR *dir;
        struct dirent *dp;
        char *curr1=".";
        char *curr2="..";
        char *ignore="gmon.out";
        int meirocount=0,nowcount=0;

        dir=opendir(meiropath);
        for(dp=readdir(dir);dp!=NULL;dp=readdir(dir)){
            if(strcmp(dp->d_name,curr1)!=0 && strcmp(dp->d_name,curr2)!=0 && strcmp(dp->d_name,ignore)!=0){
                meirocount++;
            }
        }
        closedir(dir);


        dir=opendir(meiropath);

        for(dp=readdir(dir);dp!=NULL;dp=readdir(dir)){

            if(strcmp(dp->d_name,curr1)!=0 && strcmp(dp->d_name,curr2)!=0 && strcmp(dp->d_name,ignore)!=0){
                sprintf(meirofullpath,"%s%s",meiropath,dp->d_name);
                //����ŁA���H�t�@�C���̃t���p�X��meirofullpath�Ɋi�[���ꂽ�B

                //���H���[�h
                load_meiro(meirofullpath);
                if(is_debug){
                    printf("load\n");
                    printf("%s\n",meirofullpath);
                }
                if (is_shortest) {
                    center_checked=true;

                    for (y=0;y<31;y++)
                    {
                        for(x=0;x<16;x++){
                            if((y%2==0&&x>=15)||(y%2==1&&x>=16)){
                                continue;
                            }
                            //�y���邽�ߎg��Ȃ��v�f�ɂ��Z�b�g���Ă�
                            nodes[x][y].winfo = loadedmeiro[x][y].winfo;
                        }
                    }
                }else{
                    center_checked=false;
                    for (y=0;y<31;y++)
                    {
                        for(x=0;x<16;x++){
                            if((y%2==0&&x>=15)||(y%2==1&&x>=16)){
                                continue;
                            }
                            //�y���邽�ߎg��Ȃ��v�f�ɂ��Z�b�g���Ă�
                            nodes[x][y].winfo=Unknown;
                        }
                    }
                }


                //���s�I
                while (nextstep()) {
                    //�J��Ԃ�.......
                }

                if(is_debug){
                    inform_message("*�����܂�*");
                }

                nowcount++;

                fprintf(stderr,"%d%%  %d/%d\n",(int)(nowcount*100/meirocount),nowcount,meirocount);

            }

            mouse_runcount=0;

        }

        closedir(dir);


        printf("msg\nfstack:%d, pqueue:%d, cost:%d\n",max_fstack,max_pqueue,max_cost);

    }else{
        strcpy(meirofullpath, meiropath);
        strcat(meirofullpath, filename);
        //����ŁA���H�t�@�C���̃t���p�X��meirofullpath�Ɋi�[���ꂽ�B

        //���H���[�h
        load_meiro(meirofullpath);
        if(is_debug){
            printf("load\n");
            printf("%s\n",meirofullpath);
        }
        if (is_shortest) {
            center_checked=true;

            for (y=0;y<31;y++)
            {
                for(x=0;x<16;x++){
                    if((y%2==0&&x>=15)||(y%2==1&&x>=16)){
                        continue;
                    }
                    //�y���邽�ߎg��Ȃ��v�f�ɂ��Z�b�g���Ă�
                    nodes[x][y].winfo = loadedmeiro[x][y].winfo;
                }
            }
        }else{
            center_checked=false;
            for (y=0;y<31;y++)
            {
                for(x=0;x<16;x++){
                    if((y%2==0&&x>=15)||(y%2==1&&x>=16)){
                        continue;
                    }
                    //�y���邽�ߎg��Ȃ��v�f�ɂ��Z�b�g���Ă�
                    nodes[x][y].winfo=Unknown;
                }
            }
        }


        //���s�I
        while (nextstep()) {
            //�J��Ԃ�.......
        }

        if(is_debug){
            inform_message("*�����܂�*");
        }

        printf("msg\nfstack:%d, pqueue:%d, cost:%d\n",max_fstack,max_pqueue,max_cost);
    }

	return 0;
}
