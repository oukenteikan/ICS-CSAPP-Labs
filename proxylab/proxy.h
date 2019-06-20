/* You won't lose style points for including this long line in your code */
const char *cmd_format = "usage: %s <port>\n";
const char *listen_format = "Accepted connection from (%s %s).\n";
const char *method_format = "Proxy can't implement the method %s\n";
const char *return_format = "Proxy received %lu bytes,then send\n";
const char *request_hdr_format = "GET %s HTTP/1.0\r\n";
const char *host_hdr_format = "Host: %s\r\n";
const char *host_title = "Host";
const char *user_agent_title= "User-Agent";
const char *connection_title = "Connection";
const char *proxy_connection_title = "Proxy-Connection";
const char *user_agent_hdr = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";
const char *conn_hdr = "Connection: close\r\n";
const char *prox_hdr = "Proxy-Connection: close\r\n";
const char *end_of_hdr = "\r\n";

/* Frame function */
void *thread(void *vargp);
void doit(int fd);
int parse_uri(char *uri, char *hostname, char *path);
void build_http_hdr(char *http_hdr, char *hostname, char *path, int port, rio_t *rio);

