#include "pin.H"
#include <map>
#include <fstream>
#include <iostream>
using namespace std;


bool RecordF1 = false, RecordF2 = false;
string ProgramImage;
string f1Name, f2Name;

VOID ReadsMem (ADDRINT applicationIp, ADDRINT memoryAddressRead, UINT32 memoryReadSize) {
}

map< void *, long> f1_addrs, f2_addrs;
vector< ADDRINT> f1_syscalls, f2_syscalls;
void *f1_rsp=0, *f2_rsp=0;
UINT8 f1_ret_val, f2_ret_val;

VOID WritesMem (ADDRINT applicationIp, ADDRINT memoryAddressWrite, UINT32 memoryWriteSize, ADDRINT rsp_val) {
  string fname;
  if(RecordF1) fname="f1: ";
  else if(RecordF2) fname="f2: ";
  else return;
  if(RecordF1) 
    f1_addrs[(void *) memoryAddressWrite] = 0;
  if(RecordF2) 
    f2_addrs[(void *) memoryAddressWrite] = 0;
}

VOID RecordSyscall(ADDRINT applicationIp, ADDRINT syscallnum) {
  string fname;
  if(RecordF1) fname="f1: ";
  else if(RecordF2) fname="f2: ";
  else return;
  if(RecordF1) 
    f1_syscalls.push_back(syscallnum);
  if(RecordF2) 
    f2_syscalls.push_back(syscallnum);
  cout<<fname<<" called syscall("<<syscallnum<<")\n";
  fflush(stdout);
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
    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR) RecordSyscall,
		   IARG_INST_PTR,// application IP
		   IARG_SYSCALL_NUMBER,
		   IARG_END);
  }
}

VOID RecordF1Begin(ADDRINT rsp_val) {
  printf("f1 began, rsp_val = 0x%lx\n",rsp_val);
  RecordF1 = true;
  if(f1_rsp == 0) f1_rsp = (void *) rsp_val;
}

VOID RecordF1End(CONTEXT *ctx) {
  f1_ret_val = PIN_GetContextReg(ctx, REG_RAX);
  printf("f1 ended with retval = %d\n",f1_ret_val);
  RecordF1 = false;
  bool isglobal=false;
  map<void *, long> :: iterator it = f1_addrs.begin();
  while(it!=f1_addrs.end()) {
    isglobal=false;
    if( (((long) f1_rsp) & 0x7ffe00000000) == 0) printf("panic, cannot classify write address\n");
    else {
      if ( (((long) it->first) & 0x7ffe00000000) == 0) isglobal=true;
	//printf("global write\n");
      //else printf("local write\n");
    }
    if(isglobal) {
      printf("f1write: mem[%p] = %lx\n", it->first, *(long *)(it->first));
      it->second = *(long *) it->first;
    }
    ++it;
  }
}

VOID RecordF2Begin(ADDRINT rsp_val) {
  printf("f2 began, rsp_val = 0x%lx\n",rsp_val);
  RecordF2 = true;
  if(f2_rsp ==0 ) f2_rsp = (void *) rsp_val;
}

long getF1Val(void *f2_addr, bool &found) {
  found=true;
  map<void *, long> :: iterator it = f1_addrs.begin();
  while(it!=f1_addrs.end()) {
    if(it->first == f2_addr) return it->second;
    ++it;
  }
  found=false;
  return -1;
}

void *containsNonLocalAddr(map <void *, long> m) {
  map<void *, long> :: iterator it = m.begin();
  while(it!=m.end()) {
    if ( (((long) it->first) & 0x7ffe00000000) == 0) return it->first;
    ++it;
  }
  return NULL;
}

void replaceRetVal(CONTEXT *ctx) {
  UINT8 t;
  t = f1_ret_val + 1;
  PIN_SetContextRegval(ctx, REG_RAX, &t);
  PIN_ExecuteAt(ctx);
}

void cleanupAfterF2() {
  fflush(stdout);
  f1_addrs.clear();
  f2_addrs.clear();
  f1_syscalls.clear();
  f2_syscalls.clear();
  RecordF2 = false;
}

VOID RecordF2End(CONTEXT *ctx) {
  // PIN_GetContextRegval(ctx, REG_RAX, &f2_ret_val);
  bool mismatch=false;
  f2_ret_val = PIN_GetContextReg(ctx, REG_RAX);
  printf("f2 ended with retval = %d\n",f2_ret_val);
  if(f1_ret_val != f2_ret_val) {
    cleanupAfterF2();
    return;
  }
  bool isglobal=false;
  map<void *, long> :: iterator it = f2_addrs.begin();
  while(it!=f2_addrs.end()) {
    isglobal=false;
    if( (((long) f2_rsp) & 0x7ffe00000000) == 0) 
      printf("panic, cannot classify write address\n");
    else {
      if ( (((long) it->first) & 0x7ffe00000000) == 0) isglobal=true;
	//printf("global write\n");
      //else printf("local write\n");
    }
    if(isglobal) {
      bool found;
      long f1_val = getF1Val(it->first, found);
      long f2_val = *(long *)(it->first);
      printf("f2write: mem[%p] = %lx ;", it->first, f2_val);
      if(!found || (found && (f1_val != f2_val)) ) { 
	printf("unequal values written, 0x%lx, 0x%lx, ", f1_val, f2_val);
	if(f1_ret_val == f2_ret_val) {
	  printf("replacing REG_RAX\n");
	  fflush(stdout);
	  replaceRetVal(ctx);
	  mismatch=true;
	  break;
	}
      }
      else {
	printf("equal values written\n");
	f1_addrs.erase(it->first);
      }
    }
    ++it;
  }
  if(f1_addrs.size() > 0 && !mismatch) {
    void *addr = containsNonLocalAddr(f1_addrs);
    if(f1_ret_val == f2_ret_val && addr != NULL) {
      printf("f1 wrote to %p, f2 did not, ", addr);
      printf("replacing REG_RAX\n");
      fflush(stdout);
      replaceRetVal(ctx);
      mismatch=true;
    }
  }
  if(!mismatch && f1_ret_val == f2_ret_val) {
    if(f1_syscalls.size() != f2_syscalls.size()) {
      printf("f1, f2 made unequal number of syscalls, replacing REG_RAX\n");
      replaceRetVal(ctx);
      mismatch = true;
    }
    for(unsigned int i=0;i<f1_syscalls.size(); i++) {
      if(f2_syscalls[i] != f1_syscalls[i]) {
	printf("f1 made syscall(%lu), f2 made syscall(%lu), replacing REG_RAX\n",
	       f1_syscalls[i],f2_syscalls[i]);
	replaceRetVal(ctx);
	mismatch = true;
	break;
      }
    }
  }
  cleanupAfterF2();
}

VOID Image(IMG img, VOID *v) {
  cout<<"IMG_Name(img) = "<<IMG_Name(img)<<endl;
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
    }
  }
}

VOID Fini(INT32 code, VOID *v) {
}

int main(int argc, char * argv[]) {
  PIN_Init(argc, argv);
  PIN_InitSymbols();
  ProgramImage = argv[6];
  f1Name = argv[13];
  f2Name = argv[14];
  INS_AddInstrumentFunction(Instruction, 0);
  IMG_AddInstrumentFunction(Image, NULL);
  PIN_AddFiniFunction(Fini, NULL);
  PIN_StartProgram();
}
