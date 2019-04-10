#ifndef _STRUCT_INFO_H
#define _STRUCT_INFO_H
void print_struct_info() {
  // sources of these number of fields was eglibc-2.19 unless a TAG wasn't available in which case the source is mentioned as an inline comment
  printf(" sizeof(struct hsearch_data) = %lu, number of fields = %d\n", sizeof(struct hsearch_data), 3);
    printf(" sizeof(struct ustat) = %lu, number of fields = %d\n", sizeof(struct ustat), 4);
    printf(" sizeof(struct timex) = %lu, number of fields = %d\n", sizeof(struct timex), 20);
    printf(" sizeof(struct epoll_event) = %lu, number of fields = %d\n", sizeof(struct epoll_event), 2);
    printf(" sizeof(struct sysinfo) = %lu, number of fields = %d\n", sizeof(struct sysinfo), 10); // source: https://linux.die.net/man/2/sysinfo
    printf(" sizeof(struct iovec) = %lu, number of fields = %d\n", sizeof(struct iovec), 2);
    printf(" sizeof(struct itimerspec) = %lu, number of fields = %d\n", sizeof(struct itimerspec), 2);
    printf(" sizeof(struct file_handle) = %lu, number of fields = %d\n", sizeof(struct file_handle), 3);
    printf(" sizeof(struct msghdr) = %lu, number of fields = %d\n", sizeof(struct msghdr), 7);
    printf(" sizeof(struct mmsghdr) = %lu, number of fields = %d\n", sizeof(struct mmsghdr), 2);
    printf(" sizeof(struct msqid_ds) = %lu, number of fields = %d\n", sizeof(struct msqid_ds), 8);
    printf(" sizeof(struct sembuf) = %lu, number of fields = %d\n", sizeof(struct sembuf), 3);
    printf(" sizeof(struct shmid_ds) = %lu, number of fields = %d\n", sizeof(struct shmid_ds), 8);
    printf(" sizeof(struct argp_state_ds) = %lu, number of fields = %d\n", sizeof(struct argp_state), 14);
    printf(" sizeof(struct sched_param) = %lu, number of fields = %d\n", sizeof(struct sched_param), 1);
    printf(" sizeof(struct if_nameindex) = %lu, number of fields = %d\n", sizeof(struct if_nameindex), 2);
    printf(" sizeof(struct ifaddrs) = %lu, number of fields = %d\n", sizeof(struct ifaddrs), 7);
    printf(" sizeof(struct in_addr) = %lu, number of fields = %d\n", sizeof(struct in_addr), 1);
    printf(" sizeof(struct sockaddr_in) = %lu, number of fields = %d\n", sizeof(struct sockaddr_in), 4);
    printf(" sizeof(struct key_netstarg) = %lu, number of fields = %d\n", sizeof(struct key_netstarg), 3);
    printf(" sizeof(struct pollfd) = %lu, number of fields = %d\n", sizeof(struct pollfd), 3);
    printf(" sizeof(struct __jmp_buf_tag) = %lu, number of fields = %d\n", sizeof(struct __jmp_buf_tag), 3);
    printf(" sizeof(struct sigcontext) = %lu, number of fields = %d\n", sizeof(struct sigcontext), 2);
    printf(" sizeof(struct random_data) = %lu, number of fields = %d\n", sizeof(struct random_data), 7);
    printf(" sizeof(struct drand48_data) = %lu, number of fields = %d\n", sizeof(struct drand48_data), 5);
    printf(" sizeof(struct tm) = %lu, number of fields = %d\n", sizeof(struct tm), 11);
    printf(" sizeof(struct itimerval) = %lu, number of fields = %d\n", sizeof(struct itimerval), 2);
    printf(" sizeof(struct timeb) = %lu, number of fields = %d\n", sizeof(struct timeb), 4);
    printf(" sizeof(struct ntptimeval) = %lu, number of fields = %d\n", sizeof(struct ntptimeval), 8);
    printf(" sizeof(struct utsname) = %lu, number of fields = %d\n", sizeof(struct utsname), 6);
    printf(" sizeof(struct tms) = %lu, number of fields = %d\n", sizeof(struct tms), 4);
    printf(" sizeof(struct rusage) = %lu, number of fields = %d\n", sizeof(struct rusage), 16);
    printf(" sizeof(struct timespec) = %lu, number of fields = %d\n", sizeof(struct timespec), 2);
    printf(" sizeof(struct addrinfo) = %lu, number of fields = %d\n", sizeof(struct addrinfo), 8);
    printf(" sizeof(struct re_pattern_buffer) = %lu, number of fields = %d\n", sizeof(struct re_pattern_buffer), 14);
    printf(" sizeof(struct statfs) = %lu, number of fields = %d\n", sizeof(struct statfs), 10);
    printf(" sizeof(struct statvfs) = %lu, number of fields = %d\n", sizeof(struct statvfs), 12);
    printf(" sizeof(struct pollfd) = %lu, number of fields = %d\n", sizeof(struct pollfd), 3);
    printf(" sizeof(struct termios) = %lu, number of fields = %d\n", sizeof(struct termios), 6);
    printf(" sizeof(struct rlimit) = %lu, number of fields = %d\n", sizeof(struct rlimit), 2);
    printf(" sizeof(struct sgttyb) = %lu, number of fields = %d\n", 8, 3); /* assumed from looking at the layout of sgttyb in bits/ioctl-types.h */
    printf(" sizeof(struct timeval) = %lu, number of fields = %d\n", sizeof(struct timeval), 2);
}
#endif
