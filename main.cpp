/*Main of the program */

using namespace std;

#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include "lzw.h"

extern int code;
extern int max_len;

void stats(int, int);

int main(int argc, char *argv[]) {

    int opt = 0, ufilesize, cfilesize;
    float compress_ratio;

    opt = getopt(argc, argv, "cd");
    switch(opt) {
        case 'c' : {
                    if(argc < 2) {
                        printf("File not specified.\n");
                        return 0;
                    }
                    int in = open(argv[2], O_RDONLY);
                    if(in == -1) {
                        perror("File not found");
                        return 0;
                    }
                    char name[128];
                    strcpy(name, strcat(argv[2], (char *) ".lzw"));
                    int out = open(name, O_WRONLY | O_CREAT);
                    if(out == -1) {
                        perror("File could not be created");
                        return 0;
                    }
                    compress(in, out);
                    ufilesize = lseek(in, 0, SEEK_END);
                    cfilesize = lseek(out, 0, SEEK_END);
                    close(in);
                    close(out);
                    stats(ufilesize, cfilesize);
                   }
                    break;
        case 'd' : {
                    if(argc < 2) {
                        printf("File not specified.\n");
                        return 0;
                    }
                    int in = open(argv[2], O_RDONLY);
                    if(in == -1) {
                        perror("File not found");
                        return 0;
                    }
                    char name[128];
                    strcpy(name, strtok(argv[2], (char *) "."));
                    strcat(name, ".");
                    strcat(name, strtok(NULL, (char *) "."));
                    int out = open(name, O_WRONLY | O_CREAT);
                    if(out == -1) {
                        perror("File could not be created");
                        return 0;
                    }
                    decompress(in, out);
                   }
                    break;
        default:  {
                   printf("No option specified.\n");
                   return 0;
                  }
    }
    return 0;
}

void stats(int ufilesize, int cfilesize) {

    printf("Debug stats:\n");
    printf("Codes created - %d\n", code);
    printf("Max code length - %d\n", max_len);
    printf("Uncompressed filesize - %d\n", ufilesize);
    printf("Compressed filesize - %d\n", cfilesize);
    printf("Compression Ratio - %.2f\n", (float) ufilesize/ (float) cfilesize);
    char *color = cfilesize > ufilesize ? (char *)"\x1B[31m" : (char *)"\x1B[32m";
    printf("Space savings - %s%.2lf%%\e[0m\n", color, fabs(((float) (ufilesize - cfilesize) / (float) ufilesize) * 100));

}
