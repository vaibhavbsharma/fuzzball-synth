#include "pin.H"
#include <map>
#include <fstream>
#include <iostream>
#include "PinMonitor.h"
#include <sys/stat.h>
using namespace std;


bool logfile=false;

#define STACK_CONST 0x7ff000000000

FILE *trace;

bool RecordF1 = false, RecordF2 = false;
string ProgramImage;
string f1Name="f1", f2Name="f2";
long *sideEffectsEqualAddr;

VOID ReadsMem (ADDRINT applicationIp, ADDRINT memoryAddressRead, UINT32 memoryReadSize) {
}

map< long*, int> f1_addrs, f2_addrs;
vector< ADDRINT> f1_syscalls, f2_syscalls;
vector< syscallArgs > f1_syscall_args, f2_syscall_args;
long f1_rsp=0, f2_rsp=0;
UINT8 f1_ret_val, f2_ret_val;
map < int, bool> noopSyscalls;

bool isGlobalAddr(long addr, long rsp) {
  //long int li = (long int) addr;
  //long val = * (long *) addr;
  //return ((li & STACK_CONST) == 0) && 
  //  ((val & STACK_CONST) == 0) && 
  //  ( val != 0 );
  //http://stackoverflow.com/questions/41087728/what-are-the-maximum-and-minimum-sizes-of-a-segment-on-the-8086
  return labs(addr-rsp) > 65536;
}

VOID WritesMem (ADDRINT applicationIp, ADDRINT memoryAddressWrite, UINT32 memoryWriteSize, ADDRINT rsp_val) {
  string fname;
  if(RecordF1) fname="f1: ";
  else if(RecordF2) fname="f2: ";
  else return;
  if(RecordF1 && isGlobalAddr(memoryAddressWrite, f1_rsp)) 
    if(f1_addrs.find((long *)memoryAddressWrite) == f1_addrs.end())
      f1_addrs[(long *) memoryAddressWrite] = (int) *(long *) memoryAddressWrite;
  if(RecordF2 && isGlobalAddr(memoryAddressWrite, f2_rsp)) 
    if(f2_addrs.find((long *)memoryAddressWrite) == f2_addrs.end())
      f2_addrs[(long *) memoryAddressWrite] = (int) *(long *) memoryAddressWrite;
  fprintf(trace, "WritesMem: %s0x%lx\n", fname.c_str(), memoryAddressWrite);
}

VOID RecordSyscall(CONTEXT *ctx, ADDRINT ip, ADDRINT num, ADDRINT arg0, ADDRINT arg1, ADDRINT arg2, ADDRINT arg3, ADDRINT arg4, ADDRINT arg5) {
  fprintf(trace, "starting RecordSyscall(%ld)\n", num);
  fflush(trace);
  string fname;
  int args = getArgsForSyscallnum(num);
  ADDRINT argsVector[] = { arg0, arg1, arg2, arg3, arg4, arg5 };
  syscallArgs sa;
  for(int i=0;i<6; i++) { sa.args[i] = argsVector[i]; }
  sa.numArgs = args;
  sa.syscallNum = num;

  if(RecordF1) fname="f1: ";
  else if(RecordF2) fname="f2: ";
  else return;

  if(RecordF1) {
    f1_syscalls.push_back(num);
    f1_syscall_args.push_back(sa);
  }
  if(RecordF2) {
    f2_syscalls.push_back(num);
    f2_syscall_args.push_back(sa);
  }
  fprintf(trace, "%s called syscall(%ld) args = (", fname.c_str(), num);
  for(int i=0;i<args; i++) fprintf(trace, "0x%lx, ", argsVector[i]);
  fprintf(trace, ")\n");
  fflush(trace);
}

VOID Instruction(INS ins, void * v) {// Jitting time routine
  if (INS_IsMemoryWrite(ins) ) {
    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR) WritesMem,
		   IARG_INST_PTR,// application IP
		   IARG_MEMORYWRITE_EA,
		   IARG_MEMORYWRITE_SIZE,
		   IARG_REG_VALUE, REG_STACK_PTR, 
		   IARG_END);
  }
  if (INS_IsSyscall(ins)) {
    INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(RecordSyscall),
		   IARG_CONTEXT,
		   IARG_INST_PTR, IARG_SYSCALL_NUMBER,
		   IARG_SYSARG_VALUE, 0, IARG_SYSARG_VALUE, 1,
		   IARG_SYSARG_VALUE, 2, IARG_SYSARG_VALUE, 3,
		   IARG_SYSARG_VALUE, 4, IARG_SYSARG_VALUE, 5,
		   IARG_END);
  }
}

VOID RecordF1Begin(ADDRINT rsp_val) {
  fprintf(trace, "f1 began, rsp_val = 0x%lx\n",rsp_val);
  RecordF1 = true;
  if(f1_rsp == 0) f1_rsp = (long ) rsp_val;
}

VOID RecordF1End(CONTEXT *ctx) {
  f1_ret_val = PIN_GetContextReg(ctx, REG_RAX);
  fprintf(trace, "f1 ended with retval = %d\n",f1_ret_val);
  RecordF1 = false;
  map<long *, int> :: iterator it = f1_addrs.begin();
  while(it!=f1_addrs.end()) {
    fprintf(trace, "f1write: mem[%p] = 0x%x, old value = 0x%x\n", 
	    it->first, (int) *(long *)(it->first), it->second);
    // save current value
    int tmp = (int) *(long *) it->first;
    // restore old value
    *(int *) it->first = it->second;
    // store current value for later side-effect equivalence checking
    it->second = tmp;
    ++it;
  }
  fflush(trace);
}

VOID RecordF2Begin(ADDRINT rsp_val) {
  fprintf(trace, "f2 began, rsp_val = 0x%lx\n",rsp_val);
  RecordF2 = true;
  if(f2_rsp ==0 ) f2_rsp = (long ) rsp_val;
  fflush(trace);
}

int getF1Val(long *f2_addr, bool &found) {
  found=true;
  map<long *, int> :: iterator it = f1_addrs.begin();
  while(it!=f1_addrs.end()) {
    if(it->first == f2_addr) return it->second;
    ++it;
  }
  found=false;
  return -1;
}

void replaceRetVal(CONTEXT *ctx) {
  //long *a = (long *)0x7b5e88;
  *sideEffectsEqualAddr = 0;
  //UINT8 t;
  //t = f1_ret_val + 1;
  //PIN_SetContextRegval(ctx, REG_RAX, &t);
  //PIN_ExecuteAt(ctx);
}

void cleanupAfterF2() {
  fflush(trace);
  f1_addrs.clear();
  f2_addrs.clear();
  f1_syscalls.clear();
  f2_syscalls.clear();
  f1_syscall_args.clear();
  f2_syscall_args.clear();
  RecordF2 = false;
}

VOID RecordF2End(CONTEXT *ctx) {
  // PIN_GetContextRegval(ctx, REG_RAX, &f2_ret_val);
  bool mismatch=false;
  f2_ret_val = PIN_GetContextReg(ctx, REG_RAX);
  //fprintf(trace, "Starting RecordF2End\n");
  fprintf(trace, "f2 ended with retval = %d\n",f2_ret_val);
  fflush(trace);
  if(f1_ret_val != f2_ret_val) {
    cleanupAfterF2();
    return;
  }
  map<long *, int> :: iterator it = f2_addrs.begin();
  while(it!=f2_addrs.end()) {
    bool found;
    int f1_val = getF1Val(it->first, found);
    int f2_val = (int) *(long *)(it->first);
    fprintf(trace, "f2write: mem[%p] = %x ;", it->first, f2_val);
    if(!found || (found && (f1_val != f2_val)) ) { 
      fprintf(trace, "unequal values written, 0x%x, 0x%x, ", f1_val, f2_val);
      if(f1_ret_val == f2_ret_val) {
	fprintf(trace, "replacing REG_RAX\n");
	fflush(trace);
	replaceRetVal(ctx);
	mismatch=true;
	break;
      }
    }
    else {
      fprintf(trace, "equal values written\n");
      f1_addrs.erase(it->first);
    }
    ++it;
  }
  if(f1_addrs.size() > 0 && !mismatch) {
    long *addr = NULL;
    long val=0;
    // Did f1 write a non-zero value to a non-local address ?
    it = f1_addrs.begin();
    while(it!=f1_addrs.end()) { 
      if(it->second!=0) {
	addr=it->first;
	if( *addr == it->second) {
	  ++it;
	  continue;
	}
	val=it->second;
	break;
      } 
      ++it;
    }
    if(f1_ret_val == f2_ret_val && addr != NULL) {
      fprintf(trace, "f1 wrote to %p (val=0x%lx), f2 did not (val=0x%lx), ", 
	      addr, val, *addr);
      fprintf(trace, "replacing REG_RAX\n");
      fflush(trace);
      replaceRetVal(ctx);
      mismatch=true;
    }
  }
  if(!mismatch && f1_ret_val == f2_ret_val) {
    if(f1_syscalls.size() != f2_syscalls.size()) {
      fprintf(trace, "f1, f2 made unequal number of syscalls, replacing REG_RAX\n");
      replaceRetVal(ctx);
      mismatch = true;
    }
    for(unsigned int i=0;i<f1_syscalls.size(); i++) {
      if(f2_syscalls[i] != f1_syscalls[i]) {
	fprintf(trace, "f1 made syscall(%lu), f2 made syscall(%lu), replacing REG_RAX\n",
	       f1_syscalls[i],f2_syscalls[i]);
	replaceRetVal(ctx);
	mismatch = true;
	break;
      } else {
	syscallArgs sa1 = f1_syscall_args[i];
	syscallArgs sa2 = f2_syscall_args[i];
	if(sa1.numArgs != sa2.numArgs || sa1.syscallNum != sa2.syscallNum) {
	  fprintf(trace, "syscallArgs mismatch, panic!\n");
	  replaceRetVal(ctx);
	  mismatch = true;
	  break;
	}
	for(int j=0; j<sa1.numArgs; j++) {
	  long a = (long) sa1.args[j];
	  long b = (long) sa2.args[j];
	  if(!isGlobalAddr(a, f1_rsp) || !isGlobalAddr(b, f2_rsp)) continue;
	  // wait uses only the low 32 bits of its 1st and 3rd arguments
	  // similar hack is implemented in FuzzBALL
	  if(sa1.syscallNum == 61 && (j == 0 || j == 2)) {
	    a = (int) a; b = (int) b;
	  }
	  if(a != b) {
	    fprintf(trace, "syscallArgs mismatch on arg %d, %lx != %lx\n", j, a, b);
	    replaceRetVal(ctx);
	    mismatch = true;
	    break;
	  }
	}
	if(mismatch) break;
      }
    }
  }
  if(!mismatch) //fprintf(trace, "f1 <- f2\n");
  fflush(trace);
  cleanupAfterF2();
}

VOID Image(IMG img, VOID *v) {
  //fprintf(trace, "IMG_Name(img) = %s\n",IMG_Name(img).c_str());
  if (IMG_Name(img) == ProgramImage) {
    RTN f1Rtn = RTN_FindByName(img, f1Name.c_str());
    if (f1Rtn.is_valid()) {
      RTN_Open(f1Rtn);
      RTN_InsertCall(f1Rtn, IPOINT_BEFORE, (AFUNPTR)RecordF1Begin,
		     IARG_REG_VALUE, REG_STACK_PTR,
        IARG_END);
      RTN_InsertCall(f1Rtn, IPOINT_AFTER, (AFUNPTR)RecordF1End,
		     IARG_CONTEXT,
        IARG_END);
      RTN_Close(f1Rtn);
    } else { 
      fprintf(trace, "failed to add hooks for f1(%s), panic!\n", f1Name.c_str());
      fflush(trace);
    }

    RTN f2Rtn = RTN_FindByName(img, f2Name.c_str());
    if (f2Rtn.is_valid()) {
      RTN_Open(f2Rtn);
      RTN_InsertCall(f2Rtn, IPOINT_BEFORE, (AFUNPTR)RecordF2Begin,
		     IARG_REG_VALUE, REG_STACK_PTR,
        IARG_END);
      RTN_InsertCall(f2Rtn, IPOINT_AFTER, (AFUNPTR)RecordF2End,
		     IARG_CONTEXT,
        IARG_END);
      RTN_Close(f2Rtn);
    } else { 
      fprintf(trace, "failed to add hooks for f2(%s), panic!\n", f2Name.c_str());
      fflush(trace);
    }
  }
  fflush(trace);
}

VOID Fini(INT32 code, VOID *v) {
  //::fprintf(trace,"#eof\n");
  fclose(stdout);
}

// http://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
inline bool fileExists(const std::string& name) {
  ifstream f(name.c_str());
  return f.good();
}

void setupNoopSyscalls() {
  ifstream fin("noop_syscalls.lst");
  if(!fin.good()) return;
  int num;
  while(fin>>num) noopSyscalls[num]=true;
}

char *getUniqueLogFileName(char *fileName) {
  int i=0;
  while (true) {
    sprintf(fileName, "logs/pinmonitor%d.log", i);
    if(fileExists( fileName )) i++;
    else break;
  }
  return fileName;
}

int main(int argc, char * argv[]) {
  char fileName[100];
  if(logfile)
    trace = fopen(getUniqueLogFileName(fileName), "w");
  else trace=stdout;
  PIN_Init(argc, argv);
  PIN_InitSymbols();
  ProgramImage = argv[6];
  sscanf(argv[13], "0x%p", &sideEffectsEqualAddr);
  //f1Name = argv[13];
  //f2Name = argv[14];
  ////fprintf(trace, "f1Name = %s f2Name = %s\n", f1Name.c_str(), f2Name.c_str());
  //fprintf(trace, "sideEffectsEqualAddr = %p\n", sideEffectsEqualAddr);
  setupNoopSyscalls();
  INS_AddInstrumentFunction(Instruction, 0);
  IMG_AddInstrumentFunction(Image, NULL);
  PIN_AddFiniFunction(Fini, NULL);
  PIN_StartProgram();
}
