#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE

#include <float.h>

#include <stdbool.h>
#include <inttypes.h>
#include <locale.h>
#include <math.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*#include <uchar.h>*/
#include <wchar.h>
#include <wctype.h>

#include <arpa/inet.h>
#include <dirent.h>
#include <fcntl.h>
#include <grp.h>
#include <netdb.h>
#include <pthread.h>
#include <poll.h>
#include <pwd.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <sys/msg.h>
#include <sys/resource.h>
#include <sys/sem.h>
#include <sys/socket.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <aliases.h>
#include <argp.h>
#include <argz.h>
#include <envz.h>
#include <err.h>
#include <error.h>
#include <execinfo.h>
#include <fmtmsg.h>
#include <fnmatch.h>
#include <fstab.h>
#include <fts.h>
#include <ftw.h>
#include <glob.h>
#include <gnu/libc-version.h>
#include <gshadow.h>
#include <iconv.h>
#include <ifaddrs.h>
#include <langinfo.h>
/*#include <libaudit.h>*/
#include <libgen.h>
#include <libintl.h>
#include <link.h>
#include <malloc.h>
#include <mcheck.h>
#include <monetary.h>
#include <mntent.h>
#include <net/if.h>
#include <netinet/ether.h>
#include <obstack.h>
#include <printf.h>
#define _REGEX_RE_COMP
#include <regex.h>
#include <search.h>
#include <sgtty.h>
#include <syslog.h>
#include <sched.h>
#include <shadow.h>
#include <spawn.h>
#include <stropts.h>
#include <ttyent.h>
#include <ucontext.h>
#include <ulimit.h>
#include <ustat.h>
#include <utime.h>
#include <utmp.h>
#include <utmpx.h>
#include <wordexp.h>
/*#include <sys/auxv.h>*/
/*#include <sys/capability.h>*/
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <sys/fanotify.h>
#include <sys/fsuid.h>
#include <sys/gmon.h>
#include <sys/inotify.h>
#include <sys/io.h>
//#include <sys/kdaemon.h>
#include <sys/klog.h>
#include <sys/mount.h>
#include <sys/personality.h>
#include <sys/prctl.h>
#include <sys/profil.h>
#include <sys/ptrace.h>
#include <sys/quota.h>
#include <sys/reboot.h>
#include <sys/sendfile.h>
#include <sys/signalfd.h>
#include <sys/statvfs.h>
#include <sys/swap.h>
#include <sys/sysctl.h>
#include <sys/sysinfo.h>
#include <sys/timeb.h>
#include <sys/timerfd.h>
#include <sys/timex.h>
#include <sys/utsname.h>
#include <sys/vfs.h>
#include <sys/vlimit.h>
#include <sys/vtimes.h>
#include <sys/xattr.h>
#include <rpc/des_crypt.h>
#include <rpc/key_prot.h>
#include <rpc/pmap_clnt.h>
#include <rpc/pmap_prot.h>
#include <rpc/pmap_rmt.h>
#include <rpc/rpc.h>
#include <rpc/svc.h>

#include "struct_info.h"
#include "functions.h"

#define INIT /**/
#define GETC() getchar()
#define PEEKC() 'x'
#define UNGETC(c) ungetc(c, stdin)
#define RETURN(ptr) return ptr
#define ERROR(val) return 0
//#include <regexp.h>
#undef INIT
#undef GETC
#undef PEEKC
#undef UNGETC
#undef RETURN
#undef ERROR




# define STRTOL_LONG_MIN LONG_MIN
# define STRTOL_LONG_MAX LONG_MAX
# define L_(Ch) Ch

// int _f1(int x, unsigned y, int z) {
// //int _f1(int x){//, int z) {
//   //return (x << 1);// + (z << 1);
//   return (x << 1) + (y % 2);
// }
// 
// int _f2(int a, int b) {//, int c, int d) {//,int e){//, int f) {
// //int _f2(int y1, int y2) {//,int e){//, int f) {
//   //return y1 << y2;// + e;// + f;
//   //return c + d + (a & b);// + e;// + f;
//     //return a + b + (c & d);
//   return (a & 1) + (b * 2);
// }

// unsigned short _f2(unsigned short x, 
// 		   //unsigned short fives,
// 		   //unsigned short threes,
// 		   //unsigned short sevens,
// 		 unsigned short f) {
//   //unsigned short popCountSketch(unsigned short x) {
//   x= (x & 0x5555)+ ((x>> 1) & 0x5555); 
//   x= (x & 0x3333)+ ((x>> 2) & 0x3333); 
//   x= (x & 0x0077)+ ((x>> 8) & 0x0077); 
//   x= (x & f)+ ((x>> 4) & f); 
//   return x;
// }


// unsigned short _f2(unsigned short x, 
// 		 unsigned short fives,
// 		 unsigned short threes,
// 		 unsigned short sevens,
// 		 unsigned short f) {
//   //unsigned short popCountSketch(unsigned short x) {
//   x= (x & fives)+ ((x>> 1) & fives); 
//   x= (x & threes)+ ((x>> 2) & threes); 
//   x= (x & sevens)+ ((x>> 8) & sevens); 
//   x= (x & f)+ ((x>> 4) & f); 
//   return x;
// }

int noop2( int a, int b) { return 0; }

// unsigned short popCountNaive(unsigned short v) {
//   unsigned short c;
//   for (c = 0; v; v >>= 1) {
//     c += v & 1;
//   }
//   return c;
// }

int _f1(int x, unsigned y) { return (x << 1) + (y % 2);}

unsigned short _f11(unsigned short v) {
  // code corresponds to popCountNaive
  char code[] = {0x55, 0x48, 0x89, 0xe5, 0x89, 0xf8, 0x66, 0x89, 0x45, 0xec, 0x66, 0xc7, 0x45, 0xfe, 0x00, 0x00, 0xeb, 0x0f, 0x0f, 0xb7, 0x45, 0xec, 0x83, 0xe0, 0x01, 0x66, 0x01, 0x45, 0xfe, 0x66, 0xd1, 0x6d, 0xec, 0x66, 0x83, 0x7d, 0xec, 0x00, 0x75, 0xea, 0x0f, 0xb7, 0x45, 0xfe, 0x5d, 0xc3};
  void *buf;

  /* copy code to executable buffer */    
  // buf = mmap (0,sizeof(code),PROT_READ|PROT_WRITE|PROT_EXEC,
  //             MAP_PRIVATE|MAP_ANON,-1,0);
  // memcpy (buf, code, sizeof(code));
  // printf(" buf = %p\n", buf);

  /* run code */
  return ((int (*) (int))code)(v);
}

#if (F2VER == 0)
int _f2(int a, int b, int c, int d) { return c + d + (a & b); }
#elif  ((F2VER==1 ) || (F2VER==2 ) || (F2VER==4 ) || (F2VER==5 ) || (F2VER==7 ) || (F2VER==8 ) || (F2VER==12) || (F2VER==15))
unsigned short _f2(unsigned short x) {
  x= (x & 0x5555)+ ((x>> 1) & 0x5555); 
  x= (x & 0x3333)+ ((x>> 2) & 0x3333); 
  x= (x & 0x0077)+ ((x>> 8) & 0x0077); 
  x= (x & 0xf)+ ((x>> 4) & 0xf); 
  return x;
}
#elif F2VER==3
unsigned short _f2(unsigned short x,
		   unsigned short c1) {
  x= (x & 0x5555)+ ((x>> 1) & 0x5555); 
  x= (x & 0x3333)+ ((x>> 2) & 0x3333); 
  x= (x & 0x0077)+ ((x>> c1) & 0x0077); 
  x= (x & 0xf)+ ((x>> 4) & 0xf); 
  return x;
}
#elif F2VER==6
unsigned short _f2(unsigned short x,
		   unsigned short c1) {
  x= (x & 0x5555)+ ((x>> 1) & 0x5555); 
  x= (x & 0x3333)+ ((x>> 2) & 0x3333); 
  x= (x & 0x0077)+ ((x>> 8) & 0x0077); 
  x= (x & c1)+ ((x>> 4) & c1); 
  return x;
}
#elif F2VER==9
unsigned short _f2(unsigned short x,
		   unsigned short c1,
		   unsigned short c2) {
  x= (x & 0x5555)+ ((x>> 1) & 0x5555); 
  x= (x & 0x3333)+ ((x>> 2) & 0x3333); 
  x= (x & 0x0077)+ ((x>> c2) & 0x0077); 
  x= (x & 0xf)+ ((x>> c1) & 0xf); 
  return x;
}
#elif F2VER==10
unsigned short _f2(unsigned short x,
		   unsigned short c1,
		   unsigned short c2) {
  x= (x & 0x5555)+ ((x>> 1) & 0x5555); 
  x= (x & 0x3333)+ ((x>> 2) & 0x3333); 
  x= (x & 0x0077)+ ((x>> c1) & 0x0077); 
  x= (x & c2)+ ((x>> 4) & c2); 
  return x;
}
#elif F2VER==11
unsigned short _f2(unsigned short x,
		   unsigned short c1,
		   unsigned short c2, 
		   unsigned short c3) {
  x= (x & 0x5555)+ ((x>> 1) & 0x5555); 
  x= (x & 0x3333)+ ((x>> c1) & 0x3333); 
  x= (x & 0x0077)+ ((x>> c3) & 0x0077); 
  x= (x & 0xf)+ ((x>> c2) & 0xf); 
  return x;
}
#elif ((F2VER==13) || (F2VER==14))
unsigned short _f2(unsigned short x,
		   unsigned short c1) {
  x= (x & 0x5555)+ ((x>> 1) & 0x5555); 
  x= (x & 0x3333)+ ((x>> 2) & 0x3333); 
  x= (x & c1)+ ((x>> 8) & c1); 
  x= (x & 0xf)+ ((x>> 4) & 0xf); 
  return x;
}
#elif F2VER==16
unsigned short _f2(unsigned short x,
		   unsigned short c1, 
		   unsigned short c2,
		   unsigned short c3,
		   unsigned short c4) {
  x= (x & 0x5555)+ ((x>> c1) & 0x5555); 
  x= (x & 0x3333)+ ((x>> c2) & 0x3333); 
  x= (x & 0x0077)+ ((x>> c4) & 0x0077); 
  x= (x & 0xf)+ ((x>> c3) & 0xf); 
  return x;
}
#elif F2VER==17
unsigned short _f2(unsigned short x,
		   unsigned short c1,
		   unsigned short c2,
		   unsigned short c3) {
  x= (x & 0x5555)+ ((x>> 1) & 0x5555); 
  x= (x & 0x3333)+ ((x>> 2) & 0x3333); 
  x= (x & 0x0077)+ ((x>> c2) & 0x0077); 
  x= (x & c3)+ ((x>> c1) & c3); 
  return x;
}
#elif ((F2VER==18) || (F2VER==19))
unsigned short _f2(unsigned short x,
		   unsigned short c1) {
  x= (x & 0x5555)+ ((x>> 1) & 0x5555); 
  x= (x & 0x3333)+ ((x>> 2) & 0x3333); 
  x= (x & c1)+ ((x>> 8) & c1); 
  x= (x & 0xf)+ ((x>> 4) & 0xf); 
  return x;
}
#elif F2VER==21
unsigned short _f2(unsigned short x,
		   unsigned short c1,
		   unsigned short c2,
		   unsigned short c3,
		   unsigned short c4) {
  x= (x & 0x5555)+ ((x>> 1) & 0x5555); 
  x= (x & 0x3333)+ ((x>> c1) & 0x3333); 
  x= (x & 0x0077)+ ((x>> c3) & 0x0077); 
  x= (x & c4)+ ((x>> c2) & c4); 
  return x;
}
#elif ((F2VER==22) || (F2VER==23))
unsigned short _f2(unsigned short x,
		   unsigned short c1,
		   unsigned short c2) {
  x= (x & 0x5555)+ ((x>> 1) & 0x5555); 
  x= (x & 0x3333)+ ((x>> 2) & 0x3333); 
  x= (x & c2)+ ((x>> 8) & c2); 
  x= (x & c1)+ ((x>> 4) & c1); 
  return x;
}
#elif F2VER==24
unsigned short _f2(unsigned short x,
		   unsigned short c1,
		   unsigned short c2,
		   unsigned short c3,
		   unsigned short c4,
		   unsigned short c5) {
  x= (x & 0x5555)+ ((x>> c1) & 0x5555); 
  x= (x & 0x3333)+ ((x>> c2) & 0x3333); 
  x= (x & 0x0077)+ ((x>> c4) & 0x0077); 
  x= (x & c5)+ ((x>> c3) & c5); 
  return x;
}
#elif F2VER==25
unsigned short _f2(unsigned short x,
		   unsigned short c1,
		   unsigned short c2) {
  x= (x & 0x5555)+ ((x>> 1) & 0x5555); 
  x= (x & 0x3333)+ ((x>> 2) & 0x3333); 
  x= (x & c2)+ ((x>> 8) & c2); 
  x= (x & c1)+ ((x>> 4) & c1); 
  return x;
}
#else
unsigned short _f2(unsigned short x) {
  x= (x & 0x5555)+ ((x>> 1) & 0x5555); 
  x= (x & 0x3333)+ ((x>> 2) & 0x3333); 
  x= (x & 0x0077)+ ((x>> 8) & 0x0077); 
  x= (x & 0xf)+ ((x>> 4) & 0xf); 
  return x;
}
#endif

/* int _f1(char *s) {
   return s[0]=='\0';
   } */
int my_isupper(int c) {
  if((c >= 0) && (c <= 127)) {
    if(isupper(c)) return 1;
    else return 0;
  } else return 0;
  //return (unsigned)c-'A' < 26;
}

int my_islower(int c) {
  if((c >= 0) && (c <= 127)) {
    if(islower(c)) return 1;
    else return 0;
  } else return 0;
  //return (unsigned)c-'a' < 26;
}

int _isalpha(int i) {
  if( ( i < 0 ) || ( i > 127 ) ) {
    return 0;
  }
  if(isalpha(i)!=0) return 1;
  else return 0;
}

int _isdigit(int i) {
  if( ( i < 0 ) || ( i > 127 ) ) {
    return 0;
  }
  return (isdigit(i)!=0 || isalpha(i)!=0);
}

int _isalnum(int i) {
  if( ( i < 0 ) || ( i > 127 ) ) {
    return 0;
  }
  return isalnum(i);
  //if(isalnum(i)!=0) return 1;
  //else return 0;
}

int _seteuid(uid_t uid) {
  if(uid == (uid_t) ~0) {
    return 0;
  }
  return seteuid(uid);
}

int _killpg(__pid_t pgrp, int sig) {
  return killpg(abs(pgrp), sig);
}

long int mystrtol_1(char *nptr, char **endptr, int base) 
{
  int negative;
  unsigned long int cutoff;
  unsigned long int i;
  const char *s;
  unsigned char c;
  const char *save, *end;

  if (base < 0 || base == 1 || base > 36)
    {
      return 0;
    }

  save = s = nptr;

  /* Skip white space.  */
  while (isspace (*s))
    ++s;
  if (__builtin_expect (*s == L_('\0'), 0))
    goto noconv;

  /* Check for a sign.  */
  negative = 0;
  if (*s == L_('-'))
    {
      negative = 1;
      ++s;
    }
  else if (*s == L_('+'))
    ++s;

  /* Recognize number prefix and if BASE is zero, figure it out ourselves.  */
  if (*s == L_('0'))
    {
      if ((base == 0 || base == 16) && toupper (s[1]) == L_('X'))
	{
	  s += 2;
	  base = 16;
	}
      else if (base == 0)
	base = 8;
    }
  else if (base == 0)
    base = 10;

  /* Save the pointer so we can check later if anything happened.  */
  save = s;

  end = NULL;

  i = 0;
  c = *s;
  for (;c != L_('\0'); c = *++s)
    {
      if (s == end)
	break;
      if (c >= L_('0') && c <= L_('9'))
	c -= L_('0');
      else if (isalpha (c))
	c = toupper (c) - L_('A') + 10;
      else
	break;
      if ((int) c >= base)
	break;
      i *= (unsigned long int) base;
      i += c;
    }

  /* Check if anything actually happened.  */
  if (s == save)
    goto noconv;

  /* Store in ENDPTR the address of one character
     past the last character we converted.  */
  if (endptr != NULL)
    *endptr = (char *) s;

  /* Return the result of the appropriate sign.  */
  return negative ? -i : i;

 noconv:
  /* We must handle a special case here: the base is 0 or 16 and the
     first two characters are '0' and 'x', but the rest are no
     hexadecimal digits.  This is no error case.  We return 0 and
     ENDPTR points to the `x`.  */
  if (endptr != NULL)
    {
      if (save - nptr >= 2 && toupper (save[-1]) == L_('X')
	  && save[-2] == L_('0'))
	*endptr = (char *) &save[-1];
      else
	/*  There was no number to convert.  */
	*endptr = (char *) nptr;
    }

  return 0L;
}

long int myatol(char *nptr) {
  return mystrtol_1(nptr, (char **) NULL, 10);
}

long int mystrtol(char *nptr, char **endptr, int base) 
{
  int negative;
  unsigned long int cutoff;
  //unsigned int cutlim;
  unsigned long int i;
  const char *s;
  unsigned char c;
  const char *save, *end;
  //int overflow;

  if (base < 0 || base == 1 || base > 36)
    {
      return 0;
    }

  save = s = nptr;

  /* Skip white space.  */
  while (isspace (*s))
    ++s;
  if (__builtin_expect (*s == L_('\0'), 0))
    goto noconv;

  /* Check for a sign.  */
  negative = 0;
  if (*s == L_('-'))
    {
      negative = 1;
      ++s;
    }
  else if (*s == L_('+'))
    ++s;

  /* Recognize number prefix and if BASE is zero, figure it out ourselves.  */
  if (*s == L_('0'))
    {
      if ((base == 0 || base == 16) && toupper (s[1]) == L_('X'))
	{
	  s += 2;
	  base = 16;
	}
      else if (base == 0)
	base = 8;
    }
  else if (base == 0)
    base = 10;

  /* Save the pointer so we can check later if anything happened.  */
  save = s;

  end = NULL;

  /* Avoid runtime division; lookup cutoff and limit.  */
  /*cutoff = cutoff_tab[base - 2];
    cutlim = cutlim_tab[base - 2];*/

  //overflow = 0;
  i = 0;
  c = *s;
  /*if (sizeof (long int) != sizeof (long int))
    {
    unsigned long int j = 0;
    //unsigned long int jmax = jmax_tab[base - 2];

    for (;c != L_('\0'); c = *++s)
    {
    if (s == end)
    break;
    if (c >= L_('0') && c <= L_('9'))
    c -= L_('0');
    else if (isalpha (c))
    c = toupper (c) - L_('A') + 10;
    else
    break;
    if ((int) c >= base)
    break;
    //else if (j >= jmax)
    //  {
    //    i = (unsigned long int) j;
    //    goto use_long;
    //  }
    else
    j = j * (unsigned long int) base + c;
    }

    i = (unsigned long int) j;
    }
    else*/
  for (;c != L_('\0'); c = *++s)
    {
      if (s == end)
	break;
      if (c >= L_('0') && c <= L_('9'))
	c -= L_('0');
      else if (isalpha (c))
	c = toupper (c) - L_('A') + 10;
      else
	break;
      if ((int) c >= base)
	break;
      /* Check for overflow.  */
      //if (i > cutoff || (i == cutoff && c > cutlim))
      //	overflow = 1;
      //	else
      //	{
      //    use_long:
      i *= (unsigned long int) base;
      i += c;
      //}
    }

  /* Check if anything actually happened.  */
  if (s == save)
    goto noconv;

  /* Store in ENDPTR the address of one character
     past the last character we converted.  */
  if (endptr != NULL)
    *endptr = (char *) s;


  //if (__builtin_expect (overflow, 0))
  //  {
  //    //__set_errno (ERANGE);
  //    return negative ? STRTOL_LONG_MIN : STRTOL_LONG_MAX;
  //  }

  /* Return the result of the appropriate sign.  */
  return negative ? -i : i;

 noconv:
  /* We must handle a special case here: the base is 0 or 16 and the
     first two characters are '0' and 'x', but the rest are no
     hexadecimal digits.  This is no error case.  We return 0 and
     ENDPTR points to the `x`.  */
  if (endptr != NULL)
    {
      if (save - nptr >= 2 && toupper (save[-1]) == L_('X')
	  && save[-2] == L_('0'))
	*endptr = (char *) &save[-1];
      else
	/*  There was no number to convert.  */
	*endptr = (char *) nptr;
    }

  return 0L;
}

int sketch_f1( int x, int y ) {
  return 2*(x + (y*3)) + 7;
}
int sketch_f2( int a, int b, int c, int d ) {
  return c + d + (a * 6) + b; 
}

int arch_prctl(int, unsigned long);
//caddr_t create_module(const char *, size_t);
int delete_module(const char *, int);
//int get_kernel_syms(void *);
char *gets(char *s);
int init_module(void *, unsigned long, const char *);
int modify_ldt(int, void *, unsigned long);
long nfsservctl(int, void *, void *);
int pivot_root(const char *, const char *);
//int query_module(const char *, int, void *, size_t, size_t);
//int uselib(const char *);

void passwd2des(char *passwd, char *key);
int xencrypt(char *secret, char *passwd);
int xdecrypt(char *secret, char *passwd);

#if 0
struct sigvec {
  void (*sv_handler)(int); /* Signal disposition */
  int    sv_mask;          /* Signals to be blocked in handler */
  int    sv_flags;         /* Flags */
};
int sigvec(int sig, const struct sigvec *vec, struct sigvec *ovec);
#endif


/* Copied from the glibc source: */
/* gmon/gmon.c */
void moncontrol(int);
/* gmon/sprofil.c */
int sprofil(struct prof *, int, struct timeval *, unsigned int);
/* include/netdb.h */
int ruserpass(const char *, const char **, const char **);
/* sunrpc/rpc_prot.c */
bool_t xdr_accepted_reply(XDR *xdrs, struct accepted_reply *ar);
bool_t xdr_rejected_reply(XDR *xdrs, struct rejected_reply *rr);
/* sunrpc/svc_simple.c */
int registerrpc(u_long prognum, u_long versnum, u_long procnum,
                char *(*progname) (char *), xdrproc_t inproc,
                xdrproc_t outproc);
/* sunrpc/authdes_prot.c */
bool_t xdr_authdes_cred (XDR *xdrs, struct authdes_cred *cred);
bool_t xdr_authdes_verf (XDR *xdrs, struct authdes_verf *verf);
/* sunrpc/svc_unix.c */
SVCXPRT * svcunixfd_create (int fd, u_int sendsize, u_int recvsize);
/* sunrpc/key_call.c */
int key_setnet (struct key_netstarg *arg);
/* sunrpc/svc_udp.c */
int svcudp_enablecache (SVCXPRT *transp, u_long size);
/* malloc/mcheck.c */
void tr_break(void);
/* sysdeps/unix/sysv/linux/sys/timex.h */
int ntp_gettimex (struct ntptimeval *__ntv);
/* misc/sstk.c */
void *sstk(int);
/* misc/stty.c */
int stty(int fd, const struct sgttyb *);


/* Defined only in assembly on x86_64: */
void mcount(void);

typedef long (func)(long, long, long, long, long, long);

struct func_info {
  const char *fname;
  func *fptr;
  int num_args;
  int is_varargs;
  int is_voidret;
};

struct func_info funcs[] = {
   /* 0 */ {"hcreate_r", (func*)&hcreate_r, 2, 0, 0},
   /* 1 */ {"hdestroy_r", (func*)&hdestroy_r, 1, 0, 1},
   /* 2 */ {"ustat", (func*)&ustat, 2, 0, 0},
   /* 3 */ {"adjtimex", (func*)&adjtimex, 1, 0, 0},
   /* 4 */ {"clock_adjtime", (func*)&clock_adjtime, 2, 0, 0},
   /* 5 */ {"epoll_ctl", (func*)&epoll_ctl, 4, 0, 0},
   /* 6 */ {"epoll_wait", (func*)&epoll_wait, 4, 0, 0},
   /* 7 */ {"sysinfo", (func*)&sysinfo, 1, 0, 0},
   /* 8 */ {"vmsplice", (func*)&vmsplice, 4, 0, 0},
   /* 9 */ {"timerfd_gettime", (func*)&timerfd_gettime, 2, 0, 0},
   /* 10 */{"open_by_handle_at", (func*)&open_by_handle_at, 3, 0, 0},
   /* 11 */{"recvmsg", (func*)&recvmsg, 3, 0, 0},
   /* 12 */{"sendmsg", (func*)&sendmsg, 3, 0, 0},
   /* 13 */{"sendmmsg", (func*)&sendmmsg, 4, 0, 0},
   /* 14 */{"msgctl", (func*)&msgctl, 3, 0, 0},
   /* 15 */{"semop", (func*)&semop, 3, 0, 0},
   /* 16 */{"shmctl", (func*)&shmctl, 3, 0, 0},
   /* 17 */{"argp_usage", (func*)&argp_usage, 1, 0, 1},
   /* 18 */{"pthread_attr_setschedparam", (func*)&pthread_attr_setschedparam, 2, 0, 0},
   /* 19 */{"if_freenameindex", (func*)&if_freenameindex, 1, 0, 1},
   /* 20 */{"freeifaddrs", (func*)&freeifaddrs, 1, 0, 1},
   /* 21 */{"setipv4sourcefilter", (func*)&setipv4sourcefilter, 6, 0, 0},
   /* 22 */{"bindresvport", (func*)&bindresvport, 2, 0, 0},
   /* 23 */{"key_setnet", (func*)&key_setnet, 1, 0, 0},
   /* 24 */{"pmap_getport", (func*)&pmap_getport, 4, 0, 0},
   /* 25 */{"svc_getreq_poll", (func*)&svc_getreq_poll, 2, 0, 1},
   /* 26 */{"setjmp", (func*)&setjmp, 1, 0, 0},
   /* 27 */{"_setjmp", (func*)&_setjmp, 1, 0, 0},
   /* 28 */{"sigreturn", (func*)&sigreturn, 1, 0, 0},
   /* 29 */{"srandom_r", (func*)&srandom_r, 2, 0, 0},
   /* 30 */{"srand48_r", (func*)&srand48_r, 2, 0, 0},
   /* 31 */{"mktime", (func*)&mktime, 1, 0, 0},
   /* 32 */{"getitimer", (func*)&getitimer, 2, 0, 0},
   /* 33 */{"timegm", (func*)&timegm, 1, 0, 0},
   /* 34 */{"ftime", (func*)&ftime, 1, 0, 0},
   /* 35 */{"ntp_gettime", (func*)&ntp_gettime, 1, 0, 0},
   /* 36 */{"ntp_gettimex", (func*)&ntp_gettimex, 1, 0, 0},
   /* 37 */{"uname", (func*)&uname, 1, 0, 0},
   /* 38 */{"times", (func*)&times, 1, 0, 0},
   /* 39 */{"wait3", (func*)&wait3, 3, 0, 0},
   /* 40 */{"wait4", (func*)&wait4, 4, 0, 0},
   /* 41 */{"sched_setparam", (func*)&sched_setparam, 2, 0, 0},
   /* 42 */{"sched_getparam", (func*)&sched_getparam, 2, 0, 0},
   /* 43 */{"sched_setscheduler", (func*)&sched_setscheduler, 3, 0, 0},
   /* 44 */{"sched_rr_get_interval", (func*)&sched_rr_get_interval, 2, 0, 0},
   /* 45 */{"freeaddrinfo", (func*)&freeaddrinfo, 1, 0, 1},
   /* 46 */{"re_compile_fastmap", (func*)&re_compile_fastmap, 1, 0, 0},
   /* 47 */{"fstatfs", (func*)&fstatfs, 2, 0, 0},
   /* 48 */{"fstatvfs", (func*)&fstatvfs, 2, 0, 0},
   /* 49 */{"poll", (func*)&poll, 3, 0, 0},
   /* 50 */{"futimens", (func*)&futimens, 2, 0, 0},
   /* 51 */{"cfgetospeed", (func*)&cfgetospeed, 1, 0, 0},
   /* 52 */{"cfgetispeed", (func*)&cfgetispeed, 1, 0, 0},
   /* 53 */{"cfsetospeed", (func*)&cfsetospeed, 2, 0, 0},
   /* 54 */{"cfsetispeed", (func*)&cfsetispeed, 2, 0, 0},
   /* 55 */{"cfsetspeed", (func*)&cfsetspeed, 2, 0, 0},
   /* 56 */{"tcsetattr", (func*)&tcsetattr, 3, 0, 0},
   /* 57 */{"tcgetattr", (func*)&tcgetattr, 2, 0, 0},
   /* 58 */{"cfmakeraw", (func*)&cfmakeraw, 1, 0, 1},
   /* 59 */{"getrlimit", (func*)&getrlimit, 2, 0, 0},
   /* 60 */{"setrlimit", (func*)&setrlimit, 2, 0, 0},
   /* 61 */{"getrusage", (func*)&getrusage, 2, 0, 0},
   /* 62 */{"readv", (func*)&readv, 3, 0, 0},
   /* 63 */{"writev", (func*)&writev, 3, 0, 0},
   /* 64 */{"preadv", (func*)&preadv, 4, 0, 0},
   /* 65 */{"pwritev", (func*)&pwritev, 4, 0, 0},
   /* 66 */{"gtty", (func*)&gtty, 2, 0, 0},
   /* 67 */{"stty", (func*)&stty, 2, 0, 0},
   /* 68 */{"futimes", (func*)&futimes, 2, 0, 0},
   /* 69 */{"f1_sf", (func*)&f1_sf, 2, 0, 0},
   /* 70 */{"f2_sf", (func*)&f2_sf, 2, 0, 0},
};


int f1num, f2num;
bool void_flag=false;

long f1(long a, long b, long c, long d, long e, long f) {
  return (funcs[f1num].fptr)(a, b, c, d, e, f);
}

long f2(long a, long b, long c, long d, long e, long f) {
  return (funcs[f2num].fptr)(a, b, c, d, e, f);
}

long wrap_f2(long a, long b, long c, long d, long e, long f) {
  return f2(a, b, c, d, e, f);
}

int compare(long *r1p, long *r2p,
	    long a0, long a1, long a2, long a3, long a4, long a5) {
  printf("Starting f1\n");  
  fflush(stdout);
  long r1 = f1(a0, a1, a2, a3, a4, a5);
  printf("Completed f1\n");
  fflush(stdout);
  printf("Starting f2\n");
  fflush(stdout);
  long r2 = wrap_f2(a0, a1, a2, a3, a4, a5);
  printf("Completed f2\n");
  fflush(stdout);
  if (((r1==r2) || (void_flag)) == true) {
    printf("Match\n");
  } else {
    printf("Mismatch\n");
  }
  if (r1p)
    *r1p = r1;
  if (r2p)
    *r2p = r2;
  return r1 == r2;
}

long global_arg0, global_arg1, global_arg2,
  global_arg3, global_arg4, global_arg5;

void fuzz_start() {}

int main(int argc, char **argv) { 
  FILE *fh, *fh_ce;
  if (argc == 5 && argv[3][0]=='f') { // reads tests file for adapter search
    fh = fopen(argv[4], "r");
  } else if (argc == 6 && argv[3][0] == 'g'){ // reads ceinputs file for CE search
    fh_ce = fopen(argv[5], "r");
  }
  fuzz_start(); // needed to create fuzz-start-address for FuzzBALL

  if (argc < 4 && argv[1][0] != 'p') {
    fprintf(stderr, "Usage: two-funcs <f1num> <f2num> a [0-6 args]\n");
    fprintf(stderr, "    or two-funcs <f1num> <f2num> g <struct-arg-pos> <fname>\n");
    fprintf(stderr, "    or two-funcs <f1num> <f2num> f <fname or ->\n");
    fprintf(stderr, "    or two-funcs p # prints struct sizes\n");
    exit(1);
  }
  if (argc == 2 && argv[1][0] == 'p') {
    // prints some glibc structure sizes and number of fields
    print_struct_info();
    return 0;
  }
  f1num = atoi(argv[1]);
  if (f1num < 0 || f1num >= sizeof(funcs)/sizeof(struct func_info)) {
    fprintf(stderr, "Error: f1num %d out of range\n", f1num);
  }
  f2num = atoi(argv[2]);
  if (f2num < 0 || f2num >= sizeof(funcs)/sizeof(struct func_info)) {
    fprintf(stderr, "Error: f2num %d out of range\n", f2num);
  }
  if((funcs[f1num].is_voidret==1) || (funcs[f2num].is_voidret==1) ) {
    void_flag=true;
  }
  
  if (argv[3][0] == 'a') {
    long args[6] = {0, 0, 0, 0, 0, 0};
    long r1, r2;
    int i;
    for (i = 0; i < 6 && i + 4 < argc; i++) {
      char *s = argv[i + 4];
      if (isdigit(s[0])) {
	args[i] = atol(s);
      } else {
	args[i] = (long)s;
      }
    }
    compare(&r1, &r2,
	    args[0], args[1], args[2], args[3], args[4], args[5]);
    if (r1 == r2) {
      printf("Both %ld\n", r1);
    } else {
      printf("Difference %ld vs. %ld\n", r1, r2);
    }
  } else if (argv[3][0] == 'g') {
    int struct_arg_pos = atoi(argv[4]);
    long global_args[6] = {global_arg0, global_arg1, global_arg2, global_arg3, global_arg4, global_arg5};
    long addr;
    fscanf(fh_ce, "%lx",
	   &addr); 
    printf("read ce inputs\n");
    fflush(stdout);
    global_args[struct_arg_pos] = addr;
    compare(0, 0,
	    global_args[0], global_args[1], global_args[2],
	    global_args[3], global_args[4], global_args[5]);
  } else if (argv[3][0] == 'f') {
    long a, b, c, d, e, f;
    if (argv[4][0] == '-' && argv[4][1] == 0) {
      fh = stdin;
    } else {
      //fh = fopen(argv[4], "r");
      if (!fh) {
	fprintf(stderr, "Failed to open %s for reading: %s\n",
		argv[4], strerror(errno));
	return 1;
      }
    }
    while (fscanf(fh, "%lx %lx %lx %lx %lx %lx",
		  &a, &b, &c, &d, &e, &f) != EOF) {
      printf("read a test\n");
      fflush(stdout);
      int is_eq = compare(0, 0, a, b, c, d, e, f);
      if (!is_eq)
	exit(1);
    }
    printf("All tests succeeded!\n");
  } else {
    fprintf(stderr, "Unhandled command argument\n");
    exit(1);
  }
  return 0;
}
