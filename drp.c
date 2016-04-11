#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include "md5.h"
#define MD5_DIGEST_LENGTH    32
#define BUFSIZE (1025*16)

void readDir(char *argv[]);
void getHash(char argv[]);

DIR * dir;
FILE *fp;
struct dirent * de;
struct stat statbuf;
int status, i = 0;

int main(int argc, char *argv[]) {

	readDir(argv);
	return 0;

}

void readDir(char * argv[]) {
	fp = fopen("dirlist.drb", "w+");
	dir = opendir(argv[1]);
	while ((de = readdir(dir)) != NULL) {

		fprintf(fp, "%s", de->d_name);

		lstat(de->d_name, &statbuf);

		/* printf("%d\n",status); */
		if (S_ISDIR(statbuf.st_mode)) {

			fprintf(fp, "%s\n", "/");

		} else {
			getHash(de->d_name);
			fprintf(fp, "\n");

		}
	}

	closedir(dir = 0);
	fclose(fp);
}
void getHash(char nameoff[]) {
	FILE *fpr;
	/*char bigfut[] = "/home/modus/c++/crypta/Debug/";*/
	/*nameoff = strncat(bigfut, nameoff, 50);*/
	printf("\n  %s      ", nameoff);
	fpr = fopen(nameoff, "rb");
	MD5_CTX ctx;
	BYTE md_buf[MD5_BLOCK_SIZE];
	fseek(fpr, 0L, SEEK_END);
	long size = ftell(fpr);
	fseek(fpr, 0L, SEEK_SET);
	BYTE buf[size];
	fread(buf, 1, size, fpr);
	md5_init(&ctx);

	md5_update(&ctx, buf, size);

	md5_final(&ctx, md_buf);
	fprintf(fp, "  md5sum ");
	for (i = 0; i < 16; i++) {
		fprintf(fp,"%x", md_buf[i]);

	}

	fclose(fpr);

}

