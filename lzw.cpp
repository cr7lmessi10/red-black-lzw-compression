/*LZW Compression Decompression using RBTree */

using namespace std;

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include "lzw.h"

extern int code;
extern int max_len;

bool compress(int in, int out) {

    /*Creating the rbtree */
    rbtree *rb =  new rbtree();
    init(rb);

    /*w is the longest prefix */
    string w = ""; 
    w.reserve(4 * BLOCK);

    /*Getting file-size */
    float sum, filesize = 0, progress = 0;
    filesize = (float) lseek(in, 0, SEEK_END);
    lseek(in, 0, SEEK_SET);

    char rbuffer[BLOCK + 1];
    int wbuffer[BLOCK + 1];
    int out_code;
    int len = read(in, rbuffer, BLOCK);
    int i = 1, j = 0, k = 0;

    sum = len;
    progress = sum / filesize;
    printf("%.2f%% completed.\r", progress * 100.0);

    w += rbuffer[j++];
//    w += '\0';
    wbuffer[k] = out_code = search(rb, w);

    while(len != 0) {
        for(j; j < len; j++) {
            int curr_code = search(rb, w + rbuffer[j]);
            if(curr_code != -1) {
                wbuffer[k] = out_code = curr_code;
                w += rbuffer[j];
//                w += '\0';
                i++;
                if(i > max_len) {
                    max_len = i;
                }
            } else {
                k++;
                //write(out, &out_code, sizeof(int));
                if(k == BLOCK) {
                    write(out, wbuffer, k * sizeof(int));
                    k = 0;
                }
                insert(rb, w + rbuffer[j], code++);
                i = 1;
                w = "";
                w += rbuffer[j];
//                w += '\0';
                wbuffer[k] = out_code = search(rb, w);
            }
        }
        len = read(in, rbuffer, BLOCK);
        j = 0;
        sum += len;
        progress = sum / filesize;
        printf("%.2f%% completed.\r", progress * 100.0);
    }
    write(out, wbuffer, (k + 1) * sizeof(int));
    free(rb->root);
    delete rb;
    printf("\n");

    return true;
}

bool decompress(int in, int out) {

}
