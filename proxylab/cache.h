#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400
#define CACHE_BLOCK_NUM 8

/* Define my cache */
typedef struct {
    char cache_obj[MAX_OBJECT_SIZE];
    char cache_url[MAXLINE];
    unsigned long timestamp;
    int valid;

    int readcnt;
    sem_t w;
    sem_t mutex;
} Cache;
Cache cache[CACHE_BLOCK_NUM];

/* Cache function */
void cache_init();
int cache_find(char *url);
void readerin(int i);
void readerout(int i);
void writerin(int i);
void writerout(int i);
int cache_position();
void cache_store(char *uri, char *buf);

