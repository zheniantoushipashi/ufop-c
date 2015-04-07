


#include "test.h"

const static char html_re_hd_su[] = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n"; //html response header : success
 
int CreatTcpSocket_fd(){
    int socket_fd;
    struct sockaddr_in address;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0); //tcp protocal
    //catch up exception
    if(socket_fd < 0){
        printf("socket creation failed\n");
        exit(1); // 1 means exit with exception
        return 1;
    }
 
    //step 2: bind the socket file description
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET; //Internet protocal
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY; //set the host ip
    if(bind(socket_fd, (struct sockaddr*)&address, sizeof(struct sockaddr_in))){
        //catch up exception
        printf("socket binding failed!\n");
        exit(1);
        return 1;
    }
    return socket_fd;
}
 
char* AnalyseTcpRequest(const int socket_fd){
    char requestMessage[BUF_LEN];
    read(socket_fd, requestMessage, BUF_LEN);
    printf("%s \n",  requestMessage);
    char *pData = requestMessage;
    while ('\0' != *pData)
    {
        if (*pData == '\r' && *(pData+1) == '\n' && *(pData+2) == '\r' && *(pData+3) == '\n') break;
 
        pData++;
    }
    pData += 4; 
    cJSON *root_json = cJSON_Parse(pData);
    cJSON *src_json = cJSON_GetObjectItem(root_json, "src");
    char *mimetype = cJSON_Print(cJSON_GetObjectItem(src_json, "mimetype"));
    printf("%s  \n", mimetype);
    return   mimetype;
}
 
void ReplyTcpRequest(int socket_fd, char* mimetype){
    char replyMessage[]=
        "<html><head><title>ufop  test  c  for  linux</title></head>" 
        "<body><h1> the   mimetype  of  this  file  is </h1> "
        "</body></html>"; 
    printf(replyMessage); 
    write(socket_fd, html_re_hd_su, strlen(html_re_hd_su));
    write(socket_fd, replyMessage, strlen(replyMessage));
    write(socket_fd, mimetype ,  strlen(mimetype) );
    printf("replyed...\n");
}
 
int main(){
    int socket_fd = CreatTcpSocket_fd();
    listen(socket_fd, 5); //max conection number is 5 now.
     
    //step 3: begin to accept tcp request
    struct sockaddr_in their_address;
    int their_sin_len = sizeof(struct sockaddr_in);
     
    for ( ; ; )
    {  
        printf("begin to accept tcp request...\n");
        //begin to block the processing
        int newSocket_fd = accept(socket_fd, (struct sockaddr*)&their_address, &their_sin_len);
        printf("analysing...\n");
        char * mimetype = AnalyseTcpRequest(newSocket_fd);
        ReplyTcpRequest(newSocket_fd, mimetype);
        close(newSocket_fd);
    }
 
    exit(0);
    return 0;
}

