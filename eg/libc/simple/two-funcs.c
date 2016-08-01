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
#include <sys/kdaemon.h>
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

#define INIT /**/
#define GETC() getchar()
#define PEEKC() 'x'
#define UNGETC(c) ungetc(c, stdin)
#define RETURN(ptr) return ptr
#define ERROR(val) return 0
#include <regexp.h>
#undef INIT
#undef GETC
#undef PEEKC
#undef UNGETC
#undef RETURN
#undef ERROR




# define STRTOL_LONG_MIN LONG_MIN
# define STRTOL_LONG_MAX LONG_MAX
# define L_(Ch) Ch

/* Equivalent with 0,00000000,0,00000000,0,00000001,1,00000001 
int _f1(int x, unsigned y){//, int z) {
    return (x << 1) + (y % 2);// + (z << 1);
}*/

int _f2(int a, int b, int c, int d) {//,int e){//, int f) {
  return c + d + (a & b);// + e;// + f;
    //return a + b + (c & d);
}

int _f1(char *s) {
  return s[0]=='\0';
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


int arch_prctl(int, unsigned long);
caddr_t create_module(const char *, size_t);
int delete_module(const char *, int);
int get_kernel_syms(void *);
char *gets(char *s);
int init_module(void *, unsigned long, const char *);
int modify_ldt(int, void *, unsigned long);
long nfsservctl(int, void *, void *);
int pivot_root(const char *, const char *);
int query_module(const char *, int, void *, size_t, size_t);
int uselib(const char *);

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
    /*    0 */ {"syslog", (func*)&syslog, 2, 1, 1},
    /*    1 */ {"vsyslog", (func*)&vsyslog, 3, 0, 1},
    /*    2 */ {"openlog", (func*)&openlog, 3, 0, 1},
    /*    3 */ {"closelog", (func*)&closelog, 0, 0, 1},
    /*    4 */ {"setlogmask", (func*)&setlogmask, 1, 0, 0},
    /*    5 */ {"syscall", (func*)&syscall, 1, 1, 0}, //**NOTE: Maybe this function should be blacklisted
    /*    6 */ {"daemon", (func*)&daemon, 2, 0, 0},
    /*    7 */ {"mmap", (func*)&mmap, 6, 0, 0},
    /*    8 */ {"munmap", (func*)&munmap, 2, 0, 0},
    /*    9 */ {"mprotect", (func*)&mprotect, 3, 0, 0},
    /*   10 */ {"msync", (func*)&msync, 3, 0, 0},
    /*   11 */ {"madvise", (func*)&madvise, 3, 0, 0},
    /*   12 */ {"mincore", (func*)&mincore, 3, 0, 0},
    /*   13 */ {"remap_file_pages", (func*)&remap_file_pages, 5, 0, 0},
    /*   14 */ {"mlock", (func*)&mlock, 2, 0, 0},
    /*   15 */ {"munlock", (func*)&munlock, 2, 0, 0},
    /*   16 */ {"mlockall", (func*)&mlockall, 1, 0, 0},
    /*   17 */ {"munlockall", (func*)&munlockall, 0, 0, 0},
    /*   18 */ {"hdestroy", (func*)&hdestroy, 0, 0, 1},
    /*   19 */ {"hsearch", (func*)&hsearch, 2, 0, 0},
    /*   20 */ {"hcreate", (func*)&hcreate, 1, 0, 0},
    /*   21 */ {"hcreate_r", (func*)&hcreate_r, 2, 0, 0},
    /*   22 */ {"hdestroy_r", (func*)&hdestroy_r, 1, 0, 1},
    /*   23 */ {"hsearch_r", (func*)&hsearch_r, 4, 0, 0},
    /*   24 */ {"tsearch", (func*)&tsearch, 3, 0, 0},
    /*   25 */ {"tfind", (func*)&tfind, 3, 0, 0},
    /*   26 */ {"tdelete", (func*)&tdelete, 3, 0, 0},
    /*   27 */ {"twalk", (func*)&twalk, 2, 0, 1},
    /*   28 */ {"tdestroy", (func*)&tdestroy, 2, 0, 1},
    /*   29 */ {"lsearch", (func*)&lsearch, 5, 0, 0},
    /*   30 */ {"lfind", (func*)&lfind, 5, 0, 0},
    /*   31 */ {"vwarnx", (func*)&vwarnx, 2, 0, 1},
    /*   32 */ {"vwarn", (func*)&vwarn, 2, 0, 1},
    /*   33 */ {"warn", (func*)&warn, 1, 1, 1},
    /*   34 */ {"warnx", (func*)&warnx, 1, 1, 1},
    /*   35 */ {"verr", (func*)&verr, 3, 0, 1},
    /*   36 */ {"verrx", (func*)&verrx, 3, 0, 1},
    /*   37 */ {"err", (func*)&err, 2, 1, 1},
    /*   38 */ {"errx", (func*)&errx, 2, 1, 1},
    /*   39 */ {"error", (func*)&error, 3, 1, 1},
    /*   40 */ {"error_at_line", (func*)&error_at_line, 5, 1, 1},
    /*   41 */ {"ustat", (func*)&ustat, 2, 0, 0},
    /*   42 */ {"get_nprocs", (func*)&get_nprocs, 0, 0, 0},
    /*   43 */ {"get_nprocs_conf", (func*)&get_nprocs_conf, 0, 0, 0},
    /*   44 */ {"get_phys_pages", (func*)&get_phys_pages, 0, 0, 0},
    /*   45 */ {"get_avphys_pages", (func*)&get_avphys_pages, 0, 0, 0},
    /*   46 */ {"dirname", (func*)&dirname, 1, 0, 0},
    /*   47 */ {"fgetxattr", (func*)&fgetxattr, 4, 0, 0},
    /*   48 */ {"flistxattr", (func*)&flistxattr, 3, 0, 0},
    /*   49 */ {"fremovexattr", (func*)&fremovexattr, 2, 0, 0},
    /*   50 */ {"fsetxattr", (func*)&fsetxattr, 5, 0, 0},
    /*   51 */ {"getxattr", (func*)&getxattr, 4, 0, 0},
    /*   52 */ {"listxattr", (func*)&listxattr, 3, 0, 0},
    /*   53 */ {"lgetxattr", (func*)&lgetxattr, 4, 0, 0},
    /*   54 */ {"llistxattr", (func*)&llistxattr, 3, 0, 0},
    /*   55 */ {"lremovexattr", (func*)&lremovexattr, 2, 0, 0},
    /*   56 */ {"lsetxattr", (func*)&lsetxattr, 5, 0, 0},
    /*   57 */ {"removexattr", (func*)&removexattr, 2, 0, 0},
    /*   58 */ {"setxattr", (func*)&setxattr, 5, 0, 0},
    /*   59 */ {"step", (func*)&step, 2, 0, 0},
    /*   60 */ {"advance", (func*)&advance, 2, 0, 0},
    /*   61 */ {"setfsent", (func*)&setfsent, 0, 0, 0},
    /*   62 */ {"getfsent", (func*)&getfsent, 0, 0, 0},
    /*   63 */ {"getfsspec", (func*)&getfsspec, 1, 0, 0},
    /*   64 */ {"getfsfile", (func*)&getfsfile, 1, 0, 0},
    /*   65 */ {"endfsent", (func*)&endfsent, 0, 0, 1},
    /*   66 */ {"revoke", (func*)&revoke, 1, 0, 0},
    /*   67 */ {"ioperm", (func*)&ioperm, 3, 0, 0},
    /*   68 */ {"iopl", (func*)&iopl, 1, 0, 0},
    /*   69 */ {"sysctl", (func*)&sysctl, 6, 0, 0},
    /*   70 */ {"clone", (func*)&clone, 4, 1, 0},
    /*   71 */ {"lseek", (func*)&lseek, 3, 0, 0},
    /*   72 */ {"umount", (func*)&umount, 1, 0, 0},
    /*   73 */ {"umount2", (func*)&umount2, 2, 0, 0},
    /*   74 */ {"readahead", (func*)&readahead, 3, 0, 0},
    /*   75 */ {"setfsuid", (func*)&setfsuid, 1, 0, 0},
    /*   76 */ {"setfsgid", (func*)&setfsgid, 1, 0, 0},
    /*   77 */ {"gnu_dev_major", (func*)&gnu_dev_major, 1, 0, 0},
    /*   78 */ {"gnu_dev_minor", (func*)&gnu_dev_minor, 1, 0, 0},
    /*   79 */ {"gnu_dev_makedev", (func*)&gnu_dev_makedev, 2, 0, 0},
    /*   80 */ {"epoll_pwait", (func*)&epoll_pwait, 5, 0, 0},
    /*   81 */ {"signalfd", (func*)&signalfd, 3, 0, 0},
    /*   82 */ {"eventfd", (func*)&eventfd, 2, 0, 0},
    /*   83 */ {"eventfd_read", (func*)&eventfd_read, 2, 0, 0},
    /*   84 */ {"eventfd_write", (func*)&eventfd_write, 2, 0, 0},
    /*   85 */ {"prlimit", (func*)&prlimit, 4, 0, 0},
    /*   86 */ {"arch_prctl", (func*)&arch_prctl, 2, 0, 0},
    /*   87 */ {"modify_ldt", (func*)&modify_ldt, 3, 0, 0},
    /*   88 */ {"fanotify_mark", (func*)&fanotify_mark, 5, 0, 0},
    /*   89 */ {"adjtimex", (func*)&adjtimex, 1, 0, 0},
    /*   90 */ {"clock_adjtime", (func*)&clock_adjtime, 2, 0, 0},
    /*   91 */ {"create_module", (func*)&create_module, 2, 0, 0},
    /*   92 */ {"delete_module", (func*)&delete_module, 2, 0, 0},
    /*   93 */ {"epoll_create", (func*)&epoll_create, 1, 0, 0},
    /*   94 */ {"epoll_create1", (func*)&epoll_create1, 1, 0, 0},
    /*   95 */ {"epoll_ctl", (func*)&epoll_ctl, 4, 0, 0},
    /*   96 */ {"epoll_wait", (func*)&epoll_wait, 4, 0, 0},
    /*   97 */ {"get_kernel_syms", (func*)&get_kernel_syms, 1, 0, 0},
    /*   98 */ {"init_module", (func*)&init_module, 3, 0, 0},
    /*   99 */ {"inotify_add_watch", (func*)&inotify_add_watch, 3, 0, 0},
    /*  100 */ {"inotify_init", (func*)&inotify_init, 0, 0, 0},
    /*  101 */ {"inotify_init1", (func*)&inotify_init1, 1, 0, 0},
    /*  102 */ {"inotify_rm_watch", (func*)&inotify_rm_watch, 2, 0, 0},
    /*  103 */ {"klogctl", (func*)&klogctl, 3, 0, 0},
    /*  104 */ {"mount", (func*)&mount, 5, 0, 0},
    /*  105 */ {"mremap", (func*)&mremap, 4, 1, 0},
    /*  106 */ {"nfsservctl", (func*)&nfsservctl, 3, 0, 0},
    /*  107 */ {"personality", (func*)&personality, 1, 0, 0},
    /*  108 */ {"pivot_root", (func*)&pivot_root, 2, 0, 0},
    /*  109 */ {"prctl", (func*)&prctl, 1, 1, 0},
    /*  110 */ {"query_module", (func*)&query_module, 5, 0, 0},
    /*  111 */ {"quotactl", (func*)&quotactl, 4, 0, 0},
    /*  112 */ {"splice", (func*)&splice, 6, 0, 0},
    /*  113 */ {"sysinfo", (func*)&sysinfo, 1, 0, 0},
    /*  114 */ {"tee", (func*)&tee, 4, 0, 0},
    /*  115 */ {"unshare", (func*)&unshare, 1, 0, 0},
    /*  116 */ {"uselib", (func*)&uselib, 1, 0, 0},
    /*  117 */ {"vmsplice", (func*)&vmsplice, 4, 0, 0},
    /*  118 */ {"timerfd_create", (func*)&timerfd_create, 2, 0, 0},
    /*  119 */ {"timerfd_settime", (func*)&timerfd_settime, 4, 0, 0},
    /*  120 */ {"timerfd_gettime", (func*)&timerfd_gettime, 2, 0, 0},
    /*  121 */ {"fanotify_init", (func*)&fanotify_init, 2, 0, 0},
    /*  122 */ {"name_to_handle_at", (func*)&name_to_handle_at, 5, 0, 0},
    /*  123 */ {"open_by_handle_at", (func*)&open_by_handle_at, 3, 0, 0},
    /*  124 */ {"setns", (func*)&setns, 2, 0, 0},
    /*  125 */ {"process_vm_readv", (func*)&process_vm_readv, 6, 0, 0},
    /*  126 */ {"process_vm_writev", (func*)&process_vm_writev, 6, 0, 0},
    /*  127 */ {"bdflush", (func*)&bdflush, 2, 0, 0},
    /*  128 */ {"accept", (func*)&accept, 3, 0, 0},
    /*  129 */ {"bind", (func*)&bind, 3, 0, 0},
    /*  130 */ {"connect", (func*)&connect, 3, 0, 0},
    /*  131 */ {"getpeername", (func*)&getpeername, 3, 0, 0},
    /*  132 */ {"getsockname", (func*)&getsockname, 3, 0, 0},
    /*  133 */ {"getsockopt", (func*)&getsockopt, 5, 0, 0},
    /*  134 */ {"listen", (func*)&listen, 2, 0, 0},
    /*  135 */ {"recv", (func*)&recv, 4, 0, 0},
    /*  136 */ {"recvfrom", (func*)&recvfrom, 6, 0, 0},
    /*  137 */ {"recvmsg", (func*)&recvmsg, 3, 0, 0},
    /*  138 */ {"send", (func*)&send, 4, 0, 0},
    /*  139 */ {"sendmsg", (func*)&sendmsg, 3, 0, 0},
    /*  140 */ {"sendto", (func*)&sendto, 6, 0, 0},
    /*  141 */ {"setsockopt", (func*)&setsockopt, 5, 0, 0},
    /*  142 */ {"shutdown", (func*)&shutdown, 2, 0, 0},
    /*  143 */ {"socket", (func*)&socket, 3, 0, 0},
    /*  144 */ {"socketpair", (func*)&socketpair, 4, 0, 0},
    /*  145 */ {"isfdtype", (func*)&isfdtype, 2, 0, 0},
    /*  146 */ {"sockatmark", (func*)&sockatmark, 1, 0, 0},
    /*  147 */ {"accept4", (func*)&accept4, 4, 0, 0},
    /*  148 */ {"recvmmsg", (func*)&recvmmsg, 5, 0, 0},
    /*  149 */ {"sendmmsg", (func*)&sendmmsg, 4, 0, 0},
    /*  150 */ {"ftok", (func*)&ftok, 2, 0, 0},
    /*  151 */ {"msgsnd", (func*)&msgsnd, 4, 0, 0},
    /*  152 */ {"msgrcv", (func*)&msgrcv, 5, 0, 0},
    /*  153 */ {"msgget", (func*)&msgget, 2, 0, 0},
    /*  154 */ {"msgctl", (func*)&msgctl, 3, 0, 0},
    /*  155 */ {"semop", (func*)&semop, 3, 0, 0},
    /*  156 */ {"semget", (func*)&semget, 3, 0, 0},
    /*  157 */ {"semctl", (func*)&semctl, 3, 1, 0},
    /*  158 */ {"semtimedop", (func*)&semtimedop, 4, 0, 0},
    /*  159 */ {"shmat", (func*)&shmat, 3, 0, 0},
    /*  160 */ {"shmdt", (func*)&shmdt, 1, 0, 0},
    /*  161 */ {"shmget", (func*)&shmget, 3, 0, 0},
    /*  162 */ {"shmctl", (func*)&shmctl, 3, 0, 0},
    /*  163 */ {"moncontrol", (func*)&moncontrol, 1, 0, 1},
    /*  164 */ {"monstartup", (func*)&monstartup, 2, 0, 1},
    /*  165 */ {"_mcleanup", (func*)&_mcleanup, 0, 0, 1},
    /*  166 */ {"profil", (func*)&profil, 4, 0, 0},
    /*  167 */ {"sprofil", (func*)&sprofil, 4, 0, 0},
    /*  168 */ {"mcount", (func*)&mcount, 0, 0, 1},
    /*  169 */ {"wctrans", (func*)&wctrans, 1, 0, 0},
    /*  170 */ {"towctrans", (func*)&towctrans, 2, 0, 0},
    /*  171 */ {"towctrans_l", (func*)&towctrans_l, 3, 0, 0},
    /*  172 */ {"iswalnum", (func*)&iswalnum, 1, 0, 0},
    /*  173 */ {"iswalpha", (func*)&iswalpha, 1, 0, 0},
    /*  174 */ {"iswblank", (func*)&iswblank, 1, 0, 0},
    /*  175 */ {"iswcntrl", (func*)&iswcntrl, 1, 0, 0},
    /*  176 */ {"iswdigit", (func*)&iswdigit, 1, 0, 0},
    /*  177 */ {"iswlower", (func*)&iswlower, 1, 0, 0},
    /*  178 */ {"iswgraph", (func*)&iswgraph, 1, 0, 0},
    /*  179 */ {"iswprint", (func*)&iswprint, 1, 0, 0},
    /*  180 */ {"iswpunct", (func*)&iswpunct, 1, 0, 0},
    /*  181 */ {"iswspace", (func*)&iswspace, 1, 0, 0},
    /*  182 */ {"iswupper", (func*)&iswupper, 1, 0, 0},
    /*  183 */ {"iswxdigit", (func*)&iswxdigit, 1, 0, 0},
    /*  184 */ {"towlower", (func*)&towlower, 1, 0, 0},
    /*  185 */ {"towupper", (func*)&towupper, 1, 0, 0},
    /*  186 */ {"wctype", (func*)&wctype, 1, 0, 0},
    /*  187 */ {"iswctype", (func*)&iswctype, 2, 0, 0},
    /*  188 */ {"iswalnum_l", (func*)&iswalnum_l, 2, 0, 0},
    /*  189 */ {"iswalpha_l", (func*)&iswalpha_l, 2, 0, 0},
    /*  190 */ {"iswblank_l", (func*)&iswblank_l, 2, 0, 0},
    /*  191 */ {"iswcntrl_l", (func*)&iswcntrl_l, 2, 0, 0},
    /*  192 */ {"iswdigit_l", (func*)&iswdigit_l, 2, 0, 0},
    /*  193 */ {"iswlower_l", (func*)&iswlower_l, 2, 0, 0},
    /*  194 */ {"iswgraph_l", (func*)&iswgraph_l, 2, 0, 0},
    /*  195 */ {"iswprint_l", (func*)&iswprint_l, 2, 0, 0},
    /*  196 */ {"iswpunct_l", (func*)&iswpunct_l, 2, 0, 0},
    /*  197 */ {"iswspace_l", (func*)&iswspace_l, 2, 0, 0},
    /*  198 */ {"iswupper_l", (func*)&iswupper_l, 2, 0, 0},
    /*  199 */ {"iswxdigit_l", (func*)&iswxdigit_l, 2, 0, 0},
    /*  200 */ {"towlower_l", (func*)&towlower_l, 2, 0, 0},
    /*  201 */ {"towupper_l", (func*)&towupper_l, 2, 0, 0},
    /*  202 */ {"wctype_l", (func*)&wctype_l, 2, 0, 0},
    /*  203 */ {"iswctype_l", (func*)&iswctype_l, 3, 0, 0},
    /*  204 */ {"wctrans_l", (func*)&wctrans_l, 2, 0, 0},
    /*  205 */ {"getspent", (func*)&getspent, 0, 0, 0},
    /*  206 */ {"getspnam", (func*)&getspnam, 1, 0, 0},
    /*  207 */ {"sgetspent", (func*)&sgetspent, 1, 0, 0},
    /*  208 */ {"fgetspent", (func*)&fgetspent, 1, 0, 0},
    /*  209 */ {"putspent", (func*)&putspent, 2, 0, 0},
    /*  210 */ {"setspent", (func*)&setspent, 0, 0, 1},
    /*  211 */ {"endspent", (func*)&endspent, 0, 0, 1},
    /*  212 */ {"getspent_r", (func*)&getspent_r, 4, 0, 0},
    /*  213 */ {"getspnam_r", (func*)&getspnam_r, 5, 0, 0},
    /*  214 */ {"sgetspent_r", (func*)&sgetspent_r, 5, 0, 0},
    /*  215 */ {"fgetspent_r", (func*)&fgetspent_r, 5, 0, 0},
    /*  216 */ {"lckpwdf", (func*)&lckpwdf, 0, 0, 0},
    /*  217 */ {"ulckpwdf", (func*)&ulckpwdf, 0, 0, 0},
    /*  218 */ {"getsgent", (func*)&getsgent, 0, 0, 0},
    /*  219 */ {"getsgnam", (func*)&getsgnam, 1, 0, 0},
    /*  220 */ {"sgetsgent", (func*)&sgetsgent, 1, 0, 1},
    /*  221 */ {"fgetsgent", (func*)&fgetsgent, 1, 0, 0},
    /*  222 */ {"putsgent", (func*)&putsgent, 2, 0, 0},
    /*  223 */ {"setsgent", (func*)&setsgent, 0, 0, 0},
    /*  224 */ {"endsgent", (func*)&endsgent, 0, 0, 1},
    /*  225 */ {"getsgent_r", (func*)&getsgent_r, 4, 0, 0},
    /*  226 */ {"getsgnam_r", (func*)&getsgnam_r, 5, 0, 0},
    /*  227 */ {"sgetsgent_r", (func*)&sgetsgent_r, 5, 0, 0},
    /*  228 */ {"fgetsgent_r", (func*)&fgetsgent_r, 5, 0, 0},
    /*  229 */ {"argp_failure", (func*)&argp_failure, 4, 1, 1},
    /*  230 */ {"argp_help", (func*)&argp_help, 4, 0, 1},
    /*  231 */ {"argp_state_help", (func*)&argp_state_help, 3, 0, 1},
    /*  232 */ {"argp_error", (func*)&argp_error, 2, 1, 1},
    /*  233 */ {"argp_parse", (func*)&argp_parse, 6, 0, 0},
    /*  234 */ {"argp_usage", (func*)&argp_usage, 1, 0, 1},
    /*  235 */ {"pthread_equal", (func*)&pthread_equal, 2, 0, 0},
    /*  236 */ {"pthread_attr_destroy", (func*)&pthread_attr_destroy, 1, 0, 0},
    /*  237 */ {"pthread_attr_init", (func*)&pthread_attr_init, 1, 0, 0},
    /*  238 */ {"pthread_attr_getdetachstate", (func*)&pthread_attr_getdetachstate, 2, 0, 0},
    /*  239 */ {"pthread_attr_setdetachstate", (func*)&pthread_attr_setdetachstate, 2, 0, 0},
    /*  240 */ {"pthread_attr_getinheritsched", (func*)&pthread_attr_getinheritsched, 2, 0, 0},
    /*  241 */ {"pthread_attr_setinheritsched", (func*)&pthread_attr_setinheritsched, 2, 0, 0},
    /*  242 */ {"pthread_attr_getschedparam", (func*)&pthread_attr_getschedparam, 2, 0, 0},
    /*  243 */ {"pthread_attr_setschedparam", (func*)&pthread_attr_setschedparam, 2, 0, 0},
    /*  244 */ {"pthread_attr_getschedpolicy", (func*)&pthread_attr_getschedpolicy, 2, 0, 0},
    /*  245 */ {"pthread_attr_setschedpolicy", (func*)&pthread_attr_setschedpolicy, 2, 0, 0},
    /*  246 */ {"pthread_attr_getscope", (func*)&pthread_attr_getscope, 2, 0, 0},
    /*  247 */ {"pthread_attr_setscope", (func*)&pthread_attr_setscope, 2, 0, 0},
    /*  248 */ {"pthread_condattr_destroy", (func*)&pthread_condattr_destroy, 1, 0, 0},
    /*  249 */ {"pthread_condattr_init", (func*)&pthread_condattr_init, 1, 0, 0},
    /*  250 */ {"pthread_cond_broadcast", (func*)&pthread_cond_broadcast, 1, 0, 0},
    /*  251 */ {"pthread_cond_destroy", (func*)&pthread_cond_destroy, 1, 0, 0},
    /*  252 */ {"pthread_cond_init", (func*)&pthread_cond_init, 2, 0, 0},
    /*  253 */ {"pthread_cond_signal", (func*)&pthread_cond_signal, 1, 0, 0},
    /*  254 */ {"pthread_cond_wait", (func*)&pthread_cond_wait, 2, 0, 0},
    /*  255 */ {"pthread_cond_timedwait", (func*)&pthread_cond_timedwait, 3, 0, 0},
    /*  256 */ {"pthread_exit", (func*)&pthread_exit, 1, 0, 1},
    /*  257 */ {"pthread_getschedparam", (func*)&pthread_getschedparam, 3, 0, 0},
    /*  258 */ {"pthread_setschedparam", (func*)&pthread_setschedparam, 3, 0, 0},
    /*  259 */ {"pthread_mutex_destroy", (func*)&pthread_mutex_destroy, 1, 0, 0},
    /*  260 */ {"pthread_mutex_init", (func*)&pthread_mutex_init, 2, 0, 0},
    /*  261 */ {"pthread_mutex_lock", (func*)&pthread_mutex_lock, 1, 0, 0},
    /*  262 */ {"pthread_mutex_unlock", (func*)&pthread_mutex_unlock, 1, 0, 0},
    /*  263 */ {"pthread_self", (func*)&pthread_self, 0, 0, 0},
    /*  264 */ {"pthread_setcancelstate", (func*)&pthread_setcancelstate, 2, 0, 0},
    /*  265 */ {"pthread_setcanceltype", (func*)&pthread_setcanceltype, 2, 0, 0},
    /*  266 */ {"backtrace", (func*)&backtrace, 2, 0, 0},
    /*  267 */ {"backtrace_symbols", (func*)&backtrace_symbols, 2, 0, 0},
    /*  268 */ {"backtrace_symbols_fd", (func*)&backtrace_symbols_fd, 3, 0, 1},
    /*  269 */ {"htonl", (func*)&htonl, 1, 0, 0},
    /*  270 */ {"htons", (func*)&htons, 1, 0, 0},
    /*  271 */ {"inet_lnaof", (func*)&inet_lnaof, 1, 0, 0},
    /*  272 */ {"inet_makeaddr", (func*)&inet_makeaddr, 2, 0, 0},
    /*  273 */ {"inet_netof", (func*)&inet_netof, 1, 0, 0},
    /*  274 */ {"inet_ntoa", (func*)&inet_ntoa, 1, 0, 0},
    /*  275 */ {"inet_network", (func*)&inet_network, 1, 0, 0},
    /*  276 */ {"gethostbyaddr", (func*)&gethostbyaddr, 3, 0, 0},
    /*  277 */ {"gethostbyname", (func*)&gethostbyname, 1, 0, 0},
    /*  278 */ {"gethostbyname2", (func*)&gethostbyname2, 2, 0, 0},
    /*  279 */ {"gethostbyname_r", (func*)&gethostbyname_r, 6, 0, 0},
    /*  280 */ {"gethostent", (func*)&gethostent, 0, 0, 0},
    /*  281 */ {"sethostent", (func*)&sethostent, 1, 0, 1},
    /*  282 */ {"endhostent", (func*)&endhostent, 0, 0, 1},
    /*  283 */ {"gethostent_r", (func*)&gethostent_r, 5, 0, 0},
    /*  284 */ {"getnetbyaddr", (func*)&getnetbyaddr, 2, 0, 0},
    /*  285 */ {"getnetbyname", (func*)&getnetbyname, 1, 0, 0},
    /*  286 */ {"getnetent", (func*)&getnetent, 0, 0, 0},
    /*  287 */ {"setnetent", (func*)&setnetent, 1, 0, 1},
    /*  288 */ {"endnetent", (func*)&endnetent, 0, 0, 1},
    /*  289 */ {"getnetent_r", (func*)&getnetent_r, 5, 0, 0},
    /*  290 */ {"getnetbyname_r", (func*)&getnetbyname_r, 6, 0, 0},
    /*  291 */ {"getprotobynumber", (func*)&getprotobynumber, 1, 0, 0},
    /*  292 */ {"getprotobynumber_r", (func*)&getprotobynumber_r, 5, 0, 0},
    /*  293 */ {"getprotoent", (func*)&getprotoent, 0, 0, 0},
    /*  294 */ {"setprotoent", (func*)&setprotoent, 1, 0, 1},
    /*  295 */ {"endprotoent", (func*)&endprotoent, 0, 0, 1},
    /*  296 */ {"getprotoent_r", (func*)&getprotoent_r, 4, 0, 0},
    /*  297 */ {"getprotobyname", (func*)&getprotobyname, 1, 0, 0},
    /*  298 */ {"getprotobyname_r", (func*)&getprotobyname_r, 5, 0, 0},
    /*  299 */ {"getservbyname", (func*)&getservbyname, 2, 0, 0},
    /*  300 */ {"getservbyname_r", (func*)&getservbyname_r, 6, 0, 0},
    /*  301 */ {"getservbyport", (func*)&getservbyport, 2, 0, 0},
    /*  302 */ {"getservbyport_r", (func*)&getservbyport_r, 6, 0, 0},
    /*  303 */ {"getservent", (func*)&getservent, 0, 0, 0},
    /*  304 */ {"setservent", (func*)&setservent, 1, 0, 1},
    /*  305 */ {"endservent", (func*)&endservent, 0, 0, 1},
    /*  306 */ {"getservent_r", (func*)&getservent_r, 4, 0, 0},
    /*  307 */ {"getrpcent", (func*)&getrpcent, 0, 0, 0},
    /*  308 */ {"getrpcbyname", (func*)&getrpcbyname, 1, 0, 0},
    /*  309 */ {"getrpcbynumber", (func*)&getrpcbynumber, 1, 0, 0},
    /*  310 */ {"setrpcent", (func*)&setrpcent, 1, 0, 1},
    /*  311 */ {"endrpcent", (func*)&endrpcent, 0, 0, 1},
    /*  312 */ {"getrpcent_r", (func*)&getrpcent_r, 4, 0, 0},
    /*  313 */ {"getrpcbyname_r", (func*)&getrpcbyname_r, 5, 0, 0},
    /*  314 */ {"getrpcbynumber_r", (func*)&getrpcbynumber_r, 5, 0, 0},
    /*  315 */ {"ether_aton", (func*)&ether_aton, 1, 0, 0},
    /*  316 */ {"ether_aton_r", (func*)&ether_aton_r, 2, 0, 0},
    /*  317 */ {"ether_hostton", (func*)&ether_hostton, 2, 0, 0},
    /*  318 */ {"ether_line", (func*)&ether_line, 3, 0, 0},
    /*  319 */ {"ether_ntoa", (func*)&ether_ntoa, 1, 0, 0},
    /*  320 */ {"ether_ntoa_r", (func*)&ether_ntoa_r, 2, 0, 0},
    /*  321 */ {"ether_ntohost", (func*)&ether_ntohost, 2, 0, 0},
    /*  322 */ {"setnetgrent", (func*)&setnetgrent, 1, 0, 0},
    /*  323 */ {"endnetgrent", (func*)&endnetgrent, 0, 0, 1},
    /*  324 */ {"getnetgrent_r", (func*)&getnetgrent_r, 5, 0, 0},
    /*  325 */ {"innetgr", (func*)&innetgr, 4, 0, 0},
    /*  326 */ {"getnetgrent", (func*)&getnetgrent, 3, 0, 0},
    /*  327 */ {"if_nametoindex", (func*)&if_nametoindex, 1, 0, 0},
    /*  328 */ {"if_freenameindex", (func*)&if_freenameindex, 1, 0, 1},
    /*  329 */ {"if_nameindex", (func*)&if_nameindex, 0, 0, 0},
    /*  330 */ {"if_indextoname", (func*)&if_indextoname, 2, 0, 0},
    /*  331 */ {"getifaddrs", (func*)&getifaddrs, 1, 0, 0},
    /*  332 */ {"freeifaddrs", (func*)&freeifaddrs, 1, 0, 1},
    /*  333 */ {"getipv4sourcefilter", (func*)&getipv4sourcefilter, 6, 0, 0},
    /*  334 */ {"setipv4sourcefilter", (func*)&setipv4sourcefilter, 6, 0, 0},
    /*  335 */ {"rresvport_af", (func*)&rresvport_af, 2, 0, 0},
    /*  336 */ {"rcmd", (func*)&rcmd, 6, 0, 0},
    /*  337 */ {"rresvport", (func*)&rresvport, 1, 0, 0},
    /*  338 */ {"ruserok_af", (func*)&ruserok_af, 5, 0, 0},
    /*  339 */ {"ruserok", (func*)&ruserok, 4, 0, 0},
    /*  340 */ {"iruserok_af", (func*)&iruserok_af, 5, 0, 0},
    /*  341 */ {"iruserok", (func*)&iruserok, 4, 0, 0},
    /*  342 */ {"rexec", (func*)&rexec, 6, 0, 0},
    /*  343 */ {"ruserpass", (func*)&ruserpass, 3, 0, 0},
    /*  344 */ {"setaliasent", (func*)&setaliasent, 0, 0, 1},
    /*  345 */ {"endaliasent", (func*)&endaliasent, 0, 0, 1},
    /*  346 */ {"getaliasent_r", (func*)&getaliasent_r, 4, 0, 0},
    /*  347 */ {"getaliasent", (func*)&getaliasent, 0, 0, 0},
    /*  348 */ {"getaliasbyname", (func*)&getaliasbyname, 1, 0, 0},
    /*  349 */ {"getaliasbyname_r", (func*)&getaliasbyname_r, 5, 0, 0},
    /*  350 */ {"inet6_option_space", (func*)&inet6_option_space, 1, 0, 0},
    /*  351 */ {"inet6_option_init", (func*)&inet6_option_init, 3, 0, 0},
    /*  352 */ {"inet6_option_append", (func*)&inet6_option_append, 4, 0, 0},
    /*  353 */ {"inet6_option_alloc", (func*)&inet6_option_alloc, 4, 0, 0},
    /*  354 */ {"inet6_option_next", (func*)&inet6_option_next, 2, 0, 0},
    /*  355 */ {"inet6_option_find", (func*)&inet6_option_find, 3, 0, 0},
    /*  356 */ {"inet6_opt_init", (func*)&inet6_opt_init, 2, 0, 0},
    /*  357 */ {"inet6_opt_finish", (func*)&inet6_opt_finish, 3, 0, 0},
    /*  358 */ {"inet6_opt_set_val", (func*)&inet6_opt_set_val, 4, 0, 0},
    /*  359 */ {"inet6_opt_next", (func*)&inet6_opt_next, 6, 0, 0},
    /*  360 */ {"inet6_opt_find", (func*)&inet6_opt_find, 6, 0, 0},
    /*  361 */ {"inet6_opt_get_val", (func*)&inet6_opt_get_val, 4, 0, 0},
    /*  362 */ {"inet6_rth_space", (func*)&inet6_rth_space, 2, 0, 0},
    /*  363 */ {"inet6_rth_init", (func*)&inet6_rth_init, 4, 0, 0},
    /*  364 */ {"inet6_rth_add", (func*)&inet6_rth_add, 2, 0, 0},
    /*  365 */ {"inet6_rth_reverse", (func*)&inet6_rth_reverse, 2, 0, 0},
    /*  366 */ {"inet6_rth_segments", (func*)&inet6_rth_segments, 1, 0, 0},
    /*  367 */ {"inet6_rth_getaddr", (func*)&inet6_rth_getaddr, 2, 0, 0},
    /*  368 */ {"herror", (func*)&herror, 1, 0, 1},
    /*  369 */ {"hstrerror", (func*)&hstrerror, 1, 0, 0},
    /*  370 */ {"inet_addr", (func*)&inet_addr, 1, 0, 0},
    /*  371 */ {"inet_aton", (func*)&inet_aton, 2, 0, 0},
    /*  372 */ {"inet_ntop", (func*)&inet_ntop, 4, 0, 0},
    /*  373 */ {"inet_pton", (func*)&inet_pton, 3, 0, 0},
    /*  374 */ {"inet_nsap_addr", (func*)&inet_nsap_addr, 3, 0, 0},
    /*  375 */ {"inet_nsap_ntoa", (func*)&inet_nsap_ntoa, 3, 0, 0},
    /*  376 */ {"authnone_create", (func*)&authnone_create, 0, 0, 0},
    /*  377 */ {"xdr_authunix_parms", (func*)&xdr_authunix_parms, 2, 0, 0},
    /*  378 */ {"bindresvport", (func*)&bindresvport, 2, 0, 0},
    /*  379 */ {"clntraw_create", (func*)&clntraw_create, 2, 0, 0},
    /*  380 */ {"_rpc_dtablesize", (func*)&_rpc_dtablesize, 0, 0, 0},
    /*  381 */ {"getrpcport", (func*)&getrpcport, 4, 0, 0},
    /*  382 */ {"pmap_set", (func*)&pmap_set, 4, 0, 0},
    /*  383 */ {"pmap_unset", (func*)&pmap_unset, 2, 0, 0},
    /*  384 */ {"pmap_getmaps", (func*)&pmap_getmaps, 1, 0, 0},
    /*  385 */ {"xdr_pmap", (func*)&xdr_pmap, 2, 0, 0},
    /*  386 */ {"xdr_pmaplist", (func*)&xdr_pmaplist, 2, 0, 0},
    /*  387 */ {"xdr_rmtcallres", (func*)&xdr_rmtcallres, 2, 0, 0},
    /*  388 */ {"xdr_rmtcall_args", (func*)&xdr_rmtcall_args, 2, 0, 0},
    /*  389 */ {"xdr_rejected_reply", (func*)&xdr_rejected_reply, 2, 0, 0},
    /*  390 */ {"xdr_accepted_reply", (func*)&xdr_accepted_reply, 2, 0, 0},
    /*  391 */ {"xdr_opaque_auth", (func*)&xdr_opaque_auth, 2, 0, 0},
    /*  392 */ {"xdr_des_block", (func*)&xdr_des_block, 2, 0, 0},
    /*  393 */ {"xdr_replymsg", (func*)&xdr_replymsg, 2, 0, 0},
    /*  394 */ {"xdr_callhdr", (func*)&xdr_callhdr, 2, 0, 0},
    /*  395 */ {"_seterr_reply", (func*)&_seterr_reply, 2, 0, 1},
    /*  396 */ {"xdr_callmsg", (func*)&xdr_callmsg, 2, 0, 0},
    /*  397 */ {"_authenticate", (func*)&_authenticate, 2, 0, 0},
    /*  398 */ {"svcraw_create", (func*)&svcraw_create, 0, 0, 0},
    /*  399 */ {"xdrrec_create", (func*)&xdrrec_create, 6, 0, 1},
    /*  400 */ {"xdrrec_skiprecord", (func*)&xdrrec_skiprecord, 1, 0, 0},
    /*  401 */ {"xdrrec_eof", (func*)&xdrrec_eof, 1, 0, 0},
    /*  402 */ {"xdrrec_endofrecord", (func*)&xdrrec_endofrecord, 2, 0, 0},
    /*  403 */ {"getpublickey", (func*)&getpublickey, 2, 0, 0},
    /*  404 */ {"getsecretkey", (func*)&getsecretkey, 3, 0, 0},
    /*  405 */ {"xdr_authdes_cred", (func*)&xdr_authdes_cred, 2, 0, 0},
    /*  406 */ {"xdr_authdes_verf", (func*)&xdr_authdes_verf, 2, 0, 0},
    /*  407 */ {"xdr_keystatus", (func*)&xdr_keystatus, 2, 0, 0},
    /*  408 */ {"xdr_keybuf", (func*)&xdr_keybuf, 2, 0, 0},
    /*  409 */ {"xdr_netnamestr", (func*)&xdr_netnamestr, 2, 0, 0},
    /*  410 */ {"xdr_cryptkeyarg", (func*)&xdr_cryptkeyarg, 2, 0, 0},
    /*  411 */ {"xdr_cryptkeyarg2", (func*)&xdr_cryptkeyarg2, 2, 0, 0},
    /*  412 */ {"xdr_cryptkeyres", (func*)&xdr_cryptkeyres, 2, 0, 0},
    /*  413 */ {"xdr_unixcred", (func*)&xdr_unixcred, 2, 0, 0},
    /*  414 */ {"xdr_getcredres", (func*)&xdr_getcredres, 2, 0, 0},
    /*  415 */ {"xdr_key_netstarg", (func*)&xdr_key_netstarg, 2, 0, 0},
    /*  416 */ {"xdr_key_netstres", (func*)&xdr_key_netstres, 2, 0, 0},
    /*  417 */ {"rtime", (func*)&rtime, 3, 0, 0},
    /*  418 */ {"authdes_getucred", (func*)&authdes_getucred, 5, 0, 0},
    /*  419 */ {"clntunix_create", (func*)&clntunix_create, 6, 0, 0},
    /*  420 */ {"svcunix_create", (func*)&svcunix_create, 4, 0, 0},
    /*  421 */ {"svcunixfd_create", (func*)&svcunixfd_create, 3, 0, 0},
    /*  422 */ {"cbc_crypt", (func*)&cbc_crypt, 5, 0, 0},
    /*  423 */ {"ecb_crypt", (func*)&ecb_crypt, 4, 0, 0},
    /*  424 */ {"des_setparity", (func*)&des_setparity, 1, 0, 1},
    /*  425 */ {"authdes_create", (func*)&authdes_create, 4, 0, 0},
    /*  426 */ {"authdes_pk_create", (func*)&authdes_pk_create, 5, 0, 0},
    /*  427 */ {"authunix_create", (func*)&authunix_create, 5, 0, 0},
    /*  428 */ {"authunix_create_default", (func*)&authunix_create_default, 0, 0, 0},
    /*  429 */ {"clnt_create", (func*)&clnt_create, 4, 0, 0},
    /*  430 */ {"clnt_sperror", (func*)&clnt_sperror, 2, 0, 0},
    /*  431 */ {"clnt_perror", (func*)&clnt_perror, 2, 0, 1},
    /*  432 */ {"clnt_sperrno", (func*)&clnt_sperrno, 1, 0, 0},
    /*  433 */ {"clnt_perrno", (func*)&clnt_perrno, 1, 0, 1},
    /*  434 */ {"clnt_spcreateerror", (func*)&clnt_spcreateerror, 1, 0, 0},
    /*  435 */ {"clnt_pcreateerror", (func*)&clnt_pcreateerror, 1, 0, 1},
    /*  436 */ {"clnttcp_create", (func*)&clnttcp_create, 6, 0, 0},
    /*  437 */ {"clntudp_create", (func*)&clntudp_create, 5, 0, 0},
    /*  438 */ {"get_myaddress", (func*)&get_myaddress, 1, 0, 1},
    /*  439 */ {"key_setsecret", (func*)&key_setsecret, 1, 0, 0},
    /*  440 */ {"key_secretkey_is_set", (func*)&key_secretkey_is_set, 0, 0, 0},
    /*  441 */ {"key_encryptsession", (func*)&key_encryptsession, 2, 0, 0},
    /*  442 */ {"key_decryptsession", (func*)&key_decryptsession, 2, 0, 0},
    /*  443 */ {"key_encryptsession_pk", (func*)&key_encryptsession_pk, 3, 0, 0},
    /*  444 */ {"key_decryptsession_pk", (func*)&key_decryptsession_pk, 3, 0, 0},
    /*  445 */ {"key_gendes", (func*)&key_gendes, 1, 0, 0},
    /*  446 */ {"key_setnet", (func*)&key_setnet, 1, 0, 0},
    /*  447 */ {"key_get_conv", (func*)&key_get_conv, 2, 0, 0},
    /*  448 */ {"user2netname", (func*)&user2netname, 3, 0, 0},
    /*  449 */ {"host2netname", (func*)&host2netname, 3, 0, 0},
    /*  450 */ {"getnetname", (func*)&getnetname, 1, 0, 0},
    /*  451 */ {"netname2user", (func*)&netname2user, 5, 0, 0},
    /*  452 */ {"netname2host", (func*)&netname2host, 3, 0, 0},
    /*  453 */ {"pmap_getport", (func*)&pmap_getport, 4, 0, 0},
    /*  454 */ {"xprt_register", (func*)&xprt_register, 1, 0, 1},
    /*  455 */ {"xprt_unregister", (func*)&xprt_unregister, 1, 0, 1},
    /*  456 */ {"svc_register", (func*)&svc_register, 5, 0, 0},
    /*  457 */ {"svc_unregister", (func*)&svc_unregister, 2, 0, 1},
    /*  458 */ {"svc_sendreply", (func*)&svc_sendreply, 3, 0, 0},
    /*  459 */ {"svcerr_noproc", (func*)&svcerr_noproc, 1, 0, 1},
    /*  460 */ {"svcerr_decode", (func*)&svcerr_decode, 1, 0, 1},
    /*  461 */ {"svcerr_systemerr", (func*)&svcerr_systemerr, 1, 0, 1},
    /*  462 */ {"svcerr_auth", (func*)&svcerr_auth, 2, 0, 1},
    /*  463 */ {"svcerr_weakauth", (func*)&svcerr_weakauth, 1, 0, 1},
    /*  464 */ {"svcerr_noprog", (func*)&svcerr_noprog, 1, 0, 1},
    /*  465 */ {"svcerr_progvers", (func*)&svcerr_progvers, 3, 0, 1},
    /*  466 */ {"svc_getreq_common", (func*)&svc_getreq_common, 1, 0, 1},
    /*  467 */ {"svc_getreqset", (func*)&svc_getreqset, 1, 0, 1},
    /*  468 */ {"svc_getreq_poll", (func*)&svc_getreq_poll, 2, 0, 1},
    /*  469 */ {"svc_getreq", (func*)&svc_getreq, 1, 0, 1},
    /*  470 */ {"svctcp_create", (func*)&svctcp_create, 3, 0, 0},
    /*  471 */ {"svcfd_create", (func*)&svcfd_create, 3, 0, 0},
    /*  472 */ {"svcudp_bufcreate", (func*)&svcudp_bufcreate, 3, 0, 0},
    /*  473 */ {"svcudp_create", (func*)&svcudp_create, 1, 0, 0},
    /*  474 */ {"svcudp_enablecache", (func*)&svcudp_enablecache, 2, 0, 0},
    /*  475 */ {"xdr_array", (func*)&xdr_array, 6, 0, 0},
    /*  476 */ {"xdr_vector", (func*)&xdr_vector, 5, 0, 0},
    /*  477 */ {"xdr_free", (func*)&xdr_free, 2, 0, 1},
    /*  478 */ {"xdr_void", (func*)&xdr_void, 0, 0, 0},
    /*  479 */ {"xdr_int", (func*)&xdr_int, 2, 0, 0},
    /*  480 */ {"xdr_u_int", (func*)&xdr_u_int, 2, 0, 0},
    /*  481 */ {"xdr_long", (func*)&xdr_long, 2, 0, 0},
    /*  482 */ {"xdr_u_long", (func*)&xdr_u_long, 2, 0, 0},
    /*  483 */ {"xdr_hyper", (func*)&xdr_hyper, 2, 0, 0},
    /*  484 */ {"xdr_u_hyper", (func*)&xdr_u_hyper, 2, 0, 0},
    /*  485 */ {"xdr_longlong_t", (func*)&xdr_longlong_t, 2, 0, 0},
    /*  486 */ {"xdr_u_longlong_t", (func*)&xdr_u_longlong_t, 2, 0, 0},
    /*  487 */ {"xdr_short", (func*)&xdr_short, 2, 0, 0},
    /*  488 */ {"xdr_u_short", (func*)&xdr_u_short, 2, 0, 0},
    /*  489 */ {"xdr_char", (func*)&xdr_char, 2, 0, 0},
    /*  490 */ {"xdr_u_char", (func*)&xdr_u_char, 2, 0, 0},
    /*  491 */ {"xdr_bool", (func*)&xdr_bool, 2, 0, 0},
    /*  492 */ {"xdr_enum", (func*)&xdr_enum, 2, 0, 0},
    /*  493 */ {"xdr_opaque", (func*)&xdr_opaque, 3, 0, 0},
    /*  494 */ {"xdr_bytes", (func*)&xdr_bytes, 4, 0, 0},
    /*  495 */ {"xdr_netobj", (func*)&xdr_netobj, 2, 0, 0},
    /*  496 */ {"xdr_union", (func*)&xdr_union, 5, 0, 0},
    /*  497 */ {"xdr_string", (func*)&xdr_string, 3, 0, 0},
    /*  498 */ {"xdr_wrapstring", (func*)&xdr_wrapstring, 2, 0, 0},
    /*  499 */ {"xdr_int64_t", (func*)&xdr_int64_t, 2, 0, 0},
    /*  500 */ {"xdr_quad_t", (func*)&xdr_quad_t, 2, 0, 0},
    /*  501 */ {"xdr_uint64_t", (func*)&xdr_uint64_t, 2, 0, 0},
    /*  502 */ {"xdr_u_quad_t", (func*)&xdr_u_quad_t, 2, 0, 0},
    /*  503 */ {"xdr_int32_t", (func*)&xdr_int32_t, 2, 0, 0},
    /*  504 */ {"xdr_uint32_t", (func*)&xdr_uint32_t, 2, 0, 0},
    /*  505 */ {"xdr_int16_t", (func*)&xdr_int16_t, 2, 0, 0},
    /*  506 */ {"xdr_uint16_t", (func*)&xdr_uint16_t, 2, 0, 0},
    /*  507 */ {"xdr_int8_t", (func*)&xdr_int8_t, 2, 0, 0},
    /*  508 */ {"xdr_uint8_t", (func*)&xdr_uint8_t, 2, 0, 0},
    /*  509 */ {"xdrmem_create", (func*)&xdrmem_create, 4, 0, 1},
    /*  510 */ {"xdr_reference", (func*)&xdr_reference, 4, 0, 0},
    /*  511 */ {"xdr_pointer", (func*)&xdr_pointer, 4, 0, 0},
    /*  512 */ {"xdr_sizeof", (func*)&xdr_sizeof, 2, 0, 0},
    /*  513 */ {"xdrstdio_create", (func*)&xdrstdio_create, 3, 0, 1},
    /*  514 */ {"svc_exit", (func*)&svc_exit, 0, 0, 1},
    /*  515 */ {"svc_run", (func*)&svc_run, 0, 0, 1},
    /*  516 */ {"xencrypt", (func*)&xencrypt, 2, 0, 0},
    /*  517 */ {"xdecrypt", (func*)&xdecrypt, 2, 0, 0},
    /*  518 */ {"isastream", (func*)&isastream, 1, 0, 0},
    /*  519 */ {"getmsg", (func*)&getmsg, 4, 0, 0},
    /*  520 */ {"getpmsg", (func*)&getpmsg, 5, 0, 0},
    /*  521 */ {"putmsg", (func*)&putmsg, 4, 0, 0},
    /*  522 */ {"putpmsg", (func*)&putpmsg, 5, 0, 0},
    /*  523 */ {"fattach", (func*)&fattach, 2, 0, 0},
    /*  524 */ {"fdetach", (func*)&fdetach, 1, 0, 0},
    /*  525 */ {"posix_openpt", (func*)&posix_openpt, 1, 0, 0},
    /*  526 */ {"getpt", (func*)&getpt, 0, 0, 0},
    /*  527 */ {"grantpt", (func*)&grantpt, 1, 0, 0},
    /*  528 */ {"unlockpt", (func*)&unlockpt, 1, 0, 0},
    /*  529 */ {"ptsname_r", (func*)&ptsname_r, 3, 0, 0},
    /*  530 */ {"ptsname", (func*)&ptsname, 1, 0, 0},
    /*  531 */ {"getutent", (func*)&getutent, 0, 0, 0},
    /*  532 */ {"setutent", (func*)&setutent, 0, 0, 1},
    /*  533 */ {"getutent_r", (func*)&getutent_r, 2, 0, 0},
    /*  534 */ {"pututline", (func*)&pututline, 1, 0, 0},
    /*  535 */ {"endutent", (func*)&endutent, 0, 0, 1},
    /*  536 */ {"getutid", (func*)&getutid, 1, 0, 0},
    /*  537 */ {"getutline", (func*)&getutline, 1, 0, 0},
    /*  538 */ {"getutid_r", (func*)&getutid_r, 3, 0, 0},
    /*  539 */ {"getutline_r", (func*)&getutline_r, 3, 0, 0},
    /*  540 */ {"utmpname", (func*)&utmpname, 1, 0, 0},
    /*  541 */ {"updwtmp", (func*)&updwtmp, 2, 0, 1},
    /*  542 */ {"getlogin", (func*)&getlogin, 0, 0, 0},
    /*  543 */ {"getlogin_r", (func*)&getlogin_r, 2, 0, 0},
    /*  544 */ {"setlogin", (func*)&setlogin, 1, 0, 0},
    /*  545 */ {"setutxent", (func*)&setutxent, 0, 0, 1},
    /*  546 */ {"getutxent", (func*)&getutxent, 0, 0, 0},
    /*  547 */ {"endutxent", (func*)&endutxent, 0, 0, 1},
    /*  548 */ {"getutxid", (func*)&getutxid, 1, 0, 0},
    /*  549 */ {"getutxline", (func*)&getutxline, 1, 0, 0},
    /*  550 */ {"pututxline", (func*)&pututxline, 1, 0, 0},
    /*  551 */ {"utmpxname", (func*)&utmpxname, 1, 0, 0},
    /*  552 */ {"updwtmpx", (func*)&updwtmpx, 2, 0, 1},
    /*  553 */ {"getutmp", (func*)&getutmp, 2, 0, 1},
    /*  554 */ {"dl_iterate_phdr", (func*)&dl_iterate_phdr, 2, 0, 0},
    /*  555 */ {"realpath", (func*)&realpath, 2, 0, 0},
    /*  556 */ {"sched_getaffinity", (func*)&sched_getaffinity, 3, 0, 0},
    /*  557 */ {"sched_setaffinity", (func*)&sched_setaffinity, 3, 0, 0},
    /*  558 */ {"regexec", (func*)&regexec, 5, 0, 0},
    /*  559 */ {"posix_spawn", (func*)&posix_spawn, 6, 0, 0},
    /*  560 */ {"posix_spawnp", (func*)&posix_spawnp, 6, 0, 0},
    /*  561 */ {"nftw", (func*)&nftw, 4, 0, 0},
    /*  562 */ {"pthread_cond_broadcast", (func*)&pthread_cond_broadcast, 1, 0, 0},
    /*  563 */ {"pthread_cond_destroy", (func*)&pthread_cond_destroy, 1, 0, 0},
    /*  564 */ {"pthread_cond_init", (func*)&pthread_cond_init, 2, 0, 0},
    /*  565 */ {"pthread_cond_signal", (func*)&pthread_cond_signal, 1, 0, 0},
    /*  566 */ {"pthread_cond_wait", (func*)&pthread_cond_wait, 2, 0, 0},
    /*  567 */ {"pthread_cond_timedwait", (func*)&pthread_cond_timedwait, 3, 0, 0},
    /*  568 */ {"gnu_get_libc_release", (func*)&gnu_get_libc_release, 0, 0, 0},
    /*  569 */ {"gnu_get_libc_version", (func*)&gnu_get_libc_version, 0, 0, 0},
    /*  570 */ {"iconv_open", (func*)&iconv_open, 2, 0, 0},
    /*  571 */ {"iconv", (func*)&iconv, 5, 0, 0},
    /*  572 */ {"iconv_close", (func*)&iconv_close, 1, 0, 0},
    /*  573 */ {"setlocale", (func*)&setlocale, 2, 0, 0},
    /*  574 */ {"localeconv", (func*)&localeconv, 0, 0, 0},
    /*  575 */ {"nl_langinfo", (func*)&nl_langinfo, 1, 0, 0},
    /*  576 */ {"nl_langinfo_l", (func*)&nl_langinfo_l, 2, 0, 0},
    /*  577 */ {"newlocale", (func*)&newlocale, 3, 0, 0},
    /*  578 */ {"duplocale", (func*)&duplocale, 1, 0, 0},
    /*  579 */ {"freelocale", (func*)&freelocale, 1, 0, 1},
    /*  580 */ {"uselocale", (func*)&uselocale, 1, 0, 0},
    /*  581 */ {"isalnum", (func*)&isalnum, 1, 0, 0},
    /*  582 */ {"isalpha", (func*)&isalpha, 1, 0, 0},
    /*  583 */ {"iscntrl", (func*)&iscntrl, 1, 0, 0},
    /*  584 */ {"isdigit", (func*)&isdigit, 1, 0, 0},
    /*  585 */ {"islower", (func*)&islower, 1, 0, 0},
    /*  586 */ {"isgraph", (func*)&isgraph, 1, 0, 0},
    /*  587 */ {"isprint", (func*)&isprint, 1, 0, 0},
    /*  588 */ {"ispunct", (func*)&ispunct, 1, 0, 0},
    /*  589 */ {"isspace", (func*)&isspace, 1, 0, 0},
    /*  590 */ {"isupper", (func*)&isupper, 1, 0, 0},
    /*  591 */ {"isxdigit", (func*)&isxdigit, 1, 0, 0},
    /*  592 */ {"tolower", (func*)&tolower, 1, 0, 0},
    /*  593 */ {"toupper", (func*)&toupper, 1, 0, 0},
    /*  594 */ {"isblank", (func*)&isblank, 1, 0, 0},
    /*  595 */ {"_tolower", (func*)&_tolower, 1, 0, 0},
    /*  596 */ {"_toupper", (func*)&_toupper, 1, 0, 0},
    /*  597 */ {"toascii", (func*)&toascii, 1, 0, 0},
    /*  598 */ {"isascii", (func*)&isascii, 1, 0, 0},
    /*  599 */ {"isblank_l", (func*)&isblank_l, 2, 0, 0},
    /*  600 */ {"isalnum_l", (func*)&isalnum_l, 2, 0, 0},
    /*  601 */ {"isalpha_l", (func*)&isalpha_l, 2, 0, 0},
    /*  602 */ {"iscntrl_l", (func*)&iscntrl_l, 2, 0, 0},
    /*  603 */ {"isdigit_l", (func*)&isdigit_l, 2, 0, 0},
    /*  604 */ {"islower_l", (func*)&islower_l, 2, 0, 0},
    /*  605 */ {"isgraph_l", (func*)&isgraph_l, 2, 0, 0},
    /*  606 */ {"isprint_l", (func*)&isprint_l, 2, 0, 0},
    /*  607 */ {"ispunct_l", (func*)&ispunct_l, 2, 0, 0},
    /*  608 */ {"isspace_l", (func*)&isspace_l, 2, 0, 0},
    /*  609 */ {"isupper_l", (func*)&isupper_l, 2, 0, 0},
    /*  610 */ {"isxdigit_l", (func*)&isxdigit_l, 2, 0, 0},
    /*  611 */ {"tolower_l", (func*)&tolower_l, 2, 0, 0},
    /*  612 */ {"toupper_l", (func*)&toupper_l, 2, 0, 0},
    /*  613 */ {"isctype", (func*)&isctype, 2, 0, 0},
    /*  614 */ {"bindtextdomain", (func*)&bindtextdomain, 2, 0, 0},
    /*  615 */ {"bind_textdomain_codeset", (func*)&bind_textdomain_codeset, 2, 0, 0},
    /*  616 */ {"dcgettext", (func*)&dcgettext, 3, 0, 0},
    /*  617 */ {"dgettext", (func*)&dgettext, 2, 0, 0},
    /*  618 */ {"gettext", (func*)&gettext, 1, 0, 0},
    /*  619 */ {"dcngettext", (func*)&dcngettext, 5, 0, 0},
    /*  620 */ {"dngettext", (func*)&dngettext, 4, 0, 0},
    /*  621 */ {"ngettext", (func*)&ngettext, 3, 0, 0},
    /*  622 */ {"textdomain", (func*)&textdomain, 1, 0, 0},
    /*  623 */ {"catopen", (func*)&catopen, 2, 0, 0},
    /*  624 */ {"catgets", (func*)&catgets, 4, 0, 0},
    /*  625 */ {"catclose", (func*)&catclose, 1, 0, 0},
    /*  626 */ {"setjmp", (func*)&setjmp, 1, 0, 0},
    /*  627 */ {"_setjmp", (func*)&_setjmp, 1, 0, 0},
    /*  628 */ {"longjmp", (func*)&longjmp, 2, 0, 1},
    /*  629 */ {"signal", (func*)&signal, 2, 0, 0},
    /*  630 */ {"raise", (func*)&raise, 1, 0, 0},
    /*  631 */ {"killpg", (func*)&killpg, 2, 0, 0},
    /*  632 */ {"sigaction", (func*)&sigaction, 3, 0, 0},
    /*  633 */ {"sigprocmask", (func*)&sigprocmask, 3, 0, 0},
    /*  634 */ {"kill", (func*)&kill, 2, 0, 0},
    /*  635 */ {"sigpending", (func*)&sigpending, 1, 0, 0},
    /*  636 */ {"sigsuspend", (func*)&sigsuspend, 1, 0, 0},
    /*  637 */ {"sigwait", (func*)&sigwait, 2, 0, 0},
    /*  638 */ {"sigblock", (func*)&sigblock, 1, 0, 0},
    /*  639 */ {"sigsetmask", (func*)&sigsetmask, 1, 0, 0},
    /*  640 */ {"sigpause", (func*)&sigpause, 1, 0, 0},
    /*  641 */ {"sigstack", (func*)&sigstack, 2, 0, 0},
    /*  642 */ {"sigaltstack", (func*)&sigaltstack, 2, 0, 0},
    /*  643 */ {"siginterrupt", (func*)&siginterrupt, 2, 0, 0},
    /*  644 */ {"sigemptyset", (func*)&sigemptyset, 1, 0, 0},
    /*  645 */ {"sigfillset", (func*)&sigfillset, 1, 0, 0},
    /*  646 */ {"sigaddset", (func*)&sigaddset, 2, 0, 0},
    /*  647 */ {"sigdelset", (func*)&sigdelset, 2, 0, 0},
    /*  648 */ {"sigismember", (func*)&sigismember, 2, 0, 0},
    /*  649 */ {"sigreturn", (func*)&sigreturn, 1, 0, 0},
    /*  650 */ {"siggetmask", (func*)&siggetmask, 0, 0, 0},
    /*  651 */ {"sysv_signal", (func*)&sysv_signal, 2, 0, 0},
    /*  652 */ {"sigisemptyset", (func*)&sigisemptyset, 1, 0, 0},
    /*  653 */ {"sigandset", (func*)&sigandset, 3, 0, 0},
    /*  654 */ {"sigorset", (func*)&sigorset, 3, 0, 0},
    /*  655 */ {"sigtimedwait", (func*)&sigtimedwait, 3, 0, 0},
    /*  656 */ {"sigwaitinfo", (func*)&sigwaitinfo, 2, 0, 0},
    /*  657 */ {"sigqueue", (func*)&sigqueue, 3, 0, 0},
    /*  658 */ {"sighold", (func*)&sighold, 1, 0, 0},
    /*  659 */ {"sigrelse", (func*)&sigrelse, 1, 0, 0},
    /*  660 */ {"sigignore", (func*)&sigignore, 1, 0, 0},
    /*  661 */ {"sigset", (func*)&sigset, 2, 0, 0},
    /*  662 */ {"atoi", (func*)&atoi, 1, 0, 0},
    /*  663 */ {"atol", (func*)&atol, 1, 0, 0},
    /*  664 */ {"atoll", (func*)&atoll, 1, 0, 0},
    /*  665 */ {"abort", (func*)&abort, 0, 0, 1},
    /*  666 */ {"bsearch", (func*)&bsearch, 5, 0, 0},
    /*  667 */ {"qsort_r", (func*)&qsort_r, 5, 0, 1},
    /*  668 */ {"qsort", (func*)&qsort, 4, 0, 1},
    /*  669 */ {"getenv", (func*)&getenv, 1, 0, 0},
    /*  670 */ {"putenv", (func*)&putenv, 1, 0, 0},
    /*  671 */ {"setenv", (func*)&setenv, 3, 0, 0},
    /*  672 */ {"unsetenv", (func*)&unsetenv, 1, 0, 0},
    /*  673 */ {"clearenv", (func*)&clearenv, 0, 0, 0},
    /*  674 */ {"exit", (func*)&exit, 1, 0, 1},
    /*  675 */ {"on_exit", (func*)&on_exit, 2, 0, 1},
    /*  676 */ {"quick_exit", (func*)&quick_exit, 1, 0, 1},
    /*  677 */ {"abs", (func*)&abs, 1, 0, 0},
    /*  678 */ {"labs", (func*)&labs, 1, 0, 0},
    /*  679 */ {"llabs", (func*)&llabs, 1, 0, 0},
    /*  680 */ {"div", (func*)&div, 2, 0, 0},
    /*  681 */ {"ldiv", (func*)&ldiv, 2, 0, 0},
    /*  682 */ {"lldiv", (func*)&lldiv, 2, 0, 0},
    /*  683 */ {"srand", (func*)&srand, 1, 0, 1},
    /*  684 */ {"initstate", (func*)&initstate, 3, 0, 0},
    /*  685 */ {"setstate", (func*)&setstate, 1, 0, 0},
    /*  686 */ {"random", (func*)&random, 0, 0, 0},
    /*  687 */ {"setstate_r", (func*)&setstate_r, 2, 0, 0},
    /*  688 */ {"random_r", (func*)&random_r, 2, 0, 0},
    /*  689 */ {"srandom_r", (func*)&srandom_r, 2, 0, 0},
    /*  690 */ {"initstate_r", (func*)&initstate_r, 4, 0, 0},
    /*  691 */ {"rand", (func*)&rand, 0, 0, 0},
    /*  692 */ {"rand_r", (func*)&rand_r, 1, 0, 0},
    /*  693 */ {"lrand48", (func*)&lrand48, 0, 0, 0},
    /*  694 */ {"nrand48", (func*)&nrand48, 1, 0, 0},
    /*  695 */ {"mrand48", (func*)&mrand48, 0, 0, 0},
    /*  696 */ {"jrand48", (func*)&jrand48, 1, 0, 0},
    /*  697 */ {"srand48", (func*)&srand48, 1, 0, 1},
    /*  698 */ {"seed48", (func*)&seed48, 1, 0, 0},
    /*  699 */ {"lcong48", (func*)&lcong48, 1, 0, 1},
    /*  700 */ {"lrand48_r", (func*)&lrand48_r, 2, 0, 0},
    /*  701 */ {"nrand48_r", (func*)&nrand48_r, 3, 0, 0},
    /*  702 */ {"mrand48_r", (func*)&mrand48_r, 2, 0, 0},
    /*  703 */ {"jrand48_r", (func*)&jrand48_r, 3, 0, 0},
    /*  704 */ {"srand48_r", (func*)&srand48_r, 2, 0, 0},
    /*  705 */ {"seed48_r", (func*)&seed48_r, 2, 0, 0},
    /*  706 */ {"lcong48_r", (func*)&lcong48_r, 2, 0, 0},
    /*  707 */ {"strtol", (func*)&strtol, 3, 0, 0},
    /*  708 */ {"strtoul", (func*)&strtoul, 3, 0, 0},
    /*  709 */ {"strtol_l", (func*)&strtol_l, 4, 0, 0},
    /*  710 */ {"strtoul_l", (func*)&strtoul_l, 4, 0, 0},
    /*  711 */ {"system", (func*)&system, 1, 0, 0},
    /*  712 */ {"realpath", (func*)&realpath, 2, 0, 0},
    /*  713 */ {"canonicalize_file_name", (func*)&canonicalize_file_name, 1, 0, 0},
    /*  714 */ {"a64l", (func*)&a64l, 1, 0, 0},
    /*  715 */ {"l64a", (func*)&l64a, 1, 0, 0},
    /*  716 */ {"getsubopt", (func*)&getsubopt, 3, 0, 0},
    /*  717 */ {"strtoimax", (func*)&strtoimax, 3, 0, 0},
    /*  718 */ {"strtoumax", (func*)&strtoumax, 3, 0, 0},
    /*  719 */ {"getcontext", (func*)&getcontext, 1, 0, 0},
    /*  720 */ {"setcontext", (func*)&setcontext, 1, 0, 0},
    /*  721 */ {"makecontext", (func*)&makecontext, 3, 1, 1},
    /*  722 */ {"swapcontext", (func*)&swapcontext, 2, 0, 0},
    /*  723 */ {"strfmon", (func*)&strfmon, 3, 1, 0},
    /*  724 */ {"strfmon_l", (func*)&strfmon_l, 4, 1, 0},
    /*  725 */ {"mblen", (func*)&mblen, 2, 0, 0},
    /*  726 */ {"mbstowcs", (func*)&mbstowcs, 3, 0, 0},
    /*  727 */ {"mbtowc", (func*)&mbtowc, 3, 0, 0},
    /*  728 */ {"wcstombs", (func*)&wcstombs, 3, 0, 0},
    /*  729 */ {"wctomb", (func*)&wctomb, 2, 0, 0},
    /*  730 */ {"wcstoimax", (func*)&wcstoimax, 3, 0, 0},
    /*  731 */ {"wcstoumax", (func*)&wcstoumax, 3, 0, 0},
    /*  732 */ {"rpmatch", (func*)&rpmatch, 1, 0, 0},
    /*  733 */ {"fmtmsg", (func*)&fmtmsg, 6, 0, 0},
    /*  734 */ {"addseverity", (func*)&addseverity, 2, 0, 0},
    /*  735 */ {"ctermid", (func*)&ctermid, 1, 0, 0},
    /*  736 */ {"cuserid", (func*)&cuserid, 1, 0, 0},
    /*  737 */ {"vfprintf", (func*)&vfprintf, 3, 0, 0},
    /*  738 */ {"vprintf", (func*)&vprintf, 2, 0, 0},
    /*  739 */ {"register_printf_specifier", (func*)&register_printf_specifier, 3, 0, 0},
    /*  740 */ {"register_printf_function", (func*)&register_printf_function, 3, 0, 0},
    /*  741 */ {"parse_printf_format", (func*)&parse_printf_format, 3, 0, 0},
    /*  742 */ {"register_printf_modifier", (func*)&register_printf_modifier, 1, 0, 0},
    /*  743 */ {"register_printf_type", (func*)&register_printf_type, 1, 0, 0},
    /*  744 */ {"printf_size", (func*)&printf_size, 3, 0, 0},
    /*  745 */ {"printf_size_info", (func*)&printf_size_info, 3, 0, 0},
    /*  746 */ {"fprintf", (func*)&fprintf, 2, 1, 0},
    /*  747 */ {"printf", (func*)&printf, 1, 1, 0},
    /*  748 */ {"snprintf", (func*)&snprintf, 3, 1, 0},
    /*  749 */ {"sprintf", (func*)&sprintf, 2, 1, 0},
    /*  750 */ {"asprintf", (func*)&asprintf, 2, 1, 0},
    /*  751 */ {"dprintf", (func*)&dprintf, 2, 1, 0},
    /*  752 */ {"_IO_vfscanf", (func*)&_IO_vfscanf, 4, 0, 0},
    /*  753 */ {"vfscanf", (func*)&vfscanf, 3, 0, 0},
    /*  754 */ {"fscanf", (func*)&fscanf, 2, 1, 0},
    /*  755 */ {"scanf", (func*)&scanf, 1, 1, 0},
    /*  756 */ {"sscanf", (func*)&sscanf, 2, 1, 0},
    /*  757 */ {"perror", (func*)&perror, 1, 0, 1},
    /*  758 */ {"psignal", (func*)&psignal, 2, 0, 1},
    /*  759 */ {"tmpfile", (func*)&tmpfile, 0, 0, 0},
    /*  760 */ {"tmpnam", (func*)&tmpnam, 1, 0, 0},
    /*  761 */ {"tmpnam_r", (func*)&tmpnam_r, 1, 0, 0},
    /*  762 */ {"tempnam", (func*)&tempnam, 2, 0, 0},
    /*  763 */ {"getline", (func*)&getline, 3, 0, 0},
    /*  764 */ {"getw", (func*)&getw, 1, 0, 0},
    /*  765 */ {"putw", (func*)&putw, 2, 0, 0},
    /*  766 */ {"remove", (func*)&remove, 1, 0, 0},
    /*  767 */ {"rename", (func*)&rename, 2, 0, 0},
    /*  768 */ {"renameat", (func*)&renameat, 4, 0, 0},
    /*  769 */ {"flockfile", (func*)&flockfile, 1, 0, 1},
    /*  770 */ {"ftrylockfile", (func*)&ftrylockfile, 1, 0, 0},
    /*  771 */ {"funlockfile", (func*)&funlockfile, 1, 0, 1},
    /*  772 */ {"psiginfo", (func*)&psiginfo, 2, 0, 1},
    /*  773 */ {"vfwprintf", (func*)&vfwprintf, 3, 0, 0},
    /*  774 */ {"vfwscanf", (func*)&vfwscanf, 3, 0, 0},
    /*  775 */ {"fclose", (func*)&fclose, 1, 0, 0},
    /*  776 */ {"fdopen", (func*)&fdopen, 2, 0, 0},
    /*  777 */ {"fflush", (func*)&fflush, 1, 0, 0},
    /*  778 */ {"fgetpos", (func*)&fgetpos, 2, 0, 0},
    /*  779 */ {"fgets", (func*)&fgets, 3, 0, 0},
    /*  780 */ {"fopen", (func*)&fopen, 2, 0, 0},
    /*  781 */ {"fopencookie", (func*)&fopencookie, 3, 0, 0},
    /*  782 */ {"fputs", (func*)&fputs, 2, 0, 0},
    /*  783 */ {"fread", (func*)&fread, 4, 0, 0},
    /*  784 */ {"fsetpos", (func*)&fsetpos, 2, 0, 0},
    /*  785 */ {"ftell", (func*)&ftell, 1, 0, 0},
    /*  786 */ {"fwrite", (func*)&fwrite, 4, 0, 0},
    /*  787 */ {"getdelim", (func*)&getdelim, 4, 0, 0},
    /*  788 */ {"gets", (func*)&gets, 1, 0, 0},
    /*  789 */ {"popen", (func*)&popen, 2, 0, 0},
    /*  790 */ {"puts", (func*)&puts, 1, 0, 0},
    /*  791 */ {"setbuffer", (func*)&setbuffer, 3, 0, 1},
    /*  792 */ {"setvbuf", (func*)&setvbuf, 4, 0, 0},
    /*  793 */ {"ungetc", (func*)&ungetc, 2, 0, 0},
    /*  794 */ {"vsprintf", (func*)&vsprintf, 3, 0, 0},
    /*  795 */ {"vsscanf", (func*)&vsscanf, 3, 0, 0},
    /*  796 */ {"putchar", (func*)&putchar, 1, 0, 0},
    /*  797 */ {"putchar_unlocked", (func*)&putchar_unlocked, 1, 0, 0},
    /*  798 */ {"clearerr", (func*)&clearerr, 1, 0, 1},
    /*  799 */ {"feof", (func*)&feof, 1, 0, 0},
    /*  800 */ {"ferror", (func*)&ferror, 1, 0, 0},
    /*  801 */ {"fileno", (func*)&fileno, 1, 0, 0},
    /*  802 */ {"fputc", (func*)&fputc, 2, 0, 0},
    /*  803 */ {"freopen", (func*)&freopen, 3, 0, 0},
    /*  804 */ {"fseek", (func*)&fseek, 3, 0, 0},
    /*  805 */ {"getc", (func*)&getc, 1, 0, 0},
    /*  806 */ {"getchar", (func*)&getchar, 0, 0, 0},
    /*  807 */ {"open_memstream", (func*)&open_memstream, 2, 0, 0},
    /*  808 */ {"pclose", (func*)&pclose, 1, 0, 0},
    /*  809 */ {"putc", (func*)&putc, 2, 0, 0},
    /*  810 */ {"rewind", (func*)&rewind, 1, 0, 1},
    /*  811 */ {"setbuf", (func*)&setbuf, 2, 0, 1},
    /*  812 */ {"setlinebuf", (func*)&setlinebuf, 1, 0, 1},
    /*  813 */ {"vasprintf", (func*)&vasprintf, 3, 0, 0},
    /*  814 */ {"vdprintf", (func*)&vdprintf, 3, 0, 0},
    /*  815 */ {"vscanf", (func*)&vscanf, 2, 0, 0},
    /*  816 */ {"vsnprintf", (func*)&vsnprintf, 4, 0, 0},
    /*  817 */ {"obstack_vprintf", (func*)&obstack_vprintf, 3, 0, 0},
    /*  818 */ {"obstack_printf", (func*)&obstack_printf, 2, 1, 0},
    /*  819 */ {"fcloseall", (func*)&fcloseall, 0, 0, 0},
    /*  820 */ {"fseeko", (func*)&fseeko, 3, 0, 0},
    /*  821 */ {"ftello", (func*)&ftello, 1, 0, 0},
    /*  822 */ {"freopen64", (func*)&freopen64, 3, 0, 0},
    /*  823 */ {"fmemopen", (func*)&fmemopen, 3, 0, 0},
    /*  824 */ {"clearerr_unlocked", (func*)&clearerr_unlocked, 1, 0, 1},
    /*  825 */ {"feof_unlocked", (func*)&feof_unlocked, 1, 0, 0},
    /*  826 */ {"ferror_unlocked", (func*)&ferror_unlocked, 1, 0, 0},
    /*  827 */ {"fputc_unlocked", (func*)&fputc_unlocked, 2, 0, 0},
    /*  828 */ {"getc_unlocked", (func*)&getc_unlocked, 1, 0, 0},
    /*  829 */ {"getchar_unlocked", (func*)&getchar_unlocked, 0, 0, 0},
    /*  830 */ {"fflush_unlocked", (func*)&fflush_unlocked, 1, 0, 0},
    /*  831 */ {"putc_unlocked", (func*)&putc_unlocked, 2, 0, 0},
    /*  832 */ {"_IO_peekc_locked", (func*)&_IO_peekc_locked, 1, 0, 0},
    /*  833 */ {"fread_unlocked", (func*)&fread_unlocked, 4, 0, 0},
    /*  834 */ {"fwrite_unlocked", (func*)&fwrite_unlocked, 4, 0, 0},
    /*  835 */ {"fgets_unlocked", (func*)&fgets_unlocked, 3, 0, 0},
    /*  836 */ {"fputs_unlocked", (func*)&fputs_unlocked, 2, 0, 0},
    /*  837 */ {"swprintf", (func*)&swprintf, 3, 1, 0},
    /*  838 */ {"vswprintf", (func*)&vswprintf, 4, 0, 0},
    /*  839 */ {"vswscanf", (func*)&vswscanf, 3, 0, 0},
    /*  840 */ {"swscanf", (func*)&swscanf, 2, 1, 0},
    /*  841 */ {"open_wmemstream", (func*)&open_wmemstream, 2, 0, 0},
    /*  842 */ {"fputwc", (func*)&fputwc, 2, 0, 0},
    /*  843 */ {"fputwc_unlocked", (func*)&fputwc_unlocked, 2, 0, 0},
    /*  844 */ {"getwc", (func*)&getwc, 1, 0, 0},
    /*  845 */ {"getwc_unlocked", (func*)&getwc_unlocked, 1, 0, 0},
    /*  846 */ {"getwchar", (func*)&getwchar, 0, 0, 0},
    /*  847 */ {"getwchar_unlocked", (func*)&getwchar_unlocked, 0, 0, 0},
    /*  848 */ {"fgetws", (func*)&fgetws, 3, 0, 0},
    /*  849 */ {"fgetws_unlocked", (func*)&fgetws_unlocked, 3, 0, 0},
    /*  850 */ {"fputws", (func*)&fputws, 2, 0, 0},
    /*  851 */ {"fputws_unlocked", (func*)&fputws_unlocked, 2, 0, 0},
    /*  852 */ {"ungetwc", (func*)&ungetwc, 2, 0, 0},
    /*  853 */ {"putwc", (func*)&putwc, 2, 0, 0},
    /*  854 */ {"putwc_unlocked", (func*)&putwc_unlocked, 2, 0, 0},
    /*  855 */ {"putwchar", (func*)&putwchar, 1, 0, 0},
    /*  856 */ {"putwchar_unlocked", (func*)&putwchar_unlocked, 1, 0, 0},
    /*  857 */ {"fwprintf", (func*)&fwprintf, 2, 1, 0},
    /*  858 */ {"vwprintf", (func*)&vwprintf, 2, 0, 0},
    /*  859 */ {"wprintf", (func*)&wprintf, 1, 1, 0},
    /*  860 */ {"wscanf", (func*)&wscanf, 1, 1, 0},
    /*  861 */ {"fwscanf", (func*)&fwscanf, 2, 1, 0},
    /*  862 */ {"vwscanf", (func*)&vwscanf, 2, 0, 0},
    /*  863 */ {"fwide", (func*)&fwide, 2, 0, 0},
    /*  864 */ {"malloc", (func*)&malloc, 1, 0, 0},
    /*  865 */ {"malloc_get_state", (func*)&malloc_get_state, 0, 0, 0},
    /*  866 */ {"free", (func*)&free, 1, 0, 1},
    /*  867 */ {"realloc", (func*)&realloc, 2, 0, 0},
    /*  868 */ {"memalign", (func*)&memalign, 2, 0, 0},
    /*  869 */ {"calloc", (func*)&calloc, 2, 0, 0},
    /*  870 */ {"malloc_usable_size", (func*)&malloc_usable_size, 1, 0, 0},
    /*  871 */ {"mallopt", (func*)&mallopt, 2, 0, 0},
    /*  872 */ {"malloc_set_state", (func*)&malloc_set_state, 1, 0, 0},
    /*  873 */ {"valloc", (func*)&valloc, 1, 0, 0},
    /*  874 */ {"pvalloc", (func*)&pvalloc, 1, 0, 0},
    /*  875 */ {"malloc_trim", (func*)&malloc_trim, 1, 0, 0},
    /*  876 */ {"mallinfo", (func*)&mallinfo, 0, 0, 0},
    /*  877 */ {"malloc_stats", (func*)&malloc_stats, 0, 0, 1},
    /*  878 */ {"posix_memalign", (func*)&posix_memalign, 3, 0, 0},
    /*  879 */ {"malloc_info", (func*)&malloc_info, 2, 0, 0},
    /*  880 */ {"mcheck_check_all", (func*)&mcheck_check_all, 0, 0, 1},
    /*  881 */ {"mcheck", (func*)&mcheck, 1, 0, 1},
    /*  882 */ {"mcheck_pedantic", (func*)&mcheck_pedantic, 1, 0, 1},
    /*  883 */ {"mprobe", (func*)&mprobe, 1, 0, 0},
    /*  884 */ {"tr_break", (func*)&tr_break, 0, 0, 1},
    /*  885 */ {"mtrace", (func*)&mtrace, 0, 0, 1},
    /*  886 */ {"muntrace", (func*)&muntrace, 0, 0, 1},
    /*  887 */ {"strcoll", (func*)&strcoll, 2, 0, 0},
    /*  888 */ {"strverscmp", (func*)&strverscmp, 2, 0, 0},
    /*  889 */ {"strdup", (func*)&strdup, 1, 0, 0},
    /*  890 */ {"strndup", (func*)&strndup, 2, 0, 0},
    /*  891 */ {"strerror", (func*)&strerror, 1, 0, 0},
    /*  892 */ {"strerror_r", (func*)&strerror_r, 3, 0, 0},
    /*  893 */ {"strlen", (func*)&strlen, 1, 0, 0},
    /*  894 */ {"strnlen", (func*)&strnlen, 2, 0, 0},
    /*  895 */ {"rindex", (func*)&rindex, 2, 0, 0},
    /*  896 */ {"strsignal", (func*)&strsignal, 1, 0, 0},
    /*  897 */ {"strtok", (func*)&strtok, 2, 0, 0},
    /*  898 */ {"strtok_r", (func*)&strtok_r, 3, 0, 0},
    /*  899 */ {"strxfrm", (func*)&strxfrm, 3, 0, 0},
    /*  900 */ {"memchr", (func*)&memchr, 3, 0, 0},
    /*  901 */ {"bzero", (func*)&bzero, 2, 0, 1},
    /*  902 */ {"memset", (func*)&memset, 3, 0, 0},
    /*  903 */ {"bcopy", (func*)&bcopy, 3, 0, 1},
    /*  904 */ {"ffs", (func*)&ffs, 1, 0, 0},
    /*  905 */ {"ffsl", (func*)&ffsl, 1, 0, 0},
    /*  906 */ {"memccpy", (func*)&memccpy, 4, 0, 0},
    /*  907 */ {"strsep", (func*)&strsep, 2, 0, 0},
    /*  908 */ {"swab", (func*)&swab, 3, 0, 1},
    /*  909 */ {"strfry", (func*)&strfry, 1, 0, 0},
    /*  910 */ {"memfrob", (func*)&memfrob, 2, 0, 0},
    /*  911 */ {"memmem", (func*)&memmem, 4, 0, 0},
    /*  912 */ {"rawmemchr", (func*)&rawmemchr, 2, 0, 0},
    /*  913 */ {"strchrnul", (func*)&strchrnul, 2, 0, 0},
    /*  914 */ {"argz_append", (func*)&argz_append, 4, 0, 0},
    /*  915 */ {"argz_add", (func*)&argz_add, 3, 0, 0},
    /*  916 */ {"argz_count", (func*)&argz_count, 2, 0, 0},
    /*  917 */ {"argz_create", (func*)&argz_create, 3, 0, 0},
    /*  918 */ {"argz_create_sep", (func*)&argz_create_sep, 4, 0, 0},
    /*  919 */ {"argz_next", (func*)&argz_next, 3, 0, 0},
    /*  920 */ {"argz_delete", (func*)&argz_delete, 3, 0, 1},
    /*  921 */ {"argz_extract", (func*)&argz_extract, 3, 0, 1},
    /*  922 */ {"argz_insert", (func*)&argz_insert, 4, 0, 0},
    /*  923 */ {"argz_stringify", (func*)&argz_stringify, 3, 0, 1},
    /*  924 */ {"argz_add_sep", (func*)&argz_add_sep, 4, 0, 0},
    /*  925 */ {"argz_replace", (func*)&argz_replace, 5, 0, 0},
    /*  926 */ {"basename", (func*)&basename, 1, 0, 0},
    /*  927 */ {"strcoll_l", (func*)&strcoll_l, 3, 0, 0},
    /*  928 */ {"strxfrm_l", (func*)&strxfrm_l, 4, 0, 0},
    /*  929 */ {"memrchr", (func*)&memrchr, 3, 0, 0},
    /*  930 */ {"strerror_l", (func*)&strerror_l, 2, 0, 0},
    /*  931 */ {"envz_entry", (func*)&envz_entry, 3, 0, 0},
    /*  932 */ {"envz_get", (func*)&envz_get, 3, 0, 0},
    /*  933 */ {"envz_remove", (func*)&envz_remove, 3, 0, 1},
    /*  934 */ {"envz_add", (func*)&envz_add, 4, 0, 0},
    /*  935 */ {"envz_merge", (func*)&envz_merge, 5, 0, 0},
    /*  936 */ {"envz_strip", (func*)&envz_strip, 2, 0, 1},
    /*  937 */ {"wmemcpy", (func*)&wmemcpy, 3, 0, 0},
    /*  938 */ {"wmemset", (func*)&wmemset, 3, 0, 0},
    /*  939 */ {"wcscat", (func*)&wcscat, 2, 0, 0},
    /*  940 */ {"wcschr", (func*)&wcschr, 2, 0, 0},
    /*  941 */ {"wcscmp", (func*)&wcscmp, 2, 0, 0},
    /*  942 */ {"wcscspn", (func*)&wcscspn, 2, 0, 0},
    /*  943 */ {"wcsdup", (func*)&wcsdup, 1, 0, 0},
    /*  944 */ {"wcslen", (func*)&wcslen, 1, 0, 0},
    /*  945 */ {"wcsncat", (func*)&wcsncat, 3, 0, 0},
    /*  946 */ {"wcsncmp", (func*)&wcsncmp, 3, 0, 0},
    /*  947 */ {"wcsncpy", (func*)&wcsncpy, 3, 0, 0},
    /*  948 */ {"wcspbrk", (func*)&wcspbrk, 2, 0, 0},
    /*  949 */ {"wcsrchr", (func*)&wcsrchr, 2, 0, 0},
    /*  950 */ {"wcsspn", (func*)&wcsspn, 2, 0, 0},
    /*  951 */ {"wcstok", (func*)&wcstok, 3, 0, 0},
    /*  952 */ {"wcsstr", (func*)&wcsstr, 2, 0, 0},
    /*  953 */ {"wmemchr", (func*)&wmemchr, 3, 0, 0},
    /*  954 */ {"wmemmove", (func*)&wmemmove, 3, 0, 0},
    /*  955 */ {"wcpcpy", (func*)&wcpcpy, 2, 0, 0},
    /*  956 */ {"wcpncpy", (func*)&wcpncpy, 3, 0, 0},
    /*  957 */ {"wmempcpy", (func*)&wmempcpy, 3, 0, 0},
    /*  958 */ {"btowc", (func*)&btowc, 1, 0, 0},
    /*  959 */ {"wctob", (func*)&wctob, 1, 0, 0},
    /*  960 */ {"mbsinit", (func*)&mbsinit, 1, 0, 0},
    /*  961 */ {"mbrlen", (func*)&mbrlen, 3, 0, 0},
    /*  962 */ {"mbrtowc", (func*)&mbrtowc, 4, 0, 0},
    /*  963 */ {"wcrtomb", (func*)&wcrtomb, 3, 0, 0},
    /*  964 */ {"mbsrtowcs", (func*)&mbsrtowcs, 4, 0, 0},
    /*  965 */ {"wcsrtombs", (func*)&wcsrtombs, 4, 0, 0},
    /*  966 */ {"mbsnrtowcs", (func*)&mbsnrtowcs, 5, 0, 0},
    /*  967 */ {"wcsnrtombs", (func*)&wcsnrtombs, 5, 0, 0},
    /*  968 */ {"wcsnlen", (func*)&wcsnlen, 2, 0, 0},
    /*  969 */ {"wcschrnul", (func*)&wcschrnul, 2, 0, 0},
    /*  970 */ {"wcstol", (func*)&wcstol, 3, 0, 0},
    /*  971 */ {"wcstoul", (func*)&wcstoul, 3, 0, 0},
    /*  972 */ {"wcstol_l", (func*)&wcstol_l, 4, 0, 0},
    /*  973 */ {"wcstoul_l", (func*)&wcstoul_l, 4, 0, 0},
    /*  974 */ {"wcscoll", (func*)&wcscoll, 2, 0, 0},
    /*  975 */ {"wcsxfrm", (func*)&wcsxfrm, 3, 0, 0},
    /*  976 */ {"wcwidth", (func*)&wcwidth, 1, 0, 0},
    /*  977 */ {"wcswidth", (func*)&wcswidth, 2, 0, 0},
    /*  978 */ {"wcscoll_l", (func*)&wcscoll_l, 3, 0, 0},
    /*  979 */ {"wcsxfrm_l", (func*)&wcsxfrm_l, 4, 0, 0},
    /*  980 */ {"wcscasecmp", (func*)&wcscasecmp, 2, 0, 0},
    /*  981 */ {"wcsncasecmp", (func*)&wcsncasecmp, 3, 0, 0},
    /*  982 */ {"wcscasecmp_l", (func*)&wcscasecmp_l, 3, 0, 0},
    /*  983 */ {"wcsncasecmp_l", (func*)&wcsncasecmp_l, 4, 0, 0},
    /*  984 */ {"asctime_r", (func*)&asctime_r, 2, 0, 0},
    /*  985 */ {"asctime", (func*)&asctime, 1, 0, 0},
    /*  986 */ {"clock", (func*)&clock, 0, 0, 0},
    /*  987 */ {"ctime", (func*)&ctime, 1, 0, 0},
    /*  988 */ {"ctime_r", (func*)&ctime_r, 2, 0, 0},
    /*  989 */ {"gmtime_r", (func*)&gmtime_r, 2, 0, 0},
    /*  990 */ {"gmtime", (func*)&gmtime, 1, 0, 0},
    /*  991 */ {"localtime_r", (func*)&localtime_r, 2, 0, 0},
    /*  992 */ {"localtime", (func*)&localtime, 1, 0, 0},
    /*  993 */ {"mktime", (func*)&mktime, 1, 0, 0},
    /*  994 */ {"settimeofday", (func*)&settimeofday, 2, 0, 0},
    /*  995 */ {"adjtime", (func*)&adjtime, 2, 0, 0},
    /*  996 */ {"tzset", (func*)&tzset, 0, 0, 1},
    /*  997 */ {"getitimer", (func*)&getitimer, 2, 0, 0},
    /*  998 */ {"setitimer", (func*)&setitimer, 3, 0, 0},
    /*  999 */ {"stime", (func*)&stime, 1, 0, 0},
    /* 1000 */ {"dysize", (func*)&dysize, 1, 0, 0},
    /* 1001 */ {"timegm", (func*)&timegm, 1, 0, 0},
    /* 1002 */ {"ftime", (func*)&ftime, 1, 0, 0},
    /* 1003 */ {"getdate_r", (func*)&getdate_r, 2, 0, 0},
    /* 1004 */ {"getdate", (func*)&getdate, 1, 0, 0},
    /* 1005 */ {"strptime", (func*)&strptime, 3, 0, 0},
    /* 1006 */ {"strptime_l", (func*)&strptime_l, 4, 0, 0},
    /* 1007 */ {"strftime", (func*)&strftime, 4, 0, 0},
    /* 1008 */ {"strftime_l", (func*)&strftime_l, 5, 0, 0},
    /* 1009 */ {"wcsftime", (func*)&wcsftime, 4, 0, 0},
    /* 1010 */ {"wcsftime_l", (func*)&wcsftime_l, 5, 0, 0},
    /* 1011 */ {"ntp_gettime", (func*)&ntp_gettime, 1, 0, 0},
    /* 1012 */ {"ntp_gettimex", (func*)&ntp_gettimex, 1, 0, 0},
    /* 1013 */ {"opendir", (func*)&opendir, 1, 0, 0},
    /* 1014 */ {"closedir", (func*)&closedir, 1, 0, 0},
    /* 1015 */ {"readdir", (func*)&readdir, 1, 0, 0},
    /* 1016 */ {"readdir_r", (func*)&readdir_r, 3, 0, 0},
    /* 1017 */ {"rewinddir", (func*)&rewinddir, 1, 0, 1},
    /* 1018 */ {"seekdir", (func*)&seekdir, 2, 0, 1},
    /* 1019 */ {"telldir", (func*)&telldir, 1, 0, 0},
    /* 1020 */ {"scandir", (func*)&scandir, 4, 0, 0},
    /* 1021 */ {"alphasort", (func*)&alphasort, 2, 0, 0},
    /* 1022 */ {"versionsort", (func*)&versionsort, 2, 0, 0},
    /* 1023 */ {"dirfd", (func*)&dirfd, 1, 0, 0},
    /* 1024 */ {"fdopendir", (func*)&fdopendir, 1, 0, 0},
    /* 1025 */ {"scandirat", (func*)&scandirat, 5, 0, 0},
    /* 1026 */ {"getdirentries", (func*)&getdirentries, 4, 0, 0},
    /* 1027 */ {"fgetgrent", (func*)&fgetgrent, 1, 0, 0},
    /* 1028 */ {"getgrouplist", (func*)&getgrouplist, 4, 0, 0},
    /* 1029 */ {"initgroups", (func*)&initgroups, 2, 0, 0},
    /* 1030 */ {"setgroups", (func*)&setgroups, 2, 0, 0},
    /* 1031 */ {"getgrent", (func*)&getgrent, 0, 0, 0},
    /* 1032 */ {"getgrgid", (func*)&getgrgid, 1, 0, 0},
    /* 1033 */ {"getgrnam", (func*)&getgrnam, 1, 0, 0},
    /* 1034 */ {"putgrent", (func*)&putgrent, 2, 0, 0},
    /* 1035 */ {"setgrent", (func*)&setgrent, 0, 0, 1},
    /* 1036 */ {"endgrent", (func*)&endgrent, 0, 0, 1},
    /* 1037 */ {"getgrent_r", (func*)&getgrent_r, 4, 0, 0},
    /* 1038 */ {"getgrgid_r", (func*)&getgrgid_r, 5, 0, 0},
    /* 1039 */ {"getgrnam_r", (func*)&getgrnam_r, 5, 0, 0},
    /* 1040 */ {"fgetgrent_r", (func*)&fgetgrent_r, 5, 0, 0},
    /* 1041 */ {"fgetpwent", (func*)&fgetpwent, 1, 0, 0},
    /* 1042 */ {"getpw", (func*)&getpw, 2, 0, 0},
    /* 1043 */ {"putpwent", (func*)&putpwent, 2, 0, 0},
    /* 1044 */ {"getpwent", (func*)&getpwent, 0, 0, 0},
    /* 1045 */ {"getpwnam", (func*)&getpwnam, 1, 0, 0},
    /* 1046 */ {"getpwuid", (func*)&getpwuid, 1, 0, 0},
    /* 1047 */ {"setpwent", (func*)&setpwent, 0, 0, 1},
    /* 1048 */ {"endpwent", (func*)&endpwent, 0, 0, 1},
    /* 1049 */ {"getpwent_r", (func*)&getpwent_r, 4, 0, 0},
    /* 1050 */ {"getpwnam_r", (func*)&getpwnam_r, 5, 0, 0},
    /* 1051 */ {"getpwuid_r", (func*)&getpwuid_r, 5, 0, 0},
    /* 1052 */ {"fgetpwent_r", (func*)&fgetpwent_r, 5, 0, 0},
    /* 1053 */ {"uname", (func*)&uname, 1, 0, 0},
    /* 1054 */ {"times", (func*)&times, 1, 0, 0},
    /* 1055 */ {"wait", (func*)&wait, 1, 0, 0},
    /* 1056 */ {"waitpid", (func*)&waitpid, 3, 0, 0},
    /* 1057 */ {"wait3", (func*)&wait3, 3, 0, 0},
    /* 1058 */ {"wait4", (func*)&wait4, 4, 0, 0},
    /* 1059 */ {"waitid", (func*)&waitid, 4, 0, 0},
    /* 1060 */ {"alarm", (func*)&alarm, 1, 0, 0},
    /* 1061 */ {"sleep", (func*)&sleep, 1, 0, 0},
    /* 1062 */ {"pause", (func*)&pause, 0, 0, 0},
    /* 1063 */ {"nanosleep", (func*)&nanosleep, 2, 0, 0},
    /* 1064 */ {"fork", (func*)&fork, 0, 0, 0},
    /* 1065 */ {"vfork", (func*)&vfork, 0, 0, 0},
    /* 1066 */ {"_Exit", (func*)&_Exit, 1, 0, 1},
    /* 1067 */ {"execve", (func*)&execve, 3, 0, 0},
    /* 1068 */ {"fexecve", (func*)&fexecve, 3, 0, 0},
    /* 1069 */ {"execv", (func*)&execv, 2, 0, 0},
    /* 1070 */ {"execle", (func*)&execle, 2, 1, 0},
    /* 1071 */ {"execl", (func*)&execl, 2, 1, 0},
    /* 1072 */ {"execvp", (func*)&execvp, 2, 0, 0},
    /* 1073 */ {"execlp", (func*)&execlp, 2, 1, 0},
    /* 1074 */ {"execvpe", (func*)&execvpe, 3, 0, 0},
    /* 1075 */ {"getpid", (func*)&getpid, 0, 0, 0},
    /* 1076 */ {"getppid", (func*)&getppid, 0, 0, 0},
    /* 1077 */ {"getuid", (func*)&getuid, 0, 0, 0},
    /* 1078 */ {"geteuid", (func*)&geteuid, 0, 0, 0},
    /* 1079 */ {"getgid", (func*)&getgid, 0, 0, 0},
    /* 1080 */ {"getegid", (func*)&getegid, 0, 0, 0},
    /* 1081 */ {"getgroups", (func*)&getgroups, 2, 0, 0},
    /* 1082 */ {"setuid", (func*)&setuid, 1, 0, 0},
    /* 1083 */ {"setgid", (func*)&setgid, 1, 0, 0},
    /* 1084 */ {"group_member", (func*)&group_member, 1, 0, 0},
    /* 1085 */ {"getpgid", (func*)&getpgid, 1, 0, 0},
    /* 1086 */ {"setpgid", (func*)&setpgid, 2, 0, 0},
    /* 1087 */ {"getpgrp", (func*)&getpgrp, 0, 0, 0},
    /* 1088 */ {"setpgrp", (func*)&setpgrp, 0, 0, 0},
    /* 1089 */ {"getsid", (func*)&getsid, 1, 0, 0},
    /* 1090 */ {"setsid", (func*)&setsid, 0, 0, 0},
    /* 1091 */ {"getresuid", (func*)&getresuid, 3, 0, 0},
    /* 1092 */ {"getresgid", (func*)&getresgid, 3, 0, 0},
    /* 1093 */ {"setresuid", (func*)&setresuid, 3, 0, 0},
    /* 1094 */ {"setresgid", (func*)&setresgid, 3, 0, 0},
    /* 1095 */ {"pathconf", (func*)&pathconf, 2, 0, 0},
    /* 1096 */ {"sysconf", (func*)&sysconf, 1, 0, 0},
    /* 1097 */ {"fpathconf", (func*)&fpathconf, 2, 0, 0},
    /* 1098 */ {"globfree", (func*)&globfree, 1, 0, 1},
    /* 1099 */ {"glob", (func*)&glob, 4, 0, 0},
    /* 1100 */ {"glob_pattern_p", (func*)&glob_pattern_p, 2, 0, 0},
    /* 1101 */ {"fnmatch", (func*)&fnmatch, 3, 0, 0},
    /* 1102 */ {"confstr", (func*)&confstr, 3, 0, 0},
    /* 1103 */ {"getopt", (func*)&getopt, 3, 0, 0},
    /* 1104 */ {"getopt_long", (func*)&getopt_long, 5, 0, 0},
    /* 1105 */ {"getopt_long_only", (func*)&getopt_long_only, 5, 0, 0},
    /* 1106 */ {"sched_setparam", (func*)&sched_setparam, 2, 0, 0},
    /* 1107 */ {"sched_getparam", (func*)&sched_getparam, 2, 0, 0},
    /* 1108 */ {"sched_setscheduler", (func*)&sched_setscheduler, 3, 0, 0},
    /* 1109 */ {"sched_getscheduler", (func*)&sched_getscheduler, 1, 0, 0},
    /* 1110 */ {"sched_yield", (func*)&sched_yield, 0, 0, 0},
    /* 1111 */ {"sched_get_priority_max", (func*)&sched_get_priority_max, 1, 0, 0},
    /* 1112 */ {"sched_get_priority_min", (func*)&sched_get_priority_min, 1, 0, 0},
    /* 1113 */ {"sched_rr_get_interval", (func*)&sched_rr_get_interval, 2, 0, 0},
    /* 1114 */ {"sched_getaffinity", (func*)&sched_getaffinity, 3, 0, 0},
    /* 1115 */ {"sched_setaffinity", (func*)&sched_setaffinity, 3, 0, 0},
    /* 1116 */ {"pread", (func*)&pread, 4, 0, 0},
    /* 1117 */ {"pwrite", (func*)&pwrite, 4, 0, 0},
    /* 1118 */ {"posix_madvise", (func*)&posix_madvise, 3, 0, 0},
    /* 1119 */ {"getaddrinfo", (func*)&getaddrinfo, 4, 0, 0},
    /* 1120 */ {"freeaddrinfo", (func*)&freeaddrinfo, 1, 0, 1},
    /* 1121 */ {"gai_strerror", (func*)&gai_strerror, 1, 0, 0},
    /* 1122 */ {"re_compile_pattern", (func*)&re_compile_pattern, 3, 0, 0},
    /* 1123 */ {"re_set_syntax", (func*)&re_set_syntax, 1, 0, 0},
    /* 1124 */ {"re_compile_fastmap", (func*)&re_compile_fastmap, 1, 0, 0},
    /* 1125 */ {"regcomp", (func*)&regcomp, 3, 0, 0},
    /* 1126 */ {"regerror", (func*)&regerror, 4, 0, 0},
    /* 1127 */ {"regfree", (func*)&regfree, 1, 0, 1},
    /* 1128 */ {"re_comp", (func*)&re_comp, 1, 0, 0},
    /* 1129 */ {"regexec", (func*)&regexec, 5, 0, 0},
    /* 1130 */ {"re_match", (func*)&re_match, 5, 0, 0},
    /* 1131 */ {"re_search", (func*)&re_search, 6, 0, 0},
    /* 1132 */ {"re_set_registers", (func*)&re_set_registers, 5, 0, 1},
    /* 1133 */ {"re_exec", (func*)&re_exec, 1, 0, 0},
    /* 1134 */ {"posix_spawn_file_actions_init", (func*)&posix_spawn_file_actions_init, 1, 0, 0},
    /* 1135 */ {"posix_spawn_file_actions_destroy", (func*)&posix_spawn_file_actions_destroy, 1, 0, 0},
    /* 1136 */ {"posix_spawn_file_actions_addclose", (func*)&posix_spawn_file_actions_addclose, 2, 0, 0},
    /* 1137 */ {"posix_spawn_file_actions_addopen", (func*)&posix_spawn_file_actions_addopen, 5, 0, 0},
    /* 1138 */ {"posix_spawn_file_actions_adddup2", (func*)&posix_spawn_file_actions_adddup2, 3, 0, 0},
    /* 1139 */ {"posix_spawnattr_init", (func*)&posix_spawnattr_init, 1, 0, 0},
    /* 1140 */ {"posix_spawnattr_destroy", (func*)&posix_spawnattr_destroy, 1, 0, 0},
    /* 1141 */ {"posix_spawnattr_getsigdefault", (func*)&posix_spawnattr_getsigdefault, 2, 0, 0},
    /* 1142 */ {"posix_spawnattr_setsigdefault", (func*)&posix_spawnattr_setsigdefault, 2, 0, 0},
    /* 1143 */ {"posix_spawnattr_getflags", (func*)&posix_spawnattr_getflags, 2, 0, 0},
    /* 1144 */ {"posix_spawnattr_setflags", (func*)&posix_spawnattr_setflags, 2, 0, 0},
    /* 1145 */ {"posix_spawnattr_getpgroup", (func*)&posix_spawnattr_getpgroup, 2, 0, 0},
    /* 1146 */ {"posix_spawnattr_setpgroup", (func*)&posix_spawnattr_setpgroup, 2, 0, 0},
    /* 1147 */ {"posix_spawn", (func*)&posix_spawn, 6, 0, 0},
    /* 1148 */ {"posix_spawnp", (func*)&posix_spawnp, 6, 0, 0},
    /* 1149 */ {"posix_spawnattr_getsigmask", (func*)&posix_spawnattr_getsigmask, 2, 0, 0},
    /* 1150 */ {"posix_spawnattr_getschedpolicy", (func*)&posix_spawnattr_getschedpolicy, 2, 0, 0},
    /* 1151 */ {"posix_spawnattr_getschedparam", (func*)&posix_spawnattr_getschedparam, 2, 0, 0},
    /* 1152 */ {"posix_spawnattr_setsigmask", (func*)&posix_spawnattr_setsigmask, 2, 0, 0},
    /* 1153 */ {"posix_spawnattr_setschedpolicy", (func*)&posix_spawnattr_setschedpolicy, 2, 0, 0},
    /* 1154 */ {"posix_spawnattr_setschedparam", (func*)&posix_spawnattr_setschedparam, 2, 0, 0},
    /* 1155 */ {"wordfree", (func*)&wordfree, 1, 0, 1},
    /* 1156 */ {"wordexp", (func*)&wordexp, 3, 0, 0},
    /* 1157 */ {"sched_getcpu", (func*)&sched_getcpu, 0, 0, 0},
    /* 1158 */ {"utime", (func*)&utime, 2, 0, 0},
    /* 1159 */ {"mkfifo", (func*)&mkfifo, 2, 0, 0},
    /* 1160 */ {"mkfifoat", (func*)&mkfifoat, 3, 0, 0},
    /* 1161 */ {"statfs", (func*)&statfs, 2, 0, 0},
    /* 1162 */ {"fstatfs", (func*)&fstatfs, 2, 0, 0},
    /* 1163 */ {"statvfs", (func*)&statvfs, 2, 0, 0},
    /* 1164 */ {"fstatvfs", (func*)&fstatvfs, 2, 0, 0},
    /* 1165 */ {"umask", (func*)&umask, 1, 0, 0},
    /* 1166 */ {"chmod", (func*)&chmod, 2, 0, 0},
    /* 1167 */ {"fchmod", (func*)&fchmod, 2, 0, 0},
    /* 1168 */ {"fchmodat", (func*)&fchmodat, 4, 0, 0},
    /* 1169 */ {"mkdir", (func*)&mkdir, 2, 0, 0},
    /* 1170 */ {"mkdirat", (func*)&mkdirat, 3, 0, 0},
    /* 1171 */ {"open", (func*)&open, 2, 1, 0},
    /* 1172 */ {"openat", (func*)&openat, 3, 1, 0},
    /* 1173 */ {"read", (func*)&read, 3, 0, 0},
    /* 1174 */ {"write", (func*)&write, 3, 0, 0},
    /* 1175 */ {"access", (func*)&access, 2, 0, 0},
    /* 1176 */ {"eaccess", (func*)&eaccess, 2, 0, 0},
    /* 1177 */ {"faccessat", (func*)&faccessat, 4, 0, 0},
    /* 1178 */ {"fcntl", (func*)&fcntl, 2, 1, 0},
    /* 1179 */ {"flock", (func*)&flock, 2, 0, 0},
    /* 1180 */ {"lockf", (func*)&lockf, 3, 0, 0},
    /* 1181 */ {"close", (func*)&close, 1, 0, 0},
    /* 1182 */ {"dup", (func*)&dup, 1, 0, 0},
    /* 1183 */ {"dup2", (func*)&dup2, 2, 0, 0},
    /* 1184 */ {"dup3", (func*)&dup3, 3, 0, 0},
    /* 1185 */ {"pipe", (func*)&pipe, 1, 0, 0},
    /* 1186 */ {"pipe2", (func*)&pipe2, 2, 0, 0},
    /* 1187 */ {"creat", (func*)&creat, 2, 0, 0},
    /* 1188 */ {"chdir", (func*)&chdir, 1, 0, 0},
    /* 1189 */ {"fchdir", (func*)&fchdir, 1, 0, 0},
    /* 1190 */ {"getcwd", (func*)&getcwd, 2, 0, 0},
    /* 1191 */ {"getwd", (func*)&getwd, 1, 0, 0},
    /* 1192 */ {"get_current_dir_name", (func*)&get_current_dir_name, 0, 0, 0},
    /* 1193 */ {"chown", (func*)&chown, 3, 0, 0},
    /* 1194 */ {"fchown", (func*)&fchown, 3, 0, 0},
    /* 1195 */ {"lchown", (func*)&lchown, 3, 0, 0},
    /* 1196 */ {"fchownat", (func*)&fchownat, 5, 0, 0},
    /* 1197 */ {"ttyname", (func*)&ttyname, 1, 0, 0},
    /* 1198 */ {"ttyname_r", (func*)&ttyname_r, 3, 0, 0},
    /* 1199 */ {"isatty", (func*)&isatty, 1, 0, 0},
    /* 1200 */ {"link", (func*)&link, 2, 0, 0},
    /* 1201 */ {"linkat", (func*)&linkat, 5, 0, 0},
    /* 1202 */ {"symlink", (func*)&symlink, 2, 0, 0},
    /* 1203 */ {"symlinkat", (func*)&symlinkat, 3, 0, 0},
    /* 1204 */ {"readlink", (func*)&readlink, 3, 0, 0},
    /* 1205 */ {"readlinkat", (func*)&readlinkat, 4, 0, 0},
    /* 1206 */ {"unlink", (func*)&unlink, 1, 0, 0},
    /* 1207 */ {"unlinkat", (func*)&unlinkat, 3, 0, 0},
    /* 1208 */ {"rmdir", (func*)&rmdir, 1, 0, 0},
    /* 1209 */ {"poll", (func*)&poll, 3, 0, 0},
    /* 1210 */ {"ppoll", (func*)&ppoll, 4, 0, 0},
    /* 1211 */ {"posix_fadvise", (func*)&posix_fadvise, 4, 0, 0},
    /* 1212 */ {"posix_fallocate", (func*)&posix_fallocate, 3, 0, 0},
    /* 1213 */ {"sendfile", (func*)&sendfile, 4, 0, 0},
    /* 1214 */ {"utimensat", (func*)&utimensat, 4, 0, 0},
    /* 1215 */ {"futimens", (func*)&futimens, 2, 0, 0},
    /* 1216 */ {"lchmod", (func*)&lchmod, 2, 0, 0},
    /* 1217 */ {"ftw", (func*)&ftw, 3, 0, 0},
    /* 1218 */ {"nftw", (func*)&nftw, 4, 0, 0},
    /* 1219 */ {"fts_open", (func*)&fts_open, 3, 0, 0},
    /* 1220 */ {"fts_close", (func*)&fts_close, 1, 0, 0},
    /* 1221 */ {"fts_read", (func*)&fts_read, 1, 0, 0},
    /* 1222 */ {"fts_set", (func*)&fts_set, 3, 0, 0},
    /* 1223 */ {"fts_children", (func*)&fts_children, 2, 0, 0},
    /* 1224 */ {"sync_file_range", (func*)&sync_file_range, 4, 0, 0},
    /* 1225 */ {"fallocate", (func*)&fallocate, 4, 0, 0},
    /* 1226 */ {"cfgetospeed", (func*)&cfgetospeed, 1, 0, 0},
    /* 1227 */ {"cfgetispeed", (func*)&cfgetispeed, 1, 0, 0},
    /* 1228 */ {"cfsetospeed", (func*)&cfsetospeed, 2, 0, 0},
    /* 1229 */ {"cfsetispeed", (func*)&cfsetispeed, 2, 0, 0},
    /* 1230 */ {"cfsetspeed", (func*)&cfsetspeed, 2, 0, 0},
    /* 1231 */ {"tcsetattr", (func*)&tcsetattr, 3, 0, 0},
    /* 1232 */ {"tcgetattr", (func*)&tcgetattr, 2, 0, 0},
    /* 1233 */ {"tcgetpgrp", (func*)&tcgetpgrp, 1, 0, 0},
    /* 1234 */ {"tcsetpgrp", (func*)&tcsetpgrp, 2, 0, 0},
    /* 1235 */ {"tcdrain", (func*)&tcdrain, 1, 0, 0},
    /* 1236 */ {"tcflow", (func*)&tcflow, 2, 0, 0},
    /* 1237 */ {"tcflush", (func*)&tcflush, 2, 0, 0},
    /* 1238 */ {"tcsendbreak", (func*)&tcsendbreak, 2, 0, 0},
    /* 1239 */ {"cfmakeraw", (func*)&cfmakeraw, 1, 0, 1},
    /* 1240 */ {"tcgetsid", (func*)&tcgetsid, 1, 0, 0},
    /* 1241 */ {"getrlimit", (func*)&getrlimit, 2, 0, 0},
    /* 1242 */ {"setrlimit", (func*)&setrlimit, 2, 0, 0},
    /* 1243 */ {"getrusage", (func*)&getrusage, 2, 0, 0},
    /* 1244 */ {"ulimit", (func*)&ulimit, 1, 1, 0},
    /* 1245 */ {"vlimit", (func*)&vlimit, 2, 0, 0},
    /* 1246 */ {"vtimes", (func*)&vtimes, 2, 0, 0},
    /* 1247 */ {"getpriority", (func*)&getpriority, 2, 0, 0},
    /* 1248 */ {"setpriority", (func*)&setpriority, 3, 0, 0},
    /* 1249 */ {"nice", (func*)&nice, 1, 0, 0},
    /* 1250 */ {"brk", (func*)&brk, 1, 0, 0},
    /* 1251 */ {"sbrk", (func*)&sbrk, 1, 0, 0},
    /* 1252 */ {"sstk", (func*)&sstk, 1, 0, 0},
    /* 1253 */ {"ioctl", (func*)&ioctl, 2, 1, 0},
    /* 1254 */ {"readv", (func*)&readv, 3, 0, 0},
    /* 1255 */ {"writev", (func*)&writev, 3, 0, 0},
    /* 1256 */ {"preadv", (func*)&preadv, 4, 0, 0},
    /* 1257 */ {"pwritev", (func*)&pwritev, 4, 0, 0},
    /* 1258 */ {"setreuid", (func*)&setreuid, 2, 0, 0},
    /* 1259 */ {"setregid", (func*)&setregid, 2, 0, 0},
    /* 1260 */ {"seteuid", (func*)&seteuid, 1, 0, 0},
    /* 1261 */ {"setegid", (func*)&setegid, 1, 0, 0},
    /* 1262 */ {"getpagesize", (func*)&getpagesize, 0, 0, 0},
    /* 1263 */ {"getdtablesize", (func*)&getdtablesize, 0, 0, 0},
    /* 1264 */ {"gethostname", (func*)&gethostname, 2, 0, 0},
    /* 1265 */ {"sethostname", (func*)&sethostname, 2, 0, 0},
    /* 1266 */ {"getdomainname", (func*)&getdomainname, 2, 0, 0},
    /* 1267 */ {"setdomainname", (func*)&setdomainname, 2, 0, 0},
    /* 1268 */ {"select", (func*)&select, 5, 0, 0},
    /* 1269 */ {"pselect", (func*)&pselect, 6, 0, 0},
    /* 1270 */ {"acct", (func*)&acct, 1, 0, 0},
    /* 1271 */ {"chroot", (func*)&chroot, 1, 0, 0},
    /* 1272 */ {"fsync", (func*)&fsync, 1, 0, 0},
    /* 1273 */ {"sync", (func*)&sync, 0, 0, 1},
    /* 1274 */ {"fdatasync", (func*)&fdatasync, 1, 0, 0},
    /* 1275 */ {"syncfs", (func*)&syncfs, 1, 0, 0},
    /* 1276 */ {"reboot", (func*)&reboot, 1, 0, 0},
    /* 1277 */ {"gethostid", (func*)&gethostid, 0, 0, 0},
    /* 1278 */ {"sethostid", (func*)&sethostid, 1, 0, 0},
    /* 1279 */ {"vhangup", (func*)&vhangup, 0, 0, 0},
    /* 1280 */ {"swapon", (func*)&swapon, 2, 0, 0},
    /* 1281 */ {"swapoff", (func*)&swapoff, 1, 0, 0},
    /* 1282 */ {"mktemp", (func*)&mktemp, 1, 0, 0},
    /* 1283 */ {"mkstemp", (func*)&mkstemp, 1, 0, 0},
    /* 1284 */ {"mkdtemp", (func*)&mkdtemp, 1, 0, 0},
    /* 1285 */ {"mkostemp", (func*)&mkostemp, 2, 0, 0},
    /* 1286 */ {"mkstemps", (func*)&mkstemps, 2, 0, 0},
    /* 1287 */ {"mkostemps", (func*)&mkostemps, 3, 0, 0},
    /* 1288 */ {"ualarm", (func*)&ualarm, 2, 0, 0},
    /* 1289 */ {"usleep", (func*)&usleep, 1, 0, 0},
    /* 1290 */ {"gtty", (func*)&gtty, 2, 0, 0},
    /* 1291 */ {"stty", (func*)&stty, 2, 0, 0},
    /* 1292 */ {"ptrace", (func*)&ptrace, 1, 1, 0},
    /* 1293 */ {"getmntent", (func*)&getmntent, 1, 0, 0},
    /* 1294 */ {"setmntent", (func*)&setmntent, 2, 0, 0},
    /* 1295 */ {"endmntent", (func*)&endmntent, 1, 0, 0},
    /* 1296 */ {"getmntent_r", (func*)&getmntent_r, 4, 0, 0},
    /* 1297 */ {"addmntent", (func*)&addmntent, 2, 0, 0},
    /* 1298 */ {"hasmntopt", (func*)&hasmntopt, 2, 0, 0},
    /* 1299 */ {"utimes", (func*)&utimes, 2, 0, 0},
    /* 1300 */ {"lutimes", (func*)&lutimes, 2, 0, 0},
    /* 1301 */ {"futimes", (func*)&futimes, 2, 0, 0},
    /* 1302 */ {"futimesat", (func*)&futimesat, 3, 0, 0},
    /* 1303 */ {"truncate", (func*)&truncate, 2, 0, 0},
    /* 1304 */ {"ftruncate", (func*)&ftruncate, 2, 0, 0},
    /* 1305 */ {"insque", (func*)&insque, 2, 0, 1},
    /* 1306 */ {"remque", (func*)&remque, 1, 0, 1},
    /* 1307 */ {"getttyent", (func*)&getttyent, 0, 0, 0},
    /* 1308 */ {"getttynam", (func*)&getttynam, 1, 0, 0},
    /* 1309 */ {"setttyent", (func*)&setttyent, 0, 0, 0},
    /* 1310 */ {"endttyent", (func*)&endttyent, 0, 0, 0},
    /* 1311 */ {"getusershell", (func*)&getusershell, 0, 0, 0},
    /* 1312 */ {"endusershell", (func*)&endusershell, 0, 0, 1},
    /* 1313 */ {"setusershell", (func*)&setusershell, 0, 0, 1},
    /* 1314 */ {"getpass", (func*)&getpass, 1, 0, 0},
    /* 1315 */ {"ttyslot", (func*)&ttyslot, 0, 0, 0},
    /* 1316 */ {"_f1", (func*)&_f1, 1, 0, 0},
    /* 1317 */ {"_f2", (func*)&_f2, 4, 0, 0},
    /* 1318 */ {"frexpf", (func*)&frexpf, 2, 0, 0},
    /* 1319 */ {"frexp", (func*)&frexp, 2, 0, 0},
    /* 1320 */ {"_isalpha", (func*)&_isalpha, 1, 0, 0},
    /* 1321 */ {"_isdigit", (func*)&_isdigit, 1, 0, 0},
    /* 1322 */ {"_isalnum", (func*)&_isalnum, 1, 0, 0},
    /* 1323 */ {"strtoll", (func*)&strtoll, 3, 0, 0},
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
  FILE *fh;
  if (argc == 5 && argv[3][0]=='f') {
    fh = fopen(argv[4], "r");
  }
  fuzz_start();

    if (argc < 4) {
	fprintf(stderr, "Usage: two-funcs <f1num> <f2num> a [0-6 args]\n");
	fprintf(stderr, "    or two-funcs <f1num> <f2num> g\n");
	fprintf(stderr, "    or two-funcs <f1num> <f2num> f <fname or ->\n");
	exit(1);
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
	compare(0, 0,
		global_arg0, global_arg1, global_arg2,
		global_arg3, global_arg4, global_arg5);
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
