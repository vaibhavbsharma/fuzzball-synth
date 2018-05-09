#include "generate_struct_adaptors.h"
#include "generate_adaptors.h"
#include "functions.h"
#include "SignalHandlers.h"
#include "generate_adaptors.h"
#include "calc_num_adaptors.h"
#include <assert.h>
#include  <setjmp.h>
#include <memory.h>
#include <bits/errno.h>
#include <errno.h>
#include "constants.h"

#define SANE_ADDR 0x42420000
#define MAX_ADAPTORS 1000000
#define MAX_TESTS 100

fieldsub m[MAX_FIELDS];

argret ad;
int num_adaptors=0;
int const_lb, const_ub;
int adaptor_family;

jmp_buf  JumpBuffer; /* a jump buffer */

int f1num, f2num;
int f1nargs=6, f2nargs=6;
bool void_flag=false;
bool calculating = true;
unsigned long num_adaptors_g = 1;
bool find_all_correct_adaptors=false;
unsigned long number_of_adaptors_tried=0;
unsigned long number_of_correct_adaptors=0;
unsigned long region_limit=0;
unsigned int number_of_fields=0;


unsigned long f1s, f2s;
char str[2] = {97, 0};
char output_str[16] = {'\0'};

typedef struct { long a,b,c,d,e,f} test;
test tests[MAX_TESTS];
int num_tests=0;

long sideEffectsEqual;

void sanitize(long a, long *aS, char *fname, int numTest) {
    int i;
    char *p;
    char newfname[100];
    sprintf(newfname, "%s_%d", fname, numTest);
    if((a&SANE_ADDR) == SANE_ADDR) {
        FILE *f = fopen(newfname, "r");
        if(f) {
            p = (unsigned long) malloc(region_limit);
            for(i=0; i<region_limit; i++) p[i]=0;
            size_t count = fread(p, 1, region_limit, f);
            // if(count<region_limit) {
            // 	printf("Failed to read %d bytes from %s\n", region_limit, fname);
            // 	free(aS);
            // 	*aS = a;
            // 	return;
            // }
            *aS = (long) p;
            fclose(f);
            add_sane_struct_addr(p);
        } else { *aS = a; printf("failed to open %s\n", newfname); }
    } else { printf("%lx need not be sanitized\n", a); *aS = a; }
    fflush(stdout);
}

void addTest(long a, long b, long c, long d, long e, long f) {
    tests[num_tests].a=a;
    tests[num_tests].b=b;
    tests[num_tests].c=c;
    tests[num_tests].d=d;
    tests[num_tests].e=e;
    tests[num_tests].f=f;
    num_tests++;
}

bool isSaneAddr(long a) { return a > 4096; }

void print_adaptor() {
    char str[ADAPTOR_STR_LEN*3]={'\0'};
    printf("%s\n", get_adaptor_string(str, ad, m));
    fflush(stdout);
}

long convert32to64s(long a) {
    int a1=(int) a;
    return (long) a1;
}

long convert32to64u(long a) {
    unsigned int a1=(int) a;
    return (unsigned long) a1;
}

long convert16to64s(long a) {
    short a1=(short) a;
    return (long) a1;
}

long convert16to64u(long a) {
    unsigned short a1=(short) a;
    return (unsigned long) a1;
}

long convert8to64s(long a) {
    char a1=(char) a;
    return (long) a1;
}

long convert8to64u(long a) {
    unsigned char a1=(char) a;
    return (unsigned long) a1;
}

long convert1to64s(long a) {
    char a1;
    if( a & 1 ) a1=0xff; else a1=0;
    return (long) a1;
}

long convert1to64u(long a) {
    unsigned char a1=(char) a&1;
    return (unsigned long) a1;
}

long convert64to1(long a) { return (long) a != 0; }

long wrap_f2(long a, long b, long c, long d, long e, long f_arg) {
    long f1args[6] = {a, b, c, d, e, f_arg};
    long f2args[6] = {0, 0, 0, 0, 0, 0};


    int i, f;
    int struct_arg_index=-1;

    // char str[ADAPTOR_STR_LEN*2];
    // printf("trying adaptor: %s\n", get_adaptor_string(str, ad, m));
    // fflush(stdout);

    for(i=0;i<f2nargs; i++) {
        switch(ad.a_ad[i].var_is_const) {
            case 1: f2args[i]=ad.a_ad[i].var_val; break;
            case 0: f2args[i]=f1args[ad.a_ad[i].var_val] ; break;
            default: break;
        }
        if(is_sane_struct_addr(f2args[i]) && adaptor_family==14) {
            if(struct_arg_index != -1) {
                printf("two struct args (struct_arg_index = %d, i = %d, f2args[%d] = 0x%lx), panic!\n",
                       struct_arg_index, i, i, f2args[i]);
            }
            struct_arg_index=i;
        }
    }
    if(struct_arg_index != -1) {
        f1s = f2args[struct_arg_index];
        f2args[struct_arg_index] = f2s;
        //printf("f1s = 0x%lx, f2s = 0x%lx, struct_arg_index = %d\n", f1s, f2s, struct_arg_index);
    }
    if(adaptor_family==14 && struct_arg_index != -1) {
        for(i=0; i<region_limit; i++) *((unsigned long *)(f2s + i))=(unsigned char)0;
        int f2_offset=0;
        for(f=0; f<number_of_fields; f++) {
            int start_b = (m[f].type>>32);
            int end_b = 65535 & (m[f].type >> 16);
            int total_b = end_b - start_b + 1;
            int sign_ex = m[f].type & 1;
            int n = m[f].n;
            int f1_sz = total_b/n;
            int f2_sz = m[f].size;
            int w=0; // indicates widening(1) or narrowing(-1)
            assert(total_b % n == 0);
            assert(total_b % f1_sz == 0);
            assert((total_b/n == 1) || (total_b/n)==2 ||
                   (total_b/n == 4) || (total_b/n)==8);
            if(f1_sz == f2_sz) {
                memcpy(f2s + f2_offset, f1s + start_b, n*f2_sz);
                f2_offset += (n*f2_sz);
                continue;
            } else if(f1_sz > f2_sz) w=-1;
            else w=1;
            // Copy f1's structure in f1s to f2s using m[f]
            for(i=0; i<n; i++) {
                int start_addr = start_b + i*f1_sz;
                if(f2_offset%f2_sz != 0) f2_offset = ((f2_offset/f2_sz)+1)*f2_sz;
                if(w == -1) { // narrowing
                    switch(f2_sz) {
                        case 1:
                            *((unsigned long *)(f2s + f2_offset)) =
                                    (unsigned char) *(unsigned long *)(f1s + start_addr);
                            f2_offset+=1;
                            break;
                        case 2:
                            *((unsigned long *)(f2s + f2_offset)) =
                                    (unsigned short) *(unsigned long *)(f1s + start_addr);
                            f2_offset+=2;
                            break;
                        case 4:
                            *((unsigned long *)(f2s + f2_offset)) =
                                    (unsigned int) *(unsigned long *)(f1s + start_addr);
                            f2_offset+=4;
                            break;
                            //case 8:
                            //*((unsigned long *)(f2s + f2_offset)) =
                            //  (unsigned long) *(unsigned long *)(f1s + start_addr);
                            //f2_offset+=8;
                            //break;
                        default: printf("f2_sz = %d when narrowing ?!?!?!\n", f2_sz); assert(0);
                    }
                } else if(w == 1) { // widening
                    switch(f2_sz) {
                        case 1: printf("f2_sz = 1 for widening ?!?!?!\n"); assert(0);
                        case 2: // only possible f1_sz is 1
                            if(sign_ex) {
                                char c = *(unsigned long *)(f1s + start_addr);
                                *((unsigned long *)(f2s + f2_offset)) = (short) c;
                            } else {
                                unsigned char c = *(unsigned long *)(f1s + start_addr);
                                *((unsigned long *)(f2s + f2_offset)) = (unsigned short) c;
                            }
                            f2_offset+=2;
                            break;
                        case 4:
                            switch(f1_sz) {
                                case 1:
                                    if(sign_ex) {
                                        char c = *(unsigned long *)(f1s + start_addr);
                                        *((unsigned long *)(f2s + f2_offset)) = (int) c;
                                    } else {
                                        unsigned char c = *(unsigned long *)(f1s + start_addr);
                                        *((unsigned long *)(f2s + f2_offset)) = (unsigned int) c;
                                    }
                                    break;
                                case 2:
                                    if(sign_ex) {
                                        short c = *(unsigned long *)(f1s + start_addr);
                                        *((unsigned long *)(f2s + f2_offset)) = (int) c;
                                    } else {
                                        unsigned short c = *(unsigned long *)(f1s + start_addr);
                                        *((unsigned long *)(f2s + f2_offset)) = (unsigned int) c;
                                    }
                                    break;
                                default:
                                    printf("f1_sz = %d when f2_sz = 4 with widening ?!?!\n", f1_sz);
                                    assert(0);
                            }
                            f2_offset+=4;
                            break;
                        case 8:
                            switch(f1_sz) {
                                case 1:
                                    if(sign_ex) {
                                        char c = *(unsigned long *)(f1s + start_addr);
                                        *((unsigned long *)(f2s + f2_offset)) = (long) c;
                                    } else {
                                        unsigned char c = *(unsigned long *)(f1s + start_addr);
                                        *((unsigned long *)(f2s + f2_offset)) = (unsigned long) c;
                                    }
                                    break;
                                case 2:
                                    if(sign_ex) {
                                        short c = *(unsigned long *)(f1s + start_addr);
                                        *((unsigned long *)(f2s + f2_offset)) = (long) c;
                                    } else {
                                        unsigned short c = *(unsigned long *)(f1s + start_addr);
                                        *((unsigned long *)(f2s + f2_offset)) = (unsigned long) c;
                                    }
                                    break;
                                case 4:
                                    if(sign_ex) {
                                        int c = *(unsigned long *)(f1s + start_addr);
                                        *((unsigned long *)(f2s + f2_offset)) = (long) c;
                                    } else {
                                        unsigned int c = *(unsigned long *)(f1s + start_addr);
                                        *((unsigned long *)(f2s + f2_offset)) = (unsigned long) c;
                                    }
                                    break;
                                default:
                                    printf("f1_sz = %d when f2_sz = 8 with widening ?!?!\n", f1_sz);
                                    assert(0);
                            }
                            f2_offset+=8;
                            break;
                        default: printf("f2_sz = %d when widening\n", f2_sz); assert(0);
                    }
                } // end narrowing/widening
                assert(f2_offset <= region_limit);
            } // end for i = 0 to n (number of entries in this field)
            assert(f2_offset <= region_limit);
        }// end for f = 0 to number_of_fields
        // printf("f1s->x = %d f1s->y = %d\n", *(unsigned int *)f1s, ((unsigned int *)f1s)[1]);
        // printf("f2s->x = %d f2s->y = %d\n", *(unsigned int *)f2s, ((unsigned int *)f2s)[1]);
        // printf("\n");
        // printf("f1s->m[0] = %d f1s->m[1] = %d\n",
        // 	   ((unsigned char *)(f1s+8))[0],
        // 	   ((unsigned char *)(f1s+8))[1]);
        // printf("f2s->m[0] = %d f2s->m[1] = %d\n",
        // 	   ((unsigned int *)(f2s+8))[0],
        // 	   ((unsigned int *)(f2s+8))[1]);
    }// end if isSaneAddr(a)

    long ret_val=0;
    if(f2args[0] != f2s) sideEffectsEqual=0;
    else
        ret_val = f2(f2args[0], f2args[1], f2args[2], f2args[3]);
    long final_ret_val;
    switch(ad.r_ad.ret_type) {
        case 0: final_ret_val = convert32to64u(ret_val); break;
        case 1: final_ret_val = ad.r_ad.ret_val; break;
        case 11: final_ret_val = convert32to64s(f2args[ad.r_ad.ret_val]); break;
        case 12: final_ret_val = convert32to64u(f2args[ad.r_ad.ret_val]); break;
        case 21: final_ret_val = convert16to64s(f2args[ad.r_ad.ret_val]); break;
        case 22: final_ret_val = convert16to64u(f2args[ad.r_ad.ret_val]); break;
        case 31: final_ret_val =  convert8to64s(f2args[ad.r_ad.ret_val]); break;
        case 32: final_ret_val =  convert8to64u(f2args[ad.r_ad.ret_val]); break;
        case 41: final_ret_val =  convert1to64s(f2args[ad.r_ad.ret_val]); break;
        case 42: final_ret_val =  convert1to64u(f2args[ad.r_ad.ret_val]); break;
        case 51: final_ret_val = convert32to64s(ret_val); break;
        case 52: final_ret_val = convert32to64u(ret_val); break;
        case 53: final_ret_val = convert64to1  (ret_val); break;
        case 61: final_ret_val = convert16to64s(ret_val); break;
        case 62: final_ret_val = convert16to64u(ret_val); break;
        case 71: final_ret_val =  convert8to64s(ret_val); break;
        case 72: final_ret_val =  convert8to64u(ret_val); break;
        case 81: final_ret_val =  convert1to64s(ret_val); break;
        case 82: final_ret_val =  convert1to64u(ret_val); break;
        default: break;
    }
    return final_ret_val;
}

int compare() {
    int j, k;
    bool is_all_match;
    long a0, a1, a2, a3, a4, a5;
    bool is_match[MAX_TESTS];
    if(calculating) {
        printf("Loose upper bound on number of adaptors = %ld\n", num_adaptors_g);
        calculating=false;
    }
    for(k=0; k<MAX_TESTS; k++) is_match[k]=false;
    for(j=0; j<num_tests; j++) {
        sideEffectsEqual=1;
        a0=tests[j].a;
        a1=tests[j].b;
        a2=tests[j].c;
        a3=tests[j].d;
        a4=tests[j].e;
        a5=tests[j].f;
        //printf("Starting f1, j=%d\n", j);
        fflush(stdout);
        long r1, r2;
        if (sigsetjmp(JumpBuffer, 1) != 0) {     /* set a return mark   */
            printf("returning from longjmp, j=%d\n", j);
            fflush(stdout);
            is_match[j]=false;
            break;
            continue;
        } // else printf("setjmp setup\n");
        fflush(stdout);
        f1s = a0;
        assert(a1 == 1);
        a2 = str;
        a3 = output_str;
        r1 = f1(a0, a1, a2, a3); //, a3, a4, a5);
        // printf("Completed f1\n");
        // fflush(stdout);
        // printf("Starting f2\n");
        // fflush(stdout);
        r2 = wrap_f2(a0, a1, a2, a3, a4, a5);
        // printf("Completed f2\n");
        // fflush(stdout);
        //printf("r1 = 0x%lx, r2 = 0x%lx\n", r1, r2);
        if (r1==r2 && sideEffectsEqual) {
            printf("Match\n");
            is_match[j]=true;
        } else break;
    }
    is_all_match=true;
    for(j=0;j<num_tests; j++) is_all_match = is_all_match & is_match[j];
    if(is_all_match == 1 && !find_all_correct_adaptors) {
        printf("Number of adaptors tried = %ld\n", number_of_adaptors_tried);
        printf("All tests succeeded!\n");
        print_adaptor();
        fflush(stdout);
        exit(0);
    }
    return is_all_match;
}

long global_arg0, global_arg1, global_arg2,
        global_arg3, global_arg4, global_arg5;

int main(int argc, char **argv) {
    struct sigaction sSigaction;
    /* Register the signal hander using the siginfo interface*/
    sSigaction.sa_sigaction = div0_signal_handler;
    sSigaction.sa_flags = SA_SIGINFO;
    /* mask all other signals */
    sigfillset(&sSigaction.sa_mask);
    int ret = sigaction(SIGFPE, &sSigaction, NULL);
    if(ret) {
        perror("ERROR, sigaction failed");
        exit(-1);
    }

    struct sigaction sSigaction1;
    /* Register the signal hander using the siginfo interface*/
    sSigaction1.sa_sigaction = segv_signal_handler;
    sSigaction1.sa_flags = SA_SIGINFO;
    /* mask all other signals */
    sigfillset(&sSigaction1.sa_mask);
    ret = sigaction(SIGSEGV, &sSigaction1, NULL);
    if(ret) {
        perror("ERROR, sigaction failed");
        exit(-1);
    }


    int numTests=0;
    FILE *fh;
    if (argc == 12 && argv[3][0]=='f') {
        f1num = atoi(argv[1]);
        f2num = atoi(argv[2]);
        fh = fopen(argv[4], "r");
        const_lb = atoi(argv[5]);
        const_ub = atoi(argv[6]);
        //argv[7] is sideEffectEqual's address
        adaptor_family = atoi(argv[8]);
        region_limit = atoi(argv[9]);
        number_of_fields = atoi(argv[10]);
        if(atoi(argv[11])==1) {
            find_all_correct_adaptors=false;
        } else find_all_correct_adaptors=true;
    }
    if (argc < 12) {
        fprintf(stderr, "Usage: two-funcs <f1num> <f2num> a [0-6 args]\n");
        fprintf(stderr, "    or two-funcs <f1num> <f2num> g\n");
        fprintf(stderr, "    or two-funcs <f1num> <f2num> f <fname or -> <lower bound> <upper bound> \n<sideEffectsEqual's address> <memsub=4> <region-limit> <number-of-fields> <1=find one correct adaptor, 0=find all correct adaptors>");
        exit(1);
    }
    f1nargs = 4;
    f2nargs = 4;
    int i;
    if (argv[3][0] == 'f') {
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
        if(adaptor_family == 1)
            printf("Tight upper bound on number of adaptors = %ld\n", calc_total_adaptor_num_argsub());
        else if(adaptor_family == 2)
            printf("Tight upper bound on number of adaptors = %ld\n", calc_total_adaptor_num_typeconv());
        while (fscanf(fh, "%lx %lx %lx %lx %lx %lx",
                      &a, &b, &c, &d, &e, &f) != EOF) {
            printf("read a test\n");
            fflush(stdout);
            long aS, bS, cS, dS, eS, fS;
            sanitize(a, &aS, "ce_arg0", numTests);
            //printf("0x%lx sanitized to 0x%lx, string = %s\n", a, aS, (char *)aS);
            sanitize(b, &bS, "ce_arg1", numTests);
            sanitize(c, &cS, "ce_arg2", numTests);
            sanitize(d, &dS, "ce_arg3", numTests);
            sanitize(e, &eS, "ce_arg4", numTests);
            sanitize(f, &fS, "ce_arg5", numTests);
            addTest(aS, bS, cS, dS, eS, fS);
            numTests++;
        }
        if(adaptor_family==1)
            generate_adaptors_randomized(0, m);
        else if(adaptor_family==4) {
            f2s = (unsigned long) malloc(region_limit);
            generate_struct_adaptors_randomized(0, 0, m);
            free((unsigned char *)f2s);
        } else if(adaptor_family==14) {
            f2s = (unsigned long) malloc(region_limit);
            generate_adaptors_randomized(0, m);
            free((unsigned char *)f2s);
        } else {
            printf("unknown adaptor family\n");
            exit(1);
        }
        //int is_eq = compare();
        //if (!is_eq)
        //  exit(1);
    } else {
        fprintf(stderr, "Unhandled command argument\n");
        exit(1);
    }
    if(find_all_correct_adaptors) {
        fflush(stdout);
        printf("\n\nNumber of adaptors tried = %ld\n", number_of_adaptors_tried);
        printf("Number of correct adaptors = %ld\n", number_of_correct_adaptors);
        fflush(stdout);
    }
    return 0;
}
