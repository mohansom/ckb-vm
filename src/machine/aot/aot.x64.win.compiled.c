/*
** This file has been pre-processed with DynASM.
** https://luajit.org/dynasm.html
** DynASM version 1.4.0, DynASM x64 version 1.4.0
** DO NOT EDIT! The original file is in "src/machine/aot/aot.x64.c".
*/

#line 1 "src/machine/aot/aot.x64.c"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "dasm_proto.h"
#include "dasm_x86.h"

#include "cdefinitions_generated.h"

#if (defined(_WIN32) != 1)
#error "Wrong DynASM flags used: pass -D WIN to dynasm.lua to generate windows specific file"
#endif

#define ERROR_INVALID_MEMORY_SIZE 0xFFFFFF00
#define ERROR_NOT_ENOUGH_LABELS 0xFFFFFF01
#define ERROR_INVALID_VALUE 0xFFFFFF02

//|.arch x64
#if DASM_VERSION != 10400
#error "Version mismatch between DynASM and included encoding engine"
#endif
#line 19 "src/machine/aot/aot.x64.c"
//|.section code
#define DASM_SECTION_CODE	0
#define DASM_MAXSECTION		1
#line 20 "src/machine/aot/aot.x64.c"
//|.globals lbl_
enum {
  lbl_zeroed_memory,
  lbl_check_write,
  lbl_check_read,
  lbl_exit,
  lbl__MAX
};
#line 21 "src/machine/aot/aot.x64.c"
//|.actionlist bf_actions
static const unsigned char bf_actions[1611] = {
  254,0,65,84,65,85,65,86,65,87,83,85,87,86,72,137,207,72,137,208,72,139,183,
  233,76,139,135,233,76,139,143,233,252,255,224,255,248,10,87,86,80,81,82,65,
  80,65,81,72,131,252,236,32,72,193,225,235,72,141,151,233,72,1,209,72,137,
  201,72,49,210,73,199,192,237,72,184,237,237,252,255,208,72,131,196,32,65,
  89,65,88,90,89,88,94,95,195,255,248,11,86,65,80,72,137,214,72,137,193,72,
  193,252,233,235,255,72,129,252,249,239,15,131,244,249,72,141,151,233,15,182,
  20,10,129,226,239,129,252,250,239,15,133,244,250,255,72,193,252,233,235,72,
  141,151,233,68,15,182,4,10,65,131,252,248,0,15,133,244,247,198,4,10,1,232,
  244,10,248,1,255,72,137,194,72,1,252,242,72,131,252,234,1,72,193,252,234,
  235,72,131,193,1,72,57,209,15,133,244,248,255,72,129,252,249,239,15,131,244,
  249,72,141,151,233,15,182,20,10,129,226,239,129,252,250,239,15,133,244,250,
  72,193,252,233,235,72,141,151,233,68,15,182,4,10,65,131,252,248,0,15,133,
  244,248,198,4,10,1,232,244,10,248,2,72,199,194,0,0,0,0,65,88,94,195,248,3,
  72,199,194,237,65,88,94,195,248,4,72,199,194,237,255,65,88,94,195,255,248,
  12,86,65,80,72,137,193,72,193,252,233,235,72,129,252,249,239,15,131,244,249,
  72,141,183,233,68,15,182,4,14,65,131,252,248,0,15,133,244,247,198,4,14,1,
  232,244,10,248,1,72,137,193,72,1,209,72,131,252,233,1,72,193,252,233,235,
  72,129,252,249,239,15,131,244,249,68,15,182,4,14,65,131,252,248,0,15,133,
  244,248,198,4,14,1,232,244,10,255,252,233,244,248,248,2,72,199,194,0,0,0,
  0,65,88,94,195,248,3,72,199,194,237,65,88,94,195,255,248,13,72,137,183,233,
  76,137,135,233,76,137,143,233,94,95,93,91,65,95,65,94,65,93,65,92,195,255,
  249,255,72,1,192,240,131,240,35,255,72,3,135,253,240,131,233,255,72,1,135,
  253,240,131,233,255,72,139,135,233,72,1,135,233,255,72,184,237,237,255,72,
  1,192,240,35,255,72,129,192,240,35,239,255,72,129,135,233,239,255,72,41,192,
  240,131,240,35,255,72,43,135,253,240,131,233,255,72,41,135,253,240,131,233,
  255,72,139,135,233,72,41,135,233,255,72,41,192,240,35,255,72,129,232,240,
  35,239,255,72,129,175,233,239,255,72,15,175,192,240,36,255,72,15,175,135,
  233,255,72,185,237,237,255,72,199,193,237,255,72,15,175,193,255,72,137,192,
  240,35,255,72,137,135,233,255,72,252,247,232,240,35,255,72,252,247,175,233,
  255,72,252,247,224,240,35,255,72,252,247,167,233,255,72,252,247,252,233,255,
  72,252,247,225,255,72,137,208,240,35,255,72,137,151,233,255,72,133,192,15,
  137,244,247,255,72,252,247,216,255,72,131,252,242,252,255,72,137,209,255,
  72,186,237,237,255,72,15,175,194,255,72,133,192,15,148,208,72,15,182,192,
  255,72,1,200,252,233,244,248,255,72,137,208,248,2,255,72,57,200,15,133,244,
  247,72,199,192,252,255,252,255,252,255,252,255,255,72,57,200,15,133,244,247,
  255,252,233,244,249,255,248,1,72,199,192,0,0,0,0,255,72,57,200,15,133,244,
  248,255,72,199,192,240,35,237,255,72,199,135,233,237,255,252,233,244,249,
  248,2,255,72,153,255,72,252,247,252,248,240,35,255,72,252,247,191,233,255,
  72,49,210,255,72,252,247,252,240,240,35,255,72,252,247,183,233,255,72,153,
  72,252,247,252,249,255,72,49,210,72,252,247,252,241,255,72,153,72,252,247,
  252,248,240,35,255,72,49,210,72,252,247,252,240,240,35,255,248,3,255,72,33,
  192,240,131,240,35,255,72,35,135,253,240,131,233,255,72,33,135,253,240,131,
  233,255,72,139,135,233,72,33,135,233,255,72,33,192,240,35,255,72,129,224,
  240,35,239,255,72,129,167,233,239,255,72,9,192,240,131,240,35,255,72,11,135,
  253,240,131,233,255,72,9,135,253,240,131,233,255,72,139,135,233,72,9,135,
  233,255,72,9,192,240,35,255,72,129,200,240,35,239,255,72,129,143,233,239,
  255,72,252,247,208,240,35,255,72,252,247,151,233,255,72,49,192,240,131,240,
  35,255,72,51,135,253,240,131,233,255,72,49,135,253,240,131,233,255,72,139,
  135,233,72,49,135,233,255,72,49,192,240,35,255,72,129,252,240,240,35,239,
  255,72,129,183,233,239,255,72,137,193,240,131,255,72,139,143,233,255,185,
  237,255,72,211,224,240,35,255,72,211,167,233,255,72,211,252,248,240,35,255,
  72,211,191,233,255,72,211,232,240,35,255,72,211,175,233,255,72,211,192,240,
  35,255,72,211,135,233,255,72,211,200,240,35,255,72,211,143,233,255,72,57,
  193,240,131,255,72,59,143,233,255,72,199,192,237,255,72,57,193,255,15,148,
  209,72,15,182,201,255,72,137,200,240,35,255,72,137,143,233,255,15,156,209,
  255,15,146,209,255,72,57,192,240,35,255,72,57,135,233,255,72,129,252,248,
  240,35,239,255,72,129,191,233,239,255,252,233,244,248,248,1,255,72,131,252,
  248,240,35,1,15,133,244,247,255,72,131,252,248,0,15,132,244,247,72,15,189,
  192,72,252,247,216,72,131,192,63,255,252,233,244,248,248,2,255,72,131,252,
  248,0,15,132,244,247,72,15,188,192,255,252,243,72,15,184,192,255,128,225,
  127,128,252,249,63,15,142,244,247,128,252,233,64,72,49,208,72,49,194,72,49,
  208,248,1,128,252,249,0,15,133,244,248,252,233,244,249,248,2,72,211,224,252,
  246,217,128,193,64,72,211,252,234,72,9,208,248,3,255,128,225,127,128,252,
  249,63,15,142,244,247,128,252,233,64,72,49,208,72,49,194,72,49,208,248,1,
  128,252,249,0,15,133,244,248,252,233,244,249,248,2,72,211,232,252,246,217,
  128,193,64,72,211,226,72,9,208,248,3,255,72,99,192,255,137,192,255,185,64,
  0,0,0,131,226,63,41,209,72,211,224,137,209,255,72,211,252,248,255,72,211,
  232,255,72,193,224,235,255,72,193,252,248,235,255,72,193,232,235,255,72,137,
  194,240,131,185,64,0,0,0,131,226,63,41,209,72,211,224,137,209,255,72,199,
  192,237,252,233,244,13,255,72,1,135,233,72,139,135,233,72,57,135,233,15,134,
  244,247,255,72,199,135,233,237,252,233,245,255,72,137,135,253,240,131,233,
  255,72,199,194,237,232,244,11,72,131,252,250,0,15,133,244,247,72,141,151,
  233,255,136,12,2,255,102,137,12,2,255,72,137,12,2,255,252,233,244,248,248,
  1,72,137,208,252,233,244,13,248,2,255,72,199,194,237,232,244,12,72,131,252,
  250,0,15,133,244,247,72,137,194,72,129,194,239,15,130,244,247,72,129,252,
  250,239,255,15,135,244,247,255,15,131,244,247,255,15,182,12,2,255,15,183,
  12,2,255,139,12,2,255,72,139,12,2,255,72,137,192,240,131,240,35,255,72,139,
  135,253,240,131,233,255,72,139,135,253,240,131,233,72,137,135,253,240,131,
  233,255,72,184,240,34,237,237,255
};

#line 22 "src/machine/aot/aot.x64.c"

typedef struct {
  dasm_State* d;
  void* labels[lbl__MAX];
  uint32_t npc;
  uint32_t version;
} AotContext;

/*
 * RISC-V has 32 general purpose registers, rax, rcx * and rdx are set aside
 * for x64 level work. PC is handled separately so we can inline jumps.
 * Besides that, we also have other temporary registers for handling AST
 * intermediate nodes.
 *
 */
#define REGISTER_ZERO 0
#define REGISTER_RA 1
#define REGISTER_SP 2
#define REGISTER_GP 3
#define REGISTER_TP 4
#define REGISTER_T0 5
#define REGISTER_T1 6
#define REGISTER_T2 7
#define REGISTER_S0 8
#define REGISTER_S1 9
#define REGISTER_A0 10
#define REGISTER_A1 11
#define REGISTER_A2 12
#define REGISTER_A3 13
#define REGISTER_A4 14
#define REGISTER_A5 15
#define REGISTER_A6 16
#define REGISTER_A7 17
#define REGISTER_S2 18
#define REGISTER_S3 19
#define REGISTER_S4 20
#define REGISTER_S5 21
#define REGISTER_S6 22
#define REGISTER_S7 23
#define REGISTER_S8 24
#define REGISTER_S9 25
#define REGISTER_S10 26
#define REGISTER_S11 27
#define REGISTER_T3 28
#define REGISTER_T4 29
#define REGISTER_T5 30
#define REGISTER_T6 31
#define REGISTER_TEMP1 32
#define REGISTER_TEMP2 33
#define REGISTER_TEMP3 34
#define REGISTER_TEMP4 35
#define MAXIMUM_REGISTER 35
#define INVALID_REGISTER (MAXIMUM_REGISTER + 1)
#define VALID_REGISTER(r) ((r) <= MAXIMUM_REGISTER)

#define X64_RAX 0
#define X64_RCX 1
#define X64_RDX 2
#define X64_RBX 3
#define X64_RSP 4
#define X64_RBP 5
#define X64_RSI 6
#define X64_RDI 7
#define X64_R8 8
#define X64_R9 9
#define X64_R10 10
#define X64_R11 11
#define X64_R12 12
#define X64_R13 13
#define X64_R14 14
#define X64_R15 15
#define MAXIMUM_X64_REGISTER 15
#define INVALID_X64_REGISTER (MAXIMUM_X64_REGISTER + 1)
#define VALID_X64_REGISTER(r) ((r) <= MAXIMUM_X64_REGISTER)

typedef struct {
  uint64_t registers[32];
  uint64_t pc;
  uint8_t running;
  uint64_t cycles;
  uint64_t max_cycles;
  uint8_t isa;
  uint32_t version;
  uint8_t flags[CKB_VM_ASM_RISCV_PAGES];
  uint8_t memory[CKB_VM_ASM_RISCV_MAX_MEMORY];
  uint8_t frames[CKB_VM_ASM_MEMORY_FRAMES];
  /* We won't access traces here */
  uint8_t _traces[CKB_VM_ASM_ASM_CORE_MACHINE_STRUCT_SIZE -
                  CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_TRACES];
} AsmMachine;

#define AOT_TAG_REGISTER 0x1
#define AOT_TAG_IMMEDIATE 0x2
#define AOT_TAG_X64_REGISTER 0x3

typedef uint32_t riscv_register_t;
typedef int32_t x64_register_t;

typedef struct {
  uint32_t tag;
  union {
    riscv_register_t reg;
    uint64_t i;
    x64_register_t x64_reg;
  } value;
} AotValue;

int aot_value_is_riscv_register(AotValue v, riscv_register_t r)
{
  return (v.tag == AOT_TAG_REGISTER) && (v.value.reg == r);
}

x64_register_t riscv_reg_to_x64_reg(riscv_register_t r)
{
  switch (r) {
    case REGISTER_RA:
      return X64_RSI;
    case REGISTER_SP:
      return X64_R8;
    case REGISTER_A0:
      return X64_R9;
    case REGISTER_TEMP1:
      return X64_R10;
    case REGISTER_TEMP2:
      return X64_R11;
    case REGISTER_TEMP3:
      return X64_R12;
    case REGISTER_TEMP4:
      return X64_R13;
    default:
      return INVALID_X64_REGISTER;
  }
}

//|.type machine, AsmMachine, rdi
#define Dt1(_V) (int)(ptrdiff_t)&(((AsmMachine *)0)_V)
#line 157 "src/machine/aot/aot.x64.c"

//|.macro load_imm64, x64_reg, imm64
//| mov64 x64_reg, imm64
//|.endmacro

/* We can leverage sign extension to save bits when handling negative integers */
//|.macro load_imm, x64_reg, imm
//||if (imm > 0xFFFFFFFF && ((imm & 0xFFFFFFFF80000000) != 0xFFFFFFFF80000000)) {
//|   load_imm64 x64_reg, imm
//||} else {
//|   mov x64_reg, imm
//||}
//|.endmacro

/* r_r means both operands here are RISC-V registers */
//|.macro op2_r_r, op, target, source, x64_temp_reg
//||loc1 = riscv_reg_to_x64_reg(target);
//||loc2 = riscv_reg_to_x64_reg(source);
//||if (VALID_X64_REGISTER(loc1) && VALID_X64_REGISTER(loc2)) {
//|  op Rq(loc1), Rq(loc2)
//||} else if (VALID_X64_REGISTER(loc1)) {
//|  op Rq(loc1), machine->registers[source]
//||} else if (VALID_X64_REGISTER(loc2)) {
//|  op machine->registers[target], Rq(loc2)
//||} else {
//|  mov x64_temp_reg, qword machine->registers[source]
//|  op qword machine->registers[target], x64_temp_reg
//||}
//|.endmacro

//|.macro op1_r, op, reg
//||loc1 = riscv_reg_to_x64_reg(reg);
//||if (VALID_X64_REGISTER(loc1)) {
//|  op Rq(loc1)
//||} else {
//|  op qword machine->registers[reg]
//||}
//|.endmacro

/* r_x means that the first operand is RISC-V register, the second is X86 one */
//|.macro op2_r_x, op, target, x64_source
//||loc1 = riscv_reg_to_x64_reg(target);
//||if (VALID_X64_REGISTER(loc1)) {
//|  op Rq(loc1), x64_source
//||} else {
//|  op qword machine->registers[target], x64_source
//||}
//|.endmacro

//|.macro op2_r_imm, op, target, imm, x64_temp_reg
//||if (imm > 0xFFFFFFFF && ((imm & 0xFFFFFFFF80000000) != 0xFFFFFFFF80000000)) {
//||  loc1 = riscv_reg_to_x64_reg(target);
//|   load_imm64 x64_temp_reg, imm
//||  if (VALID_X64_REGISTER(loc1)) {
//|     op Rq(loc1), x64_temp_reg
//||  } else {
//|     op qword machine->registers[target], x64_temp_reg
//||  }
//||} else {
//||  loc1 = riscv_reg_to_x64_reg(target);
//||  if (VALID_X64_REGISTER(loc1)) {
//|     op Rq(loc1), imm
//||  } else {
//|     op qword machine->registers[target], imm
//||  }
//||}
//|.endmacro

//|.macro op2_x_r, op, x64_target, source
//||loc1 = riscv_reg_to_x64_reg(source);
//||if (VALID_X64_REGISTER(loc1)) {
//|  op x64_target, Rq(loc1)
//||} else {
//|  op x64_target, machine->registers[source]
//||}
//|.endmacro

AotContext* aot_new(uint32_t npc, uint32_t version)
{
  dasm_State** Dst;
  AotContext* context = malloc(sizeof(AotContext));
  context->npc = npc;
  context->version = version;
  dasm_init(&context->d, DASM_MAXSECTION);
  dasm_setupglobal(&context->d, context->labels, lbl__MAX);
  dasm_setup(&context->d, bf_actions);
  dasm_growpc(&context->d, context->npc);
  Dst = &context->d;

  //|.if WIN
    //|.define rArg1, rcx
    //|.define rArg2, rdx
    //|.define rArg3, r8
  //|.else
    //|.define rArg1, rdi
    //|.define rArg2, rsi
    //|.define rArg3, rdx
  //|.endif
  //|.macro prepcall
    //| push rdi
    //| push rsi
    //| push rax
    //| push rcx
    //| push rdx
    //| push r8
    //| push r9
    //|.if WIN
      //| sub rsp, 32
    //|.endif
  //|.endmacro
  //|.macro postcall
    //|.if WIN
      //| add rsp, 32
    //|.endif
    //| pop r9
    //| pop r8
    //| pop rdx
    //| pop rcx
    //| pop rax
    //| pop rsi
    //| pop rdi
  //|.endmacro

  /*
   * The function we are generating has the following prototype:
   *
   * uint8_t execute_aot_code(AsmMachine* machine, uint64_t offset);
   *
   * +machine+ here contains the actual data used by the VM, offset specify
   * the location in the x64 assembly to jump to so as to start execution, it
   * should be derived from a label associated with the binary.
   * In System V AMD64 ABI, the first argument is already kept in rdi, so we
   * don't need any tweak on AsmMachine variable, the second argument is kept
   * in rsi, since we would keep RISC-V register RA in rsi, we first copy rsi
   * to rax for latter jumps.
   * As shown in aot_exit, the return result is kept in rax.
   */
  //|.code
  dasm_put(Dst, 0);
#line 295 "src/machine/aot/aot.x64.c"
  //| push r12
  //| push r13
  //| push r14
  //| push r15
  //| push rbx
  //| push rbp
  //|.if WIN
    //| push rdi
    //| push rsi
    //| mov rdi, rcx
    //| mov rax, rdx
  //|.else
    //| mov rax, rsi
  //|.endif
  //| mov rsi, machine->registers[REGISTER_RA]
  //| mov r8, machine->registers[REGISTER_SP]
  //| mov r9, machine->registers[REGISTER_A0]
  //| jmp rax
  dasm_put(Dst, 2, Dt1(->registers[REGISTER_RA]), Dt1(->registers[REGISTER_SP]), Dt1(->registers[REGISTER_A0]));
#line 313 "src/machine/aot/aot.x64.c"
  return context;
}

void aot_finalize(AotContext* context)
{
  dasm_free(&context->d);
  free(context);
}

int aot_link(AotContext* context, size_t *szp)
{
  dasm_State** Dst = &context->d;

  /*
   * Fill the specified frame with zeros. Required arguments to this
   * pseudo function include:
   *
   * rcx: index of the frame
   */
  //|->zeroed_memory:
  //| prepcall
  //| shl rcx, CKB_VM_ASM_MEMORY_FRAME_SHIFTS
  //| lea rArg2, machine->memory
  //| add rcx, rArg2
  //| mov rArg1, rcx
  //| xor rArg2, rArg2
  //| mov rArg3, CKB_VM_ASM_MEMORY_FRAMESIZE
  //| mov64 rax, (uint64_t)memset
  //| call rax
  //| postcall
  //| ret
  dasm_put(Dst, 36, CKB_VM_ASM_MEMORY_FRAME_SHIFTS, Dt1(->memory), CKB_VM_ASM_MEMORY_FRAMESIZE, (unsigned int)((uint64_t)memset), (unsigned int)(((uint64_t)memset)>>32));
#line 344 "src/machine/aot/aot.x64.c"
  /*
   * Check memory write permissions. Note this pseudo function does not use
   * C's standard calling convention, since the AOT code here has its own
   * register allocations for maximum performance. Required arguments to this
   * pseudo function include:
   *
   * rax: the memory address to check for permissions
   * rdx: length of memory to write
   *
   * The return value is kept in rdx, 0 means success, while non-zero values
   * mean permission check fails.
   *
   * Note the free register rcx might also be modified in this pseudo function.
   */
  //|->check_write:
  //| push rsi
  //| push r8
  //| mov rsi, rdx
  //| mov rcx, rax
  //| shr rcx, CKB_VM_ASM_RISCV_PAGE_SHIFTS
  dasm_put(Dst, 95, CKB_VM_ASM_RISCV_PAGE_SHIFTS);
#line 364 "src/machine/aot/aot.x64.c"
  /*
   * Test if the page stored in rcx is out of bound, and if the page has
   * correct write permissions
   */
  //| cmp rcx, CKB_VM_ASM_RISCV_PAGES
  //| jae >3
  //| lea rdx, machine->flags
  //| movzx edx, byte [rdx+rcx]
  //| and edx, CKB_VM_ASM_MEMORY_FLAG_WXORX_BIT
  //| cmp edx, CKB_VM_ASM_MEMORY_FLAG_WRITABLE
  //| jne >4
  dasm_put(Dst, 112, CKB_VM_ASM_RISCV_PAGES, Dt1(->flags), CKB_VM_ASM_MEMORY_FLAG_WXORX_BIT, CKB_VM_ASM_MEMORY_FLAG_WRITABLE);
#line 375 "src/machine/aot/aot.x64.c"
  /*
   * If the frame not initialized, then initialize it.
   */
  //| shr rcx, CKB_VM_ASM_MEMORY_FRAME_PAGE_SHIFTS
  //| lea rdx, machine->frames
  //| movzx r8d, byte [rdx+rcx]
  //| cmp r8d, 0
  //| jne >1
  //| mov byte [rdx+rcx], 1
  //| call ->zeroed_memory
  //|1:
  dasm_put(Dst, 141, CKB_VM_ASM_MEMORY_FRAME_PAGE_SHIFTS, Dt1(->frames));
#line 386 "src/machine/aot/aot.x64.c"
  /* Check if the write spans to a second memory page */
  //| mov rdx, rax
  //| add rdx, rsi
  //| sub rdx, 1
  //| shr rdx, CKB_VM_ASM_RISCV_PAGE_SHIFTS
  //| add rcx, 1
  //| cmp rcx, rdx
  //| jne >2
  dasm_put(Dst, 174, CKB_VM_ASM_RISCV_PAGE_SHIFTS);
#line 394 "src/machine/aot/aot.x64.c"
  /*
   * Test if the page stored in rcx is out of bound, and if the page has
   * correct write permissions
   */
  //| cmp rcx, CKB_VM_ASM_RISCV_PAGES
  //| jae >3
  //| lea rdx, machine->flags
  //| movzx edx, byte [rdx+rcx]
  //| and edx, CKB_VM_ASM_MEMORY_FLAG_WXORX_BIT
  //| cmp edx, CKB_VM_ASM_MEMORY_FLAG_WRITABLE
  //| jne >4
  //| shr rcx, CKB_VM_ASM_MEMORY_FRAME_PAGE_SHIFTS
  //| lea rdx, machine->frames
  //| movzx r8d, byte [rdx+rcx]
  //| cmp r8d, 0
  //| jne >2
  //| mov byte [rdx+rcx], 1
  //| call ->zeroed_memory
  //|2:
  //| mov rdx, 0
  //| pop r8
  //| pop rsi
  //| ret
  //|3:
  //| mov rdx, CKB_VM_ASM_RET_OUT_OF_BOUND
  //| pop r8
  //| pop rsi
  //| ret
  //|4:
  //| mov rdx, CKB_VM_ASM_RET_INVALID_PERMISSION
  //| pop r8
  dasm_put(Dst, 203, CKB_VM_ASM_RISCV_PAGES, Dt1(->flags), CKB_VM_ASM_MEMORY_FLAG_WXORX_BIT, CKB_VM_ASM_MEMORY_FLAG_WRITABLE, CKB_VM_ASM_MEMORY_FRAME_PAGE_SHIFTS, Dt1(->frames), CKB_VM_ASM_RET_OUT_OF_BOUND, CKB_VM_ASM_RET_INVALID_PERMISSION);
#line 425 "src/machine/aot/aot.x64.c"
  //| pop rsi
  //| ret
  dasm_put(Dst, 291);
#line 427 "src/machine/aot/aot.x64.c"
  /*
   * Zeroed frame by memory address and length if it's necessary.
   *
   * rax: the memory address to read/write
   * rdx: length of memory to read/write
   */
  //|->check_read:
  //| push rsi
  //| push r8
  //| mov rcx, rax
  //| shr rcx, CKB_VM_ASM_MEMORY_FRAME_SHIFTS
  //| cmp rcx, CKB_VM_ASM_MEMORY_FRAMES
  //| jae >3
  //| lea rsi, machine->frames
  //| movzx r8d, byte [rsi+rcx]
  //| cmp r8d, 0
  //| jne >1
  //| mov byte [rsi+rcx], 1
  //| call ->zeroed_memory
  //|1:
  //| mov rcx, rax
  //| add rcx, rdx
  //| sub rcx, 1
  //| shr rcx, CKB_VM_ASM_MEMORY_FRAME_SHIFTS
  //| cmp rcx, CKB_VM_ASM_MEMORY_FRAMES
  //| jae >3
  //| movzx r8d, byte [rsi+rcx]
  //| cmp r8d, 0
  //| jne >2
  //| mov byte [rsi+rcx], 1
  //| call ->zeroed_memory
  //| jmp >2
  dasm_put(Dst, 296, CKB_VM_ASM_MEMORY_FRAME_SHIFTS, CKB_VM_ASM_MEMORY_FRAMES, Dt1(->frames), CKB_VM_ASM_MEMORY_FRAME_SHIFTS, CKB_VM_ASM_MEMORY_FRAMES);
#line 459 "src/machine/aot/aot.x64.c"
  //|2:
  //| mov rdx, 0
  //| pop r8
  //| pop rsi
  //| ret
  //|3:
  //| mov rdx, CKB_VM_ASM_RET_OUT_OF_BOUND
  //| pop r8
  //| pop rsi
  //| ret
  dasm_put(Dst, 392, CKB_VM_ASM_RET_OUT_OF_BOUND);
#line 469 "src/machine/aot/aot.x64.c"
  /* rax should store the return value here */
  //|->exit:
  //| mov machine->registers[REGISTER_RA], rsi
  //| mov machine->registers[REGISTER_SP], r8
  //| mov machine->registers[REGISTER_A0], r9
  //|.if WIN
    //| pop rsi
    //| pop rdi
  //|.endif
  //| pop rbp
  //| pop rbx
  //| pop r15
  //| pop r14
  //| pop r13
  //| pop r12
  //| ret
  dasm_put(Dst, 420, Dt1(->registers[REGISTER_RA]), Dt1(->registers[REGISTER_SP]), Dt1(->registers[REGISTER_A0]));
#line 485 "src/machine/aot/aot.x64.c"
  return dasm_link(&context->d, szp);
}

int aot_encode(AotContext* context, void *buffer)
{
  return dasm_encode(&context->d, buffer);
}

int aot_getpclabel(AotContext* context, uint32_t label, uint32_t* offset)
{
  int ret;
  if (label >= context->npc) {
    return ERROR_NOT_ENOUGH_LABELS;
  }
  ret = dasm_getpclabel(&context->d, label);
  if (ret < 0) { return ret; }
  *offset = (uint32_t) ret;
  return DASM_S_OK;
}

int aot_label(AotContext* context, uint32_t label)
{
  dasm_State** Dst = &context->d;
  if (label >= context->npc) {
    return ERROR_NOT_ENOUGH_LABELS;
  }
  //|=>label:
  dasm_put(Dst, 448, label);
#line 512 "src/machine/aot/aot.x64.c"
  return DASM_S_OK;
}

static int aot_mov_internal(AotContext* context, riscv_register_t target, AotValue value, x64_register_t x64_temp_reg);
static int aot_mov_pc_internal(AotContext* context, AotValue value);
static int aot_mov_x64(AotContext* context, x64_register_t x64_target, AotValue value);

int aot_mov(AotContext* context, riscv_register_t target, AotValue value)
{
  return aot_mov_internal(context, target, value, X64_RAX);
}

int aot_mov_pc(AotContext* context, AotValue value)
{
  return aot_mov_pc_internal(context, value);
}

int aot_add(AotContext* context, riscv_register_t target, AotValue a, AotValue b)
{
  int ret;
  uint32_t loc1, loc2;
  dasm_State** Dst = &context->d;

  if (aot_value_is_riscv_register(b, target)) {
    ret = aot_mov_x64(context, X64_RCX, b);
    if (ret != DASM_S_OK) { return ret; }
    b.tag = AOT_TAG_X64_REGISTER;
    b.value.x64_reg = X64_RCX;
  }

  ret = aot_mov_internal(context, target, a, X64_RAX);
  if (ret != DASM_S_OK) { return ret; }

  switch (b.tag) {
    case AOT_TAG_REGISTER:
      //| op2_r_r add, target, b.value.reg, rax
      loc1 = riscv_reg_to_x64_reg(target);
      loc2 = riscv_reg_to_x64_reg(b.value.reg);
      if (VALID_X64_REGISTER(loc1) && VALID_X64_REGISTER(loc2)) {
      dasm_put(Dst, 450, (loc2), (loc1));
      } else if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 458, (loc1), Dt1(->registers[b.value.reg]));
      } else if (VALID_X64_REGISTER(loc2)) {
      dasm_put(Dst, 466, (loc2), Dt1(->registers[target]));
      } else {
      dasm_put(Dst, 474, Dt1(->registers[b.value.reg]), Dt1(->registers[target]));
      }
#line 548 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_IMMEDIATE:
      //| op2_r_imm add, target, b.value.i, rax
      if (b.value.i > 0xFFFFFFFF && ((b.value.i & 0xFFFFFFFF80000000) != 0xFFFFFFFF80000000)) {
        loc1 = riscv_reg_to_x64_reg(target);
      dasm_put(Dst, 483, (unsigned int)(b.value.i), (unsigned int)((b.value.i)>>32));
        if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 488, (loc1));
        } else {
      dasm_put(Dst, 478, Dt1(->registers[target]));
        }
      } else {
        loc1 = riscv_reg_to_x64_reg(target);
        if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 494, (loc1), b.value.i);
        } else {
      dasm_put(Dst, 501, Dt1(->registers[target]), b.value.i);
        }
      }
#line 551 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_X64_REGISTER:
      //| op2_r_x add, target, Rq(b.value.x64_reg)
      loc1 = riscv_reg_to_x64_reg(target);
      if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 450, (b.value.x64_reg), (loc1));
      } else {
      dasm_put(Dst, 466, (b.value.x64_reg), Dt1(->registers[target]));
      }
#line 554 "src/machine/aot/aot.x64.c"
      break;
  }

  return DASM_S_OK;
}

int aot_sub(AotContext* context, riscv_register_t target, AotValue a, AotValue b)
{
  int ret;
  uint32_t loc1, loc2;
  dasm_State** Dst = &context->d;

  if (aot_value_is_riscv_register(b, target)) {
    ret = aot_mov_x64(context, X64_RCX, b);
    if (ret != DASM_S_OK) { return ret; }
    b.tag = AOT_TAG_X64_REGISTER;
    b.value.x64_reg = X64_RCX;
  }

  ret = aot_mov_internal(context, target, a, X64_RAX);
  if (ret != DASM_S_OK) { return ret; }

  switch (b.tag) {
    case AOT_TAG_REGISTER:
      //| op2_r_r sub, target, b.value.reg, rax
      loc1 = riscv_reg_to_x64_reg(target);
      loc2 = riscv_reg_to_x64_reg(b.value.reg);
      if (VALID_X64_REGISTER(loc1) && VALID_X64_REGISTER(loc2)) {
      dasm_put(Dst, 507, (loc2), (loc1));
      } else if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 515, (loc1), Dt1(->registers[b.value.reg]));
      } else if (VALID_X64_REGISTER(loc2)) {
      dasm_put(Dst, 523, (loc2), Dt1(->registers[target]));
      } else {
      dasm_put(Dst, 531, Dt1(->registers[b.value.reg]), Dt1(->registers[target]));
      }
#line 579 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_IMMEDIATE:
      //| op2_r_imm sub, target, b.value.i, rax
      if (b.value.i > 0xFFFFFFFF && ((b.value.i & 0xFFFFFFFF80000000) != 0xFFFFFFFF80000000)) {
        loc1 = riscv_reg_to_x64_reg(target);
      dasm_put(Dst, 483, (unsigned int)(b.value.i), (unsigned int)((b.value.i)>>32));
        if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 540, (loc1));
        } else {
      dasm_put(Dst, 535, Dt1(->registers[target]));
        }
      } else {
        loc1 = riscv_reg_to_x64_reg(target);
        if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 546, (loc1), b.value.i);
        } else {
      dasm_put(Dst, 553, Dt1(->registers[target]), b.value.i);
        }
      }
#line 582 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_X64_REGISTER:
      //| op2_r_x sub, target, Rq(b.value.x64_reg)
      loc1 = riscv_reg_to_x64_reg(target);
      if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 507, (b.value.x64_reg), (loc1));
      } else {
      dasm_put(Dst, 523, (b.value.x64_reg), Dt1(->registers[target]));
      }
#line 585 "src/machine/aot/aot.x64.c"
      break;
  }

  return DASM_S_OK;
}

int aot_mul(AotContext* context, riscv_register_t target, AotValue a, AotValue b)
{
  int ret;
  uint32_t loc1;
  dasm_State** Dst = &context->d;

  ret = aot_mov_x64(context, X64_RAX, a);
  if (ret != DASM_S_OK) { return ret; }

  switch (b.tag) {
    case AOT_TAG_REGISTER:
      //| op2_x_r imul, rax, b.value.reg
      loc1 = riscv_reg_to_x64_reg(b.value.reg);
      if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 559, (loc1));
      } else {
      dasm_put(Dst, 566, Dt1(->registers[b.value.reg]));
      }
#line 603 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_IMMEDIATE:
      //| load_imm rcx, b.value.i
      if (b.value.i > 0xFFFFFFFF && ((b.value.i & 0xFFFFFFFF80000000) != 0xFFFFFFFF80000000)) {
      dasm_put(Dst, 572, (unsigned int)(b.value.i), (unsigned int)((b.value.i)>>32));
      } else {
      dasm_put(Dst, 577, b.value.i);
      }
#line 606 "src/machine/aot/aot.x64.c"
      //| imul rax, rcx
      dasm_put(Dst, 582);
#line 607 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_X64_REGISTER:
      //| imul rax, Rq(b.value.x64_reg)
      dasm_put(Dst, 559, (b.value.x64_reg));
#line 610 "src/machine/aot/aot.x64.c"
      break;
  }

  //| op2_r_x mov, target, rax
  loc1 = riscv_reg_to_x64_reg(target);
  if (VALID_X64_REGISTER(loc1)) {
  dasm_put(Dst, 587, (loc1));
  } else {
  dasm_put(Dst, 593, Dt1(->registers[target]));
  }
#line 614 "src/machine/aot/aot.x64.c"

  return DASM_S_OK;
}

int aot_mulh(AotContext* context, riscv_register_t target, AotValue a, AotValue b, int is_signed)
{
  int ret;
  uint32_t loc1;
  dasm_State** Dst = &context->d;

  ret = aot_mov_x64(context, X64_RAX, a);
  if (ret != DASM_S_OK) { return ret; }

  switch (b.tag) {
    case AOT_TAG_REGISTER:
      if (is_signed) {
        //| op1_r imul, b.value.reg
        loc1 = riscv_reg_to_x64_reg(b.value.reg);
        if (VALID_X64_REGISTER(loc1)) {
        dasm_put(Dst, 598, (loc1));
        } else {
        dasm_put(Dst, 605, Dt1(->registers[b.value.reg]));
        }
#line 631 "src/machine/aot/aot.x64.c"
      } else {
        //| op1_r mul, b.value.reg
        loc1 = riscv_reg_to_x64_reg(b.value.reg);
        if (VALID_X64_REGISTER(loc1)) {
        dasm_put(Dst, 611, (loc1));
        } else {
        dasm_put(Dst, 618, Dt1(->registers[b.value.reg]));
        }
#line 633 "src/machine/aot/aot.x64.c"
      }
      break;
    case AOT_TAG_IMMEDIATE:
      //| load_imm rcx, b.value.i
      if (b.value.i > 0xFFFFFFFF && ((b.value.i & 0xFFFFFFFF80000000) != 0xFFFFFFFF80000000)) {
      dasm_put(Dst, 572, (unsigned int)(b.value.i), (unsigned int)((b.value.i)>>32));
      } else {
      dasm_put(Dst, 577, b.value.i);
      }
#line 637 "src/machine/aot/aot.x64.c"
      if (is_signed) {
        //| imul rcx
        dasm_put(Dst, 624);
#line 639 "src/machine/aot/aot.x64.c"
      } else {
        //| mul rcx
        dasm_put(Dst, 630);
#line 641 "src/machine/aot/aot.x64.c"
      }
      break;
    case AOT_TAG_X64_REGISTER:
      if (is_signed) {
        //| imul Rq(b.value.x64_reg)
        dasm_put(Dst, 598, (b.value.x64_reg));
#line 646 "src/machine/aot/aot.x64.c"
      } else {
        //| mul Rq(b.value.x64_reg)
        dasm_put(Dst, 611, (b.value.x64_reg));
#line 648 "src/machine/aot/aot.x64.c"
      }
      break;
  }
  //| op2_r_x mov, target, rdx
  loc1 = riscv_reg_to_x64_reg(target);
  if (VALID_X64_REGISTER(loc1)) {
  dasm_put(Dst, 635, (loc1));
  } else {
  dasm_put(Dst, 641, Dt1(->registers[target]));
  }
#line 652 "src/machine/aot/aot.x64.c"

  return DASM_S_OK;
}

/* Inspired from https://github.com/rv8-io/rv8/blob/834259098a5c182874aac97d82a164d144244e1a/src/jit/jit-emitter-rv64.h#L931 */
int aot_mulhsu(AotContext* context, riscv_register_t target, AotValue a, AotValue b)
{
  int ret;
  uint32_t loc1;
  dasm_State** Dst = &context->d;

  ret = aot_mov_x64(context, X64_RAX, a);
  if (ret != DASM_S_OK) { return ret; }

  //| test rax, rax
  //| jns >1
  dasm_put(Dst, 646);
#line 668 "src/machine/aot/aot.x64.c"
  /* calculate res = mulhu(-a, b), res is stored in rdx after this. */
  //| neg rax
  dasm_put(Dst, 654);
#line 670 "src/machine/aot/aot.x64.c"
  switch (b.tag) {
    case AOT_TAG_REGISTER:
      //| op1_r mul, b.value.reg
      loc1 = riscv_reg_to_x64_reg(b.value.reg);
      if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 611, (loc1));
      } else {
      dasm_put(Dst, 618, Dt1(->registers[b.value.reg]));
      }
#line 673 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_IMMEDIATE:
      //| load_imm rcx, b.value.i
      if (b.value.i > 0xFFFFFFFF && ((b.value.i & 0xFFFFFFFF80000000) != 0xFFFFFFFF80000000)) {
      dasm_put(Dst, 572, (unsigned int)(b.value.i), (unsigned int)((b.value.i)>>32));
      } else {
      dasm_put(Dst, 577, b.value.i);
      }
#line 676 "src/machine/aot/aot.x64.c"
      //| mul rcx
      dasm_put(Dst, 630);
#line 677 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_X64_REGISTER:
      //| mul Rq(b.value.x64_reg)
      dasm_put(Dst, 611, (b.value.x64_reg));
#line 680 "src/machine/aot/aot.x64.c"
      break;
  }
  /* calculate ~res and store it in rcx */
  //| xor rdx, -1
  //| mov rcx, rdx
  dasm_put(Dst, 659);
#line 685 "src/machine/aot/aot.x64.c"
  /*
   * calculate (a * b), then test (a * b == 0) and convert that to 1 or 0,
   * result is stored in rax after this.
   */
  ret = aot_mov_x64(context, X64_RAX, a);
  if (ret != DASM_S_OK) { return ret; }
  switch (b.tag) {
    case AOT_TAG_REGISTER:
      //| op2_x_r imul, rax, b.value.reg
      loc1 = riscv_reg_to_x64_reg(b.value.reg);
      if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 559, (loc1));
      } else {
      dasm_put(Dst, 566, Dt1(->registers[b.value.reg]));
      }
#line 694 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_IMMEDIATE:
      //| load_imm rdx, b.value.i
      if (b.value.i > 0xFFFFFFFF && ((b.value.i & 0xFFFFFFFF80000000) != 0xFFFFFFFF80000000)) {
      dasm_put(Dst, 669, (unsigned int)(b.value.i), (unsigned int)((b.value.i)>>32));
      } else {
      dasm_put(Dst, 286, b.value.i);
      }
#line 697 "src/machine/aot/aot.x64.c"
      //| imul rax, rdx
      dasm_put(Dst, 674);
#line 698 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_X64_REGISTER:
      //| imul rax, Rq(b.value.x64_reg)
      dasm_put(Dst, 559, (b.value.x64_reg));
#line 701 "src/machine/aot/aot.x64.c"
      break;
  }
  //| test rax, rax
  //| setz al
  //| movzx rax, al
  dasm_put(Dst, 679);
#line 706 "src/machine/aot/aot.x64.c"
  /* calculate ~res + (a * b == 0) */
  //| add rax, rcx
  //| jmp >2
  dasm_put(Dst, 690);
#line 709 "src/machine/aot/aot.x64.c"
  /* just mulhu here */
  //|1:
  dasm_put(Dst, 171);
#line 711 "src/machine/aot/aot.x64.c"
  switch (b.tag) {
    case AOT_TAG_REGISTER:
      //| op1_r mul, b.value.reg
      loc1 = riscv_reg_to_x64_reg(b.value.reg);
      if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 611, (loc1));
      } else {
      dasm_put(Dst, 618, Dt1(->registers[b.value.reg]));
      }
#line 714 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_IMMEDIATE:
      //| load_imm rcx, b.value.i
      if (b.value.i > 0xFFFFFFFF && ((b.value.i & 0xFFFFFFFF80000000) != 0xFFFFFFFF80000000)) {
      dasm_put(Dst, 572, (unsigned int)(b.value.i), (unsigned int)((b.value.i)>>32));
      } else {
      dasm_put(Dst, 577, b.value.i);
      }
#line 717 "src/machine/aot/aot.x64.c"
      //| mul rcx
      dasm_put(Dst, 630);
#line 718 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_X64_REGISTER:
      //| mul Rq(b.value.x64_reg)
      dasm_put(Dst, 611, (b.value.x64_reg));
#line 721 "src/machine/aot/aot.x64.c"
      break;
  }
  //| mov rax, rdx
  //|2:
  //| op2_r_x mov, target, rax
  dasm_put(Dst, 698);
  loc1 = riscv_reg_to_x64_reg(target);
  if (VALID_X64_REGISTER(loc1)) {
  dasm_put(Dst, 587, (loc1));
  } else {
  dasm_put(Dst, 593, Dt1(->registers[target]));
  }
#line 726 "src/machine/aot/aot.x64.c"

  return DASM_S_OK;
}

int aot_div(AotContext* context, riscv_register_t target, AotValue a, AotValue b, int is_signed)
{
  int ret;
  uint32_t loc1;
  dasm_State** Dst = &context->d;

  if (is_signed) {
    //| mov64 rax, INT64_MIN
    dasm_put(Dst, 483, (unsigned int)(INT64_MIN), (unsigned int)((INT64_MIN)>>32));
#line 738 "src/machine/aot/aot.x64.c"
    ret = aot_mov_x64(context, X64_RCX, a);
    if (ret != DASM_S_OK) { return ret; }
    //| cmp rax, rcx
    //| jne >1
    //| mov rax, -1
    dasm_put(Dst, 704);
#line 743 "src/machine/aot/aot.x64.c"
    ret = aot_mov_x64(context, X64_RCX, b);
    if (ret != DASM_S_OK) { return ret; }
    //| cmp rax, rcx
    //| jne >1
    dasm_put(Dst, 723);
#line 747 "src/machine/aot/aot.x64.c"
    ret = aot_mov_internal(context, target, a, X64_RAX);
    if (ret != DASM_S_OK) { return ret; }
    //| jmp >3
    dasm_put(Dst, 731);
#line 750 "src/machine/aot/aot.x64.c"
  }
  //|1:
  //| mov rax, 0
  dasm_put(Dst, 736);
#line 753 "src/machine/aot/aot.x64.c"
  ret = aot_mov_x64(context, X64_RCX, b);
  if (ret != DASM_S_OK) { return ret; }
  //| cmp rax, rcx
  //| jne >2
  //| op2_r_imm mov, target, (uint64_t)UINT64_MAX, rax
  dasm_put(Dst, 746);
  if ((uint64_t)UINT64_MAX > 0xFFFFFFFF && (((uint64_t)UINT64_MAX & 0xFFFFFFFF80000000) != 0xFFFFFFFF80000000)) {
    loc1 = riscv_reg_to_x64_reg(target);
  dasm_put(Dst, 483, (unsigned int)((uint64_t)UINT64_MAX), (unsigned int)(((uint64_t)UINT64_MAX)>>32));
    if (VALID_X64_REGISTER(loc1)) {
  dasm_put(Dst, 587, (loc1));
    } else {
  dasm_put(Dst, 593, Dt1(->registers[target]));
    }
  } else {
    loc1 = riscv_reg_to_x64_reg(target);
    if (VALID_X64_REGISTER(loc1)) {
  dasm_put(Dst, 754, (loc1), (uint64_t)UINT64_MAX);
    } else {
  dasm_put(Dst, 761, Dt1(->registers[target]), (uint64_t)UINT64_MAX);
    }
  }
#line 758 "src/machine/aot/aot.x64.c"
  //| jmp >3
  //|2:
  dasm_put(Dst, 767);
#line 760 "src/machine/aot/aot.x64.c"
  ret = aot_mov_x64(context, X64_RAX, a);
  if (ret != DASM_S_OK) { return ret; }
  switch (b.tag) {
    case AOT_TAG_REGISTER:
      if (is_signed) {
        //| cqo
        //| op1_r idiv, b.value.reg
        dasm_put(Dst, 774);
        loc1 = riscv_reg_to_x64_reg(b.value.reg);
        if (VALID_X64_REGISTER(loc1)) {
        dasm_put(Dst, 777, (loc1));
        } else {
        dasm_put(Dst, 785, Dt1(->registers[b.value.reg]));
        }
#line 767 "src/machine/aot/aot.x64.c"
      } else {
        //| xor rdx, rdx
        //| op1_r div, b.value.reg
        dasm_put(Dst, 791);
        loc1 = riscv_reg_to_x64_reg(b.value.reg);
        if (VALID_X64_REGISTER(loc1)) {
        dasm_put(Dst, 795, (loc1));
        } else {
        dasm_put(Dst, 803, Dt1(->registers[b.value.reg]));
        }
#line 770 "src/machine/aot/aot.x64.c"
      }
      break;
    case AOT_TAG_IMMEDIATE:
      //| load_imm, rcx, b.value.i
      if (b.value.i > 0xFFFFFFFF && ((b.value.i & 0xFFFFFFFF80000000) != 0xFFFFFFFF80000000)) {
      dasm_put(Dst, 572, (unsigned int)(b.value.i), (unsigned int)((b.value.i)>>32));
      } else {
      dasm_put(Dst, 577, b.value.i);
      }
#line 774 "src/machine/aot/aot.x64.c"
      if (is_signed) {
        //| cqo
        //| idiv rcx
        dasm_put(Dst, 809);
#line 777 "src/machine/aot/aot.x64.c"
      } else {
        //| xor rdx, rdx
        //| div rcx
        dasm_put(Dst, 817);
#line 780 "src/machine/aot/aot.x64.c"
      }
      break;
    case AOT_TAG_X64_REGISTER:
      if (is_signed) {
        //| cqo
        //| idiv Rq(b.value.x64_reg)
        dasm_put(Dst, 826, (b.value.x64_reg));
#line 786 "src/machine/aot/aot.x64.c"
      } else {
        //| xor rdx, rdx
        //| div Rq(b.value.x64_reg)
        dasm_put(Dst, 836, (b.value.x64_reg));
#line 789 "src/machine/aot/aot.x64.c"
      }
      break;
  }
  //| op2_r_x mov, target, rax
  loc1 = riscv_reg_to_x64_reg(target);
  if (VALID_X64_REGISTER(loc1)) {
  dasm_put(Dst, 587, (loc1));
  } else {
  dasm_put(Dst, 593, Dt1(->registers[target]));
  }
#line 793 "src/machine/aot/aot.x64.c"
  //|3:
  dasm_put(Dst, 847);
#line 794 "src/machine/aot/aot.x64.c"

  return DASM_S_OK;
}

int aot_rem(AotContext* context, riscv_register_t target, AotValue a, AotValue b, int is_signed)
{
  int ret;
  uint32_t loc1;
  dasm_State** Dst = &context->d;

  if (is_signed) {
    //| mov64 rax, INT64_MIN
    dasm_put(Dst, 483, (unsigned int)(INT64_MIN), (unsigned int)((INT64_MIN)>>32));
#line 806 "src/machine/aot/aot.x64.c"
    ret = aot_mov_x64(context, X64_RCX, a);
    if (ret != DASM_S_OK) { return ret; }
    //| cmp rax, rcx
    //| jne >1
    //| mov rax, -1
    dasm_put(Dst, 704);
#line 811 "src/machine/aot/aot.x64.c"
    ret = aot_mov_x64(context, X64_RCX, b);
    if (ret != DASM_S_OK) { return ret; }
    //| cmp rax, rcx
    //| jne >1
    //| op2_r_imm mov, target, (uint64_t)0, rax
    dasm_put(Dst, 723);
    if ((uint64_t)0 > 0xFFFFFFFF && (((uint64_t)0 & 0xFFFFFFFF80000000) != 0xFFFFFFFF80000000)) {
      loc1 = riscv_reg_to_x64_reg(target);
    dasm_put(Dst, 483, (unsigned int)((uint64_t)0), (unsigned int)(((uint64_t)0)>>32));
      if (VALID_X64_REGISTER(loc1)) {
    dasm_put(Dst, 587, (loc1));
      } else {
    dasm_put(Dst, 593, Dt1(->registers[target]));
      }
    } else {
      loc1 = riscv_reg_to_x64_reg(target);
      if (VALID_X64_REGISTER(loc1)) {
    dasm_put(Dst, 754, (loc1), (uint64_t)0);
      } else {
    dasm_put(Dst, 761, Dt1(->registers[target]), (uint64_t)0);
      }
    }
#line 816 "src/machine/aot/aot.x64.c"
    //| jmp >3
    dasm_put(Dst, 731);
#line 817 "src/machine/aot/aot.x64.c"
  }
  //|1:
  //| mov rax, 0
  dasm_put(Dst, 736);
#line 820 "src/machine/aot/aot.x64.c"
  ret = aot_mov_x64(context, X64_RCX, b);
  if (ret != DASM_S_OK) { return ret; }
  //| cmp rax, rcx
  //| jne >2
  dasm_put(Dst, 746);
#line 824 "src/machine/aot/aot.x64.c"
  ret = aot_mov_internal(context, target, a, X64_RAX);
  if (ret != DASM_S_OK) { return ret; }
  //| jmp >3
  //|2:
  dasm_put(Dst, 767);
#line 828 "src/machine/aot/aot.x64.c"
  ret = aot_mov_x64(context, X64_RAX, a);
  if (ret != DASM_S_OK) { return ret; }
  switch (b.tag) {
    case AOT_TAG_REGISTER:
      if (is_signed) {
        //| cqo
        //| op1_r idiv, b.value.reg
        dasm_put(Dst, 774);
        loc1 = riscv_reg_to_x64_reg(b.value.reg);
        if (VALID_X64_REGISTER(loc1)) {
        dasm_put(Dst, 777, (loc1));
        } else {
        dasm_put(Dst, 785, Dt1(->registers[b.value.reg]));
        }
#line 835 "src/machine/aot/aot.x64.c"
      } else {
        //| xor rdx, rdx
        //| op1_r div, b.value.reg
        dasm_put(Dst, 791);
        loc1 = riscv_reg_to_x64_reg(b.value.reg);
        if (VALID_X64_REGISTER(loc1)) {
        dasm_put(Dst, 795, (loc1));
        } else {
        dasm_put(Dst, 803, Dt1(->registers[b.value.reg]));
        }
#line 838 "src/machine/aot/aot.x64.c"
      }
      break;
    case AOT_TAG_IMMEDIATE:
      //| load_imm, rcx, b.value.i
      if (b.value.i > 0xFFFFFFFF && ((b.value.i & 0xFFFFFFFF80000000) != 0xFFFFFFFF80000000)) {
      dasm_put(Dst, 572, (unsigned int)(b.value.i), (unsigned int)((b.value.i)>>32));
      } else {
      dasm_put(Dst, 577, b.value.i);
      }
#line 842 "src/machine/aot/aot.x64.c"
      if (is_signed) {
        //| cqo
        //| idiv rcx
        dasm_put(Dst, 809);
#line 845 "src/machine/aot/aot.x64.c"
      } else {
        //| xor rdx, rdx
        //| div rcx
        dasm_put(Dst, 817);
#line 848 "src/machine/aot/aot.x64.c"
      }
      break;
    case AOT_TAG_X64_REGISTER:
      if (is_signed) {
        //| cqo
        //| idiv Rq(b.value.x64_reg)
        dasm_put(Dst, 826, (b.value.x64_reg));
#line 854 "src/machine/aot/aot.x64.c"
      } else {
        //| xor rdx, rdx
        //| div Rq(b.value.x64_reg)
        dasm_put(Dst, 836, (b.value.x64_reg));
#line 857 "src/machine/aot/aot.x64.c"
      }
      break;
  }
  //| op2_r_x mov, target, rdx
  loc1 = riscv_reg_to_x64_reg(target);
  if (VALID_X64_REGISTER(loc1)) {
  dasm_put(Dst, 635, (loc1));
  } else {
  dasm_put(Dst, 641, Dt1(->registers[target]));
  }
#line 861 "src/machine/aot/aot.x64.c"
  //|3:
  dasm_put(Dst, 847);
#line 862 "src/machine/aot/aot.x64.c"

  return DASM_S_OK;
}

int aot_and(AotContext* context, riscv_register_t target, AotValue a, AotValue b)
{
  int ret;
  uint32_t loc1, loc2;
  dasm_State** Dst = &context->d;

  if (aot_value_is_riscv_register(b, target)) {
    ret = aot_mov_x64(context, X64_RCX, b);
    if (ret != DASM_S_OK) { return ret; }
    b.tag = AOT_TAG_X64_REGISTER;
    b.value.x64_reg = X64_RCX;
  }

  ret = aot_mov_internal(context, target, a, X64_RAX);
  if (ret != DASM_S_OK) { return ret; }

  switch (b.tag) {
    case AOT_TAG_REGISTER:
      //| op2_r_r and, target, b.value.reg, rax
      loc1 = riscv_reg_to_x64_reg(target);
      loc2 = riscv_reg_to_x64_reg(b.value.reg);
      if (VALID_X64_REGISTER(loc1) && VALID_X64_REGISTER(loc2)) {
      dasm_put(Dst, 850, (loc2), (loc1));
      } else if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 858, (loc1), Dt1(->registers[b.value.reg]));
      } else if (VALID_X64_REGISTER(loc2)) {
      dasm_put(Dst, 866, (loc2), Dt1(->registers[target]));
      } else {
      dasm_put(Dst, 874, Dt1(->registers[b.value.reg]), Dt1(->registers[target]));
      }
#line 885 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_IMMEDIATE:
      //| op2_r_imm and, target, b.value.i, rax
      if (b.value.i > 0xFFFFFFFF && ((b.value.i & 0xFFFFFFFF80000000) != 0xFFFFFFFF80000000)) {
        loc1 = riscv_reg_to_x64_reg(target);
      dasm_put(Dst, 483, (unsigned int)(b.value.i), (unsigned int)((b.value.i)>>32));
        if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 883, (loc1));
        } else {
      dasm_put(Dst, 878, Dt1(->registers[target]));
        }
      } else {
        loc1 = riscv_reg_to_x64_reg(target);
        if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 889, (loc1), b.value.i);
        } else {
      dasm_put(Dst, 896, Dt1(->registers[target]), b.value.i);
        }
      }
#line 888 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_X64_REGISTER:
      //| op2_r_x and, target, Rq(b.value.x64_reg)
      loc1 = riscv_reg_to_x64_reg(target);
      if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 850, (b.value.x64_reg), (loc1));
      } else {
      dasm_put(Dst, 866, (b.value.x64_reg), Dt1(->registers[target]));
      }
#line 891 "src/machine/aot/aot.x64.c"
      break;
  }

  return DASM_S_OK;
}

int aot_or(AotContext* context, riscv_register_t target, AotValue a, AotValue b)
{
  int ret;
  uint32_t loc1, loc2;
  dasm_State** Dst = &context->d;

  if (aot_value_is_riscv_register(b, target)) {
    ret = aot_mov_x64(context, X64_RCX, b);
    if (ret != DASM_S_OK) { return ret; }
    b.tag = AOT_TAG_X64_REGISTER;
    b.value.x64_reg = X64_RCX;
  }

  ret = aot_mov_internal(context, target, a, X64_RAX);
  if (ret != DASM_S_OK) { return ret; }

  switch (b.tag) {
    case AOT_TAG_REGISTER:
      //| op2_r_r or, target, b.value.reg, rax
      loc1 = riscv_reg_to_x64_reg(target);
      loc2 = riscv_reg_to_x64_reg(b.value.reg);
      if (VALID_X64_REGISTER(loc1) && VALID_X64_REGISTER(loc2)) {
      dasm_put(Dst, 902, (loc2), (loc1));
      } else if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 910, (loc1), Dt1(->registers[b.value.reg]));
      } else if (VALID_X64_REGISTER(loc2)) {
      dasm_put(Dst, 918, (loc2), Dt1(->registers[target]));
      } else {
      dasm_put(Dst, 926, Dt1(->registers[b.value.reg]), Dt1(->registers[target]));
      }
#line 916 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_IMMEDIATE:
      //| op2_r_imm or, target, b.value.i, rax
      if (b.value.i > 0xFFFFFFFF && ((b.value.i & 0xFFFFFFFF80000000) != 0xFFFFFFFF80000000)) {
        loc1 = riscv_reg_to_x64_reg(target);
      dasm_put(Dst, 483, (unsigned int)(b.value.i), (unsigned int)((b.value.i)>>32));
        if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 935, (loc1));
        } else {
      dasm_put(Dst, 930, Dt1(->registers[target]));
        }
      } else {
        loc1 = riscv_reg_to_x64_reg(target);
        if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 941, (loc1), b.value.i);
        } else {
      dasm_put(Dst, 948, Dt1(->registers[target]), b.value.i);
        }
      }
#line 919 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_X64_REGISTER:
      //| op2_r_x or, target, Rq(b.value.x64_reg)
      loc1 = riscv_reg_to_x64_reg(target);
      if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 902, (b.value.x64_reg), (loc1));
      } else {
      dasm_put(Dst, 918, (b.value.x64_reg), Dt1(->registers[target]));
      }
#line 922 "src/machine/aot/aot.x64.c"
      break;
  }

  return DASM_S_OK;
}

int aot_not(AotContext* context, riscv_register_t target, AotValue a, int logical)
{
  int ret;
  uint32_t loc1;
  dasm_State** Dst = &context->d;

  ret = aot_mov_internal(context, target, a, X64_RAX);
  if (ret != DASM_S_OK) { return ret; }

  //| op1_r not, target
  loc1 = riscv_reg_to_x64_reg(target);
  if (VALID_X64_REGISTER(loc1)) {
  dasm_put(Dst, 954, (loc1));
  } else {
  dasm_put(Dst, 961, Dt1(->registers[target]));
  }
#line 938 "src/machine/aot/aot.x64.c"
  if (logical) {
    //| op2_r_imm and, target, (uint64_t)1, rax
    if ((uint64_t)1 > 0xFFFFFFFF && (((uint64_t)1 & 0xFFFFFFFF80000000) != 0xFFFFFFFF80000000)) {
      loc1 = riscv_reg_to_x64_reg(target);
    dasm_put(Dst, 483, (unsigned int)((uint64_t)1), (unsigned int)(((uint64_t)1)>>32));
      if (VALID_X64_REGISTER(loc1)) {
    dasm_put(Dst, 883, (loc1));
      } else {
    dasm_put(Dst, 878, Dt1(->registers[target]));
      }
    } else {
      loc1 = riscv_reg_to_x64_reg(target);
      if (VALID_X64_REGISTER(loc1)) {
    dasm_put(Dst, 889, (loc1), (uint64_t)1);
      } else {
    dasm_put(Dst, 896, Dt1(->registers[target]), (uint64_t)1);
      }
    }
#line 940 "src/machine/aot/aot.x64.c"
  }

  return DASM_S_OK;
}

int aot_xor(AotContext* context, riscv_register_t target, AotValue a, AotValue b)
{
  int ret;
  uint32_t loc1, loc2;
  dasm_State** Dst = &context->d;

  if (aot_value_is_riscv_register(b, target)) {
    ret = aot_mov_x64(context, X64_RCX, b);
    if (ret != DASM_S_OK) { return ret; }
    b.tag = AOT_TAG_X64_REGISTER;
    b.value.x64_reg = X64_RCX;
  }

  ret = aot_mov_internal(context, target, a, X64_RAX);
  if (ret != DASM_S_OK) { return ret; }

  switch (b.tag) {
    case AOT_TAG_REGISTER:
      //| op2_r_r xor, target, b.value.reg, rax
      loc1 = riscv_reg_to_x64_reg(target);
      loc2 = riscv_reg_to_x64_reg(b.value.reg);
      if (VALID_X64_REGISTER(loc1) && VALID_X64_REGISTER(loc2)) {
      dasm_put(Dst, 967, (loc2), (loc1));
      } else if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 975, (loc1), Dt1(->registers[b.value.reg]));
      } else if (VALID_X64_REGISTER(loc2)) {
      dasm_put(Dst, 983, (loc2), Dt1(->registers[target]));
      } else {
      dasm_put(Dst, 991, Dt1(->registers[b.value.reg]), Dt1(->registers[target]));
      }
#line 964 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_IMMEDIATE:
      //| op2_r_imm xor, target, b.value.i, rax
      if (b.value.i > 0xFFFFFFFF && ((b.value.i & 0xFFFFFFFF80000000) != 0xFFFFFFFF80000000)) {
        loc1 = riscv_reg_to_x64_reg(target);
      dasm_put(Dst, 483, (unsigned int)(b.value.i), (unsigned int)((b.value.i)>>32));
        if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 1000, (loc1));
        } else {
      dasm_put(Dst, 995, Dt1(->registers[target]));
        }
      } else {
        loc1 = riscv_reg_to_x64_reg(target);
        if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 1006, (loc1), b.value.i);
        } else {
      dasm_put(Dst, 1014, Dt1(->registers[target]), b.value.i);
        }
      }
#line 967 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_X64_REGISTER:
      //| op2_r_x xor, target, Rq(b.value.x64_reg)
      loc1 = riscv_reg_to_x64_reg(target);
      if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 967, (b.value.x64_reg), (loc1));
      } else {
      dasm_put(Dst, 983, (b.value.x64_reg), Dt1(->registers[target]));
      }
#line 970 "src/machine/aot/aot.x64.c"
      break;
  }

  return DASM_S_OK;
}

int aot_shl(AotContext* context, riscv_register_t target, AotValue a, AotValue b)
{
  int ret;
  uint32_t loc1;
  dasm_State** Dst = &context->d;

  ret = aot_mov_internal(context, target, a, X64_RAX);
  if (ret != DASM_S_OK) { return ret; }

  switch (b.tag) {
    case AOT_TAG_REGISTER:
      //| op2_x_r mov, rcx, b.value.reg
      loc1 = riscv_reg_to_x64_reg(b.value.reg);
      if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 1020, (loc1));
      } else {
      dasm_put(Dst, 1026, Dt1(->registers[b.value.reg]));
      }
#line 988 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_IMMEDIATE:
      /*
       * shift operations only use cl as operand, there won't be any
       * overflowing issues.
       */
      //| mov ecx, b.value.i
      dasm_put(Dst, 1031, b.value.i);
#line 995 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_X64_REGISTER:
      //| mov rcx, Rq(b.value.x64_reg)
      dasm_put(Dst, 1020, (b.value.x64_reg));
#line 998 "src/machine/aot/aot.x64.c"
      break;
  }

  //| op2_r_x shl, target, cl
  loc1 = riscv_reg_to_x64_reg(target);
  if (VALID_X64_REGISTER(loc1)) {
  dasm_put(Dst, 1034, (loc1));
  } else {
  dasm_put(Dst, 1040, Dt1(->registers[target]));
  }
#line 1002 "src/machine/aot/aot.x64.c"

  return DASM_S_OK;
}

int aot_shr(AotContext* context, riscv_register_t target, AotValue a, AotValue b, int is_signed)
{
  int ret;
  uint32_t loc1;
  dasm_State** Dst = &context->d;

  ret = aot_mov_internal(context, target, a, X64_RAX);
  if (ret != DASM_S_OK) { return ret; }

  switch (b.tag) {
    case AOT_TAG_REGISTER:
      //| op2_x_r mov, rcx, b.value.reg
      loc1 = riscv_reg_to_x64_reg(b.value.reg);
      if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 1020, (loc1));
      } else {
      dasm_put(Dst, 1026, Dt1(->registers[b.value.reg]));
      }
#line 1018 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_IMMEDIATE:
      /*
       * shift operations only use cl as operand, there won't be any
       * overflowing issues.
       */
      //| mov ecx, b.value.i
      dasm_put(Dst, 1031, b.value.i);
#line 1025 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_X64_REGISTER:
      //| mov rcx, Rq(b.value.x64_reg)
      dasm_put(Dst, 1020, (b.value.x64_reg));
#line 1028 "src/machine/aot/aot.x64.c"
      break;
  }

  if (is_signed) {
    //| op2_r_x sar, target, cl
    loc1 = riscv_reg_to_x64_reg(target);
    if (VALID_X64_REGISTER(loc1)) {
    dasm_put(Dst, 1045, (loc1));
    } else {
    dasm_put(Dst, 1052, Dt1(->registers[target]));
    }
#line 1033 "src/machine/aot/aot.x64.c"
  } else {
    //| op2_r_x shr, target, cl
    loc1 = riscv_reg_to_x64_reg(target);
    if (VALID_X64_REGISTER(loc1)) {
    dasm_put(Dst, 1057, (loc1));
    } else {
    dasm_put(Dst, 1063, Dt1(->registers[target]));
    }
#line 1035 "src/machine/aot/aot.x64.c"
  }

  return DASM_S_OK;
}

int aot_rol(AotContext* context, riscv_register_t target, AotValue a, AotValue b)
{
  int ret;
  uint32_t loc1;
  dasm_State** Dst = &context->d;

  ret = aot_mov_internal(context, target, a, X64_RAX);
  if (ret != DASM_S_OK) { return ret; }

  switch (b.tag) {
    case AOT_TAG_REGISTER:
      //| op2_x_r mov, rcx, b.value.reg
      loc1 = riscv_reg_to_x64_reg(b.value.reg);
      if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 1020, (loc1));
      } else {
      dasm_put(Dst, 1026, Dt1(->registers[b.value.reg]));
      }
#line 1052 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_IMMEDIATE:
      /*
       * shift operations only use cl as operand, there won't be any
       * overflowing issues.
       */
      //| mov ecx, b.value.i
      dasm_put(Dst, 1031, b.value.i);
#line 1059 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_X64_REGISTER:
      //| mov rcx, Rq(b.value.x64_reg)
      dasm_put(Dst, 1020, (b.value.x64_reg));
#line 1062 "src/machine/aot/aot.x64.c"
      break;
  }

  //| op2_r_x rol, target, cl
  loc1 = riscv_reg_to_x64_reg(target);
  if (VALID_X64_REGISTER(loc1)) {
  dasm_put(Dst, 1068, (loc1));
  } else {
  dasm_put(Dst, 1074, Dt1(->registers[target]));
  }
#line 1066 "src/machine/aot/aot.x64.c"

  return DASM_S_OK;
}

int aot_ror(AotContext* context, riscv_register_t target, AotValue a, AotValue b)
{
  int ret;
  uint32_t loc1;
  dasm_State** Dst = &context->d;

  ret = aot_mov_internal(context, target, a, X64_RAX);
  if (ret != DASM_S_OK) { return ret; }

  switch (b.tag) {
    case AOT_TAG_REGISTER:
      //| op2_x_r mov, rcx, b.value.reg
      loc1 = riscv_reg_to_x64_reg(b.value.reg);
      if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 1020, (loc1));
      } else {
      dasm_put(Dst, 1026, Dt1(->registers[b.value.reg]));
      }
#line 1082 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_IMMEDIATE:
      /*
       * shift operations only use cl as operand, there won't be any
       * overflowing issues.
       */
      //| mov ecx, b.value.i
      dasm_put(Dst, 1031, b.value.i);
#line 1089 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_X64_REGISTER:
      //| mov rcx, Rq(b.value.x64_reg)
      dasm_put(Dst, 1020, (b.value.x64_reg));
#line 1092 "src/machine/aot/aot.x64.c"
      break;
  }

  //| op2_r_x ror, target, cl
  loc1 = riscv_reg_to_x64_reg(target);
  if (VALID_X64_REGISTER(loc1)) {
  dasm_put(Dst, 1079, (loc1));
  } else {
  dasm_put(Dst, 1085, Dt1(->registers[target]));
  }
#line 1096 "src/machine/aot/aot.x64.c"

  return DASM_S_OK;
}

int aot_eq(AotContext* context, riscv_register_t target, AotValue a, AotValue b)
{
  uint32_t loc1;
  int ret;
  dasm_State** Dst = &context->d;

  ret = aot_mov_x64(context, X64_RCX, a);
  if (ret != DASM_S_OK) { return ret; }

  switch (b.tag) {
    case AOT_TAG_REGISTER:
      //| op2_x_r cmp, rcx, b.value.reg
      loc1 = riscv_reg_to_x64_reg(b.value.reg);
      if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 1090, (loc1));
      } else {
      dasm_put(Dst, 1096, Dt1(->registers[b.value.reg]));
      }
#line 1112 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_IMMEDIATE:
      //| load_imm rax, b.value.i
      if (b.value.i > 0xFFFFFFFF && ((b.value.i & 0xFFFFFFFF80000000) != 0xFFFFFFFF80000000)) {
      dasm_put(Dst, 483, (unsigned int)(b.value.i), (unsigned int)((b.value.i)>>32));
      } else {
      dasm_put(Dst, 1101, b.value.i);
      }
#line 1115 "src/machine/aot/aot.x64.c"
      //| cmp rcx, rax
      dasm_put(Dst, 1106);
#line 1116 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_X64_REGISTER:
      //| cmp rcx, Rq(b.value.x64_reg)
      dasm_put(Dst, 1090, (b.value.x64_reg));
#line 1119 "src/machine/aot/aot.x64.c"
      break;
  }

  //| sete cl
  //| movzx rcx, cl
  //| op2_r_x mov, target, rcx
  dasm_put(Dst, 1110);
  loc1 = riscv_reg_to_x64_reg(target);
  if (VALID_X64_REGISTER(loc1)) {
  dasm_put(Dst, 1118, (loc1));
  } else {
  dasm_put(Dst, 1124, Dt1(->registers[target]));
  }
#line 1125 "src/machine/aot/aot.x64.c"

  return DASM_S_OK;
}

int aot_lt(AotContext* context, riscv_register_t target, AotValue a, AotValue b, int is_signed)
{
  uint32_t loc1;
  int ret;
  dasm_State** Dst = &context->d;

  ret = aot_mov_x64(context, X64_RCX, a);
  if (ret != DASM_S_OK) { return ret; }

  switch (b.tag) {
    case AOT_TAG_REGISTER:
      //| op2_x_r cmp, rcx, b.value.reg
      loc1 = riscv_reg_to_x64_reg(b.value.reg);
      if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 1090, (loc1));
      } else {
      dasm_put(Dst, 1096, Dt1(->registers[b.value.reg]));
      }
#line 1141 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_IMMEDIATE:
      //| load_imm rax, b.value.i
      if (b.value.i > 0xFFFFFFFF && ((b.value.i & 0xFFFFFFFF80000000) != 0xFFFFFFFF80000000)) {
      dasm_put(Dst, 483, (unsigned int)(b.value.i), (unsigned int)((b.value.i)>>32));
      } else {
      dasm_put(Dst, 1101, b.value.i);
      }
#line 1144 "src/machine/aot/aot.x64.c"
      //| cmp rcx, rax
      dasm_put(Dst, 1106);
#line 1145 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_X64_REGISTER:
      //| cmp rcx, Rq(b.value.x64_reg)
      dasm_put(Dst, 1090, (b.value.x64_reg));
#line 1148 "src/machine/aot/aot.x64.c"
      break;
  }

  if (is_signed) {
    //| setl cl
    dasm_put(Dst, 1129);
#line 1153 "src/machine/aot/aot.x64.c"
  } else {
    //| setb cl
    dasm_put(Dst, 1133);
#line 1155 "src/machine/aot/aot.x64.c"
  }
  //| movzx rcx, cl
  //| op2_r_x mov, target, rcx
  dasm_put(Dst, 1113);
  loc1 = riscv_reg_to_x64_reg(target);
  if (VALID_X64_REGISTER(loc1)) {
  dasm_put(Dst, 1118, (loc1));
  } else {
  dasm_put(Dst, 1124, Dt1(->registers[target]));
  }
#line 1158 "src/machine/aot/aot.x64.c"

  return DASM_S_OK;
}

int aot_cond(AotContext* context, riscv_register_t target, AotValue condition, AotValue true_value, AotValue false_value) {
  uint32_t loc1;
  int ret;
  dasm_State** Dst = &context->d;

  switch (condition.tag) {
    case AOT_TAG_REGISTER:
      //| op2_r_imm cmp, condition.value.reg, (uint64_t)1, rax
      if ((uint64_t)1 > 0xFFFFFFFF && (((uint64_t)1 & 0xFFFFFFFF80000000) != 0xFFFFFFFF80000000)) {
        loc1 = riscv_reg_to_x64_reg(condition.value.reg);
      dasm_put(Dst, 483, (unsigned int)((uint64_t)1), (unsigned int)(((uint64_t)1)>>32));
        if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 1137, (loc1));
        } else {
      dasm_put(Dst, 1143, Dt1(->registers[condition.value.reg]));
        }
      } else {
        loc1 = riscv_reg_to_x64_reg(condition.value.reg);
        if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 1148, (loc1), (uint64_t)1);
        } else {
      dasm_put(Dst, 1156, Dt1(->registers[condition.value.reg]), (uint64_t)1);
        }
      }
#line 1170 "src/machine/aot/aot.x64.c"
      //| jne >1
      dasm_put(Dst, 726);
#line 1171 "src/machine/aot/aot.x64.c"
      ret = aot_mov_internal(context, target, true_value, X64_RAX);
      if (ret != DASM_S_OK) { return ret; }
      //| jmp >2
      //|1:
      dasm_put(Dst, 1162);
#line 1175 "src/machine/aot/aot.x64.c"
      ret = aot_mov_internal(context, target, false_value, X64_RAX);
      if (ret != DASM_S_OK) { return ret; }
      //|2:
      dasm_put(Dst, 701);
#line 1178 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_IMMEDIATE:
      ret = aot_mov_internal(context, target, (condition.value.i == 1) ? true_value : false_value, X64_RAX);
      if (ret != DASM_S_OK) { return ret; }
      break;
    case AOT_TAG_X64_REGISTER:
      //| cmp Rq(condition.value.x64_reg), 1
      //| jne >1
      dasm_put(Dst, 1169, (condition.value.x64_reg));
#line 1186 "src/machine/aot/aot.x64.c"
      ret = aot_mov_internal(context, target, true_value, X64_RAX);
      if (ret != DASM_S_OK) { return ret; }
      //| jmp >2
      //|1:
      dasm_put(Dst, 1162);
#line 1190 "src/machine/aot/aot.x64.c"
      ret = aot_mov_internal(context, target, false_value, X64_RAX);
      if (ret != DASM_S_OK) { return ret; }
      //|2:
      dasm_put(Dst, 701);
#line 1193 "src/machine/aot/aot.x64.c"
      break;
  }

  return DASM_S_OK;
}

int aot_clz(AotContext* context, riscv_register_t target, AotValue a)
{
  uint32_t loc1;
  int ret;
  dasm_State** Dst = &context->d;

  ret = aot_mov_x64(context, X64_RAX, a);
  if (ret != DASM_S_OK) { return ret; }

  //| cmp rax, 0
  //| je >1
  //| bsr rax, rax
  //| neg rax
  //| add rax, 63
  //| op2_r_x mov, target, rax
  dasm_put(Dst, 1181);
  loc1 = riscv_reg_to_x64_reg(target);
  if (VALID_X64_REGISTER(loc1)) {
  dasm_put(Dst, 587, (loc1));
  } else {
  dasm_put(Dst, 593, Dt1(->registers[target]));
  }
#line 1214 "src/machine/aot/aot.x64.c"
  //| jmp >2
  //|1:
  //| op2_r_imm mov, target, (uint64_t)64, rax
  dasm_put(Dst, 1162);
  if ((uint64_t)64 > 0xFFFFFFFF && (((uint64_t)64 & 0xFFFFFFFF80000000) != 0xFFFFFFFF80000000)) {
    loc1 = riscv_reg_to_x64_reg(target);
  dasm_put(Dst, 483, (unsigned int)((uint64_t)64), (unsigned int)(((uint64_t)64)>>32));
    if (VALID_X64_REGISTER(loc1)) {
  dasm_put(Dst, 587, (loc1));
    } else {
  dasm_put(Dst, 593, Dt1(->registers[target]));
    }
  } else {
    loc1 = riscv_reg_to_x64_reg(target);
    if (VALID_X64_REGISTER(loc1)) {
  dasm_put(Dst, 754, (loc1), (uint64_t)64);
    } else {
  dasm_put(Dst, 761, Dt1(->registers[target]), (uint64_t)64);
    }
  }
#line 1217 "src/machine/aot/aot.x64.c"
  //| jmp >2
  //|2:
  dasm_put(Dst, 1203);
#line 1219 "src/machine/aot/aot.x64.c"

  return DASM_S_OK;
}

int aot_ctz(AotContext* context, riscv_register_t target, AotValue a)
{
  uint32_t loc1;
  int ret;
  dasm_State** Dst = &context->d;

  ret = aot_mov_x64(context, X64_RAX, a);
  if (ret != DASM_S_OK) { return ret; }

  //| cmp rax, 0
  //| je >1
  //| bsf rax, rax
  //| op2_r_x mov, target, rax
  dasm_put(Dst, 1210);
  loc1 = riscv_reg_to_x64_reg(target);
  if (VALID_X64_REGISTER(loc1)) {
  dasm_put(Dst, 587, (loc1));
  } else {
  dasm_put(Dst, 593, Dt1(->registers[target]));
  }
#line 1236 "src/machine/aot/aot.x64.c"
  //| jmp >2
  //|1:
  //| op2_r_imm mov, target, (uint64_t)64, rax
  dasm_put(Dst, 1162);
  if ((uint64_t)64 > 0xFFFFFFFF && (((uint64_t)64 & 0xFFFFFFFF80000000) != 0xFFFFFFFF80000000)) {
    loc1 = riscv_reg_to_x64_reg(target);
  dasm_put(Dst, 483, (unsigned int)((uint64_t)64), (unsigned int)(((uint64_t)64)>>32));
    if (VALID_X64_REGISTER(loc1)) {
  dasm_put(Dst, 587, (loc1));
    } else {
  dasm_put(Dst, 593, Dt1(->registers[target]));
    }
  } else {
    loc1 = riscv_reg_to_x64_reg(target);
    if (VALID_X64_REGISTER(loc1)) {
  dasm_put(Dst, 754, (loc1), (uint64_t)64);
    } else {
  dasm_put(Dst, 761, Dt1(->registers[target]), (uint64_t)64);
    }
  }
#line 1239 "src/machine/aot/aot.x64.c"
  //| jmp >2
  //|2:
  dasm_put(Dst, 1203);
#line 1241 "src/machine/aot/aot.x64.c"

  return DASM_S_OK;
}

int aot_pcnt(AotContext* context, riscv_register_t target, AotValue a)
{
  uint32_t loc1;
  int ret;
  dasm_State** Dst = &context->d;

  ret = aot_mov_x64(context, X64_RAX, a);
  if (ret != DASM_S_OK) { return ret; }

  //| popcnt rax, rax
  //| op2_r_x mov, target, rax
  dasm_put(Dst, 1224);
  loc1 = riscv_reg_to_x64_reg(target);
  if (VALID_X64_REGISTER(loc1)) {
  dasm_put(Dst, 587, (loc1));
  } else {
  dasm_put(Dst, 593, Dt1(->registers[target]));
  }
#line 1256 "src/machine/aot/aot.x64.c"

  return DASM_S_OK;
}

int aot_fsl(AotContext* context, riscv_register_t target, AotValue a, AotValue b, AotValue c)
{
  int ret;
  uint32_t loc1;
  dasm_State** Dst = &context->d;

  ret = aot_mov_x64(context, X64_RAX, a);
  if (ret != DASM_S_OK) { return ret; }
  ret = aot_mov_x64(context, X64_RDX, b);
  if (ret != DASM_S_OK) { return ret; }

  switch (c.tag) {
    case AOT_TAG_REGISTER:
      //| op2_x_r mov, rcx, c.value.reg
      loc1 = riscv_reg_to_x64_reg(c.value.reg);
      if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 1020, (loc1));
      } else {
      dasm_put(Dst, 1026, Dt1(->registers[c.value.reg]));
      }
#line 1274 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_IMMEDIATE:
      //| mov ecx, c.value.i
      dasm_put(Dst, 1031, c.value.i);
#line 1277 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_X64_REGISTER:
      //| mov rcx, Rq(c.value.x64_reg)
      dasm_put(Dst, 1020, (c.value.x64_reg));
#line 1280 "src/machine/aot/aot.x64.c"
      break;
  }

  //| and cl, 0x7F
  //| cmp cl, 0x3F
  //| jle >1
  //| sub cl, 0x40
  //| xor rax, rdx
  //| xor rdx, rax
  //| xor rax, rdx
  //|1:
  //| cmp cl, 0x00
  //| jnz >2
  //| jmp >3
  //|2:
  //| shl rax, cl
  //| neg cl
  //| add cl, 0x40
  //| shr rdx, cl
  //| or rax, rdx
  //|3:
  //| op2_r_x mov, target, rax
  dasm_put(Dst, 1231);
  loc1 = riscv_reg_to_x64_reg(target);
  if (VALID_X64_REGISTER(loc1)) {
  dasm_put(Dst, 587, (loc1));
  } else {
  dasm_put(Dst, 593, Dt1(->registers[target]));
  }
#line 1302 "src/machine/aot/aot.x64.c"

  return DASM_S_OK;
}

int aot_fsr(AotContext* context, riscv_register_t target, AotValue a, AotValue b, AotValue c)
{
  int ret;
  uint32_t loc1;
  dasm_State** Dst = &context->d;

  ret = aot_mov_x64(context, X64_RAX, a);
  if (ret != DASM_S_OK) { return ret; }
  ret = aot_mov_x64(context, X64_RDX, b);
  if (ret != DASM_S_OK) { return ret; }

  switch (c.tag) {
    case AOT_TAG_REGISTER:
      //| op2_x_r mov, rcx, c.value.reg
      loc1 = riscv_reg_to_x64_reg(c.value.reg);
      if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 1020, (loc1));
      } else {
      dasm_put(Dst, 1026, Dt1(->registers[c.value.reg]));
      }
#line 1320 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_IMMEDIATE:
      //| mov ecx, c.value.i
      dasm_put(Dst, 1031, c.value.i);
#line 1323 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_X64_REGISTER:
      //| mov rcx, Rq(c.value.x64_reg)
      dasm_put(Dst, 1020, (c.value.x64_reg));
#line 1326 "src/machine/aot/aot.x64.c"
      break;
  }

  //| and cl, 0x7F
  //| cmp cl, 0x3F
  //| jle >1
  //| sub cl, 0x40
  //| xor rax, rdx
  //| xor rdx, rax
  //| xor rax, rdx
  //|1:
  //| cmp cl, 0x00
  //| jnz >2
  //| jmp >3
  //|2:
  //| shr rax, cl
  //| neg cl
  //| add cl, 0x40
  //| shl rdx, cl
  //| or rax, rdx
  //|3:
  //| op2_r_x mov, target, rax
  dasm_put(Dst, 1290);
  loc1 = riscv_reg_to_x64_reg(target);
  if (VALID_X64_REGISTER(loc1)) {
  dasm_put(Dst, 587, (loc1));
  } else {
  dasm_put(Dst, 593, Dt1(->registers[target]));
  }
#line 1348 "src/machine/aot/aot.x64.c"

  return DASM_S_OK;
}

int aot_extend(AotContext* context, riscv_register_t target, AotValue src, AotValue bits, int is_signed)
{
  uint32_t loc1;
  int ret;
  dasm_State** Dst = &context->d;

  if (bits.tag == AOT_TAG_IMMEDIATE && bits.value.i == 32) {
    /* Shortcut */
    ret = aot_mov_x64(context, X64_RAX, src);
    if (ret != DASM_S_OK) { return ret; }

    if (is_signed) {
      //| movsxd rax, eax
      dasm_put(Dst, 1348);
#line 1365 "src/machine/aot/aot.x64.c"
    } else {
      //| mov eax, eax
      dasm_put(Dst, 1352);
#line 1367 "src/machine/aot/aot.x64.c"
    }
    //| op2_r_x mov, target, rax
    loc1 = riscv_reg_to_x64_reg(target);
    if (VALID_X64_REGISTER(loc1)) {
    dasm_put(Dst, 587, (loc1));
    } else {
    dasm_put(Dst, 593, Dt1(->registers[target]));
    }
#line 1369 "src/machine/aot/aot.x64.c"
    return DASM_S_OK;
  }

  /*
   * In the general path, we do sign_extend by shifting left (64 - bits) bits,
   * then shifting right arithmetically (64 - bits) bits again.
   */
  ret = aot_mov_x64(context, X64_RAX, src);
  if (ret != DASM_S_OK) { return ret; }

  switch (bits.tag) {
    case AOT_TAG_REGISTER:
      ret = aot_mov_x64(context, X64_RDX, bits);
      if (ret != DASM_S_OK) { return ret; }

      //| mov ecx, 64
      //| and edx, 0x3F
      //| sub ecx, edx
      //| shl rax, cl
      //| mov ecx, edx
      dasm_put(Dst, 1355);
#line 1389 "src/machine/aot/aot.x64.c"
      if (is_signed) {
        //| sar rax, cl
        dasm_put(Dst, 1371);
#line 1391 "src/machine/aot/aot.x64.c"
      } else {
        //| shr rax, cl
        dasm_put(Dst, 1376);
#line 1393 "src/machine/aot/aot.x64.c"
      }
      break;
    case AOT_TAG_IMMEDIATE:
      if (bits.value.i < 64) {
        //| shl rax, (64 - bits.value.i)
        dasm_put(Dst, 1380, (64 - bits.value.i));
#line 1398 "src/machine/aot/aot.x64.c"
        if (is_signed) {
          //| sar rax, (64 - bits.value.i)
          dasm_put(Dst, 1385, (64 - bits.value.i));
#line 1400 "src/machine/aot/aot.x64.c"
        } else {
          //| shr rax, (64 - bits.value.i)
          dasm_put(Dst, 1391, (64 - bits.value.i));
#line 1402 "src/machine/aot/aot.x64.c"
        }
      }
      break;
    case AOT_TAG_X64_REGISTER:
      //| mov rdx, Rq(bits.value.x64_reg)
      //| mov ecx, 64
      //| and edx, 0x3F
      //| sub ecx, edx
      //| shl rax, cl
      //| mov ecx, edx
      dasm_put(Dst, 1396, (bits.value.x64_reg));
#line 1412 "src/machine/aot/aot.x64.c"
      if (is_signed) {
        //| sar rax, cl
        dasm_put(Dst, 1371);
#line 1414 "src/machine/aot/aot.x64.c"
      } else {
        //| shr rax, cl
        dasm_put(Dst, 1376);
#line 1416 "src/machine/aot/aot.x64.c"
      }
      break;
  }

  //| op2_r_x mov, target, rax
  loc1 = riscv_reg_to_x64_reg(target);
  if (VALID_X64_REGISTER(loc1)) {
  dasm_put(Dst, 587, (loc1));
  } else {
  dasm_put(Dst, 593, Dt1(->registers[target]));
  }
#line 1421 "src/machine/aot/aot.x64.c"

  return DASM_S_OK;
}

int aot_exit(AotContext* context, int code)
{
  dasm_State** Dst = &context->d;
  //| mov rax, code
  //| jmp ->exit
  dasm_put(Dst, 1417, code);
#line 1430 "src/machine/aot/aot.x64.c"
  return DASM_S_OK;
}

int aot_add_cycles(AotContext* context, uint64_t cycles)
{
  int ret;
  dasm_State** Dst = &context->d;
  if (cycles == 0) {
    return DASM_S_OK;
  }
  //| load_imm rax, cycles
  if (cycles > 0xFFFFFFFF && ((cycles & 0xFFFFFFFF80000000) != 0xFFFFFFFF80000000)) {
  dasm_put(Dst, 483, (unsigned int)(cycles), (unsigned int)((cycles)>>32));
  } else {
  dasm_put(Dst, 1101, cycles);
  }
#line 1441 "src/machine/aot/aot.x64.c"
  //| add machine->cycles, rax
  //| mov rax, machine->max_cycles
  //| cmp machine->cycles, rax
  //| jna >1
  dasm_put(Dst, 1426, Dt1(->cycles), Dt1(->max_cycles), Dt1(->cycles));
#line 1445 "src/machine/aot/aot.x64.c"
  ret = aot_exit(context, CKB_VM_ASM_RET_MAX_CYCLES_EXCEEDED);
  if (ret != DASM_S_OK) { return ret; }
  //|1:
  dasm_put(Dst, 171);
#line 1448 "src/machine/aot/aot.x64.c"
  return DASM_S_OK;
}

int aot_ecall(AotContext* context)
{
  return aot_exit(context, CKB_VM_ASM_RET_ECALL);
}

int aot_ebreak(AotContext* context)
{
  return aot_exit(context, CKB_VM_ASM_RET_EBREAK);
}

int aot_slowpath(AotContext* context)
{
  return aot_exit(context, CKB_VM_ASM_RET_SLOWPATH);
}

int aot_mov_pc_internal(AotContext* context, AotValue value)
{
  int ret;
  dasm_State** Dst = &context->d;

  switch (value.tag) {
    case AOT_TAG_REGISTER:
      /*
       * At encoding time we cannot tell what address to jump to here,
       * so all we can do here is to update the correct PC register,
       * exit from current function call and defer to the machine to
       * handle this.
       */
      ret = aot_mov_x64(context, X64_RCX, value);
      if (ret != DASM_S_OK) { return ret; }
      //| mov machine->pc, rcx
      dasm_put(Dst, 1124, Dt1(->pc));
#line 1482 "src/machine/aot/aot.x64.c"
      ret = aot_exit(context, CKB_VM_ASM_RET_DYNAMIC_JUMP);
      if (ret != DASM_S_OK) { return ret; }
      break;
    case AOT_TAG_IMMEDIATE:
      /*
       * It's very unlikely we will expand CKB-VM to have more than 4GB memory,
       * hence we are leveraging this fact to encode dynasm dynamic label into
       * the upper 32-bit part of immediate. This way we can both update correct
       * PC value, and do quick jumps.
       * Also, since the maximum number of labels supported now is 65535, we
       * actually only need 16 bits of the upper 32-bit part, hence we are using
       * the highest byte to store flags for different kinds of labels.
       */
      switch ((uint8_t) (value.value.i >> 56)) {
        case 0x80:
          /*
           * This means just writing the result without actually jump
           */
          //| load_imm rcx, (value.value.i & 0xFFFFFFFFFFFFFF)
          if ((value.value.i & 0xFFFFFFFFFFFFFF) > 0xFFFFFFFF && (((value.value.i & 0xFFFFFFFFFFFFFF) & 0xFFFFFFFF80000000) != 0xFFFFFFFF80000000)) {
          dasm_put(Dst, 572, (unsigned int)((value.value.i & 0xFFFFFFFFFFFFFF)), (unsigned int)(((value.value.i & 0xFFFFFFFFFFFFFF))>>32));
          } else {
          dasm_put(Dst, 577, (value.value.i & 0xFFFFFFFFFFFFFF));
          }
#line 1501 "src/machine/aot/aot.x64.c"
          //| mov qword machine->pc, rcx
          dasm_put(Dst, 1124, Dt1(->pc));
#line 1502 "src/machine/aot/aot.x64.c"
          break;
        case 0x40:
          //| mov qword machine->pc, ((uint32_t)(value.value.i & 0x7FFFFFFF))
          //| jmp =>((value.value.i >> 32) ^ 0x40000000)
          dasm_put(Dst, 1443, Dt1(->pc), ((uint32_t)(value.value.i & 0x7FFFFFFF)), ((value.value.i >> 32) ^ 0x40000000));
#line 1506 "src/machine/aot/aot.x64.c"
          break;
        case 0x0:
          //| load_imm rcx, value.value.i
          if (value.value.i > 0xFFFFFFFF && ((value.value.i & 0xFFFFFFFF80000000) != 0xFFFFFFFF80000000)) {
          dasm_put(Dst, 572, (unsigned int)(value.value.i), (unsigned int)((value.value.i)>>32));
          } else {
          dasm_put(Dst, 577, value.value.i);
          }
#line 1509 "src/machine/aot/aot.x64.c"
          //| mov machine->pc, rcx
          dasm_put(Dst, 1124, Dt1(->pc));
#line 1510 "src/machine/aot/aot.x64.c"
          ret = aot_exit(context, CKB_VM_ASM_RET_DYNAMIC_JUMP);
          if (ret != DASM_S_OK) { return ret; }
          break;
        default:
          return ERROR_INVALID_VALUE;
      }
      break;
    case AOT_TAG_X64_REGISTER:
      //| mov machine->pc, Rq(value.value.x64_reg)
      dasm_put(Dst, 1452, (value.value.x64_reg), Dt1(->pc));
#line 1519 "src/machine/aot/aot.x64.c"
      ret = aot_exit(context, CKB_VM_ASM_RET_DYNAMIC_JUMP);
      if (ret != DASM_S_OK) { return ret; }
      break;
  }

  return DASM_S_OK;
}

int aot_cond_pc(AotContext* context, AotValue condition, AotValue true_value, AotValue false_value)
{
  uint32_t loc1;
  int ret;
  dasm_State** Dst = &context->d;

  switch (condition.tag) {
    case AOT_TAG_REGISTER:
      //| op2_r_imm cmp, condition.value.reg, (uint64_t)1, rax
      if ((uint64_t)1 > 0xFFFFFFFF && (((uint64_t)1 & 0xFFFFFFFF80000000) != 0xFFFFFFFF80000000)) {
        loc1 = riscv_reg_to_x64_reg(condition.value.reg);
      dasm_put(Dst, 483, (unsigned int)((uint64_t)1), (unsigned int)(((uint64_t)1)>>32));
        if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 1137, (loc1));
        } else {
      dasm_put(Dst, 1143, Dt1(->registers[condition.value.reg]));
        }
      } else {
        loc1 = riscv_reg_to_x64_reg(condition.value.reg);
        if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 1148, (loc1), (uint64_t)1);
        } else {
      dasm_put(Dst, 1156, Dt1(->registers[condition.value.reg]), (uint64_t)1);
        }
      }
#line 1536 "src/machine/aot/aot.x64.c"
      //| jne >1
      dasm_put(Dst, 726);
#line 1537 "src/machine/aot/aot.x64.c"
      ret = aot_mov_pc_internal(context, true_value);
      if (ret != DASM_S_OK) { return ret; }
      //|1:
      dasm_put(Dst, 171);
#line 1540 "src/machine/aot/aot.x64.c"
      ret = aot_mov_pc_internal(context, false_value);
      if (ret != DASM_S_OK) { return ret; }
      break;
    case AOT_TAG_IMMEDIATE:
      ret = aot_mov_pc_internal(context, (condition.value.i == 1) ? true_value : false_value);
      if (ret != DASM_S_OK) { return ret; }
      break;
    case AOT_TAG_X64_REGISTER:
      //| cmp Rq(condition.value.x64_reg), 1
      //| jne >1
      dasm_put(Dst, 1169, (condition.value.x64_reg));
#line 1550 "src/machine/aot/aot.x64.c"
      ret = aot_mov_pc_internal(context, true_value);
      if (ret != DASM_S_OK) { return ret; }
      //|1:
      dasm_put(Dst, 171);
#line 1553 "src/machine/aot/aot.x64.c"
      ret = aot_mov_pc_internal(context, false_value);
      if (ret != DASM_S_OK) { return ret; }
      break;
  }

  return DASM_S_OK;
}

int aot_memory_write(AotContext* context, AotValue address, AotValue v, uint32_t size)
{
  int ret;
  dasm_State** Dst = &context->d;

  ret = aot_mov_x64(context, X64_RAX, address);
  if (ret != DASM_S_OK) { return ret; }

  //| mov rdx, size
  //| call ->check_write
  //| cmp rdx, 0
  //| jne >1
  //| lea rdx, machine->memory
  dasm_put(Dst, 1460, size, Dt1(->memory));
#line 1574 "src/machine/aot/aot.x64.c"
  ret = aot_mov_x64(context, X64_RCX, v);
  if (ret != DASM_S_OK) { return ret; }
  switch (size) {
    case 1:
      //| mov byte [rdx+rax], cl
      dasm_put(Dst, 1481);
#line 1579 "src/machine/aot/aot.x64.c"
      break;
    case 2:
      //| mov word [rdx+rax], cx
      dasm_put(Dst, 1485);
#line 1582 "src/machine/aot/aot.x64.c"
      break;
    case 4:
      //| mov dword [rdx+rax], ecx
      dasm_put(Dst, 1486);
#line 1585 "src/machine/aot/aot.x64.c"
      break;
    case 8:
      //| mov qword [rdx+rax], rcx
      dasm_put(Dst, 1490);
#line 1588 "src/machine/aot/aot.x64.c"
      break;
    default:
      return ERROR_INVALID_MEMORY_SIZE;
  }
  //| jmp >2
  //|1:
  //| mov rax, rdx
  //| jmp ->exit
  //|2:
  dasm_put(Dst, 1495);
#line 1597 "src/machine/aot/aot.x64.c"

  return DASM_S_OK;
}

int aot_memory_read(AotContext* context, uint32_t target, AotValue address, uint32_t size)
{
  uint32_t loc1;
  int ret;
  dasm_State** Dst = &context->d;

  ret = aot_mov_x64(context, X64_RAX, address);
  if (ret != DASM_S_OK) { return ret; }

  //| mov rdx, size
  //| call ->check_read
  //| cmp rdx, 0
  //| jne >1
  //| mov rdx, rax
  //| add rdx, size
  //| jc >1
  //| cmp rdx, CKB_VM_ASM_RISCV_MAX_MEMORY
  dasm_put(Dst, 1511, size, size, CKB_VM_ASM_RISCV_MAX_MEMORY);
#line 1618 "src/machine/aot/aot.x64.c"
  if (context->version >= 1) {
    //| ja >1
    dasm_put(Dst, 1544);
#line 1620 "src/machine/aot/aot.x64.c"
  } else {
    //| jae >1
    dasm_put(Dst, 1549);
#line 1622 "src/machine/aot/aot.x64.c"
  }
  //| lea rdx, machine->memory
  dasm_put(Dst, 1476, Dt1(->memory));
#line 1624 "src/machine/aot/aot.x64.c"
  switch (size) {
    case 1:
      //| movzx ecx, byte [rdx+rax]
      dasm_put(Dst, 1554);
#line 1627 "src/machine/aot/aot.x64.c"
      break;
    case 2:
      //| movzx ecx, word [rdx+rax]
      dasm_put(Dst, 1559);
#line 1630 "src/machine/aot/aot.x64.c"
      break;
    case 4:
      //| mov ecx, dword [rdx+rax]
      dasm_put(Dst, 1564);
#line 1633 "src/machine/aot/aot.x64.c"
      break;
    case 8:
      //| mov rcx, qword [rdx+rax]
      dasm_put(Dst, 1568);
#line 1636 "src/machine/aot/aot.x64.c"
      break;
    default:
      return ERROR_INVALID_MEMORY_SIZE;
  }
  //| op2_r_x mov, target, rcx
  loc1 = riscv_reg_to_x64_reg(target);
  if (VALID_X64_REGISTER(loc1)) {
  dasm_put(Dst, 1118, (loc1));
  } else {
  dasm_put(Dst, 1124, Dt1(->registers[target]));
  }
#line 1641 "src/machine/aot/aot.x64.c"
  //| jmp >2
  //| 1:
  dasm_put(Dst, 1162);
#line 1643 "src/machine/aot/aot.x64.c"
  ret = aot_exit(context, CKB_VM_ASM_RET_OUT_OF_BOUND);
  if (ret != DASM_S_OK) { return ret; }
  //| 2:
  dasm_put(Dst, 701);
#line 1646 "src/machine/aot/aot.x64.c"

  return DASM_S_OK;
}

static int aot_mov_internal(AotContext* context, riscv_register_t target, AotValue value, x64_register_t x64_temp_reg)
{
  uint32_t loc1, loc2;
  dasm_State** Dst = &context->d;

  switch (value.tag) {
    case AOT_TAG_REGISTER:
      if (target == value.value.reg) { return DASM_S_OK; }
      //| op2_r_r mov, target, value.value.reg, Rq(x64_temp_reg)
      loc1 = riscv_reg_to_x64_reg(target);
      loc2 = riscv_reg_to_x64_reg(value.value.reg);
      if (VALID_X64_REGISTER(loc1) && VALID_X64_REGISTER(loc2)) {
      dasm_put(Dst, 1573, (loc2), (loc1));
      } else if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 1581, (loc1), Dt1(->registers[value.value.reg]));
      } else if (VALID_X64_REGISTER(loc2)) {
      dasm_put(Dst, 1452, (loc2), Dt1(->registers[target]));
      } else {
      dasm_put(Dst, 1589, (x64_temp_reg), Dt1(->registers[value.value.reg]), (x64_temp_reg), Dt1(->registers[target]));
      }
#line 1659 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_IMMEDIATE:
      //| op2_r_imm mov, target, value.value.i, Rq(x64_temp_reg)
      if (value.value.i > 0xFFFFFFFF && ((value.value.i & 0xFFFFFFFF80000000) != 0xFFFFFFFF80000000)) {
        loc1 = riscv_reg_to_x64_reg(target);
      dasm_put(Dst, 1604, (x64_temp_reg), (unsigned int)(value.value.i), (unsigned int)((value.value.i)>>32));
        if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 1573, (x64_temp_reg), (loc1));
        } else {
      dasm_put(Dst, 1452, (x64_temp_reg), Dt1(->registers[target]));
        }
      } else {
        loc1 = riscv_reg_to_x64_reg(target);
        if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 754, (loc1), value.value.i);
        } else {
      dasm_put(Dst, 761, Dt1(->registers[target]), value.value.i);
        }
      }
#line 1662 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_X64_REGISTER:
      //| op2_r_x mov, target, Rq(value.value.x64_reg)
      loc1 = riscv_reg_to_x64_reg(target);
      if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 1573, (value.value.x64_reg), (loc1));
      } else {
      dasm_put(Dst, 1452, (value.value.x64_reg), Dt1(->registers[target]));
      }
#line 1665 "src/machine/aot/aot.x64.c"
      break;
  }

  return DASM_S_OK;
}

static int aot_mov_x64(AotContext* context, x64_register_t x64_target, AotValue value)
{
  uint32_t loc1;
  dasm_State** Dst = &context->d;
  switch (value.tag) {
    case AOT_TAG_REGISTER:
      //| op2_x_r mov, Rq(x64_target), value.value.reg
      loc1 = riscv_reg_to_x64_reg(value.value.reg);
      if (VALID_X64_REGISTER(loc1)) {
      dasm_put(Dst, 1573, (loc1), (x64_target));
      } else {
      dasm_put(Dst, 1581, (x64_target), Dt1(->registers[value.value.reg]));
      }
#line 1678 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_IMMEDIATE:
      //| load_imm Rq(x64_target), value.value.i
      if (value.value.i > 0xFFFFFFFF && ((value.value.i & 0xFFFFFFFF80000000) != 0xFFFFFFFF80000000)) {
      dasm_put(Dst, 1604, (x64_target), (unsigned int)(value.value.i), (unsigned int)((value.value.i)>>32));
      } else {
      dasm_put(Dst, 754, (x64_target), value.value.i);
      }
#line 1681 "src/machine/aot/aot.x64.c"
      break;
    case AOT_TAG_X64_REGISTER:
      if (x64_target == value.value.x64_reg) { return DASM_S_OK; }
      //| mov Rq(x64_target), Rq(value.value.x64_reg)
      dasm_put(Dst, 1573, (value.value.x64_reg), (x64_target));
#line 1685 "src/machine/aot/aot.x64.c"
      break;
  }
  return DASM_S_OK;
}
