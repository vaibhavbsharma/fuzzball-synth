#ifndef _SIGNALHANDLERS_H
#define _SIGNALHANDLERS_H
 /*BEGIN_LEGAL
Intel Open Source License 

Copyright (c) 2002-2016 Intel Corporation. All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.  Redistributions
in binary form must reproduce the above copyright notice, this list of
conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.  Neither the name of
the Intel Corporation nor the names of its contributors may be used to
endorse or promote products derived from this software without
specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE INTEL OR
ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
END_LEGAL */
// features.h does not exist on FreeBSD
#ifndef TARGET_BSD
// features initializes the system's state, including the state of __USE_GNU
#include <features.h>
#endif

// If __USE_GNU is defined, we don't need to do anything.
// If we defined it ourselves, we need to undefine it later.
#ifndef __USE_GNU
    #define __USE_GNU
    #define APP_UNDEF_USE_GNU
#endif

#include <sys/ucontext.h>

// If we defined __USE_GNU ourselves, we need to undefine it here.
#ifdef APP_UNDEF_USE_GNU
    #undef __USE_GNU
    #undef APP_UNDEF_USE_GNU
#endif


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>

#ifdef TARGET_IA32
#define REG_IP REG_EIP
#else
#define REG_IP REG_RIP
#endif

void *DivideByZeroRetPoint;
int DivideByZero()
{
    unsigned int i;
    volatile unsigned int zero = 0;
    fprintf(stderr, "Going to divide by zero\n");
    i  = 1 / zero;
    return i/i;
} 

#define DIV_OPCODE 0xf7
#define MODRM_REG   0xc0
#define MODRM_DISP8 0x40
#define MODRM_DISP32 0x80

#define IS_REG_MODE(modrmByte) ((modrmByte & MODRM_REG) == MODRM_REG)
#define IS_DISP8_MODE(modrmByte) ((modrmByte & MODRM_DISP8) == MODRM_DISP8)
#define IS_DISP32_MODE(modrmByte) ((modrmByte & MODRM_DISP32) == MODRM_DISP32)

extern long sideEffectsEqual;
extern jmp_buf  JumpBuffer;

void div0_signal_handler(int signum, siginfo_t *siginfo, void *uctxt) 
{
  printf("Inside div0 handler\n");
  ucontext_t *frameContext = (ucontext_t *)uctxt;
  
  unsigned char *bytes = (unsigned char *)frameContext->uc_mcontext.gregs[REG_IP];
  int opcode_ind=bytes[0]==DIV_OPCODE ? 0 : (bytes[1]==DIV_OPCODE ? 1 : -1);
  //if (bytes[0] == DIV_OPCODE)
  if (opcode_ind != -1) {
    sideEffectsEqual=0;
    if (IS_REG_MODE(bytes[opcode_ind+1])) {
      printf("div %reg instruction\n");
      // set IP pointing to the next instruction
      frameContext->uc_mcontext.gregs[REG_IP] += 2;
      return;
    }
    if (IS_DISP8_MODE(bytes[opcode_ind+1])) {
      printf("div mem8 instruction\n");
      // set IP pointing to the next instruction
      frameContext->uc_mcontext.gregs[REG_IP] += 3;
      return;
    }
    if (IS_DISP32_MODE(bytes[opcode_ind+1])) {
      printf("div mem32 instruction\n");
      // set IP pointing to the next instruction
      frameContext->uc_mcontext.gregs[REG_IP] += 6;
      return;
    }            
  }
    printf("Unexpected instruction at address 0x%lx\n", (unsigned long)frameContext->uc_mcontext.gregs[REG_IP]);
    printf("bytes[0,1,2] = [0x%x, 0x%x, 0x%x]\n", bytes[0], bytes[1], bytes[2]);
    exit(-1);
}

void segv_signal_handler(int signum, siginfo_t *siginfo, void *uctxt) {
  ucontext_t *frameContext = (ucontext_t *)uctxt;
  printf("Inside segv handler: 0x%lx\n", (unsigned long)frameContext->uc_mcontext.gregs[REG_IP]);
  fflush(stdout);
  siglongjmp(JumpBuffer, -1);       /* return to the setjmp mark*/
  
  // unsigned char *bytes = (unsigned char *)frameContext->uc_mcontext.gregs[REG_IP];
  // int opcode_ind;
  // if(bytes[0]==0x0f && bytes[1]==0xb6) opcode_ind=1;
  // else if(bytes[1]==0x0f && bytes[2]==0xb6) opcode_ind=2;
  // //signal(SIGSEGV, segv_signal_handler);   /* reinstall before return  */
  // if (opcode_ind != -1) {
  //   sideEffectsEqual=0;
  //   //siglongjmp(JumpBuffer, -1);       /* return to the setjmp mark*/
  //   // if (IS_REG_MODE(bytes[opcode_ind+1])) {
  //   //   printf("movzx %reg instruction\n");
  //   //   fflush(stdout);
  //   //   // set IP pointing to the next instruction
  //   //   frameContext->uc_mcontext.gregs[REG_IP] += 2;
  //   //   return;
  //   // }
  //   // // if (IS_DISP8_MODE(bytes[opcode_ind+1])) {
  //   // //   printf("movzx mem8 instruction\n");
  //   // //   fflush(stdout);
  //   // //   // set IP pointing to the next instruction
  //   // //   frameContext->uc_mcontext.gregs[REG_IP] += 3;
  //   // //   return;
  //   // // }
  //   // if (IS_DISP32_MODE(bytes[opcode_ind+1])) {
  //   //   printf("movzx mem32 instruction\n");
  //   //   fflush(stdout);
  //   //   // set IP pointing to the next instruction
  //   //   frameContext->uc_mcontext.gregs[REG_IP] += 6;
  //   //   return;
  //   // }           
  //   // printf("dont know movzx instruction, guessing IP+5\n");
  //   // fflush(stdout);
  //   // frameContext->uc_mcontext.gregs[REG_IP] += 5;
  //   // return;
  // }
  // printf("Unexpected instruction at address 0x%lx\n", (unsigned long)frameContext->uc_mcontext.gregs[REG_IP]);
  // printf("bytes[0,1,2] = [0x%x, 0x%x, 0x%x]\n", bytes[0], bytes[1], bytes[2]);
  // fflush(stdout);
  // exit(-1);
}
#endif