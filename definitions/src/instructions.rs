// For fast decoding and cache friendly, RISC-V instruction is decoded
// into 64 bit unsigned integer in the following format:
//
// +-----+-----+-----+-----+-----+-----+-----+-----+
// |           | rs1 | rs2 | res |     | rd  | op  | R-type
// +-----------+-----------------------------------+
// |    immediate    | rs1 | res |     | rd  | op  | I-type
// +-----------------------------------------------+
// |    immediate    | rs1 | res |     | rs2 | op  | S-type/B-type
// +-----------------+-----------------------------+
// |       immediate       | res |     | rd  | op  | U-type/J-type
// +-----+-----+-----+-----+-----+-----+-----+-----+
//
// +res+ here means reserved field that is not yet used.
//
// This way each op and register index are in full byte, accessing them
// will be much faster than the original compact form. Hence we will have
// a fast path where the interpreter loop reads instruction directly in this
// format, and a slow path where a full featured decoder decodes RISC-V
// instruction into the internal form here(much like how traces/micro-ops work.)
pub type Instruction = u64;

pub type InstructionOpcode = u8;

pub const OP_UNLOADED: InstructionOpcode = 0;
pub const OP_ADD: InstructionOpcode = 1;
pub const OP_ADDIW: InstructionOpcode = 2;
pub const OP_ADDW: InstructionOpcode = 3;
pub const OP_AND: InstructionOpcode = 4;
pub const OP_ANDI: InstructionOpcode = 5;
pub const OP_AUIPC: InstructionOpcode = 6;
pub const OP_BEQ: InstructionOpcode = 7;
pub const OP_BGE: InstructionOpcode = 8;
pub const OP_BGEU: InstructionOpcode = 9;
pub const OP_BLT: InstructionOpcode = 10;
pub const OP_BLTU: InstructionOpcode = 11;
pub const OP_BNE: InstructionOpcode = 12;
pub const OP_DIV: InstructionOpcode = 13;
pub const OP_DIVU: InstructionOpcode = 14;
pub const OP_DIVUW: InstructionOpcode = 15;
pub const OP_DIVW: InstructionOpcode = 16;
pub const OP_EBREAK: InstructionOpcode = 17;
pub const OP_ECALL: InstructionOpcode = 18;
pub const OP_FENCE: InstructionOpcode = 19;
pub const OP_FENCEI: InstructionOpcode = 20;
pub const OP_JAL: InstructionOpcode = 21;
pub const OP_JALR: InstructionOpcode = 22;
pub const OP_LB: InstructionOpcode = 23;
pub const OP_LBU: InstructionOpcode = 24;
pub const OP_LD: InstructionOpcode = 25;
pub const OP_LH: InstructionOpcode = 26;
pub const OP_LHU: InstructionOpcode = 27;
pub const OP_LUI: InstructionOpcode = 28;
pub const OP_LW: InstructionOpcode = 29;
pub const OP_LWU: InstructionOpcode = 30;
pub const OP_MUL: InstructionOpcode = 31;
pub const OP_MULH: InstructionOpcode = 32;
pub const OP_MULHSU: InstructionOpcode = 33;
pub const OP_MULHU: InstructionOpcode = 34;
pub const OP_MULW: InstructionOpcode = 35;
pub const OP_OR: InstructionOpcode = 36;
pub const OP_ORI: InstructionOpcode = 37;
pub const OP_REM: InstructionOpcode = 38;
pub const OP_REMU: InstructionOpcode = 39;
pub const OP_REMUW: InstructionOpcode = 40;
pub const OP_REMW: InstructionOpcode = 41;
pub const OP_SB: InstructionOpcode = 42;
pub const OP_SD: InstructionOpcode = 43;
pub const OP_SH: InstructionOpcode = 44;
pub const OP_SLL: InstructionOpcode = 45;
pub const OP_SLLI: InstructionOpcode = 46;
pub const OP_SLLIW: InstructionOpcode = 47;
pub const OP_SLLW: InstructionOpcode = 48;
pub const OP_SLT: InstructionOpcode = 49;
pub const OP_SLTI: InstructionOpcode = 50;
pub const OP_SLTIU: InstructionOpcode = 51;
pub const OP_SLTU: InstructionOpcode = 52;
pub const OP_SRA: InstructionOpcode = 53;
pub const OP_SRAI: InstructionOpcode = 54;
pub const OP_SRAIW: InstructionOpcode = 55;
pub const OP_SRAW: InstructionOpcode = 56;
pub const OP_SRL: InstructionOpcode = 57;
pub const OP_SRLI: InstructionOpcode = 58;
pub const OP_SRLIW: InstructionOpcode = 59;
pub const OP_SRLW: InstructionOpcode = 60;
pub const OP_SUB: InstructionOpcode = 61;
pub const OP_SUBW: InstructionOpcode = 62;
pub const OP_SW: InstructionOpcode = 63;
pub const OP_XOR: InstructionOpcode = 64;
pub const OP_XORI: InstructionOpcode = 65;
pub const OP_RVC_ADD: InstructionOpcode = 66;
pub const OP_RVC_ADDI: InstructionOpcode = 67;
pub const OP_RVC_ADDI16SP: InstructionOpcode = 68;
pub const OP_RVC_ADDI4SPN: InstructionOpcode = 69;
pub const OP_RVC_ADDIW: InstructionOpcode = 70;
pub const OP_RVC_ADDW: InstructionOpcode = 71;
pub const OP_RVC_AND: InstructionOpcode = 72;
pub const OP_RVC_ANDI: InstructionOpcode = 73;
pub const OP_RVC_BEQZ: InstructionOpcode = 74;
pub const OP_RVC_BNEZ: InstructionOpcode = 75;
pub const OP_RVC_EBREAK: InstructionOpcode = 76;
pub const OP_RVC_J: InstructionOpcode = 77;
pub const OP_RVC_JAL: InstructionOpcode = 78;
pub const OP_RVC_JALR: InstructionOpcode = 79;
pub const OP_RVC_JR: InstructionOpcode = 80;
pub const OP_RVC_LD: InstructionOpcode = 81;
pub const OP_RVC_LDSP: InstructionOpcode = 82;
pub const OP_RVC_LI: InstructionOpcode = 83;
pub const OP_RVC_LUI: InstructionOpcode = 84;
pub const OP_RVC_LW: InstructionOpcode = 85;
pub const OP_RVC_LWSP: InstructionOpcode = 86;
pub const OP_RVC_MV: InstructionOpcode = 87;
pub const OP_RVC_NOP: InstructionOpcode = 88;
pub const OP_RVC_OR: InstructionOpcode = 89;
pub const OP_RVC_SD: InstructionOpcode = 90;
pub const OP_RVC_SDSP: InstructionOpcode = 91;
pub const OP_RVC_SLLI: InstructionOpcode = 92;
pub const OP_RVC_SLLI64: InstructionOpcode = 93;
pub const OP_RVC_SRAI: InstructionOpcode = 94;
pub const OP_RVC_SRAI64: InstructionOpcode = 95;
pub const OP_RVC_SRLI: InstructionOpcode = 96;
pub const OP_RVC_SRLI64: InstructionOpcode = 97;
pub const OP_RVC_SUB: InstructionOpcode = 98;
pub const OP_RVC_SUBW: InstructionOpcode = 99;
pub const OP_RVC_SW: InstructionOpcode = 100;
pub const OP_RVC_SWSP: InstructionOpcode = 101;
pub const OP_RVC_XOR: InstructionOpcode = 102;
pub const OP_CUSTOM_LOAD_IMM: InstructionOpcode = 103;
pub const OP_ADDI: InstructionOpcode = 104;
pub const OP_ANDN: InstructionOpcode = 105;
pub const OP_ORN: InstructionOpcode = 106;
pub const OP_XNOR: InstructionOpcode = 107;
pub const OP_SLO: InstructionOpcode = 108;
pub const OP_SRO: InstructionOpcode = 109;
pub const OP_ROL: InstructionOpcode = 110;
pub const OP_ROR: InstructionOpcode = 111;
pub const OP_SH1ADD: InstructionOpcode = 112;
pub const OP_SH2ADD: InstructionOpcode = 113;
pub const OP_SH3ADD: InstructionOpcode = 114;
pub const OP_SBCLR: InstructionOpcode = 115;
pub const OP_SBSET: InstructionOpcode = 116;
pub const OP_SBINV: InstructionOpcode = 117;
pub const OP_SBEXT: InstructionOpcode = 118;
pub const OP_GORC: InstructionOpcode = 119;
pub const OP_GREV: InstructionOpcode = 120;
pub const OP_SLOI: InstructionOpcode = 121;
pub const OP_SROI: InstructionOpcode = 122;
pub const OP_RORI: InstructionOpcode = 123;
pub const OP_SBCLRI: InstructionOpcode = 124;
pub const OP_SBSETI: InstructionOpcode = 125;
pub const OP_SBINVI: InstructionOpcode = 126;
pub const OP_SBEXTI: InstructionOpcode = 127;
pub const OP_GORCI: InstructionOpcode = 128;
pub const OP_GREVI: InstructionOpcode = 129;
pub const OP_CMIX: InstructionOpcode = 130;
pub const OP_CMOV: InstructionOpcode = 131;
pub const OP_FSL: InstructionOpcode = 132;
pub const OP_FSR: InstructionOpcode = 133;
pub const OP_FSRI: InstructionOpcode = 134;
pub const OP_CLZ: InstructionOpcode = 135;
pub const OP_CTZ: InstructionOpcode = 136;
pub const OP_PCNT: InstructionOpcode = 137;
pub const OP_BMATFLIP: InstructionOpcode = 138;
pub const OP_SEXTB: InstructionOpcode = 139;
pub const OP_SEXTH: InstructionOpcode = 140;
pub const OP_CRC32B: InstructionOpcode = 141;
pub const OP_CRC32H: InstructionOpcode = 142;
pub const OP_CRC32W: InstructionOpcode = 143;
pub const OP_CRC32D: InstructionOpcode = 144;
pub const OP_CRC32CB: InstructionOpcode = 145;
pub const OP_CRC32CH: InstructionOpcode = 146;
pub const OP_CRC32CW: InstructionOpcode = 147;
pub const OP_CRC32CD: InstructionOpcode = 148;
pub const OP_CLMUL: InstructionOpcode = 149;
pub const OP_CLMULR: InstructionOpcode = 150;
pub const OP_CLMULH: InstructionOpcode = 151;
pub const OP_MIN: InstructionOpcode = 152;
pub const OP_MAX: InstructionOpcode = 153;
pub const OP_MINU: InstructionOpcode = 154;
pub const OP_MAXU: InstructionOpcode = 155;
pub const OP_SHFL: InstructionOpcode = 156;
pub const OP_UNSHFL: InstructionOpcode = 157;
pub const OP_BDEP: InstructionOpcode = 158;
pub const OP_BEXT: InstructionOpcode = 159;
pub const OP_PACK: InstructionOpcode = 160;
pub const OP_PACKU: InstructionOpcode = 161;
pub const OP_BMATOR: InstructionOpcode = 162;
pub const OP_BMATXOR: InstructionOpcode = 163;
pub const OP_PACKH: InstructionOpcode = 164;
pub const OP_BFP: InstructionOpcode = 165;
pub const OP_SHFLI: InstructionOpcode = 166;
pub const OP_UNSHFLI: InstructionOpcode = 167;
pub const OP_ADDIWU: InstructionOpcode = 168;
pub const OP_SLLIUW: InstructionOpcode = 169;
pub const OP_ADDWU: InstructionOpcode = 170;
pub const OP_SUBWU: InstructionOpcode = 171;
pub const OP_ADDUW: InstructionOpcode = 172;
pub const OP_SUBUW: InstructionOpcode = 173;
pub const OP_SLOW: InstructionOpcode = 174;
pub const OP_SROW: InstructionOpcode = 175;
pub const OP_ROLW: InstructionOpcode = 176;
pub const OP_RORW: InstructionOpcode = 177;
pub const OP_SH1ADDUW: InstructionOpcode = 178;
pub const OP_SH2ADDUW: InstructionOpcode = 179;
pub const OP_SH3ADDUW: InstructionOpcode = 180;
pub const OP_SBCLRW: InstructionOpcode = 181;
pub const OP_SBSETW: InstructionOpcode = 182;
pub const OP_SBINVW: InstructionOpcode = 183;
pub const OP_SBEXTW: InstructionOpcode = 184;
pub const OP_GORCW: InstructionOpcode = 185;
pub const OP_GREVW: InstructionOpcode = 186;
pub const OP_SLOIW: InstructionOpcode = 187;
pub const OP_SROIW: InstructionOpcode = 188;
pub const OP_RORIW: InstructionOpcode = 189;
pub const OP_SBCLRIW: InstructionOpcode = 190;
pub const OP_SBSETIW: InstructionOpcode = 191;
pub const OP_SBINVIW: InstructionOpcode = 192;
pub const OP_GORCIW: InstructionOpcode = 193;
pub const OP_GREVIW: InstructionOpcode = 194;
pub const OP_FSLW: InstructionOpcode = 195;
pub const OP_FSRW: InstructionOpcode = 196;
pub const OP_FSRIW: InstructionOpcode = 197;
pub const OP_CLZW: InstructionOpcode = 198;
pub const OP_CTZW: InstructionOpcode = 199;
pub const OP_PCNTW: InstructionOpcode = 200;
pub const OP_CLMULW: InstructionOpcode = 201;
pub const OP_CLMULRW: InstructionOpcode = 202;
pub const OP_CLMULHW: InstructionOpcode = 203;
pub const OP_SHFLW: InstructionOpcode = 204;
pub const OP_UNSHFLW: InstructionOpcode = 205;
pub const OP_BDEPW: InstructionOpcode = 206;
pub const OP_BEXTW: InstructionOpcode = 207;
pub const OP_PACKW: InstructionOpcode = 208;
pub const OP_PACKUW: InstructionOpcode = 209;
pub const OP_BFPW: InstructionOpcode = 210;
pub const OP_CUSTOM_TRACE_END: InstructionOpcode = 211;

// Maximum opcode for instructions consuming 4 bytes. Any opcode
// larger than this one is treated as RVC instructions(which consume
// 2 bytes)
pub const MAXIMUM_OPCODE: InstructionOpcode = OP_CUSTOM_TRACE_END;

pub const MINIMAL_RVC_OPCODE: InstructionOpcode = OP_RVC_ADD;
pub const MAXIMUM_RVC_OPCODE: InstructionOpcode = OP_RVC_XOR;

pub const INSTRUCTION_OPCODE_NAMES: [&str; MAXIMUM_OPCODE as usize + 1] = [
    "UNLOADED",
    "ADD",
    "ADDIW",
    "ADDW",
    "AND",
    "ANDI",
    "AUIPC",
    "BEQ",
    "BGE",
    "BGEU",
    "BLT",
    "BLTU",
    "BNE",
    "DIV",
    "DIVU",
    "DIVUW",
    "DIVW",
    "EBREAK",
    "ECALL",
    "FENCE",
    "FENCEI",
    "JAL",
    "JALR",
    "LB",
    "LBU",
    "LD",
    "LH",
    "LHU",
    "LUI",
    "LW",
    "LWU",
    "MUL",
    "MULH",
    "MULHSU",
    "MULHU",
    "MULW",
    "OR",
    "ORI",
    "REM",
    "REMU",
    "REMUW",
    "REMW",
    "SB",
    "SD",
    "SH",
    "SLL",
    "SLLI",
    "SLLIW",
    "SLLW",
    "SLT",
    "SLTI",
    "SLTIU",
    "SLTU",
    "SRA",
    "SRAI",
    "SRAIW",
    "SRAW",
    "SRL",
    "SRLI",
    "SRLIW",
    "SRLW",
    "SUB",
    "SUBW",
    "SW",
    "XOR",
    "XORI",
    "RVC_ADD",
    "RVC_ADDI",
    "RVC_ADDI16SP",
    "RVC_ADDI4SPN",
    "RVC_ADDIW",
    "RVC_ADDW",
    "RVC_AND",
    "RVC_ANDI",
    "RVC_BEQZ",
    "RVC_BNEZ",
    "RVC_EBREAK",
    "RVC_J",
    "RVC_JAL",
    "RVC_JALR",
    "RVC_JR",
    "RVC_LD",
    "RVC_LDSP",
    "RVC_LI",
    "RVC_LUI",
    "RVC_LW",
    "RVC_LWSP",
    "RVC_MV",
    "RVC_NOP",
    "RVC_OR",
    "RVC_SD",
    "RVC_SDSP",
    "RVC_SLLI",
    "RVC_SLLI64",
    "RVC_SRAI",
    "RVC_SRAI64",
    "RVC_SRLI",
    "RVC_SRLI64",
    "RVC_SUB",
    "RVC_SUBW",
    "RVC_SW",
    "RVC_SWSP",
    "RVC_XOR",
    "CUSTOM_LOAD_IMM",
    "ADDI",
    "ANDN",
    "ORN",
    "XNOR",
    "SLO",
    "SRO",
    "ROL",
    "ROR",
    "SH1ADD",
    "SH2ADD",
    "SH3ADD",
    "SBCLR",
    "SBSET",
    "SBINV",
    "SBEXT",
    "GORC",
    "GREV",
    "SLOI",
    "SROI",
    "RORI",
    "SBCLRI",
    "SBSETI",
    "SBINVI",
    "SBEXTI",
    "GORCI",
    "GREVI",
    "CMIX",
    "CMOV",
    "FSL",
    "FSR",
    "FSRI",
    "CLZ",
    "CTZ",
    "PCNT",
    "BMATFLIP",
    "SEXTB",
    "SEXTH",
    "CRC32B",
    "CRC32H",
    "CRC32W",
    "CRC32D",
    "CRC32CB",
    "CRC32CH",
    "CRC32CW",
    "CRC32CD",
    "CLMUL",
    "CLMULR",
    "CLMULH",
    "MIN",
    "MAX",
    "MINU",
    "MAXU",
    "SHFL",
    "UNSHFL",
    "BDEP",
    "BEXT",
    "PACK",
    "PACKU",
    "BMATOR",
    "BMATXOR",
    "PACKH",
    "BFP",
    "SHFLI",
    "UNSHFLI",
    "ADDIWU",
    "SLLIUW",
    "ADDWU",
    "SUBWU",
    "ADDUW",
    "SUBUW",
    "SLOW",
    "SROW",
    "ROLW",
    "RORW",
    "SH1ADDUW",
    "SH2ADDUW",
    "SH3ADDUW",
    "SBCLRW",
    "SBSETW",
    "SBINVW",
    "SBEXTW",
    "GORCW",
    "GREVW",
    "SLOIW",
    "SROIW",
    "RORIW",
    "SBCLRIW",
    "SBSETIW",
    "SBINVIW",
    "GORCIW",
    "GREVIW",
    "FSLW",
    "FSRW",
    "FSRIW",
    "CLZW",
    "CTZW",
    "PCNTW",
    "CLMULW",
    "CLMULRW",
    "CLMULHW",
    "SHFLW",
    "UNSHFLW",
    "BDEPW",
    "BEXTW",
    "PACKW",
    "PACKUW",
    "BFPW",
    "CUSTOM_TRACE_END",
];
