/*LZW Compression Decompression using RBTree */

using namespace std;

#include <map>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include "lzw.h"

int code = 0;
int max_len = 0;

void init(map<string, int> &m) {
    string temp = "";
    for(unsigned char i = 0; i <= 254; i++) {
        temp += i;
        m[temp] = code++;
        temp.clear();
    }
    temp += (unsigned char) 255;
    m[temp] = code++;
}

int search(map<string, int> &m, string w) {
    if(m.find(w) != m.end()) {
        return m[w];
    }
    return -1;
}

bool compress(int in, int out) {

    /*Creating STL-Map */
    map<string, int> m;
    init(m);

    /*w is the longest prefix */
    string w = "";

    /*Getting file-size */
    float sum, filesize = 0, progress = 0;
    filesize = (float) lseek(in, 0, SEEK_END);
    lseek(in, 0, SEEK_SET);

    char rbuffer[BLOCK + 1];
    int wbuffer[BLOCK + 1];
    int len = read(in, rbuffer, BLOCK);
    int i = 1, j = 0, k = 0;

    sum = len;
    progress = sum / filesize;
    printf("%.2f%% completed.\r", progress * 100.0);

    w += rbuffer[j++];
    wbuffer[k] = search(m, w);

    while(len != 0) {
        for(j; j < len; j++) {
            int curr_code = search(m, w + rbuffer[j]);
            if(curr_code != -1) {
                wbuffer[k] = curr_code;
                w += rbuffer[j];
                i++;
                if(i > max_len) {
                    max_len = i;
                }
            } else {
                k++;
                if(k == BLOCK) {
                    write(out, wbuffer, k * sizeof(int));
                    k = 0;
                }
                m[w + rbuffer[j]] = code++;
                i = 1;
                w.clear();
                w += rbuffer[j];
                wbuffer[k] = search(m, w);
            }
        }
        len = read(in, rbuffer, BLOCK);
        j = 0;
        sum += len;
        progress = sum / filesize;
        printf("%.2f%% completed.\r", progress * 100.0);
    }
    write(out, wbuffer, (k + 1) * sizeof(int));
    printf("\n");

    return true;
}

bool decompress(int in, int out) {
    
    /*Creating STL-Map */
    map<string, int> m;
    init(m);

    int rbuffer[BLOCK + 1];
    char wbuffer[BLOCK + 1];

}
