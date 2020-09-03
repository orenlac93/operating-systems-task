#define _GNU_SOURCE
#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static int printFile(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf)
{
	if(tflag != FTW_SL)
	{	
		printf("%-3s %-3s (INODE: %ld)\n",
    	(tflag == FTW_D) ?   "D"   : (tflag == FTW_DNR) ? "dnr" :
		(tflag == FTW_DP) ?  "dp"  : (tflag == FTW_F) ?   "F" :
		(tflag == FTW_NS) ?  "ns"  : (tflag == FTW_SL) ?  "..." :
		(tflag == FTW_SLN) ? "sln" : "???",
		fpath + ftwbuf->base, (long) sb->st_ino);
	}	
    memset((void *) sb, 0, sizeof(struct stat));
	
	/*** use for debug ***/
	/*
	if(tflag == FTW_SL)
	{
		printf("soft link\n");
	}
	*/
	
    return 0;  		/* To tell nftw() to continue */
}


int main(int argc, char *argv[])
{
    int flags = FTW_PHYS;

    if (argc > 2 && strchr(argv[2], 'd') != NULL)
	flags |= FTW_DEPTH;
    if (argc > 2 && strchr(argv[2], 'p') != NULL)
	flags |= FTW_PHYS;

	flags = FTW_PHYS; // use to ignore symbolic links

    if (nftw((argc < 2) ? "." : argv[1], printFile, 20 , flags) == -1)
	{
		perror("nftw");
		exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}