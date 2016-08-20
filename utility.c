#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "header.h"
#include "getopt.h"

node loadedmeiro[16][31];

void load_meiro(char *filename) {
	FILE *fp;
	char buf[32];
	int x, y;

	fp = fopen(filename, "rb");
	if (fp == NULL) {
		error_out("ファイルオープン失敗。");
		return;
	}

	fread(&buf, sizeof(char), 18, fp);
	for (x = 0; x <= 14; x++) {
		for (y = 0; y <= 30; y += 2) {
			if (fread(&buf, sizeof(char), 1, fp) != 1) {
				error_out("ファイルフォーマットが異常。");
			}
			if (buf[0] == 0x31) {
				loadedmeiro[x][ y].winfo = Exist;
			} else {
				loadedmeiro[x][ y].winfo = NoWall;
			}
		}
		fread(&buf, sizeof(char), 2, fp);
	}
	for (x = 0; x <= 15; x++) {
		fread(&buf, sizeof(char), 1, fp);
		for (y = 1; y <= 29; y += 2) {
			if (fread(&buf, sizeof(char), 1, fp) != 1) {
				error_out("ファイルフォーマットが異常。");
			}
			if (buf[0] == 0x31) {
				loadedmeiro[x][ y].winfo = Exist;
			} else {
				loadedmeiro[x][ y].winfo = NoWall;
			}
		}
		if (x != 15) fread(&buf, sizeof(char), 2, fp);
	}

	fclose(fp);
}
