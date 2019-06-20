#include "csapp.h"
#include "cache.h"

/* Initialize the cache */
void cache_init() {
    for (int i = 0 ; i < CACHE_BLOCK_NUM ; i ++) {
        cache[i].timestamp = 0;
        cache[i].valid = 1;
        Sem_init(&cache[i].w, 0, 1);
        Sem_init(&cache[i].mutex, 0, 1);
        cache[i].readcnt = 0;
    }
}

/* Fine URL in the cache */
int cache_find(char *url) {
    for (int i = 0 ; i < CACHE_BLOCK_NUM ; i ++){
        readerin(i);
        if ((cache[i].valid == 0) && (strcmp(url, cache[i].cache_url) == 0)) return i;
        readerout(i);
    }
    return -1;
}

/* Wrap reader and writer for simplicity */
/* Here we use reader first strategy */
void readerin(int i) {
    P(&cache[i].mutex);
    cache[i].readcnt ++;
    if (cache[i].readcnt == 1) P(&cache[i].w);
    V(&cache[i].mutex);
}
void readerout(int i) {
    P(&cache[i].mutex);
    cache[i].readcnt --;
    if (cache[i].readcnt == 0) V(&cache[i].w);
    V(&cache[i].mutex);
}
void writerin(int i) { P(&cache[i].w); }
void writerout(int i) { V(&cache[i].w); }

/* Find a valid cache block */
int cache_position() {
    unsigned long maxtime = 0;
    int maxindex = 0;
    for (int i = 0 ; i < CACHE_BLOCK_NUM ; i ++)
    {
        readerin(i);
        /* choose a valid cache block */
        if(cache[i].valid == 1) {
            readerout(i);
            return i;
        }
        if(cache[i].timestamp > maxtime) {/*if not valid choose the min timestamp*/
            maxindex = i;
            maxtime = cache[i].timestamp;
            readerout(i);
            continue;
        }
        readerout(i);
    }
    return maxindex;
}

/* Cache the uri and content */
void cache_store(char *uri, char *buf){
    int index = cache_position();
    writerin(index);
    strcpy(cache[index].cache_obj, buf);
    strcpy(cache[index].cache_url, uri);
    cache[index].valid = 0;
    cache[index].timestamp = 0;
    for (int i = 0 ; i < CACHE_BLOCK_NUM; i++) {
        if (i == index) continue;
        writerin(i);
        if(cache[i].valid == 0) cache[i].timestamp ++;
        writerout(i);
    }
    writerout(index);
}

