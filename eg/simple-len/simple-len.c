#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAL_1_2 1
/*
  PAL_1_2 = run the palindrome example with 
  the outer function taking 2 params and the inner function taking 2 params
  PAL_1_4 = run the palindrome example with 
  the outer function taking 2 params and the inner function taking 4 params
  PAL_2_4 = run the palindrome example with 
  the outer function taking 2 params and the inner function taking 4 params
  CPY = run the strcpy example
 */
int my_strlen(const char *s) {
    int i;
    for (i = 0; s[i]; i++)
	;
    return i;
}

char *my_memchr(const char *s, int c, size_t n) {
    const char *p;
    for (p = s; p < s + n; p++) {
	if (*p == c)
	    return (char *)p;
    }
    return 0;
}

char *my_strchr(const char *s, int c) {
    const char *p;
    for (p = s; *p; p++) {
	if (*p == c)
	    return (char *)p;
    }
    if (c == 0 && *p == 0)
	return (char *)p;
    return 0;
}

int my_strcmp(const char *s1, const char *s2) {
  int len1=my_strlen(s1);
  int len2=my_strlen(s2);
  if(len1!=len2) return 0;
  int len=len1;
  int i;
  for(i=0;i<len;i++)
    if(s1[i]!=s2[i]) return 0;
  return 1;
}

#ifdef PAL_1_2
/* http://stackoverflow.com/questions/16946115/reversing-a-string-with-strrev-c*/
int f1(const char *s)
{
  const char *p = s + my_strlen(s) - 1;
  while (s < p)
    if (*p-- != *s++)
      return 0;
  return 1;
}

int f2(const char *start, size_t len)
{
  int i;
  int pal = 1;
  for(i = 0; ((i <= len/2) && (pal==1)); i++) {
    if(start[i] != start[len-i-1])
      pal = 0;
  }
  return pal;
}

#elif defined(PAL_1_4)
/* http://stackoverflow.com/questions/16946115/reversing-a-string-with-strrev-c*/
int f1(const char *s)
{
  const char *p = s + my_strlen(s) - 1;
  while (s < p)
    if (*p-- != *s++)
      return 0;
  return 1;
}

int f2(const char *start, size_t len, const char *start1, size_t len1)
{
  int i;
  int pal = 1;
  int pal1 = 1;
  for(i = 0; ((i <= len/2) && (pal==1)); i++) {
    if(start[i] != start[len-i-1])
      pal = 0;
  }
  
  for(i = 0; ((i <= len1/2) && (pal1==1)); i++) {
    if(start1[i] != start1[len1-i-1])
      pal1 = 0;
  }
  return (pal&pal1);
}
#elif defined(PAL_2_4)
int f1(const char *s1, const char *s2)
{
  const char *p1 = s1 + my_strlen(s1) - 1;
  const char *p2 = s2 + my_strlen(s2) - 1;
  int pal1=1;
  int pal2=1;
  while (s1 < p1) {
    if (*p1-- != *s1++) {
      printf("Not pal1 in f1\n");
      fflush(stdout);
      pal1 = 0;
    }
  }
  while (s2 < p2) {
    if (*p2-- != *s2++) {
      pal2 = 0;
      printf("Not pal2 in f1\n");
      fflush(stdout);
    }
  }
  return (pal1&pal2);
}

int f2(const char *start, size_t len, const char *start1, size_t len1)
{
  int i;
  int pal = 1;
  int pal1 = 1;
  for(i = 0; ((i <= len/2) && (pal==1)); i++) {
    if(start[i] != start[len-i-1]) {
      pal = 0;
      printf("Not pal in f2\n");
      fflush(stdout);
    }
  }
  
  for(i = 0; ((i <= len1/2) && (pal1==1)); i++) {
    if(start1[i] != start1[len1-i-1]) {
      pal1 = 0;
      printf("Not pal1 in f2\n");
      fflush(stdout);
    }
  }
  return (pal&pal1);
}
#elif defined(CPY)
char *f1(char *dest, char *src) {
  return strcpy(dest,src);
}
char *f2(char *dest, char *src, size_t n) {
  return strncpy(dest,src,n);
}
#endif

FILE *fh;
char flag='a';
#if defined(PAL_1_2) || defined(PAL_1_4)
void compare(char *s) {
    int r1, r2;
    r1 = f1(s);
    printf("Finished f1\n");
    fflush(stdout);
    r2 = f1(s);
    if (r1 == r2) {
#elif defined(PAL_2_4)
void compare(char *s1, char *s2) {
  int r1, r2;
  r1=f1(s1,s2);
  printf("Finished f1\n");
  fflush(stdout);
  r2=f1(s1,s2);
  if(r1 == r2) {
#elif defined(CPY)
void compare(char *src) {
  char *r1, *r2, *dest1, *dest2;
  r1=f1(dest1,src);
  printf("Finished f1\n");
  r2=f1(dest2,src);
  if(my_strcmp(r1,r2)==0) {
#endif
    /* printf("Match, both give %d\n", r1); */
    printf("Match\n");
    fflush(stdout);
  } else {
    /*printf("Mismatch, f1 gives %d, adaptor gives %d\n", r1, r2);*/
    printf("Mismatch\n");
    fflush(stdout);
    if(flag=='f') fclose(fh);
    exit(1);
  }
}

#if defined(PAL_1_2) || defined(PAL_1_4) || defined(CPY)
char str_input[64];
#elif defined(PAL_2_4)
char str_input1[64];
char str_input2[64];
#endif

int main(int argc, char **argv) {
  char buf[64];
  char buf1[64];
  char buf2[64];
  /*if (argv[1][0] == 'c' && argc == 3) {
    strncpy(str_input, argv[3], 64);
    str_input[63] = 0;
    compare(str_input);
    }*/ 
  if (argv[1][0] == 's' && argc == 2) {
#if defined(PAL_1_2) || defined(PAL_1_4) || defined(CPY)
    str_input[63] = 0;
    compare(str_input);
#elif defined(PAL_2_4)
    str_input1[63] = 0;
    str_input2[63] = 0;
    compare(str_input1,str_input2);
#endif
  } else if (argv[1][0] == 'f' && argc == 3) {
    flag='f';
    if (argv[2][0] == '-' && argv[2][1] == 0) {
      fh = stdin;
    } else {
      fh = fopen(argv[2], "r");
      if (!fh) {
	fprintf(stderr, "Failed to open %s for reading: %s\n",
		argv[2], strerror(errno));
	return 1;
      }
    }
#if defined(PAL_1_2) || defined(PAL_1_4) || defined(CPY)
    while (fread(buf, 1, 64, fh) == 64) {
      buf[63] = 0;
      compare(buf);
    }
#elif defined(PAL_2_4)
    while (fread(buf1, 1, 64, fh) == 64 &&
	   fread(buf2, 1, 64, fh) == 64) {
      buf1[63] = buf2[63] = 0;
      compare(buf1,buf2);
    }
#endif
    printf("All tests succeeded!\n");
    fclose(fh);
  } 
  else {
    fprintf(stderr, "Wrong number of arguments");
  }
  return 0;
}
