#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Recored every thing we need to know about the cache
struct Cache
{
	int s, S, E, b, B;
	int *valid;
	long *tag;
	int *visit;
	int total, hit, miss, eviction;
};

//Change hexadecimal to decimal
int hex2dec(char c)
{
	if (c >= '0' && c <= '9') return c - '0';
	if (c >= 'a' && c <= 'f') return c - 'a' + 10;
	if (c >= 'A' && c <= 'F') return c - 'A' + 10;
	return 0;
}

//Simulate an instruction
void simulate(char* line, struct Cache *p)
{
	//remove \n
	int length = strlen(line)-1;
	line[length] = '\0';
	//Get instuction and address
	char instr = line[1];
	if (instr == 'I') return;
	long address = 0;
	for (int i = 3 ; i < length ; i ++)
	{
		if (line[i] == ',') break;
		address = address * 16 + hex2dec(line[i]);
	}
	p->total ++;
	//Get group and leave tag
	int group = 0, flag = 0;
	for (int i = 0 ; i < p->b ; i ++) address >>= 1;
	for (int i = 0 ; i < p->s ; i ++)
	{
		group = (group << 1) + (address & 1);
		address >>= 1;
	}
	//If we find it in cache
	for (int i = group * (p->E) ; i < (group+1) * p->E ; i ++)
		if (p->valid[i] && address == p->tag[i])
		{
			p->visit[i] = p->total;
			p->hit ++;
			flag ++;
			break;
		}
	//If there is empty space
	if (!flag)
	for (int i = group * (p->E) ; i < (group+1) * p->E ; i ++)
                if (!p->valid[i])
                {       
                        p->valid[i] = 1;
			p->tag[i] = address;
			p->visit[i] = p->total;
                        p->miss ++;
                        flag ++;
			break;
                }
	//If we have to evict someone
	if (!flag)
	{
		int min_visit = p->total + 1, min_position = -1;
		for (int i = group * (p->E) ; i < (group+1) * p->E ; i ++)
			if (p->visit[i] < min_visit)
			{
				min_visit = p->visit[i];
				min_position = i;
			}
		p->visit[min_position] = p->total;
		p->tag[min_position] = address;
		p->miss ++;
		p->eviction ++;
	}
	//Always hit again for 'M'
	if (instr == 'M') p->hit ++;
	return;
}

//Change string to integer
int str2int(char* str)
{
	int value = 0;
	int length = strlen(str);
	for (int i = 0 ; i < length ; i ++) value = value * 10 + str[i] - '0';
	return value;
}

//Parse the arg and initiate the cache
void argParse_cacheInit(int argc, char** argv, struct Cache *p, FILE **fin)
{
        for (int i = 1 ; i < argc ; i ++)
        {
                if (strcmp(argv[i], "-s")==0)
                {
                        p->s = str2int(argv[i+1]);
                        p->S = (1<<(p->s));
                }
                if (strcmp(argv[i], "-b")==0)
                {
                        p->b = str2int(argv[i+1]);
                        p->B = (1<<(p->b));
                }
                if (strcmp(argv[i], "-E")==0) p->E = str2int(argv[i+1]);
                if (strcmp(argv[i], "-t")==0) *fin = fopen(argv[i+1], "r");
        }
        p->valid = (int *)malloc(sizeof(int)*(p->S)*(p->E));
        p->tag = (long *)malloc(sizeof(long)*(p->S)*(p->E));
        p->visit = (int *)malloc(sizeof(int)*(p->S)*(p->E));
        for (int i = 0 ; i < (p->S)*(p->E) ; i ++)
        {
                p->valid[i] = 0;
                p->tag[i] = 0;
                p->visit[i] = 0;
        }
	p->total = p->hit = p->miss = p->eviction = 0;
	return;
}

int main(int argc, char* argv[])
{	
	struct Cache cache;
	FILE* fin = NULL;	
	argParse_cacheInit(argc, argv, &cache, &fin);
	if (!fin) return 0;
	char line[100];
	//Read line
	while (fgets(line, 100, fin)) simulate(line, &cache);
	printSummary(cache.hit, cache.miss, cache.eviction);
	return 0;
}
