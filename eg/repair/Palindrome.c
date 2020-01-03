//CADET's first C program

//#include "libcgc.h"
//#include "cgc_libc.h"

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/types.h>
#include <unistd.h>
#include <err.h>


#define HI "\nWelcome to Palindrome Finder\n\n"
#define ASK "\tPlease enter a possible palindrome: "
#define YES "\t\tYes, that's a palindrome!\n\n"
#define NO "\t\tNope, that's not a palindrome\n\n"
#define EASTEREGG "\n\nEASTER EGG!\n\n"

int cgc_check();
#define GLOBAL_STR_SIZE 2*INPUT_LEN
// char global_str[GLOBAL_STR_SIZE]; // 128 in original binary

// INPUT_LEN is 64 in the original Palindrome binary

int main(int cgc_argc, char *cgc_argv[]) {
  int r;

  /*if (cgc_transmit_all(1, HI, sizeof(HI)-1) != 0) {
    cgc__terminate(0);
    }*/
    
  /*while(1){
    if (cgc_transmit_all(1, ASK, sizeof(ASK)-1) != 0) {
    cgc__terminate(0);
    }*/
  r = cgc_check();
  /*if (r == -1){
    break;
    }
    else if (r == 0){
    if (cgc_transmit_all(1, NO, sizeof(NO)-1) != 0) {
    cgc__terminate(0);
    }
    }
    else{
    if (cgc_transmit_all(1, YES, sizeof(YES)-1) != 0) {
    cgc__terminate(0);
    }
    }
    }*/
  return 0;
}


typedef long unsigned int cgc_size_t;
/* int cgc_receive_delim(int fd, char *buf, const cgc_size_t size, char delim) {
  int i = 0;
  while (i < size-1) {
    buf[i] = global_str[i];
    i++;
  }
  buf[size-1] = '\0';
  return 0;
}*/

typedef long cgc_ssize_t;
/* Receives data from another CGC process. */
int cgc_receive(int fd, void *buf, cgc_size_t count, cgc_size_t *rx_bytes) {
    const cgc_ssize_t ret = read(fd, buf, count);

    if (ret < 0) {
        return errno;
    } else if (rx_bytes != NULL) {
        *rx_bytes = ret;
    }

    return 0;
}
int cgc_receive_delim(int fd, char *buf, const cgc_size_t size, char delim) {
    cgc_size_t rx = 0;
    cgc_size_t rx_now = 0;
    int ret;

    if (!buf) 
        return 1;

    if (!size)
        return 2;

    while (rx < size) {
        ret = cgc_receive(fd, buf + rx, 1, &rx_now);
	 /* buf[rx] = global_str[rx]; */
        if (rx_now == 0) {
            //should never return until at least something was received
            //so consider this an error too
            return 3;
        }
        if (ret != 0) {
            return 3;
        }
        if (buf[rx] == delim) {
           break;
        }
        rx += rx_now;
        /* rx += 1; */
    }

    return 0;
}


int cgc_check(){
  int len = -1;
  int i;
  int pal = 1;
  char string[INPUT_LEN]; // 64 in original binary
  for (i = 0; i < sizeof(string); i++)
    string[i] = '\0';
#ifdef PATCHED
  if (cgc_receive_delim(0, string, sizeof(string), '\n') != 0)
    return -1;
#else    
  // if (cgc_receive_delim(0, string, 128, '\n') != 0) in original binary
  if (cgc_receive_delim(0, string, 2*INPUT_LEN, '\n') != 0)
    return -1;
#endif
  for(i = 0; string[i] != '\0'; i++){
    len++;
  }
  int steps = len;
  if(len % 2 == 1){
    steps--;
  }
  for(i = 0; i <= steps/2; i++){
    if(string[i] != string[len-1-i]){
      pal = 0;
    }
  }
  /*if(string[0] == '^'){
    if (cgc_transmit_all(1, EASTEREGG, sizeof(EASTEREGG)-1) != 0) {
    cgc__terminate(0);
    }
    }*/    
  return pal;
}
