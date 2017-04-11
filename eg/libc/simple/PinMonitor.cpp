#include "pin.H"
#include <map>
#include <fstream>
#include <iostream>
using namespace std;

std::map<ADDRINT, std::string> disAssemblyMap;

#define MALLOC "asdf_malloc"
#define FREE "asdf_free"
#define F1 "_f1"
#define F2 "_f2"

bool RecordF1 = false, RecordF2 = false;
string ProgramImage;

VOID ReadsMem (ADDRINT applicationIp, ADDRINT memoryAddressRead, UINT32 memoryReadSize) {
  // printf ("0x%lx %s reads %d bytes of memory at 0x%lx\n",
  // 	  applicationIp, disAssemblyMap[applicationIp].c_str(),
  // 	  memoryReadSize, memoryAddressRead);
}

map< void *, long> f1_addrs, f2_addrs;
map< ADDRINT, bool> f1_syscalls, f2_syscalls;
void *f1_rsp=0, *f2_rsp=0;
UINT8 f1_ret_val, f2_ret_val;

VOID WritesMem (ADDRINT applicationIp, ADDRINT memoryAddressWrite, UINT32 memoryWriteSize, ADDRINT rsp_val) {
  string fname;
  if(RecordF1) fname="f1: ";
  else if(RecordF2) fname="f2: ";
  else return;
  // printf ("%s0x%lx %s wrote %d bytes of memory at 0x%lx, rsp = 0x%lx\n", fname.c_str(), 
  //  	  applicationIp, disAssemblyMap[applicationIp].c_str(),
  //  	  memoryWriteSize, memoryAddressWrite, rsp_val);
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
    f1_syscalls[syscallnum] = true;
  if(RecordF2) 
    f2_syscalls[syscallnum] = true;
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
  map<void *, long> :: iterator it = f2_addrs.begin();
  while(it!=f2_addrs.end()) {
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

VOID RecordF2End(CONTEXT *ctx) {
  // PIN_GetContextRegval(ctx, REG_RAX, &f2_ret_val);
  bool mismatch=false;
  f2_ret_val = PIN_GetContextReg(ctx, REG_RAX);
  printf("f2 ended with retval = %d\n",f2_ret_val);
  RecordF2 = false;
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
    map <ADDRINT, bool> :: iterator it = f1_syscalls.begin();
    while(it!=f1_syscalls.end()) {
      if(f2_syscalls.find(it->first) == f2_syscalls.end()) {
	printf("f1 made syscall %d, f2 did not, replacing REG_RAX\n", (int) it->first);
	replaceRetVal(ctx);
	mismatch = true;
      } else f2_syscalls.erase(it->first);
      ++it;
    }
    if(!mismatch && f2_syscalls.size() > 0) {
      printf("f2 made syscall %d, f1 did not, replacing REG_RAX\n", (int) f2_syscalls.begin()->first);
      replaceRetVal(ctx);
      mismatch = true;
    }
  }
  f1_addrs.clear();
  f2_addrs.clear();
  f1_syscalls.clear();
  f2_syscalls.clear();
  fflush(stdout);
}

VOID Image(IMG img, VOID *v) {
  cout<<"IMG_Name(img) = "<<IMG_Name(img)<<endl;
  if (IMG_Name(img) == ProgramImage) {
    RTN f1Rtn = RTN_FindByName(img, F1);
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
    RTN f2Rtn = RTN_FindByName(img, F2);
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
  INS_AddInstrumentFunction(Instruction, 0);
  IMG_AddInstrumentFunction(Image, NULL);
  PIN_AddFiniFunction(Fini, NULL);
  PIN_StartProgram();
}
