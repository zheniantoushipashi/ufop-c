#ifndef __TEST__
#define __TEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "cJSON.h"
#define BUF_LEN 1028 // 1028 ever
#define PORT 9100


typedef  struct _Src {
   char*  Url;
   char* Mimetype;
   char* Bucket;
   char*  key;
}Src;


typedef  struct  _ReqArgs {
   char * cmd;
   Src  reqsrc; 
} ReqArgs;

#endif
