/*
 * TODO: change macros to assembly directives due to MSVC compatibility issues
 */
#define CKB_VM_ASM_GENERATE_LABEL_TABLES 1
#include "cdefinitions_generated.h"

#ifdef _WIN32
#define IS_WINDOWS 1
#endif

#define INT64_MIN 0x8000000000000000
#define UINT64_MAX 0xffffffffffffffff

#ifdef IS_WINDOWS
#define ARG1 %rcx
#define ARG2 %rdx
#define ARG3 %r8
#else
#define ARG1 %rdi
#define ARG2 %rsi
#define ARG3 %rdx
#endif

#ifdef IS_WINDOWS
#define PREPCALL \
  push %rdi; \
  push %rsi; \
  push %rax; \
  push %rcx; \
  push %rdx; \
  push %r8; \
  push %r9; \
  sub $32, %rsp;
#define POSTCALL \
  add $32, %rsp; \
  pop %r9; \
  pop %r8; \
  pop %rdx; \
  pop %rcx; \
  pop %rax; \
  pop %rsi; \
  pop %rdi;
#else
#define PREPCALL \
  push %rdi; \
  push %rsi; \
  push %rax; \
  push %rcx; \
  push %rdx; \
  push %r8; \
  push %r9;
#define POSTCALL \
  pop %r9; \
  pop %r8; \
  pop %rdx; \
  pop %rcx; \
  pop %rax; \
  pop %rsi; \
  pop %rdi;
#endif

/* rax is used both in Microsoft x64 and System V AMD64 ABI */
#define ARG_RETd %eax

#define MACHINE %rsi
#define TRACE %rbx

/*
 * INST_PC contains the current address of decoded Instruction in
 * Trace item, which is different from the RISC-V PC
 */
#define INST_PC %r8
#define INST_ARGS %r9

/*
 * Rules to meet when considering register allocations:
 * * RD and TEMP1 cannot be %rcx to set aside %cl for shifts
 * * RS2r and TEMP1 cannot be %rax to allow using imul and idiv
 * * RS2r cannot be %rdx to allow using idiv
 */
#define RD_RS2s %rax
#define RD RD_RS2s
#define RS1 %rdx
#define RS2r %rbp
#define RS2s RD_RS2s
#define RS3 %r12
#define IMMEDIATE %rcx
#define TEMP1 %rdi
#define TEMP2 %r10
#define TEMP3 %r11

#define RDd_RS2sd %eax
#define RDd RDd_RS2sd
#define RS1d %edx
#define RS1h %dx
#define RS1b %dl
#define RS2rd %ebp
#define RS2rb %bpl
#define RS2sd %eax
#define RS2sb %al
#define RS2sh %ax
#define RS3d %r12d
#define IMMEDIATEb %cl
#define IMMEDIATEd %ecx
#define TEMP1b %dil
#define TEMP1d %edi
#define TEMP2d %r10d
#define TEMP2b %r10b
#define TEMP3d %r11d
#define TEMP3b %r11b

#define PC_ADDRESS \
  CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_PC(MACHINE)

#define ZERO_ADDRESS \
  (CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_REGISTERS)(MACHINE)

#define SP_ADDRESS \
  (CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_REGISTERS + CKB_VM_ASM_REGISTER_SP * 8)(MACHINE)

#define REGISTER_ADDRESS(r) \
  CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_REGISTERS(MACHINE, r, 8)

/*
 * Those macros provide slight abstractions over register allocations,
 * they might change when we alter register allocations. For example:
 *
 * * A push operation needs to do nothing if the variable to push is not
 * the register we need to save
 * * A move operation becomes nop if the variable is assigned the same
 * register as the target
 */
#define PUSH_RD_IF_RAX push %rax
#define PUSH_RD_IF_RDX
#define POP_RD_IF_RAX pop %rax
#define POP_RD_IF_RDX
#define PUSH_RS1_IF_RAX
#define PUSH_RS1_IF_RDX push %rdx
#define POP_RS1_IF_RAX
#define POP_RS1_IF_RDX pop %rdx

#define MOV_RS1_TO_RAX movq RS1, %rax
#define MOV_RAX_TO_RS1 movq %rax, RS1
#define MOV_RS2r_TO_RAX movq RS2r, %rax
#define MOV_RAX_TO_RS2r movq %rax, RS2r
#define MOV_RS1_TO_RDX
#define MOV_RDX_TO_RS1
#define MOV_RS2r_TO_RDX movq RS2r, %rdx
#define MOV_RDX_TO_RS2r movq %rdx, RS2r
#ifdef IS_WINDOWS
#define MOV_TEMP1_TO_ARG1 movq TEMP1, ARG1
#else
#define MOV_TEMP1_TO_ARG1
#endif

#ifdef __APPLE__
#define CALL_MEMSET call _memset
#elif defined IS_WINDOWS
#define CALL_MEMSET call memset
#else
#define CALL_MEMSET call memset@plt
#endif

/*
 * Make sure TEMP1 stores the frame index.
 */
#define ZEROED_MEMORY \
  PREPCALL; \
  MOV_TEMP1_TO_ARG1; \
  shl $CKB_VM_ASM_MEMORY_FRAME_SHIFTS, ARG1; \
  addq $CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_MEMORY, ARG1; \
  addq MACHINE, ARG1; \
  xor ARG2, ARG2; \
  movq $CKB_VM_ASM_MEMORY_FRAMESIZE, ARG3; \
  CALL_MEMSET; \
  POSTCALL;

#define CHECK_READ(address_reg, length) \
  movq address_reg, TEMP1; \
  shr $CKB_VM_ASM_MEMORY_FRAME_SHIFTS, TEMP1; \
  cmp $CKB_VM_ASM_MEMORY_FRAMES, TEMP1; \
  jae .exit_out_of_bound; \
  movzbl CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_FRAMES(MACHINE, TEMP1), TEMP2d; \
  cmp $0, TEMP2d; \
  jne 1f; \
  movb $1, CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_FRAMES(MACHINE, TEMP1); \
  ZEROED_MEMORY; \
1: \
  movq address_reg, TEMP1; \
  addq $length, TEMP1; \
  subq $1, TEMP1; \
  shr $CKB_VM_ASM_MEMORY_FRAME_SHIFTS, TEMP1; \
  cmp $CKB_VM_ASM_MEMORY_FRAMES, TEMP1; \
  jae .exit_out_of_bound; \
  movzbl CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_FRAMES(MACHINE, TEMP1), TEMP2d; \
  cmp $0, TEMP2d; \
  jne 2f; \
  movb $1, CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_FRAMES(MACHINE, TEMP1);\
  ZEROED_MEMORY; \
2:

#define CHECK_WRITE(address_reg, temp_regd, length) \
  movq address_reg, TEMP1; \
  shr $CKB_VM_ASM_RISCV_PAGE_SHIFTS, TEMP1; \
  cmp $CKB_VM_ASM_RISCV_PAGES, TEMP1; \
  jae .exit_out_of_bound; \
  movzbl CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_FLAGS(MACHINE, TEMP1), temp_regd; \
  and $CKB_VM_ASM_MEMORY_FLAG_WXORX_BIT, temp_regd; \
  cmp $CKB_VM_ASM_MEMORY_FLAG_WRITABLE, temp_regd; \
  jne .exit_invalid_permission; \
  movq TEMP1, TEMP2; \
  shr $CKB_VM_ASM_MEMORY_FRAME_PAGE_SHIFTS, TEMP1; \
  movzbl CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_FRAMES(MACHINE, TEMP1), temp_regd; \
  cmp $0, temp_regd; \
  jne 1f; \
  movb $1, CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_FRAMES(MACHINE, TEMP1); \
  ZEROED_MEMORY; \
1: \
  movq TEMP2, TEMP1; \
  addq $1, TEMP1; \
  shl $CKB_VM_ASM_RISCV_PAGE_SHIFTS, TEMP1; \
  movq address_reg, TEMP2; \
  addq $length, TEMP2; \
  cmp TEMP1, TEMP2; \
  jbe 2f; \
  shr $CKB_VM_ASM_RISCV_PAGE_SHIFTS, TEMP1; \
  cmp $CKB_VM_ASM_RISCV_PAGES, TEMP1; \
  jae .exit_out_of_bound; \
  movzbl CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_FLAGS(MACHINE, TEMP1), temp_regd; \
  and $CKB_VM_ASM_MEMORY_FLAG_WXORX_BIT, temp_regd; \
  cmp $CKB_VM_ASM_MEMORY_FLAG_WRITABLE, temp_regd; \
  jne .exit_invalid_permission; \
  shr $CKB_VM_ASM_MEMORY_FRAME_PAGE_SHIFTS, TEMP1; \
  movzbl CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_FRAMES(MACHINE, TEMP1), temp_regd; \
  cmp $0, temp_regd; \
  jne 2f; \
  movb $1, CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_FRAMES(MACHINE, TEMP1); \
  ZEROED_MEMORY; \
2:

#define ADDRESS_TO_SLOT_ADDRESS(r) \
  shr $5, r; \
  andq $8191, r; \
  imul $CKB_VM_ASM_TRACE_STRUCT_SIZE, r; \
  lea CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_TRACES(MACHINE, r), r

#define WRITE_RD_VALUE(v, temp_reg) \
  movq v, temp_reg; \
  movq temp_reg, REGISTER_ADDRESS(RD); \
  movq $0, ZERO_ADDRESS

#define WRITE_RD(v) \
  movq v, REGISTER_ADDRESS(RD); \
  movq $0, ZERO_ADDRESS

#define NEXT_INST \
  movq (INST_ARGS), %rcx; \
  addq $8, INST_ARGS; \
  movzbl %ch, RDd_RS2sd; \
  sar $32, %rcx; \
  movq (INST_PC), TEMP1; \
  addq $8, INST_PC; \
  jmp *TEMP1

#define DECODE_R \
  movzbl %cl, RS1d; \
  movzbl %ch, RS2rd

#define DECODE_I \
  movzbl %cl, RS1d; \
  sar $8, %rcx

#define DECODE_S \
  movzbl %cl, RS1d; \
  sar $8, %rcx

#define DECODE_U

#define DECODE_R4 \
  movzbl %cl, RS1d; \
  movzbl %ch, RS2rd; \
  sar $16, %rcx; \
  movzbl %cl, RS3d

#ifdef __APPLE__
.globl _ckb_vm_x64_execute
_ckb_vm_x64_execute:
#else
.globl ckb_vm_x64_execute
ckb_vm_x64_execute:
#endif
#ifdef IS_WINDOWS
  push %rsi
  push %rdi
#endif
  push %rbp
  push %rbx
  mov ARG1, MACHINE
.p2align 3
.CKB_VM_ASM_LABEL_OP_CUSTOM_TRACE_END:
.prepare_trace:
  movq PC_ADDRESS, %rax
  mov %eax, %ecx
  shr $5, %eax
  andq $8191, %rax
  imul $CKB_VM_ASM_TRACE_STRUCT_SIZE, %eax
  lea CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_TRACES(MACHINE, %rax), TRACE
  movq CKB_VM_ASM_TRACE_OFFSET_ADDRESS(TRACE), %rdx
  cmp %rcx, %rdx
  jne .exit_trace
  movzbl CKB_VM_ASM_TRACE_OFFSET_LENGTH(TRACE), %edx
  cmp $0, %rdx
  je .exit_trace
  movq CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_CYCLES(MACHINE), %rax
  addq CKB_VM_ASM_TRACE_OFFSET_CYCLES(TRACE), %rax
  cmp CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_MAX_CYCLES(MACHINE), %rax
  ja .exit_max_cycles_exceeded
  movq %rax, CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_CYCLES(MACHINE)
  addq %rdx, PC_ADDRESS
  lea CKB_VM_ASM_TRACE_OFFSET_INSTRUCTIONS(TRACE), INST_ARGS
  lea CKB_VM_ASM_TRACE_OFFSET_THREAD(TRACE), INST_PC
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_ADDI:
.CKB_VM_ASM_LABEL_OP_RVC_ADDI:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  addq IMMEDIATE, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_ADD:
.CKB_VM_ASM_LABEL_OP_RVC_ADD:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  addq REGISTER_ADDRESS(RS2r), RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_ADDIW:
.CKB_VM_ASM_LABEL_OP_RVC_ADDIW:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  addq IMMEDIATE, RS1
  movslq RS1d, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_ADDW:
.CKB_VM_ASM_LABEL_OP_RVC_ADDW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  addq REGISTER_ADDRESS(RS2r), RS1
  movslq RS1d, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_AND:
.CKB_VM_ASM_LABEL_OP_RVC_AND:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  andq REGISTER_ADDRESS(RS2r), RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_ANDI:
.CKB_VM_ASM_LABEL_OP_RVC_ANDI:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  andq IMMEDIATE, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_AUIPC:
  DECODE_U
  movq PC_ADDRESS, RS1
  subq $4, RS1
  addq IMMEDIATE, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_BEQ:
  DECODE_S
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2s), RS2s
  cmpq RS2s, RS1
  je .i_branch_success
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_BGE:
  DECODE_S
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2s), RS2s
  cmpq RS2s, RS1
  jge .i_branch_success
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_BGEU:
  DECODE_S
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2s), RS2s
  cmpq RS2s, RS1
  jae .i_branch_success
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_BLT:
  DECODE_S
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2s), RS2s
  cmpq RS2s, RS1
  jl .i_branch_success
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_BLTU:
  DECODE_S
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2s), RS2s
  cmpq RS2s, RS1
  jb .i_branch_success
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_BNE:
  DECODE_S
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2s), RS2s
  cmpq RS2s, RS1
  jne .i_branch_success
  NEXT_INST
.i_branch_success:
  movq PC_ADDRESS, RS1
  subq $4, RS1
  addq IMMEDIATE, RS1
  movq RS1, PC_ADDRESS
  jmp .prepare_trace
.p2align 3
.CKB_VM_ASM_LABEL_OP_DIV:
  DECODE_R
  push RD
  movq $INT64_MIN, RD
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  cmp RD, RS1
  jne .div_branch1
  cmp $-1, RS2r
  jne .div_branch1
  jmp .div_branch3
.div_branch1:
  cmp $0, RS2r
  jne .div_branch2
  movq $UINT64_MAX, RS1
  jmp .div_branch3
.div_branch2:
  MOV_RS1_TO_RAX
  cqo
  idivq RS2r
  MOV_RAX_TO_RS1
.div_branch3:
  pop RD
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_DIVU:
  DECODE_R
  movq REGISTER_ADDRESS(RS2r), RS2r
  cmp $0, RS2r
  jne .divu_branch2
  WRITE_RD_VALUE($UINT64_MAX, RS2r)
  NEXT_INST
.divu_branch2:
  PUSH_RD_IF_RAX
  PUSH_RD_IF_RDX
  movq REGISTER_ADDRESS(RS1), %rax
  xorq %rdx, %rdx
  divq RS2r
  mov %rax, RS2r
  POP_RD_IF_RDX
  POP_RD_IF_RAX
  WRITE_RD(RS2r)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_DIVUW:
  DECODE_R
  movq REGISTER_ADDRESS(RS2r), RS2r
  mov RS2rd, RS2rd
  cmp $0, RS2r
  jne .divuw_branch2
  WRITE_RD_VALUE($UINT64_MAX, RS2r)
  NEXT_INST
.divuw_branch2:
  PUSH_RD_IF_RAX
  PUSH_RD_IF_RDX
  movq REGISTER_ADDRESS(RS1), %rax
  mov %eax, %eax
  xorq %rdx, %rdx
  divq RS2r
  mov %rax, RS2r
  POP_RD_IF_RDX
  POP_RD_IF_RAX
  movslq RS2rd, RS2r
  WRITE_RD(RS2r)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_DIVW:
  DECODE_R
  push RD
  movq $INT64_MIN, RD
  movq REGISTER_ADDRESS(RS1), RS1
  movslq RS1d, RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  movslq RS2rd, RS2r
  cmp RD, RS1
  jne .divw_branch1
  cmp $-1, RS2r
  jne .divw_branch1
  jmp .divw_branch3
.divw_branch1:
  cmp $0, RS2r
  jne .divw_branch2
  movq $UINT64_MAX, RS1
  jmp .divw_branch3
.divw_branch2:
  MOV_RS1_TO_RAX
  cqo
  idivq RS2r
  MOV_RAX_TO_RS1
.divw_branch3:
  pop RD
  movslq RS1d, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_EBREAK:
  DECODE_U
  mov $CKB_VM_ASM_RET_EBREAK, ARG_RETd
  jmp .exit
.p2align 3
.CKB_VM_ASM_LABEL_OP_ECALL:
  DECODE_U
  mov $CKB_VM_ASM_RET_ECALL, ARG_RETd
  jmp .exit
.p2align 3
.CKB_VM_ASM_LABEL_OP_FENCE:
.CKB_VM_ASM_LABEL_OP_FENCEI:
.CKB_VM_ASM_LABEL_OP_RVC_NOP:
.CKB_VM_ASM_LABEL_OP_RVC_SLLI64:
.CKB_VM_ASM_LABEL_OP_RVC_SRAI64:
.CKB_VM_ASM_LABEL_OP_RVC_SRLI64:
  DECODE_U
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_JAL:
  DECODE_U
  movq PC_ADDRESS, RS1
  WRITE_RD(RS1)
  subq $4, RS1
  addq IMMEDIATE, RS1
  movq RS1, PC_ADDRESS
  jmp .prepare_trace
.p2align 3
.CKB_VM_ASM_LABEL_OP_JALR:
  DECODE_I
  movq PC_ADDRESS, TEMP1
  WRITE_RD(TEMP1)
  movq REGISTER_ADDRESS(RS1), TEMP1
  addq IMMEDIATE, TEMP1
  andq $-2, TEMP1
  movq TEMP1, PC_ADDRESS
  jmp .prepare_trace
.p2align 3
.CKB_VM_ASM_LABEL_OP_LB:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  addq IMMEDIATE, RS1
  movq RS1, TEMP1
  cmp $CKB_VM_ASM_RISCV_MAX_MEMORY, TEMP1
  jae .exit_out_of_bound
  addq $1, TEMP1
  cmp $CKB_VM_ASM_RISCV_MAX_MEMORY, TEMP1
  jae .exit_out_of_bound
  CHECK_READ(RS1, 1)
  movsbq CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_MEMORY(MACHINE, RS1), RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_LBU:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  addq IMMEDIATE, RS1
  movq RS1, TEMP1
  cmp $CKB_VM_ASM_RISCV_MAX_MEMORY, TEMP1
  jae .exit_out_of_bound
  addq $1, TEMP1
  cmp $CKB_VM_ASM_RISCV_MAX_MEMORY, TEMP1
  jae .exit_out_of_bound
  CHECK_READ(RS1, 1)
  movzbq CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_MEMORY(MACHINE, RS1), RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_LD:
.CKB_VM_ASM_LABEL_OP_RVC_LD:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  addq IMMEDIATE, RS1
  movq RS1, TEMP1
  cmp $CKB_VM_ASM_RISCV_MAX_MEMORY, TEMP1
  jae .exit_out_of_bound
  addq $8, TEMP1
  cmp $CKB_VM_ASM_RISCV_MAX_MEMORY, TEMP1
  jae .exit_out_of_bound
  CHECK_READ(RS1, 8)
  movq CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_MEMORY(MACHINE, RS1), RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_LH:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  addq IMMEDIATE, RS1
  movq RS1, TEMP1
  cmp $CKB_VM_ASM_RISCV_MAX_MEMORY, TEMP1
  jae .exit_out_of_bound
  addq $2, TEMP1
  cmp $CKB_VM_ASM_RISCV_MAX_MEMORY, TEMP1
  jae .exit_out_of_bound
  CHECK_READ(RS1, 2)
  movswq CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_MEMORY(MACHINE, RS1), RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_LHU:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  addq IMMEDIATE, RS1
  movq RS1, TEMP1
  cmp $CKB_VM_ASM_RISCV_MAX_MEMORY, TEMP1
  jae .exit_out_of_bound
  addq $2, TEMP1
  cmp $CKB_VM_ASM_RISCV_MAX_MEMORY, TEMP1
  jae .exit_out_of_bound
  CHECK_READ(RS1, 2)
  movzwq CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_MEMORY(MACHINE, RS1), RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_LUI:
.CKB_VM_ASM_LABEL_OP_RVC_LI:
.CKB_VM_ASM_LABEL_OP_RVC_LUI:
.CKB_VM_ASM_LABEL_OP_CUSTOM_LOAD_IMM:
  DECODE_U
  WRITE_RD(IMMEDIATE)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_LW:
.CKB_VM_ASM_LABEL_OP_RVC_LW:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  addq IMMEDIATE, RS1
  movq RS1, TEMP1
  cmp $CKB_VM_ASM_RISCV_MAX_MEMORY, TEMP1
  jae .exit_out_of_bound
  addq $4, TEMP1
  cmp $CKB_VM_ASM_RISCV_MAX_MEMORY, TEMP1
  jae .exit_out_of_bound
  CHECK_READ(RS1, 4)
  movslq CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_MEMORY(MACHINE, RS1), RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_LWU:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  addq IMMEDIATE, RS1
  movq RS1, TEMP1
  cmp $CKB_VM_ASM_RISCV_MAX_MEMORY, TEMP1
  jae .exit_out_of_bound
  addq $4, TEMP1
  cmp $CKB_VM_ASM_RISCV_MAX_MEMORY, TEMP1
  jae .exit_out_of_bound
  CHECK_READ(RS1, 4)
  mov CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_MEMORY(MACHINE, RS1), RS1d
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_MUL:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  imul REGISTER_ADDRESS(RS2r), RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_MULH:
  DECODE_R
  PUSH_RD_IF_RAX
  PUSH_RD_IF_RDX
  movq REGISTER_ADDRESS(RS1), %rax
  imulq REGISTER_ADDRESS(RS2r)
  MOV_RDX_TO_RS2r
  POP_RD_IF_RDX
  POP_RD_IF_RAX
  WRITE_RD(RS2r)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_MULHSU:
  DECODE_R
  PUSH_RD_IF_RAX
  PUSH_RD_IF_RDX
  PUSH_RS1_IF_RAX
  PUSH_RS1_IF_RDX
  movq REGISTER_ADDRESS(RS1), %rax
  test %rax, %rax
  jns .mulhsu_branch1
  neg %rax
  mulq REGISTER_ADDRESS(RS2r)
  xor $-1, %rdx
  movq %rdx, TEMP1
  POP_RS1_IF_RDX
  POP_RS1_IF_RAX
  movq REGISTER_ADDRESS(RS1), %rax
  imulq REGISTER_ADDRESS(RS2r)
  test %rax, %rax
  setz %al
  movzbl %al, %eax
  addq %rax, TEMP1
  POP_RD_IF_RDX
  POP_RD_IF_RAX
  WRITE_RD(TEMP1)
  NEXT_INST
.mulhsu_branch1:
  mulq REGISTER_ADDRESS(RS2r)
  movq %rdx, TEMP1
  POP_RS1_IF_RDX
  POP_RS1_IF_RAX
  POP_RD_IF_RDX
  POP_RD_IF_RAX
  WRITE_RD(TEMP1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_MULHU:
  DECODE_R
  PUSH_RD_IF_RAX
  PUSH_RD_IF_RDX
  movq REGISTER_ADDRESS(RS1), %rax
  mulq REGISTER_ADDRESS(RS2r)
  movq %rdx, RS2r
  POP_RD_IF_RDX
  POP_RD_IF_RAX
  WRITE_RD(RS2r)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_MULW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  imul RS2rd, RS1d
  movslq RS1d, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_OR:
.CKB_VM_ASM_LABEL_OP_RVC_OR:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  orq REGISTER_ADDRESS(RS2r), RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_ORI:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  orq IMMEDIATE, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_REM:
  DECODE_R
  push RD
  movq $INT64_MIN, RD
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  cmp RD, RS1
  jne .rem_branch1
  cmp $-1, RS2r
  jne .rem_branch1
  xorq RS1, RS1
  jmp .rem_branch3
.rem_branch1:
  cmp $0, RS2r
  jne .rem_branch2
  jmp .rem_branch3
.rem_branch2:
  MOV_RS1_TO_RAX
  cqo
  idivq RS2r
  MOV_RDX_TO_RS1
.rem_branch3:
  pop RD
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_REMU:
  DECODE_R
  movq REGISTER_ADDRESS(RS2r), RS2r
  cmp $0, RS2r
  jne .remu_branch2
  movq REGISTER_ADDRESS(RS1), RS1
  WRITE_RD(RS1)
  NEXT_INST
.remu_branch2:
  PUSH_RD_IF_RAX
  PUSH_RD_IF_RDX
  movq REGISTER_ADDRESS(RS1), %rax
  xorq %rdx, %rdx
  divq RS2r
  mov %rdx, RS2r
  POP_RD_IF_RDX
  POP_RD_IF_RAX
  WRITE_RD(RS2r)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_REMUW:
  DECODE_R
  movq REGISTER_ADDRESS(RS2r), RS2r
  mov RS2rd, RS2rd
  cmp $0, RS2r
  jne .remuw_branch2
  movq REGISTER_ADDRESS(RS1), RS1
  movslq RS1d, RS1
  WRITE_RD(RS1)
  NEXT_INST
.remuw_branch2:
  PUSH_RD_IF_RAX
  PUSH_RD_IF_RDX
  movq REGISTER_ADDRESS(RS1), %rax
  mov %eax, %eax
  xorq %rdx, %rdx
  divq RS2r
  mov %rdx, RS2r
  POP_RD_IF_RDX
  POP_RD_IF_RAX
  movslq RS2rd, RS2r
  WRITE_RD(RS2r)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_REMW:
  DECODE_R
  push RD
  movq $INT64_MIN, RD
  movq REGISTER_ADDRESS(RS1), RS1
  movslq RS1d, RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  movslq RS2rd, RS2r
  cmp RD, RS1
  jne .remw_branch1
  cmp $-1, RS2r
  jne .remw_branch1
  xorq RS1, RS1
  jmp .remw_branch3
.remw_branch1:
  cmp $0, RS2r
  jne .remw_branch2
  jmp .remw_branch3
.remw_branch2:
  MOV_RS1_TO_RAX
  cqo
  idivq RS2r
  MOV_RDX_TO_RS1
.remw_branch3:
  pop RD
  movslq RS1d, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SB:
  DECODE_S
  movq REGISTER_ADDRESS(RS1), RS1
  addq IMMEDIATE, RS1
  CHECK_WRITE(RS1, RS2rd, 1)
  movq REGISTER_ADDRESS(RS2s), RS2s
  mov RS2sb, CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_MEMORY(MACHINE, RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SD:
.CKB_VM_ASM_LABEL_OP_RVC_SD:
  DECODE_S
  movq REGISTER_ADDRESS(RS1), RS1
  addq IMMEDIATE, RS1
  CHECK_WRITE(RS1, RS2rd, 8)
  movq REGISTER_ADDRESS(RS2s), RS2s
  movq RS2s, CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_MEMORY(MACHINE, RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SH:
  DECODE_S
  movq REGISTER_ADDRESS(RS1), RS1
  addq IMMEDIATE, RS1
  CHECK_WRITE(RS1, RS2rd, 2)
  movq REGISTER_ADDRESS(RS2s), RS2s
  mov RS2sh, CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_MEMORY(MACHINE, RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SLL:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), TEMP1
  movq REGISTER_ADDRESS(RS2r), %rcx
  shl %cl, TEMP1
  WRITE_RD(TEMP1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SLLI:
.CKB_VM_ASM_LABEL_OP_RVC_SLLI:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), TEMP1
  movq IMMEDIATE, %rcx
  shl %cl, TEMP1
  WRITE_RD(TEMP1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SLLIW:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), TEMP1
  movq IMMEDIATE, %rcx
  shl %cl, TEMP1
  movslq TEMP1d, TEMP1
  WRITE_RD(TEMP1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SLLW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), TEMP1
  movq REGISTER_ADDRESS(RS2r), %rcx
  and $0x1F, %ecx
  shl %cl, TEMP1
  movslq TEMP1d, TEMP1
  WRITE_RD(TEMP1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SLT:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  cmpq RS2r, RS1
  setl RS1b
  movzbl RS1b, RS1d
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SLTI:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  cmpq IMMEDIATE, RS1
  setl RS1b
  movzbl RS1b, RS1d
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SLTIU:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  cmpq IMMEDIATE, RS1
  setb RS1b
  movzbl RS1b, RS1d
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SLTU:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  cmpq RS2r, RS1
  setb RS1b
  movzbl RS1b, RS1d
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SRA:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), TEMP1
  movq REGISTER_ADDRESS(RS2r), %rcx
  sar %cl, TEMP1
  WRITE_RD(TEMP1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SRAI:
.CKB_VM_ASM_LABEL_OP_RVC_SRAI:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), TEMP1
  movq IMMEDIATE, %rcx
  sar %cl, TEMP1
  WRITE_RD(TEMP1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SRAIW:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), TEMP1
  movq IMMEDIATE, %rcx
  sar %cl, TEMP1d
  movslq TEMP1d, TEMP1
  WRITE_RD(TEMP1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SRAW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), TEMP1
  movq REGISTER_ADDRESS(RS2r), %rcx
  and $0x1F, %ecx
  sar %cl, TEMP1d
  movslq TEMP1d, TEMP1
  WRITE_RD(TEMP1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SRL:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), TEMP1
  movq REGISTER_ADDRESS(RS2r), %rcx
  shr %cl, TEMP1
  WRITE_RD(TEMP1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SRLI:
.CKB_VM_ASM_LABEL_OP_RVC_SRLI:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), TEMP1
  movq IMMEDIATE, %rcx
  shr %cl, TEMP1
  WRITE_RD(TEMP1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SRLIW:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), TEMP1
  movq IMMEDIATE, %rcx
  shr %cl, TEMP1d
  movslq TEMP1d, TEMP1
  WRITE_RD(TEMP1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SRLW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), TEMP1
  movq REGISTER_ADDRESS(RS2r), %rcx
  and $0x1F, %ecx
  shr %cl, TEMP1d
  movslq TEMP1d, TEMP1
  WRITE_RD(TEMP1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SUB:
.CKB_VM_ASM_LABEL_OP_RVC_SUB:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  subq REGISTER_ADDRESS(RS2r), RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SUBW:
.CKB_VM_ASM_LABEL_OP_RVC_SUBW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  subq REGISTER_ADDRESS(RS2r), RS1
  movslq RS1d, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SW:
.CKB_VM_ASM_LABEL_OP_RVC_SW:
  DECODE_S
  movq REGISTER_ADDRESS(RS1), RS1
  addq IMMEDIATE, RS1
  CHECK_WRITE(RS1, RS2rd, 4)
  movq REGISTER_ADDRESS(RS2s), RS2s
  mov RS2sd, CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_MEMORY(MACHINE, RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_XOR:
.CKB_VM_ASM_LABEL_OP_RVC_XOR:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  xorq REGISTER_ADDRESS(RS2r), RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_XORI:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  xorq IMMEDIATE, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_RVC_ADDI16SP:
  DECODE_I
  addq IMMEDIATE, SP_ADDRESS
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_RVC_ADDI4SPN:
  DECODE_U
  movq SP_ADDRESS, RS1
  addq IMMEDIATE, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_RVC_BEQZ:
  DECODE_S
  movq REGISTER_ADDRESS(RS1), RS1
  cmpq $0, RS1
  je .rvc_branch_success
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_RVC_BNEZ:
  DECODE_S
  movq REGISTER_ADDRESS(RS1), RS1
  cmpq $0, RS1
  jne .rvc_branch_success
  NEXT_INST
.rvc_branch_success:
  movq PC_ADDRESS, RS1
  subq $2, RS1
  addq IMMEDIATE, RS1
  movq RS1, PC_ADDRESS
  jmp .prepare_trace
.p2align 3
.CKB_VM_ASM_LABEL_OP_RVC_EBREAK:
  DECODE_U
  mov $CKB_VM_ASM_RET_EBREAK, ARG_RETd
  jmp .exit
.p2align 3
.CKB_VM_ASM_LABEL_OP_RVC_J:
  DECODE_U
  movq PC_ADDRESS, RS1
  subq $2, RS1
  addq IMMEDIATE, RS1
  movq RS1, PC_ADDRESS
  jmp .prepare_trace
.p2align 3
.CKB_VM_ASM_LABEL_OP_RVC_JAL:
  DECODE_U
  movq PC_ADDRESS, RS1
  movq RS1, (CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_REGISTERS + 1 * 8)(MACHINE)
  subq $2, RS1
  addq IMMEDIATE, RS1
  movq RS1, PC_ADDRESS
  jmp .prepare_trace
.p2align 3
.CKB_VM_ASM_LABEL_OP_RVC_JALR:
  DECODE_S
  movq PC_ADDRESS, %rcx
  movq %rcx, (CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_REGISTERS + 1 * 8)(MACHINE)
  movq REGISTER_ADDRESS(RS1), %rcx
  andq $-2, %rcx
  movq %rcx, PC_ADDRESS
  jmp .prepare_trace
.p2align 3
.CKB_VM_ASM_LABEL_OP_RVC_JR:
  DECODE_S
  movq REGISTER_ADDRESS(RS1), %rcx
  andq $-2, %rcx
  movq %rcx, PC_ADDRESS
  jmp .prepare_trace
.p2align 3
.CKB_VM_ASM_LABEL_OP_RVC_LDSP:
  DECODE_U
  movq SP_ADDRESS, RS1
  addq IMMEDIATE, RS1
  movq RS1, TEMP1
  cmp $CKB_VM_ASM_RISCV_MAX_MEMORY, TEMP1
  jae .exit_out_of_bound
  addq $8, TEMP1
  cmp $CKB_VM_ASM_RISCV_MAX_MEMORY, TEMP1
  jae .exit_out_of_bound
  movq CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_MEMORY(MACHINE, RS1), RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_RVC_LWSP:
  DECODE_U
  movq SP_ADDRESS, RS1
  addq IMMEDIATE, RS1
  movq RS1, TEMP1
  cmp $CKB_VM_ASM_RISCV_MAX_MEMORY, TEMP1
  jae .exit_out_of_bound
  addq $4, TEMP1
  cmp $CKB_VM_ASM_RISCV_MAX_MEMORY, TEMP1
  jae .exit_out_of_bound
  movslq CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_MEMORY(MACHINE, RS1), RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_RVC_MV:
  DECODE_R
  movq REGISTER_ADDRESS(RS2r), RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_RVC_SDSP:
  DECODE_S
  movq SP_ADDRESS, RS1
  addq IMMEDIATE, RS1
  CHECK_WRITE(RS1, RS2rd, 8)
  movq REGISTER_ADDRESS(RS2s), RS2s
  movq RS2s, CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_MEMORY(MACHINE, RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_RVC_SWSP:
  DECODE_S
  movq SP_ADDRESS, RS1
  addq IMMEDIATE, RS1
  CHECK_WRITE(RS1, RS2rd, 4)
  movq REGISTER_ADDRESS(RS2s), RS2s
  mov RS2sd, CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_MEMORY(MACHINE, RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_CLZ:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  lzcnt RS1, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_CLZW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  lzcnt RS1d, RS1d
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_CTZ:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  tzcnt RS1, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_CTZW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  tzcnt RS1d, RS1d
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_PCNT:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  popcnt RS1, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_PCNTW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  popcnt RS1d, RS1d
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_ANDN:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  not RS2r
  and RS2r, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_ORN:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  not RS2r
  or RS2r, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_XNOR:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  not RS2r
  xor RS2r, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_PACK:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  shl $32, RS1
  shr $32, RS1
  shl $32, RS2r
  or RS2r, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_PACKU:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  shr $32, RS1
  shr $32, RS2r
  shl $32, RS2r
  or RS2r, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_PACKH:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  andq $0xff, RS1
  andq $0xff, RS2r
  shl $8, RS2r
  or RS2r, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_PACKW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  shl $16, RS1d
  shr $16, RS1d
  shl $16, RS2rd
  or RS2rd, RS1d
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_PACKUW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  shr $16, RS1d
  shr $16, RS2rd
  shl $16, RS2rd
  or RS2rd, RS1d
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_MIN:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  cmp RS1, RS2r
  movq RS1, TEMP1
  cmovle RS2r, TEMP1
  WRITE_RD(TEMP1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_MINU:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  cmp RS1, RS2r
  movq RS1, TEMP1
  cmovbe RS2r, TEMP1
  WRITE_RD(TEMP1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_MAX:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  cmp RS1, RS2r
  movq RS1, TEMP1
  cmovge RS2r, TEMP1
  WRITE_RD(TEMP1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_MAXU:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  cmp RS1, RS2r
  movq RS1, TEMP1
  cmovae RS2r, TEMP1
  WRITE_RD(TEMP1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SEXTB:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movsx RS1b, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SEXTH:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movsx RS1h, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SBSET:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), %rcx
  movq $1, TEMP1
  shl %cl, TEMP1
  or TEMP1, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SBSETW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), %rcx
  mov $1, TEMP1d
  shl %cl, TEMP1d
  or TEMP1d, RS1d
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SBSETI:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  movq IMMEDIATE, %rcx
  movq $1, TEMP1
  shl %cl, TEMP1
  or TEMP1, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SBSETIW:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  movq IMMEDIATE, %rcx
  mov $1, TEMP1d
  shl %cl, TEMP1d
  or TEMP1d, RS1d
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SBCLR:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), %rcx
  movq $1, TEMP1
  shl %cl, TEMP1
  not TEMP1
  and TEMP1, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SBCLRW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), %rcx
  mov $1, TEMP1d
  shl %cl, TEMP1d
  not TEMP1d
  and TEMP1d, RS1d
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SBCLRI:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  movq IMMEDIATE, %rcx
  movq $1, TEMP1
  shl %cl, TEMP1
  not TEMP1
  and TEMP1, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SBCLRIW:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  movq IMMEDIATE, %rcx
  mov $1, TEMP1d
  shl %cl, TEMP1d
  not TEMP1d
  and TEMP1d, RS1d
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SBINV:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), %rcx
  movq $1, TEMP1
  shl %cl, TEMP1
  xor TEMP1, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SBINVW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), %rcx
  mov $1, TEMP1d
  shl %cl, TEMP1d
  xor TEMP1d, RS1d
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SBINVI:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  movq IMMEDIATE, %rcx
  movq $1, TEMP1
  shl %cl, TEMP1
  xor TEMP1, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SBINVIW:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  movq IMMEDIATE, %rcx
  mov $1, TEMP1d
  shl %cl, TEMP1d
  xor TEMP1d, RS1d
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SBEXT:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), %rcx
  shr %cl, RS1
  and $1, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SBEXTW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), %rcx
  shr %cl, RS1d
  and $1, RS1d
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SBEXTI:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  movq IMMEDIATE, %rcx
  shr %cl, RS1
  and $1, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SLO:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), %rcx
  andq $63, %rcx
  not RS1
  shl %cl, RS1
  not RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SLOI:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  movq IMMEDIATE, %rcx
  andq $63, %rcx
  not RS1
  shl %cl, RS1
  not RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SLOW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), %rcx
  andq $63, %rcx
  not RS1d
  shl %cl, RS1d
  not RS1d
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SLOIW:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  movq IMMEDIATE, %rcx
  andq $63, %rcx
  not RS1d
  shl %cl, RS1d
  not RS1d
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SRO:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), %rcx
  andq $63, %rcx
  not RS1
  shr %cl, RS1
  not RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SROI:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  movq IMMEDIATE, %rcx
  andq $63, %rcx
  not RS1
  shr %cl, RS1
  not RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SROW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), %rcx
  andq $63, %rcx
  not RS1d
  shr %cl, RS1d
  not RS1d
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SROIW:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  movq IMMEDIATE, %rcx
  andq $63, %rcx
  not RS1d
  shr %cl, RS1d
  not RS1d
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_ROR:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  movb RS2rb, %cl
  ror %cl, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_RORI:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  ror IMMEDIATEb, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_RORW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), %rcx
  ror %cl, RS1d
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_RORIW:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  ror IMMEDIATEb, RS1d
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_ROL:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), %rcx
  rol %cl, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_ROLW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), %rcx
  rol %cl, RS1d
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_GREV:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  test $1, RS2rb
  je .grev_branch1
  movq RS1, TEMP1
  movabs $0x5555555555555555, TEMP2
  and TEMP2, RS1
  shl $1, RS1
  movabs $0xAAAAAAAAAAAAAAAA, TEMP2
  and TEMP2, TEMP1
  shr $1, TEMP1
  or TEMP1, RS1
.grev_branch1:
  test $2, RS2rb
  je .grev_branch2
  movq RS1, TEMP1
  movabs $0x3333333333333333, TEMP2
  and TEMP2, RS1
  shl $2, RS1
  movabs $0xCCCCCCCCCCCCCCCC, TEMP2
  and TEMP2, TEMP1
  shr $2, TEMP1
  or TEMP1, RS1
.grev_branch2:
  test $4, RS2rb
  je .grev_branch3
  movq RS1, TEMP1
  movabs $0x0F0F0F0F0F0F0F0F, TEMP2
  and TEMP2, RS1
  shl $4, RS1
  movabs $0xF0F0F0F0F0F0F0F0, TEMP2
  and TEMP2, TEMP1
  shr $4, TEMP1
  or TEMP1, RS1
.grev_branch3:
  test $8, RS2rb
  je .grev_branch4
  movq RS1, TEMP1
  movabs $0x00FF00FF00FF00FF, TEMP2
  and TEMP2, RS1
  shl $8, RS1
  movabs $0xFF00FF00FF00FF00, TEMP2
  and TEMP2, TEMP1
  shr $8, TEMP1
  or TEMP1, RS1
.grev_branch4:
  test $16, RS2rb
  je .grev_branch5
  movq RS1, TEMP1
  movabs $0x0000FFFF0000FFFF, TEMP2
  and TEMP2, RS1
  shl $16, RS1
  movabs $0xFFFF0000FFFF0000, TEMP2
  and TEMP2, TEMP1
  shr $16, TEMP1
  or TEMP1, RS1
.grev_branch5:
  test $32, RS2rb
  je .grev_branch6
  movq RS1, TEMP1
  movabs $0x00000000FFFFFFFF, TEMP2
  and TEMP2, RS1
  shl $32, RS1
  movabs $0xFFFFFFFF00000000, TEMP2
  and TEMP2, TEMP1
  shr $32, TEMP1
  or TEMP1, RS1
.grev_branch6:
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_GREVI:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  movq IMMEDIATE, RS2r
  test $1, RS2rb
  je .grevi_branch1
  movq RS1, TEMP1
  movabs $0x5555555555555555, TEMP2
  and TEMP2, RS1
  shl $1, RS1
  movabs $0xAAAAAAAAAAAAAAAA, TEMP2
  and TEMP2, TEMP1
  shr $1, TEMP1
  or TEMP1, RS1
.grevi_branch1:
  test $2, RS2rb
  je .grevi_branch2
  movq RS1, TEMP1
  movabs $0x3333333333333333, TEMP2
  and TEMP2, RS1
  shl $2, RS1
  movabs $0xCCCCCCCCCCCCCCCC, TEMP2
  and TEMP2, TEMP1
  shr $2, TEMP1
  or TEMP1, RS1
.grevi_branch2:
  test $4, RS2rb
  je .grevi_branch3
  movq RS1, TEMP1
  movabs $0x0F0F0F0F0F0F0F0F, TEMP2
  and TEMP2, RS1
  shl $4, RS1
  movabs $0xF0F0F0F0F0F0F0F0, TEMP2
  and TEMP2, TEMP1
  shr $4, TEMP1
  or TEMP1, RS1
.grevi_branch3:
  test $8, RS2rb
  je .grevi_branch4
  movq RS1, TEMP1
  movabs $0x00FF00FF00FF00FF, TEMP2
  and TEMP2, RS1
  shl $8, RS1
  movabs $0xFF00FF00FF00FF00, TEMP2
  and TEMP2, TEMP1
  shr $8, TEMP1
  or TEMP1, RS1
.grevi_branch4:
  test $16, RS2rb
  je .grevi_branch5
  movq RS1, TEMP1
  movabs $0x0000FFFF0000FFFF, TEMP2
  and TEMP2, RS1
  shl $16, RS1
  movabs $0xFFFF0000FFFF0000, TEMP2
  and TEMP2, TEMP1
  shr $16, TEMP1
  or TEMP1, RS1
.grevi_branch5:
  test $32, RS2rb
  je .grevi_branch6
  movq RS1, TEMP1
  movabs $0x00000000FFFFFFFF, TEMP2
  and TEMP2, RS1
  shl $32, RS1
  movabs $0xFFFFFFFF00000000, TEMP2
  and TEMP2, TEMP1
  shr $32, TEMP1
  or TEMP1, RS1
.grevi_branch6:
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_GREVW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  test $1, RS2rb
  je .grevw_branch1
  mov RS1d, TEMP1d
  and $0x55555555, RS1d
  shl $1, RS1d
  and $0xAAAAAAAA, TEMP1d
  shr $1, TEMP1d
  or TEMP1d, RS1d
.grevw_branch1:
  test $2, RS2rb
  je .grevw_branch2
  mov RS1d, TEMP1d
  and $0x33333333, RS1d
  shl $2, RS1d
  and $0xCCCCCCCC, TEMP1d
  shr $2, TEMP1d
  or TEMP1d, RS1d
.grevw_branch2:
  test $4, RS2rb
  je .grevw_branch3
  mov RS1d, TEMP1d
  and $0x0F0F0F0F, RS1d
  shl $4, RS1d
  and $0xF0F0F0F0, TEMP1d
  shr $4, TEMP1d
  or TEMP1d, RS1d
.grevw_branch3:
  test $8, RS2rb
  je .grevw_branch4
  mov RS1d, TEMP1d
  and $0x00FF00FF, RS1d
  shl $8, RS1d
  and $0xFF00FF00, TEMP1d
  shr $8, TEMP1d
  or TEMP1d, RS1d
.grevw_branch4:
  test $16, RS2rb
  je .grevw_branch5
  mov RS1d, TEMP1d
  and $0x0000FFFF, RS1d
  shl $16, RS1d
  and $0xFFFF0000, TEMP1d
  shr $16, TEMP1d
  or TEMP1d, RS1d
.grevw_branch5:
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_GREVIW:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  movq IMMEDIATE, RS2r
  test $1, RS2rb
  je .greviw_branch1
  mov RS1d, TEMP1d
  and $0x55555555, RS1d
  shl $1, RS1d
  and $0xAAAAAAAA, TEMP1d
  shr $1, TEMP1d
  or TEMP1d, RS1d
.greviw_branch1:
  test $2, RS2rb
  je .greviw_branch2
  mov RS1d, TEMP1d
  and $0x33333333, RS1d
  shl $2, RS1d
  and $0xCCCCCCCC, TEMP1d
  shr $2, TEMP1d
  or TEMP1d, RS1d
.greviw_branch2:
  test $4, RS2rb
  je .greviw_branch3
  mov RS1d, TEMP1d
  and $0x0F0F0F0F, RS1d
  shl $4, RS1d
  and $0xF0F0F0F0, TEMP1d
  shr $4, TEMP1d
  or TEMP1d, RS1d
.greviw_branch3:
  test $8, RS2rb
  je .greviw_branch4
  mov RS1d, TEMP1d
  and $0x00FF00FF, RS1d
  shl $8, RS1d
  and $0xFF00FF00, TEMP1d
  shr $8, TEMP1d
  or TEMP1d, RS1d
.greviw_branch4:
  test $16, RS2rb
  je .greviw_branch5
  mov RS1d, TEMP1d
  and $0x0000FFFF, RS1d
  shl $16, RS1d
  and $0xFFFF0000, TEMP1d
  shr $16, TEMP1d
  or TEMP1d, RS1d
.greviw_branch5:
  WRITE_RD(RS1)
  NEXT_INST
.shuffle64_stage:
  mov %rsi, %r9
  mov %rdi, %r8
  or %rdx, %r9
  shl %cl, %r8
  mov %r9, %rax
  and %r8, %rsi
  not %rax
  and %rdi, %rax
  shr %cl, %rdi
  mov %rax, %r9
  mov %rdi, %rax
  and %rdx, %rax
  or %rax, %rsi
  mov %rsi, %rax
  or %r9, %rax
  retq
.shfl64:
  test $0x10, %sil
  mov %rsi, %r10
  je .shfl64_branch1
  mov $0x10, %ecx
  mov $0xffff0000, %edx
  movabs $0xffff00000000, %rsi
  callq .shuffle64_stage
  mov %rax, %rdi
.shfl64_branch1:
  test $0x8, %r10b
  je .shfl64_branch2
  mov $0x8, %ecx
  movabs $0xff000000ff00, %rdx
  movabs $0xff000000ff0000, %rsi
  callq .shuffle64_stage
  mov %rax, %rdi
.shfl64_branch2:
  test $0x4, %r10b
  je .shfl64_branch3
  mov $0x4, %ecx
  movabs $0xf000f000f000f0, %rdx
  movabs $0xf000f000f000f00, %rsi
  callq .shuffle64_stage
  mov %rax, %rdi
.shfl64_branch3:
  test $0x2, %r10b
  je .shfl64_branch4
  mov $0x2, %ecx
  movabs $0xc0c0c0c0c0c0c0c, %rdx
  movabs $0x3030303030303030, %rsi
  callq .shuffle64_stage
  mov %rax, %rdi
.shfl64_branch4:
  and $0x1, %r10b
  je .shfl64_branch5
  mov $0x1, %ecx
  movabs $0x2222222222222222, %rdx
  movabs $0x4444444444444444, %rsi
  jmp .shuffle64_stage
.shfl64_branch5:
  mov %rdi,%rax
  retq
.p2align 3
.CKB_VM_ASM_LABEL_OP_SHFL:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  PREPCALL
  movq RS1, %rdi
  movq RS2r, %rsi
  callq .shfl64
  movq %rax, TEMP2
  POSTCALL
  WRITE_RD(TEMP2)
  NEXT_INST
.unshfl64:
  test $0x1, %sil
  mov %rsi, %r10
  je .unshfl64_branch1
  mov $0x1, %ecx
  movabs $0x2222222222222222, %rdx
  movabs $0x4444444444444444, %rsi
  callq .shuffle64_stage
  mov %rax, %rdi
.unshfl64_branch1:
  test $0x2, %r10b
  je .unshfl64_branch2
  mov $0x2, %ecx
  movabs $0xc0c0c0c0c0c0c0c, %rdx
  movabs $0x3030303030303030, %rsi
  callq .shuffle64_stage
  mov %rax, %rdi
.unshfl64_branch2:
  test $0x4, %r10b
  je .unshfl64_branch3
  mov $0x4, %ecx
  movabs $0xf000f000f000f0, %rdx
  movabs $0xf000f000f000f00, %rsi
  callq .shuffle64_stage
  mov %rax, %rdi
.unshfl64_branch3:
  test $0x8, %r10b
  je .unshfl64_branch4
  mov $0x8, %ecx
  movabs $0xff000000ff00, %rdx
  movabs $0xff000000ff0000, %rsi
  callq  .shuffle64_stage
  mov %rax, %rdi
.unshfl64_branch4:
  and $0x10, %r10b
  je .unshfl64_branch5
  mov $0x10, %ecx
  mov $0xffff0000, %edx
  movabs $0xffff00000000, %rsi
  jmp .shuffle64_stage
.unshfl64_branch5:
  mov %rdi, %rax
  retq
.p2align 3
.CKB_VM_ASM_LABEL_OP_UNSHFL:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  PREPCALL
  movq RS1, %rdi
  movq RS2r, %rsi
  callq .unshfl64
  movq %rax, TEMP2
  POSTCALL
  WRITE_RD(TEMP2)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SHFLI:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  movq IMMEDIATE, RS2r
  PREPCALL
  movq RS1, %rdi
  movq RS2r, %rsi
  callq .shfl64
  movq %rax, TEMP2
  POSTCALL
  WRITE_RD(TEMP2)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_UNSHFLI:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  movq IMMEDIATE, RS2r
  PREPCALL
  movq RS1, %rdi
  movq RS2r, %rsi
  callq .unshfl64
  movq %rax, TEMP2
  POSTCALL
  WRITE_RD(TEMP2)
  NEXT_INST
.shuffle32_stage:
  mov %esi, %r9d
  mov %edi, %r8d
  or %edx, %r9d
  shl %cl, %r8d
  mov %r9d, %eax
  and %r8d, %esi
  not %eax
  and %edi, %eax
  shr %cl, %edi
  mov %eax, %r9d
  mov %edi, %eax
  and %edx, %eax
  or %eax, %esi
  mov %esi, %eax
  or %r9d, %eax
  retq
.shfl32:
  test $0x8, %sil
  mov %esi, %r10d
  je .shfl32_branch1
  mov $0x8, %ecx
  mov $0xff00, %edx
  mov $0xff0000, %esi
  callq .shuffle32_stage
  mov %eax, %edi
.shfl32_branch1:
  test $0x4, %r10b
  je .shfl32_branch2
  mov $0x4, %ecx
  mov $0xf000f0, %edx
  mov $0xf000f00, %esi
  callq .shuffle32_stage
  mov %eax, %edi
.shfl32_branch2:
  test $0x2, %r10b
  je .shfl32_branch3
  mov $0x2, %ecx
  mov $0xc0c0c0c, %edx
  mov $0x30303030, %esi
  callq .shuffle32_stage
  mov %eax, %edi
.shfl32_branch3:
  and $0x1, %r10b
  je .shfl32_branch4
  mov $0x1, %ecx
  mov $0x22222222, %edx
  mov $0x44444444, %esi
  jmp .shuffle32_stage
.shfl32_branch4:
  mov %edi, %eax
  retq
.p2align 3
.CKB_VM_ASM_LABEL_OP_SHFLW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  PREPCALL
  mov RS1d, %edi
  mov RS2rd, %esi
  callq .shfl32
  mov %eax, TEMP2d
  POSTCALL
  WRITE_RD(TEMP2)
  NEXT_INST
.unshfl32:
  test $0x1, %sil
  mov %esi, %r10d
  je .unshfl32_branch1
  mov $0x1, %ecx
  mov $0x22222222, %edx
  mov $0x44444444, %esi
  callq .shuffle32_stage
  mov %eax,%edi
.unshfl32_branch1:
  test $0x2, %r10b
  je .unshfl32_branch2
  mov $0x2, %ecx
  mov $0xc0c0c0c, %edx
  mov $0x30303030, %esi
  callq .shuffle32_stage
  mov %eax, %edi
.unshfl32_branch2:
  test $0x4, %r10b
  je .unshfl32_branch3
  mov $0x4, %ecx
  mov $0xf000f0, %edx
  mov $0xf000f00, %esi
  callq .shuffle32_stage
  mov %eax, %edi
.unshfl32_branch3:
  and $0x8, %r10b
  je .unshfl32_branch4
  mov $0x8, %ecx
  mov $0xff00, %edx
  mov $0xff0000, %esi
  jmp .shuffle32_stage
.unshfl32_branch4:
  mov %edi,%eax
  retq
.p2align 3
.CKB_VM_ASM_LABEL_OP_UNSHFLW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  PREPCALL
  mov RS1d, %edi
  mov RS2rd, %esi
  callq .unshfl32
  mov %eax, TEMP2d
  POSTCALL
  WRITE_RD(TEMP2)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_GORC:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  movq RS1, TEMP1
  test $1, RS2rb
  je .gorc_branch1
  movq TEMP1, TEMP2
  movq $0x5555555555555555, %rcx
  andq %rcx, TEMP2
  shl $1, TEMP2
  movq TEMP1, TEMP3
  movq $0xAAAAAAAAAAAAAAAA, %rcx
  andq %rcx, TEMP3
  shr $1, TEMP3
  or TEMP2, TEMP1
  or TEMP3, TEMP1
.gorc_branch1:
  test $2, RS2rb
  je .gorc_branch2
  movq TEMP1, TEMP2
  movq $0x3333333333333333, %rcx
  andq %rcx, TEMP2
  shl $2, TEMP2
  movq TEMP1, TEMP3
  movq $0xCCCCCCCCCCCCCCCC, %rcx
  andq %rcx, TEMP3
  shr $2, TEMP3
  or TEMP2, TEMP1
  or TEMP3, TEMP1
.gorc_branch2:
  test $4, RS2rb
  je .gorc_branch3
  movq TEMP1, TEMP2
  movq $0x0F0F0F0F0F0F0F0F, %rcx
  andq %rcx, TEMP2
  shl $4, TEMP2
  movq TEMP1, TEMP3
  movq $0xF0F0F0F0F0F0F0F0, %rcx
  andq %rcx, TEMP3
  shr $4, TEMP3
  or TEMP2, TEMP1
  or TEMP3, TEMP1
.gorc_branch3:
  test $8, RS2rb
  je .gorc_branch4
  movq TEMP1, TEMP2
  movq $0x00FF00FF00FF00FF, %rcx
  andq %rcx, TEMP2
  shl $8, TEMP2
  movq TEMP1, TEMP3
  movq $0xFF00FF00FF00FF00, %rcx
  andq %rcx, TEMP3
  shr $8, TEMP3
  or TEMP2, TEMP1
  or TEMP3, TEMP1
.gorc_branch4:
  test $16, RS2rb
  je .gorc_branch5
  movq TEMP1, TEMP2
  movq $0x0000FFFF0000FFFF, %rcx
  andq %rcx, TEMP2
  shl $16, TEMP2
  movq TEMP1, TEMP3
  movq $0xFFFF0000FFFF0000, %rcx
  andq %rcx, TEMP3
  shr $16, TEMP3
  or TEMP2, TEMP1
  or TEMP3, TEMP1
.gorc_branch5:
  test $32, RS2rb
  je .gorc_branch6
  movq TEMP1, TEMP2
  movq $0x00000000FFFFFFFF, %rcx
  andq %rcx, TEMP2
  shl $32, TEMP2
  movq TEMP1, TEMP3
  movq $0xFFFFFFFF00000000, %rcx
  andq %rcx, TEMP3
  shr $32, TEMP3
  or TEMP2, TEMP1
  or TEMP3, TEMP1
.gorc_branch6:
  WRITE_RD(TEMP1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_GORCI:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  movq IMMEDIATE, RS2r
  movq RS1, TEMP1
  test $1, RS2rb
  je .gorci_branch1
  movq TEMP1, TEMP2
  movq $0x5555555555555555, %rcx
  andq %rcx, TEMP2
  shl $1, TEMP2
  movq TEMP1, TEMP3
  movq $0xAAAAAAAAAAAAAAAA, %rcx
  andq %rcx, TEMP3
  shr $1, TEMP3
  or TEMP2, TEMP1
  or TEMP3, TEMP1
.gorci_branch1:
  test $2, RS2rb
  je .gorci_branch2
  movq TEMP1, TEMP2
  movq $0x3333333333333333, %rcx
  andq %rcx, TEMP2
  shl $2, TEMP2
  movq TEMP1, TEMP3
  movq $0xCCCCCCCCCCCCCCCC, %rcx
  andq %rcx, TEMP3
  shr $2, TEMP3
  or TEMP2, TEMP1
  or TEMP3, TEMP1
.gorci_branch2:
  test $4, RS2rb
  je .gorci_branch3
  movq TEMP1, TEMP2
  movq $0x0F0F0F0F0F0F0F0F, %rcx
  andq %rcx, TEMP2
  shl $4, TEMP2
  movq TEMP1, TEMP3
  movq $0xF0F0F0F0F0F0F0F0, %rcx
  andq %rcx, TEMP3
  shr $4, TEMP3
  or TEMP2, TEMP1
  or TEMP3, TEMP1
.gorci_branch3:
  test $8, RS2rb
  je .gorci_branch4
  movq TEMP1, TEMP2
  movq $0x00FF00FF00FF00FF, %rcx
  andq %rcx, TEMP2
  shl $8, TEMP2
  movq TEMP1, TEMP3
  movq $0xFF00FF00FF00FF00, %rcx
  andq %rcx, TEMP3
  shr $8, TEMP3
  or TEMP2, TEMP1
  or TEMP3, TEMP1
.gorci_branch4:
  test $16, RS2rb
  je .gorci_branch5
  movq TEMP1, TEMP2
  movq $0x0000FFFF0000FFFF, %rcx
  andq %rcx, TEMP2
  shl $16, TEMP2
  movq TEMP1, TEMP3
  movq $0xFFFF0000FFFF0000, %rcx
  andq %rcx, TEMP3
  shr $16, TEMP3
  or TEMP2, TEMP1
  or TEMP3, TEMP1
.gorci_branch5:
  test $32, RS2rb
  je .gorci_branch6
  movq TEMP1, TEMP2
  movq $0x00000000FFFFFFFF, %rcx
  andq %rcx, TEMP2
  shl $32, TEMP2
  movq TEMP1, TEMP3
  movq $0xFFFFFFFF00000000, %rcx
  andq %rcx, TEMP3
  shr $32, TEMP3
  or TEMP2, TEMP1
  or TEMP3, TEMP1
.gorci_branch6:
  WRITE_RD(TEMP1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_GORCW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  mov RS1d, TEMP1d
  test $1, RS2rb
  je .gorcw_branch1
  mov TEMP1d, TEMP2d
  and $0x55555555, TEMP2d
  shl $1, TEMP2d
  mov TEMP1d, TEMP3d
  and $0xAAAAAAAA, TEMP3d
  shr $1, TEMP3d
  or TEMP2d, TEMP1d
  or TEMP3d, TEMP1d
.gorcw_branch1:
  test $2, RS2rb
  je .gorcw_branch2
  mov TEMP1d, TEMP2d
  and $0x33333333, TEMP2d
  shl $2, TEMP2d
  mov TEMP1d, TEMP3d
  and $0xCCCCCCCC, TEMP3d
  shr $2, TEMP3d
  or TEMP2d, TEMP1d
  or TEMP3d, TEMP1d
.gorcw_branch2:
  test $4, RS2rb
  je .gorcw_branch3
  mov TEMP1d, TEMP2d
  and $0x0F0F0F0F, TEMP2d
  shl $4, TEMP2d
  mov TEMP1d, TEMP3d
  and $0xF0F0F0F0, TEMP3d
  shr $4, TEMP3d
  or TEMP2d, TEMP1d
  or TEMP3d, TEMP1d
.gorcw_branch3:
  test $8, RS2rb
  je .gorcw_branch4
  mov TEMP1d, TEMP2d
  and $0x00FF00FF, TEMP2d
  shl $8, TEMP2d
  mov TEMP1d, TEMP3d
  and $0xFF00FF00, TEMP3d
  shr $8, TEMP3d
  or TEMP2d, TEMP1d
  or TEMP3d, TEMP1d
.gorcw_branch4:
  test $16, RS2rb
  je .gorcw_branch5
  mov TEMP1d, TEMP2d
  and $0x0000FFFF, TEMP2d
  shl $16, TEMP2d
  mov TEMP1d, TEMP3d
  and $0xFFFF0000, TEMP3d
  shr $16, TEMP3d
  or TEMP2d, TEMP1d
  or TEMP3d, TEMP1d
.gorcw_branch5:
  WRITE_RD(TEMP1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_GORCIW:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  movq IMMEDIATE, RS2r
  mov RS1d, TEMP1d
  test $1, RS2rb
  je .gorciw_branch1
  mov TEMP1d, TEMP2d
  and $0x55555555, TEMP2d
  shl $1, TEMP2d
  mov TEMP1d, TEMP3d
  and $0xAAAAAAAA, TEMP3d
  shr $1, TEMP3d
  or TEMP2d, TEMP1d
  or TEMP3d, TEMP1d
.gorciw_branch1:
  test $2, RS2rb
  je .gorciw_branch2
  mov TEMP1d, TEMP2d
  and $0x33333333, TEMP2d
  shl $2, TEMP2d
  mov TEMP1d, TEMP3d
  and $0xCCCCCCCC, TEMP3d
  shr $2, TEMP3d
  or TEMP2d, TEMP1d
  or TEMP3d, TEMP1d
.gorciw_branch2:
  test $4, RS2rb
  je .gorciw_branch3
  mov TEMP1d, TEMP2d
  and $0x0F0F0F0F, TEMP2d
  shl $4, TEMP2d
  mov TEMP1d, TEMP3d
  and $0xF0F0F0F0, TEMP3d
  shr $4, TEMP3d
  or TEMP2d, TEMP1d
  or TEMP3d, TEMP1d
.gorciw_branch3:
  test $8, RS2rb
  je .gorciw_branch4
  mov TEMP1d, TEMP2d
  and $0x00FF00FF, TEMP2d
  shl $8, TEMP2d
  mov TEMP1d, TEMP3d
  and $0xFF00FF00, TEMP3d
  shr $8, TEMP3d
  or TEMP2d, TEMP1d
  or TEMP3d, TEMP1d
.gorciw_branch4:
  test $16, RS2rb
  je .gorciw_branch5
  mov TEMP1d, TEMP2d
  and $0x0000FFFF, TEMP2d
  shl $16, TEMP2d
  mov TEMP1d, TEMP3d
  and $0xFFFF0000, TEMP3d
  shr $16, TEMP3d
  or TEMP2d, TEMP1d
  or TEMP3d, TEMP1d
.gorciw_branch5:
  WRITE_RD(TEMP1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_BFP:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  mov RS2r,TEMP1
  mov RS2r,TEMP2
  shr $0x3e,TEMP1
  shr $0x30,TEMP2
  cmp $0x2,TEMP1
  je .bfp_branch1
  mov RS2r,TEMP2
  shr $0x20,TEMP2
.bfp_branch1:
  mov TEMP2,%rcx
  shr $0x8,%rcx
  and $0x1f,%ecx
  jne .bfp_branch2
  mov $0x20,%ecx
.bfp_branch2:
  and $0x3f,TEMP2d
  or $0xffffffffffffffff,TEMP3
  shl %cl,TEMP3
  mov TEMP2b,%cl
  shl %cl,RS2r
  not TEMP3
  mov RS2r,TEMP1
  shl %cl,TEMP3
  xor RS1,TEMP1
  and TEMP1,TEMP3
  mov TEMP3,TEMP1
  xor TEMP1, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_BFPW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  mov RS2rd,%ecx
  mov RS2rd,TEMP2d
  shr $0x18,%ecx
  shr $0x10,TEMP2d
  and $0xf,%ecx
  jne .bfpw_branch1
  mov $0x10,%ecx
.bfpw_branch1:
  and $0x1f,TEMP2d
  or $0xffffffff,TEMP1d
  shl %cl,TEMP1d
  mov TEMP2b,%cl
  shl %cl,RS2rd
  not TEMP1d
  mov RS2rd,TEMP2d
  shl %cl,TEMP1d
  xor RS1d,TEMP2d
  and TEMP2d,TEMP1d
  mov TEMP1d,TEMP2d
  xor TEMP2d, RS1d
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_BEXT:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  xor %ecx,%ecx
  xor TEMP1d,TEMP1d
  xor TEMP2d,TEMP2d
.bexp_branch1:
  bt TEMP1,RS2r
  jae .bexp_branch3
  bt TEMP1,RS1
  jae .bexp_branch2
  mov $1,TEMP3
  shl %cl,TEMP3
  or TEMP3,TEMP2
.bexp_branch2:
  inc %ecx
.bexp_branch3:
  inc TEMP1d
  cmp $0x40,TEMP1d
  jne .bexp_branch1
  WRITE_RD(TEMP2)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_BEXTW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  xor    %ecx,%ecx
  xor    TEMP1d,TEMP1d
  xor    TEMP2d,TEMP2d
.bextw_branch1:
  bt     TEMP1d, RS2rd
  jae    .bextw_branch3
  bt     TEMP1d, RS1d
  jae    .bextw_branch2
  mov    $1, TEMP3d
  shl    %cl,TEMP3d
  or     TEMP3d,TEMP2d
.bextw_branch2:
  inc    %ecx
.bextw_branch3:
  inc    TEMP1d
  cmp    $0x20,TEMP1d
  jne    .bextw_branch1
  WRITE_RD(TEMP2)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_BDEP:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  xor TEMP1d,TEMP1d
  xor %ecx,%ecx
  xor TEMP2d,TEMP2d
.bdep_branch1:
  bt %rcx,RS2r
  jae .bdep_branch3
  bt TEMP1,RS1
  jae .bdep_branch2
  mov $1, TEMP3
  shl %cl,TEMP3
  or TEMP3,TEMP2
.bdep_branch2:
  inc TEMP1d
.bdep_branch3:
  inc %ecx
  cmp $0x40,%ecx
  jne .bdep_branch1
  WRITE_RD(TEMP2)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_BDEPW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  xor    TEMP1d,TEMP1d
  xor    %ecx,%ecx
  xor    TEMP2d,TEMP2d
.bdepw_branch1:
  bt     %ecx,RS2rd
  jae    .bdepw_branch3
  bt     TEMP1d,RS1d
  jae    .bdepw_branch2
  mov    $1,TEMP3d
  shl    %cl,TEMP3d
  or     TEMP3d,TEMP2d
.bdepw_branch2:
  inc    TEMP1d
.bdepw_branch3:
  inc    %ecx
  cmp    $0x20,%ecx
  jne    .bdepw_branch1
  WRITE_RD(TEMP2)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_CLMUL:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  xor TEMP3d, TEMP3d
  xor TEMP2, TEMP2
.clmul_branch1:
  bt TEMP3, RS2r
  jae .clmul_branch2
  mov RS1, TEMP1
  movb TEMP3b, %cl
  shl %cl, TEMP1
  xor TEMP1, TEMP2
.clmul_branch2:
  inc TEMP3d
  cmp $0x40, TEMP3d
  jne .clmul_branch1
  WRITE_RD(TEMP2)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_CLMULW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  xor TEMP3d, TEMP3d
  xor TEMP2d, TEMP2d
.clmulw_branch1:
  bt TEMP3d, RS2rd
  jae .clmulw_branch2
  mov RS1d, TEMP1d
  movb TEMP3b, %cl
  shl %cl, TEMP1d
  xor TEMP1d, TEMP2d
.clmulw_branch2:
  inc TEMP3d
  cmp $0x20, TEMP3d
  jne .clmulw_branch1
  WRITE_RD(TEMP2)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_CLMULH:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  movq $1, TEMP3
  xor TEMP2, TEMP2
.clmulh_branch1:
  bt TEMP3, RS2r
  jae .clmulh_branch2
  mov RS1, TEMP1
  movb TEMP3b, %cl
  neg %cl
  add $64, %cl
  shr %cl, TEMP1
  xor TEMP1, TEMP2
.clmulh_branch2:
  inc TEMP3d
  cmp $0x40, TEMP3d
  jne .clmulh_branch1
  WRITE_RD(TEMP2)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_CLMULHW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  movq $1, TEMP3
  xor TEMP2d, TEMP2d
.clmulhw_branch1:
  bt TEMP3d, RS2rd
  jae .clmulhw_branch2
  mov RS1d, TEMP1d
  movb TEMP3b, %cl
  neg %cl
  add $32, %cl
  shr %cl, TEMP1d
  xor TEMP1d, TEMP2d
.clmulhw_branch2:
  inc TEMP3d
  cmp $0x20, TEMP3d
  jne .clmulhw_branch1
  WRITE_RD(TEMP2)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_CLMULR:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  xor TEMP3, TEMP3
  xor TEMP2, TEMP2
.clmulr_branch1:
  bt TEMP3, RS2r
  jae .clmulr_branch2
  mov RS1, TEMP1
  movb TEMP3b, %cl
  neg %cl
  add $63, %cl
  shr %cl, TEMP1
  xor TEMP1, TEMP2
.clmulr_branch2:
  inc TEMP3d
  cmp $0x40, TEMP3d
  jne .clmulr_branch1
  WRITE_RD(TEMP2)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_CLMULRW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  xor TEMP3d, TEMP3d
  xor TEMP2d, TEMP2d
.clmulrw_branch1:
  bt TEMP3d, RS2rd
  jae .clmulrw_branch2
  mov RS1d, TEMP1d
  movb TEMP3b, %cl
  neg %cl
  add $31, %cl
  shr %cl, TEMP1d
  xor TEMP1d, TEMP2d
.clmulrw_branch2:
  inc TEMP3d
  cmp $0x20, TEMP3d
  jne .clmulrw_branch1
  WRITE_RD(TEMP2)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_CRC32B:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  mov $0, RS2rd
.crc32b_branch1:
  cmp $8, RS2rd
  jge .crc32b_branch2
  mov RS1, TEMP1
  and $1, RS1d
  neg RS1
  shr TEMP1
  and $0xedb88320, RS1d
  xor TEMP1, RS1
  inc RS2rd
  jmp .crc32b_branch1
.crc32b_branch2:
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_CRC32H:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  mov $0, RS2rd
.crc32h_branch1:
  cmp $16, RS2rd
  jge .crc32h_branch2
  mov RS1, TEMP1
  and $1, RS1d
  neg RS1
  shr TEMP1
  and $0xedb88320, RS1d
  xor TEMP1, RS1
  inc RS2rd
  jmp .crc32h_branch1
.crc32h_branch2:
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_CRC32W:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  mov $0, RS2rd
.crc32w_branch1:
  cmp $32, RS2rd
  jge .crc32w_branch2
  mov RS1, TEMP1
  and $1, RS1d
  neg RS1
  shr TEMP1
  and $0xedb88320, RS1d
  xor TEMP1, RS1
  inc RS2rd
  jmp .crc32w_branch1
.crc32w_branch2:
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_CRC32D:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  mov $0, RS2rd
.crc32d_branch1:
  cmp $64, RS2rd
  jge .crc32d_branch2
  mov RS1, TEMP1
  and $1, RS1d
  neg RS1
  shr TEMP1
  and $0xedb88320, RS1d
  xor TEMP1, RS1
  inc RS2rd
  jmp .crc32d_branch1
.crc32d_branch2:
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_CRC32CB:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  mov $0, RS2rd
.crc32cb_branch1:
  cmp $8, RS2rd
  jge .crc32cb_branch2
  mov RS1, TEMP1
  and $1, RS1d
  neg RS1
  shr TEMP1
  and $0x82f63b78, RS1d
  xor TEMP1, RS1
  inc RS2rd
  jmp .crc32cb_branch1
.crc32cb_branch2:
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_CRC32CH:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  mov $0, RS2rd
.crc32ch_branch1:
  cmp $16, RS2rd
  jge .crc32ch_branch2
  mov RS1, TEMP1
  and $1, RS1d
  neg RS1
  shr TEMP1
  and $0x82f63b78, RS1d
  xor TEMP1, RS1
  inc RS2rd
  jmp .crc32ch_branch1
.crc32ch_branch2:
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_CRC32CW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  mov $0, RS2rd
.crc32cw_branch1:
  cmp $32, RS2rd
  jge .crc32cw_branch2
  mov RS1, TEMP1
  and $1, RS1d
  neg RS1
  shr TEMP1
  and $0x82f63b78, RS1d
  xor TEMP1, RS1
  inc RS2rd
  jmp .crc32cw_branch1
.crc32cw_branch2:
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_CRC32CD:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  mov $0, RS2rd
.crc32cd_branch1:
  cmp $64, RS2rd
  jge .crc32cd_branch2
  mov RS1, TEMP1
  and $1, RS1d
  neg RS1
  shr TEMP1
  and $0x82f63b78, RS1d
  xor TEMP1, RS1
  inc RS2rd
  jmp .crc32cd_branch1
.crc32cd_branch2:
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_BMATOR:
  jmp .exit_invalid_permission
.p2align 3
.CKB_VM_ASM_LABEL_OP_BMATXOR:
  jmp .exit_invalid_permission
.p2align 3
.CKB_VM_ASM_LABEL_OP_BMATFLIP:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  PREPCALL
  movq RS1, %rdi
  movq $31, %rsi
  callq .shfl64
  movq %rax, %rdi
  movq $31, %rsi
  callq .shfl64
  movq %rax, %rdi
  movq $31, %rsi
  callq .shfl64
  movq %rax, TEMP2
  POSTCALL
  WRITE_RD(TEMP2)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_CMIX:
  DECODE_R4
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  movq REGISTER_ADDRESS(RS3), RS3
  xor RS3, RS1
  and RS2r, RS1
  xor RS3, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_CMOV:
  DECODE_R4
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  movq REGISTER_ADDRESS(RS3), RS3
  test RS2r, RS2r
  cmove RS3, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_FSL:
  DECODE_R4
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  movq REGISTER_ADDRESS(RS3), RS3
  and $0x7f,RS2rd
  mov RS1,TEMP1
  cmp $0x3f,RS2rd
  jle .fsl_branch1
  mov RS3,TEMP1
  sub $0x40,RS2rd
  mov RS1,RS3
.fsl_branch1:
  test RS2rd,RS2rd
  je .fsl_branch2
  mov $0x40,%ecx
  sub RS2rd,%ecx
  shr %cl,RS3
  mov RS2rb,%cl
  shl %cl,TEMP1
  or RS3,TEMP1
.fsl_branch2:
  WRITE_RD(TEMP1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_FSLW:
  DECODE_R4
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  movq REGISTER_ADDRESS(RS3), RS3
  and $0x3f,RS2rd
  mov RS1d,TEMP1d
  cmp $0x1f,RS2rd
  jle .fslw_branch1
  mov RS3d,TEMP1d
  sub $0x20,RS2rd
  mov RS1d,RS3d
.fslw_branch1:
  test RS2rd,RS2rd
  je .fslw_branch2
  mov $0x20,%ecx
  sub RS2rd,%ecx
  shr %cl,RS3d
  mov RS2rb,%cl
  shl %cl,TEMP1d
  or RS3d,TEMP1d
.fslw_branch2:
  WRITE_RD(TEMP1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_FSR:
  DECODE_R4
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  movq REGISTER_ADDRESS(RS3), RS3
  and $0x7f,RS2rd
  mov RS1,TEMP1
  cmp $0x3f,RS2rd
  jle .fsr_branch1
  mov RS3,TEMP1
  sub $0x40,RS2rd
  mov RS1,RS3
.fsr_branch1:
  test RS2rd,RS2rd
  je .fsr_branch2
  mov $0x40,%ecx
  sub RS2rd,%ecx
  shl %cl,RS3
  mov RS2rb,%cl
  shr %cl,TEMP1
  or RS3,TEMP1
.fsr_branch2:
  WRITE_RD(TEMP1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_FSRW:
  DECODE_R4
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  movq REGISTER_ADDRESS(RS3), RS3
  and $0x3f,RS2rd
  mov RS1d,TEMP1d
  cmp $0x1f,RS2rd
  jle .fslrw_branch1
  mov RS3d,TEMP1d
  sub $0x20,RS2rd
  mov RS1d,RS3d
.fslrw_branch1:
  test RS2rd,RS2rd
  je .fslrw_branch2
  mov $0x20,%ecx
  sub RS2rd,%ecx
  shl %cl,RS3d
  mov RS2rb,%cl
  shr %cl,TEMP1d
  or RS3d,TEMP1d
.fslrw_branch2:
  WRITE_RD(TEMP1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_FSRI:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  movq IMMEDIATE, RS2r
  and $0x3f, RS2r
  movq IMMEDIATE, RS3
  shr $7, RS3
  movq REGISTER_ADDRESS(RS3), RS3
  and $0x7f,RS2rd
  mov RS1,TEMP1
  cmp $0x3f,RS2rd
  jle .fsri_branch1
  mov RS3,TEMP1
  sub $0x40,RS2rd
  mov RS1,RS3
.fsri_branch1:
  test RS2rd,RS2rd
  je .fsri_branch2
  mov $0x40,%ecx
  sub RS2rd,%ecx
  shl %cl,RS3
  mov RS2rb,%cl
  shr %cl,TEMP1
  or RS3,TEMP1
.fsri_branch2:
  WRITE_RD(TEMP1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_FSRIW:
  DECODE_R4
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS3), RS3
  and $0x3f,RS2rd
  mov RS1d,TEMP1d
  cmp $0x1f,RS2rd
  jle .fslriw_branch1
  mov RS3d,TEMP1d
  sub $0x20,RS2rd
  mov RS1d,RS3d
.fslriw_branch1:
  test RS2rd,RS2rd
  je .fslriw_branch2
  mov $0x20,%ecx
  sub RS2rd,%ecx
  shl %cl,RS3d
  mov RS2rb,%cl
  shr %cl,TEMP1d
  or RS3d,TEMP1d
.fslriw_branch2:
  WRITE_RD(TEMP1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SH1ADD:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  shl $1, RS1
  add RS2r, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SH2ADD:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  shl $2, RS1
  add RS2r, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SH3ADD:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  shl $3, RS1
  add RS2r, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SH1ADDUW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  movabs $0x1ffffffff, TEMP1
  and TEMP1, RS1
  shl $1, RS1
  add RS2r, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SH2ADDUW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  movabs $0x1ffffffff, TEMP1
  and TEMP1, RS1
  shl $2, RS1
  add RS2r, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SH3ADDUW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  movabs $0x1ffffffff, TEMP1
  and TEMP1, RS1
  shl $3, RS1
  add RS2r, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_ADDIWU:
  DECODE_I
  movq REGISTER_ADDRESS(RS1), RS1
  addq IMMEDIATE, RS1
  mov RS1d, RS1d
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SLLIUW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), %rcx
  mov RS1d, RS1d
  and $63, %ecx
  shl %cl, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_ADDWU:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  addq REGISTER_ADDRESS(RS2r), RS1
  mov RS1d, RS1d
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SUBWU:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  subq REGISTER_ADDRESS(RS2r), RS1
  mov RS1d, RS1d
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_ADDUW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  mov RS2rd, RS2rd
  addq RS2r, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.CKB_VM_ASM_LABEL_OP_SUBUW:
  DECODE_R
  movq REGISTER_ADDRESS(RS1), RS1
  movq REGISTER_ADDRESS(RS2r), RS2r
  mov RS2rd, RS2rd
  subq RS2r, RS1
  WRITE_RD(RS1)
  NEXT_INST
.p2align 3
.exit_out_of_bound:
  mov $CKB_VM_ASM_RET_OUT_OF_BOUND, ARG_RETd
  jmp .exit
.p2align 3
.exit_max_cycles_exceeded:
  mov $CKB_VM_ASM_RET_MAX_CYCLES_EXCEEDED, ARG_RETd
  jmp .exit
.exit_invalid_permission:
  mov $CKB_VM_ASM_RET_INVALID_PERMISSION, ARG_RETd
  jmp .exit
.p2align 3
.exit_trace:
.CKB_VM_ASM_LABEL_OP_UNLOADED:
  DECODE_U
  mov $CKB_VM_ASM_RET_DECODE_TRACE, ARG_RETd
  jmp .exit
.exit:
  pop %rbx
  pop %rbp
#ifdef IS_WINDOWS
  pop %rdi
  pop %rsi
#endif
  retq
