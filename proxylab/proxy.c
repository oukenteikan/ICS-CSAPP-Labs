#include <stdio.h>
#include "csapp.h"
#include "cache.h"
#include "proxy.h"

int main(int argc,char **argv)
{
        /* Define string to store info */
	int listenfd, *connfdp;
	struct sockaddr_storage clientaddr;
	char hostname[MAXLINE], port[MAXLINE];
	socklen_t clientlen = sizeof(clientaddr);
	pthread_t tid;

        /* Right cmdline args */
	if (argc != 2) {
		fprintf(stderr, cmd_format, argv[0]);
		exit(1);
	}

        /* Initialize the cache */
        cache_init();

        /* listen to the port by the first argv */
        Signal(SIGPIPE, SIG_IGN);
	listenfd = Open_listenfd(argv[1]);
	while(1) {
                /* Accept connection and get name info */
                connfdp = Malloc(sizeof(int));
		*connfdp = Accept(listenfd, (SA *)&clientaddr, &clientlen);
		Getnameinfo((SA*)&clientaddr, clientlen, hostname, MAXLINE, port, MAXLINE, 0);
		printf(listen_format, hostname, port);
                Pthread_create(&tid, NULL, thread, connfdp);
	}
	exit(0);
}

/* Work on new pthread and close */
void *thread(void *vargp)
{
    int connfd = *((int*)vargp);
    Pthread_detach(pthread_self());
    Free(vargp);
    doit(connfd);
    Close(connfd);
    return NULL;
}

void doit(int fd)
{
    /* Define string to store info */
    int port, serverfd;
    size_t lenth;
    rio_t rio, server_rio;
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char hostname[MAXLINE],port_str[MAXLINE], path[MAXLINE], http_hdr[MAXLINE];

    /* Read request line */
    Rio_readinitb(&rio, fd);
    if (!Rio_readlineb(&rio, buf, MAXLINE)) return;
    sscanf(buf,"%s %s %s", method, uri, version);
    if (strcasecmp(method, "GET")) {
        printf(method_format, method);
        return;
    }

    /* Whether cached */
    char uri_copy[MAXLINE];
    strcpy(uri_copy,uri);
    int cache_index;
    if ((cache_index = cache_find(uri_copy)) != -1) {
         readerin(cache_index);
         Rio_writen(fd, cache[cache_index].cache_obj, strlen(cache[cache_index].cache_obj));
         readerout(cache_index);
         return;
    }

    /* Parse URI from GET request */
    port = parse_uri(uri, hostname, path);
    sprintf(port_str, "%d", port);

    /* Build the http header */
    build_http_hdr(http_hdr, hostname, path, port, &rio);

    /* Connect to the server*/
    serverfd = Open_clientfd(hostname, port_str);
    
    /* Write the http header to the server*/
    Rio_readinitb(&server_rio, serverfd);
    Rio_writen(serverfd, http_hdr, strlen(http_hdr));

    /* Receive message from end server and return to the client*/
    char cachebuf[MAX_OBJECT_SIZE];
    int sizebuf = 0;
    while ((lenth = Rio_readlineb(&server_rio, buf, MAXLINE)) != 0) {
        printf(return_format, lenth);
        Rio_writen(fd, buf, lenth);
        sizebuf += lenth;
        if (sizebuf < MAX_OBJECT_SIZE) strcat(cachebuf, buf);
    }
    Close(serverfd);
    if (sizebuf < MAX_OBJECT_SIZE) cache_store(uri_copy, cachebuf);
}

void build_http_hdr(char *http_hdr, char *hostname, char *path, int port, rio_t *rio)
{
    /* Define string to store info */
    char buf[MAXLINE], request_hdr[MAXLINE], other_hdr[MAXLINE], host_hdr[MAXLINE];

    /* Meet the path */
    sprintf(request_hdr, request_hdr_format, path);
    while (Rio_readlineb(rio, buf, MAXLINE)) {
        /* Meet the end */
        if (strcmp(buf, end_of_hdr) == 0) break;

        /* Meet the host */
        if (!strncasecmp(buf, host_title, strlen(host_title))) {
            strcpy(host_hdr,buf);
            continue;
        }

        /* Meet anything other than User-Agent, Connection, Proxy-Connection */
        if (!strncasecmp(buf, connection_title, strlen(connection_title))
         && !strncasecmp(buf, proxy_connection_title, strlen(proxy_connection_title))
         && !strncasecmp(buf, user_agent_title, strlen(user_agent_title)))
            strcat(other_hdr, buf);
    }
    /* host */
    if (strlen(host_hdr) == 0) sprintf(host_hdr, host_hdr_format, hostname);

    /* Mix all */
    sprintf(http_hdr,"%s%s%s%s%s%s%s", request_hdr, host_hdr, conn_hdr, prox_hdr, user_agent_hdr, other_hdr, end_of_hdr);
}

/* Parse URL from GET request */
int parse_uri(char *uri, char *hostname, char *path)
{
    int port = 80;
    char* host_pos = strstr(uri, "//");
    host_pos = host_pos ? host_pos + 2 : uri;

    char* path_pos = strstr(host_pos, ":");
    /* specify port */
    if (path_pos != NULL) {
        *(path_pos++) = '\0';
        sscanf(host_pos, "%s", hostname);
        sscanf(path_pos, "%d%s", &port, path);
    }
    /* default 80 port */
    else {
        path_pos = strstr(host_pos, "/");
        /* specify path */
        if (path_pos != NULL) {
            sscanf(path_pos, "%s", path);
            *path_pos = '\0';
            sscanf(host_pos, "%s", hostname);
        }
        /* default root path */
        else sscanf(host_pos, "%s", hostname);
    }
    return port;
}

