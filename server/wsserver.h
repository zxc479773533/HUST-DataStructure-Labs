/*
 * AUTHOR: Yue Pan
 * GITHUB: zxc479773533
 * E-MAIL: zxc479773533@gmail.com
 */

#ifndef PY_WSSERVER_H_
#define PY_WSSERVER_H_

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <signal.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <openssl/sha.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

#include "lab01/my_linearlist.c"


/* defines */

// the socket queue length
#define QUEUE 20

// the port that server use
#define PORT 8080

// the max message size receive from client
#define BUFF_SIZE 1024

// the line size
#define LINE_SIZE 256

// the key used to build conncetion
#define KEY "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"


/* struct definations */

/*-------------------------------------------------------------------
0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-------+-+-------------+-------------------------------+
|F|R|R|R| opcode|M| Payload len |    Extended payload length    |
|I|S|S|S|  (4)  |A|     (7)     |             (16/64)           |
|N|V|V|V|       |S|             |   (if payload len==126/127)   |
| |1|2|3|       |K|             |                               |
+-+-+-+-+-------+-+-------------+ - - - - - - - - - - - - - - - +
|     Extended payload length continued, if payload len == 127  |
+ - - - - - - - - - - - - - - - +-------------------------------+
|                               |Masking-key, if MASK set to 1  |
+-------------------------------+-------------------------------+
| Masking-key (continued)       |          Payload Data         |
+-------------------------------- - - - - - - - - - - - - - - - +
:                     Payload Data continued ...                :
+ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - +
|                     Payload Data continued ...                |
+---------------------------------------------------------------+
--------------------------------------------------------------------*/

typedef struct {
    u_char fin;
    u_char opencode;
    u_char mask;
    u_long payload_length;
    u_char masking_key[4];
} websocket_head;


/* functions */

int base64_encode(char *in_str, int in_len, char *out_str);
/*
* Function Name: base64_encode
* Module: Server
* Parameter: char *in_str, int in_len, char *out_str
* Return: int
* Use: Base64 encode function, used to build connection
*/

int readline(char *buff, int pos, char *line);
/*
* Function Name: readline
* Module: Server
* Parameter: char *buf, int pos, char *line
* Return: int
* Use: read a line string form buffer
*/

int shakehands(int sock_client);
/*
* Function Name: shakehands
* Module: Server
* Parameter: int sock_client
* Return: int
* Use: shakehands with client and build connection
*/

void strreverse(char *str, int len);
/*
* Function Name: strreverse
* Module: Server
* Parameter: char *str, int len
* Return: None
* Use: reverse string
*/

int receive_and_parse(int sock, websocket_head *pWS);
/*
* Function Name: receive_and_parse
* Module: Server
* Parameter: int sock, websocket_head *pWS
* Return: int
* Use: receive message from client and parse it
*/

void DecodeMessage(char *data, int len, u_char *mask);
/*
* Function Name: DecodeMessage
* Module: Server
* Parameter: char *data, int len, u_char *mask
* Return: None
* Use: decode message
*/

int SendMessage(int fd, char *payload, int payload_length);
/*
* Function Name: SendMessage
* Module: Server
* Parameter: int fd, char *payload, int payload_length
* Return: int
* Use: send message to client
*/

void Load_linear_list(Linear_list_main *Main_L);
/*
* Function Name: Load_linear_list
* Module: Server
* Parameter: Linear_list_main *Main_L
* Return: None
* Use: load linear list data from file
*/

int Save_linear_list(Linear_list_main *Main_L);
/*
* Function Name: Save_linear_list
* Module: Server
* Parameter: Linear_list_main *Main_L
* Return: int
* Use: save linear list data into file
*/

void Ls_linear_list(Linear_list_main *Main_L, char *payload);
/*
* Function Name: Ls_linear_list
* Module: Server
* Parameter: Linear_list_main *Main_L, char *payload
* Return: int
* Use: ls the linear lists'ID
*/


void Mode_choose(char *playload, int payload_length);
/*
* Function Name: Mode_choose
* Module: Server
* Parameter: char *payload, int payload_length
* Return: Node
* Use: choose a mode
*/

void Backstage_Main_linear_list(char *payload, int payload_length);
/*
* Function Name: Backstage_Main_linear_list
* Module: Server
* Parameter: char *payload, int payload_len
* Return: Node
* Use: analyze the message and schedule the functions
*/


#endif // !PY_WSSERVER_H_