#define CKB_VM_ASM_RISCV_MAX_MEMORY 4194304
#define CKB_VM_ASM_RISCV_PAGE_SHIFTS 12
#define CKB_VM_ASM_RISCV_PAGE_SIZE 4096
#define CKB_VM_ASM_RISCV_PAGE_MASK 4095
#define CKB_VM_ASM_RISCV_PAGES 1024
#define CKB_VM_ASM_MEMORY_FRAME_SHIFTS 18
#define CKB_VM_ASM_MEMORY_FRAMESIZE 262144
#define CKB_VM_ASM_MEMORY_FRAMES 16
#define CKB_VM_ASM_MEMORY_FRAME_PAGE_SHIFTS 6

#define CKB_VM_ASM_MAXIMUM_TRACE_ADDRESS_LENGTH 64

#define CKB_VM_ASM_RET_DECODE_TRACE 1
#define CKB_VM_ASM_RET_ECALL 2
#define CKB_VM_ASM_RET_EBREAK 3
#define CKB_VM_ASM_RET_DYNAMIC_JUMP 4
#define CKB_VM_ASM_RET_MAX_CYCLES_EXCEEDED 5
#define CKB_VM_ASM_RET_OUT_OF_BOUND 6
#define CKB_VM_ASM_RET_INVALID_PERMISSION 7
#define CKB_VM_ASM_RET_UNIMPLEMENTED_INSTRUCTION 8

#define CKB_VM_ASM_REGISTER_SP 2

#define CKB_VM_ASM_MEMORY_FLAG_FREEZED 1
#define CKB_VM_ASM_MEMORY_FLAG_EXECUTABLE 2
#define CKB_VM_ASM_MEMORY_FLAG_WXORX_BIT 2
#define CKB_VM_ASM_MEMORY_FLAG_WRITABLE 0

#define CKB_VM_ASM_TRACE_STRUCT_SIZE 296
#define CKB_VM_ASM_TRACE_OFFSET_ADDRESS 0
#define CKB_VM_ASM_TRACE_OFFSET_LENGTH 8
#define CKB_VM_ASM_TRACE_OFFSET_CYCLES 16
#define CKB_VM_ASM_TRACE_OFFSET_INSTRUCTIONS 24
#define CKB_VM_ASM_TRACE_OFFSET_THREAD 160

#define CKB_VM_ASM_ASM_CORE_MACHINE_STRUCT_SIZE 6620472
#define CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_REGISTERS 0
#define CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_PC 256
#define CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_CYCLES 272
#define CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_MAX_CYCLES 280
#define CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_CHAOS_MODE 288
#define CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_FLAGS 296
#define CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_MEMORY 1320
#define CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_TRACES 4195640
#define CKB_VM_ASM_ASM_CORE_MACHINE_OFFSET_FRAMES 4195624

#define CKB_VM_ASM_OP_UNLOADED 0
#define CKB_VM_ASM_OP_ADD 1
#define CKB_VM_ASM_OP_ADDI 2
#define CKB_VM_ASM_OP_ADDIW 3
#define CKB_VM_ASM_OP_ADDW 4
#define CKB_VM_ASM_OP_AND 5
#define CKB_VM_ASM_OP_ANDI 6
#define CKB_VM_ASM_OP_AUIPC 7
#define CKB_VM_ASM_OP_BEQ 8
#define CKB_VM_ASM_OP_BGE 9
#define CKB_VM_ASM_OP_BGEU 10
#define CKB_VM_ASM_OP_BLT 11
#define CKB_VM_ASM_OP_BLTU 12
#define CKB_VM_ASM_OP_BNE 13
#define CKB_VM_ASM_OP_DIV 14
#define CKB_VM_ASM_OP_DIVU 15
#define CKB_VM_ASM_OP_DIVUW 16
#define CKB_VM_ASM_OP_DIVW 17
#define CKB_VM_ASM_OP_EBREAK 18
#define CKB_VM_ASM_OP_ECALL 19
#define CKB_VM_ASM_OP_FENCE 20
#define CKB_VM_ASM_OP_FENCEI 21
#define CKB_VM_ASM_OP_JAL 22
#define CKB_VM_ASM_OP_JALR 23
#define CKB_VM_ASM_OP_LB 24
#define CKB_VM_ASM_OP_LBU 25
#define CKB_VM_ASM_OP_LD 26
#define CKB_VM_ASM_OP_LH 27
#define CKB_VM_ASM_OP_LHU 28
#define CKB_VM_ASM_OP_LUI 29
#define CKB_VM_ASM_OP_LW 30
#define CKB_VM_ASM_OP_LWU 31
#define CKB_VM_ASM_OP_MUL 32
#define CKB_VM_ASM_OP_MULH 33
#define CKB_VM_ASM_OP_MULHSU 34
#define CKB_VM_ASM_OP_MULHU 35
#define CKB_VM_ASM_OP_MULW 36
#define CKB_VM_ASM_OP_OR 37
#define CKB_VM_ASM_OP_ORI 38
#define CKB_VM_ASM_OP_REM 39
#define CKB_VM_ASM_OP_REMU 40
#define CKB_VM_ASM_OP_REMUW 41
#define CKB_VM_ASM_OP_REMW 42
#define CKB_VM_ASM_OP_SB 43
#define CKB_VM_ASM_OP_SD 44
#define CKB_VM_ASM_OP_SH 45
#define CKB_VM_ASM_OP_SLL 46
#define CKB_VM_ASM_OP_SLLI 47
#define CKB_VM_ASM_OP_SLLIW 48
#define CKB_VM_ASM_OP_SLLW 49
#define CKB_VM_ASM_OP_SLT 50
#define CKB_VM_ASM_OP_SLTI 51
#define CKB_VM_ASM_OP_SLTIU 52
#define CKB_VM_ASM_OP_SLTU 53
#define CKB_VM_ASM_OP_SRA 54
#define CKB_VM_ASM_OP_SRAI 55
#define CKB_VM_ASM_OP_SRAIW 56
#define CKB_VM_ASM_OP_SRAW 57
#define CKB_VM_ASM_OP_SRL 58
#define CKB_VM_ASM_OP_SRLI 59
#define CKB_VM_ASM_OP_SRLIW 60
#define CKB_VM_ASM_OP_SRLW 61
#define CKB_VM_ASM_OP_SUB 62
#define CKB_VM_ASM_OP_SUBW 63
#define CKB_VM_ASM_OP_SW 64
#define CKB_VM_ASM_OP_VERSION1_JALR 65
#define CKB_VM_ASM_OP_VERSION1_LB 66
#define CKB_VM_ASM_OP_VERSION1_LBU 67
#define CKB_VM_ASM_OP_VERSION1_LD 68
#define CKB_VM_ASM_OP_VERSION1_LH 69
#define CKB_VM_ASM_OP_VERSION1_LHU 70
#define CKB_VM_ASM_OP_VERSION1_LW 71
#define CKB_VM_ASM_OP_VERSION1_LWU 72
#define CKB_VM_ASM_OP_XOR 73
#define CKB_VM_ASM_OP_XORI 74
#define CKB_VM_ASM_OP_RVC_ADD 75
#define CKB_VM_ASM_OP_RVC_ADDI 76
#define CKB_VM_ASM_OP_RVC_ADDI16SP 77
#define CKB_VM_ASM_OP_RVC_ADDI4SPN 78
#define CKB_VM_ASM_OP_RVC_ADDIW 79
#define CKB_VM_ASM_OP_RVC_ADDW 80
#define CKB_VM_ASM_OP_RVC_AND 81
#define CKB_VM_ASM_OP_RVC_ANDI 82
#define CKB_VM_ASM_OP_RVC_BEQZ 83
#define CKB_VM_ASM_OP_RVC_BNEZ 84
#define CKB_VM_ASM_OP_RVC_EBREAK 85
#define CKB_VM_ASM_OP_RVC_J 86
#define CKB_VM_ASM_OP_RVC_JAL 87
#define CKB_VM_ASM_OP_RVC_JALR 88
#define CKB_VM_ASM_OP_RVC_JR 89
#define CKB_VM_ASM_OP_RVC_LD 90
#define CKB_VM_ASM_OP_RVC_LDSP 91
#define CKB_VM_ASM_OP_RVC_LI 92
#define CKB_VM_ASM_OP_RVC_LUI 93
#define CKB_VM_ASM_OP_RVC_LW 94
#define CKB_VM_ASM_OP_RVC_LWSP 95
#define CKB_VM_ASM_OP_RVC_MV 96
#define CKB_VM_ASM_OP_RVC_NOP 97
#define CKB_VM_ASM_OP_RVC_OR 98
#define CKB_VM_ASM_OP_RVC_SD 99
#define CKB_VM_ASM_OP_RVC_SDSP 100
#define CKB_VM_ASM_OP_RVC_SLLI 101
#define CKB_VM_ASM_OP_RVC_SLLI64 102
#define CKB_VM_ASM_OP_RVC_SRAI 103
#define CKB_VM_ASM_OP_RVC_SRAI64 104
#define CKB_VM_ASM_OP_RVC_SRLI 105
#define CKB_VM_ASM_OP_RVC_SRLI64 106
#define CKB_VM_ASM_OP_RVC_SUB 107
#define CKB_VM_ASM_OP_RVC_SUBW 108
#define CKB_VM_ASM_OP_RVC_SW 109
#define CKB_VM_ASM_OP_RVC_SWSP 110
#define CKB_VM_ASM_OP_RVC_XOR 111
#define CKB_VM_ASM_OP_VERSION1_RVC_JALR 112
#define CKB_VM_ASM_OP_VERSION1_RVC_LD 113
#define CKB_VM_ASM_OP_VERSION1_RVC_LDSP 114
#define CKB_VM_ASM_OP_VERSION1_RVC_LW 115
#define CKB_VM_ASM_OP_VERSION1_RVC_LWSP 116
#define CKB_VM_ASM_OP_ANDN 117
#define CKB_VM_ASM_OP_ORN 118
#define CKB_VM_ASM_OP_XNOR 119
#define CKB_VM_ASM_OP_SLO 120
#define CKB_VM_ASM_OP_SRO 121
#define CKB_VM_ASM_OP_ROL 122
#define CKB_VM_ASM_OP_ROR 123
#define CKB_VM_ASM_OP_SH1ADD 124
#define CKB_VM_ASM_OP_SH2ADD 125
#define CKB_VM_ASM_OP_SH3ADD 126
#define CKB_VM_ASM_OP_SBCLR 127
#define CKB_VM_ASM_OP_SBSET 128
#define CKB_VM_ASM_OP_SBINV 129
#define CKB_VM_ASM_OP_SBEXT 130
#define CKB_VM_ASM_OP_GORC 131
#define CKB_VM_ASM_OP_GREV 132
#define CKB_VM_ASM_OP_SLOI 133
#define CKB_VM_ASM_OP_SROI 134
#define CKB_VM_ASM_OP_RORI 135
#define CKB_VM_ASM_OP_SBCLRI 136
#define CKB_VM_ASM_OP_SBSETI 137
#define CKB_VM_ASM_OP_SBINVI 138
#define CKB_VM_ASM_OP_SBEXTI 139
#define CKB_VM_ASM_OP_GORCI 140
#define CKB_VM_ASM_OP_GREVI 141
#define CKB_VM_ASM_OP_CMIX 142
#define CKB_VM_ASM_OP_CMOV 143
#define CKB_VM_ASM_OP_FSL 144
#define CKB_VM_ASM_OP_FSR 145
#define CKB_VM_ASM_OP_FSRI 146
#define CKB_VM_ASM_OP_CLZ 147
#define CKB_VM_ASM_OP_CTZ 148
#define CKB_VM_ASM_OP_PCNT 149
#define CKB_VM_ASM_OP_BMATFLIP 150
#define CKB_VM_ASM_OP_SEXTB 151
#define CKB_VM_ASM_OP_SEXTH 152
#define CKB_VM_ASM_OP_CRC32B 153
#define CKB_VM_ASM_OP_CRC32H 154
#define CKB_VM_ASM_OP_CRC32W 155
#define CKB_VM_ASM_OP_CRC32D 156
#define CKB_VM_ASM_OP_CRC32CB 157
#define CKB_VM_ASM_OP_CRC32CH 158
#define CKB_VM_ASM_OP_CRC32CW 159
#define CKB_VM_ASM_OP_CRC32CD 160
#define CKB_VM_ASM_OP_CLMUL 161
#define CKB_VM_ASM_OP_CLMULR 162
#define CKB_VM_ASM_OP_CLMULH 163
#define CKB_VM_ASM_OP_MIN 164
#define CKB_VM_ASM_OP_MAX 165
#define CKB_VM_ASM_OP_MINU 166
#define CKB_VM_ASM_OP_MAXU 167
#define CKB_VM_ASM_OP_SHFL 168
#define CKB_VM_ASM_OP_UNSHFL 169
#define CKB_VM_ASM_OP_BDEP 170
#define CKB_VM_ASM_OP_BEXT 171
#define CKB_VM_ASM_OP_PACK 172
#define CKB_VM_ASM_OP_PACKU 173
#define CKB_VM_ASM_OP_BMATOR 174
#define CKB_VM_ASM_OP_BMATXOR 175
#define CKB_VM_ASM_OP_PACKH 176
#define CKB_VM_ASM_OP_BFP 177
#define CKB_VM_ASM_OP_SHFLI 178
#define CKB_VM_ASM_OP_UNSHFLI 179
#define CKB_VM_ASM_OP_ADDIWU 180
#define CKB_VM_ASM_OP_SLLIUW 181
#define CKB_VM_ASM_OP_ADDWU 182
#define CKB_VM_ASM_OP_SUBWU 183
#define CKB_VM_ASM_OP_ADDUW 184
#define CKB_VM_ASM_OP_SUBUW 185
#define CKB_VM_ASM_OP_SLOW 186
#define CKB_VM_ASM_OP_SROW 187
#define CKB_VM_ASM_OP_ROLW 188
#define CKB_VM_ASM_OP_RORW 189
#define CKB_VM_ASM_OP_SH1ADDUW 190
#define CKB_VM_ASM_OP_SH2ADDUW 191
#define CKB_VM_ASM_OP_SH3ADDUW 192
#define CKB_VM_ASM_OP_SBCLRW 193
#define CKB_VM_ASM_OP_SBSETW 194
#define CKB_VM_ASM_OP_SBINVW 195
#define CKB_VM_ASM_OP_SBEXTW 196
#define CKB_VM_ASM_OP_GORCW 197
#define CKB_VM_ASM_OP_GREVW 198
#define CKB_VM_ASM_OP_SLOIW 199
#define CKB_VM_ASM_OP_SROIW 200
#define CKB_VM_ASM_OP_RORIW 201
#define CKB_VM_ASM_OP_SBCLRIW 202
#define CKB_VM_ASM_OP_SBSETIW 203
#define CKB_VM_ASM_OP_SBINVIW 204
#define CKB_VM_ASM_OP_GORCIW 205
#define CKB_VM_ASM_OP_GREVIW 206
#define CKB_VM_ASM_OP_FSLW 207
#define CKB_VM_ASM_OP_FSRW 208
#define CKB_VM_ASM_OP_FSRIW 209
#define CKB_VM_ASM_OP_CLZW 210
#define CKB_VM_ASM_OP_CTZW 211
#define CKB_VM_ASM_OP_PCNTW 212
#define CKB_VM_ASM_OP_CLMULW 213
#define CKB_VM_ASM_OP_CLMULRW 214
#define CKB_VM_ASM_OP_CLMULHW 215
#define CKB_VM_ASM_OP_SHFLW 216
#define CKB_VM_ASM_OP_UNSHFLW 217
#define CKB_VM_ASM_OP_BDEPW 218
#define CKB_VM_ASM_OP_BEXTW 219
#define CKB_VM_ASM_OP_PACKW 220
#define CKB_VM_ASM_OP_PACKUW 221
#define CKB_VM_ASM_OP_BFPW 222
#define CKB_VM_ASM_OP_CUSTOM_LOAD_IMM 223
#define CKB_VM_ASM_OP_CUSTOM_TRACE_END 224

#ifdef CKB_VM_ASM_GENERATE_LABEL_TABLES
#ifdef __APPLE__
.global _ckb_vm_asm_labels
_ckb_vm_asm_labels:
#else
.global ckb_vm_asm_labels
ckb_vm_asm_labels:
#endif
.CKB_VM_ASM_LABEL_TABLE:
	.long	.CKB_VM_ASM_LABEL_OP_UNLOADED - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_ADD - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_ADDI - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_ADDIW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_ADDW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_AND - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_ANDI - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_AUIPC - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_BEQ - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_BGE - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_BGEU - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_BLT - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_BLTU - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_BNE - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_DIV - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_DIVU - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_DIVUW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_DIVW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_EBREAK - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_ECALL - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_FENCE - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_FENCEI - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_JAL - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_JALR - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_LB - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_LBU - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_LD - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_LH - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_LHU - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_LUI - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_LW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_LWU - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_MUL - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_MULH - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_MULHSU - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_MULHU - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_MULW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_OR - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_ORI - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_REM - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_REMU - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_REMUW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_REMW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SB - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SD - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SH - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SLL - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SLLI - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SLLIW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SLLW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SLT - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SLTI - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SLTIU - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SLTU - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SRA - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SRAI - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SRAIW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SRAW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SRL - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SRLI - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SRLIW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SRLW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SUB - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SUBW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_VERSION1_JALR - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_VERSION1_LB - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_VERSION1_LBU - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_VERSION1_LD - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_VERSION1_LH - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_VERSION1_LHU - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_VERSION1_LW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_VERSION1_LWU - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_XOR - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_XORI - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_ADD - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_ADDI - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_ADDI16SP - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_ADDI4SPN - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_ADDIW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_ADDW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_AND - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_ANDI - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_BEQZ - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_BNEZ - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_EBREAK - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_J - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_JAL - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_JALR - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_JR - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_LD - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_LDSP - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_LI - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_LUI - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_LW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_LWSP - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_MV - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_NOP - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_OR - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_SD - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_SDSP - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_SLLI - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_SLLI64 - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_SRAI - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_SRAI64 - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_SRLI - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_SRLI64 - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_SUB - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_SUBW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_SW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_SWSP - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RVC_XOR - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_VERSION1_RVC_JALR - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_VERSION1_RVC_LD - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_VERSION1_RVC_LDSP - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_VERSION1_RVC_LW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_VERSION1_RVC_LWSP - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_ANDN - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_ORN - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_XNOR - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SLO - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SRO - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_ROL - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_ROR - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SH1ADD - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SH2ADD - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SH3ADD - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SBCLR - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SBSET - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SBINV - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SBEXT - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_GORC - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_GREV - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SLOI - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SROI - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RORI - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SBCLRI - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SBSETI - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SBINVI - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SBEXTI - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_GORCI - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_GREVI - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_CMIX - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_CMOV - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_FSL - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_FSR - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_FSRI - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_CLZ - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_CTZ - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_PCNT - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_BMATFLIP - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SEXTB - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SEXTH - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_CRC32B - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_CRC32H - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_CRC32W - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_CRC32D - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_CRC32CB - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_CRC32CH - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_CRC32CW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_CRC32CD - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_CLMUL - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_CLMULR - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_CLMULH - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_MIN - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_MAX - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_MINU - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_MAXU - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SHFL - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_UNSHFL - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_BDEP - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_BEXT - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_PACK - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_PACKU - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_BMATOR - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_BMATXOR - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_PACKH - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_BFP - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SHFLI - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_UNSHFLI - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_ADDIWU - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SLLIUW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_ADDWU - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SUBWU - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_ADDUW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SUBUW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SLOW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SROW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_ROLW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RORW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SH1ADDUW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SH2ADDUW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SH3ADDUW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SBCLRW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SBSETW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SBINVW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SBEXTW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_GORCW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_GREVW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SLOIW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SROIW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_RORIW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SBCLRIW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SBSETIW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SBINVIW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_GORCIW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_GREVIW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_FSLW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_FSRW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_FSRIW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_CLZW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_CTZW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_PCNTW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_CLMULW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_CLMULRW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_CLMULHW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_SHFLW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_UNSHFLW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_BDEPW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_BEXTW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_PACKW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_PACKUW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_BFPW - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_CUSTOM_LOAD_IMM - .CKB_VM_ASM_LABEL_TABLE
	.long	.CKB_VM_ASM_LABEL_OP_CUSTOM_TRACE_END - .CKB_VM_ASM_LABEL_TABLE
#endif /* CKB_VM_ASM_GENERATE_LABEL_TABLES */
