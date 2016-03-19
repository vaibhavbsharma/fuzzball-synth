#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE

#include <inttypes.h>
#include <locale.h>
#include <math.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <uchar.h>
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
#include <stdio_ext.h>
#include <stropts.h>
#include <ttyent.h>
#include <ucontext.h>
#include <ulimit.h>
#include <ustat.h>
#include <utime.h>
#include <utmp.h>
#include <utmpx.h>
#include <wordexp.h>
#include <sys/auxv.h>
#include <sys/capability.h>
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

/* Man page exists, but documented in the man page as having no
   prototype in glibc, or being deprecated: */

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

struct sigvec {
  void (*sv_handler)(int); /* Signal disposition */
  int    sv_mask;          /* Signals to be blocked in handler */
  int    sv_flags;         /* Flags */
};
int sigvec(int sig, const struct sigvec *vec, struct sigvec *ovec);


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

