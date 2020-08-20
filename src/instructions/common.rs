use super::super::machine::Machine;
use super::super::memory::Memory;
use super::register::Register;
use super::utils::update_register;
use super::{Error, Immediate, RegisterIndex, UImmediate};

// Other instruction set functions common with RVC

// ======================
// #  ALU instructions  #
// ======================
pub fn add<Mac: Machine>(
    machine: &mut Mac,
    rd: RegisterIndex,
    rs1: RegisterIndex,
    rs2: RegisterIndex,
) {
    let rs1_value = &machine.registers()[rs1 as usize];
    let rs2_value = &machine.registers()[rs2 as usize];
    let value = rs1_value.overflowing_add(&rs2_value);
    update_register(machine, rd, value);
}

pub fn addw<Mac: Machine>(
    machine: &mut Mac,
    rd: RegisterIndex,
    rs1: RegisterIndex,
    rs2: RegisterIndex,
) {
    let rs1_value = &machine.registers()[rs1 as usize];
    let rs2_value = &machine.registers()[rs2 as usize];
    let value = rs1_value.overflowing_add(&rs2_value);
    update_register(machine, rd, value.sign_extend(&Mac::REG::from_u8(32)));
}

pub fn sub<Mac: Machine>(
    machine: &mut Mac,
    rd: RegisterIndex,
    rs1: RegisterIndex,
    rs2: RegisterIndex,
) {
    let rs1_value = &machine.registers()[rs1 as usize];
    let rs2_value = &machine.registers()[rs2 as usize];
    let value = rs1_value.overflowing_sub(&rs2_value);
    update_register(machine, rd, value);
}

pub fn subw<Mac: Machine>(
    machine: &mut Mac,
    rd: RegisterIndex,
    rs1: RegisterIndex,
    rs2: RegisterIndex,
) {
    let rs1_value = &machine.registers()[rs1 as usize];
    let rs2_value = &machine.registers()[rs2 as usize];
    let value = rs1_value.overflowing_sub(&rs2_value);
    update_register(machine, rd, value.sign_extend(&Mac::REG::from_u8(32)));
}

pub fn addi<Mac: Machine>(
    machine: &mut Mac,
    rd: RegisterIndex,
    rs1: RegisterIndex,
    imm: Immediate,
) {
    let value = machine.registers()[rs1 as usize].overflowing_add(&Mac::REG::from_i32(imm));
    update_register(machine, rd, value);
}

pub fn addiw<Mac: Machine>(
    machine: &mut Mac,
    rd: RegisterIndex,
    rs1: RegisterIndex,
    imm: Immediate,
) {
    let value = machine.registers()[rs1 as usize].overflowing_add(&Mac::REG::from_i32(imm));
    update_register(machine, rd, value.sign_extend(&Mac::REG::from_u8(32)));
}

// =======================
// #  LOAD instructions  #
// =======================
pub fn lb<Mac: Machine>(
    machine: &mut Mac,
    rd: RegisterIndex,
    rs1: RegisterIndex,
    imm: Immediate,
) -> Result<(), Error> {
    let address = machine.registers()[rs1 as usize].overflowing_add(&Mac::REG::from_i32(imm));
    let value = machine.memory_mut().load8(&address)?;
    // sign-extened
    update_register(machine, rd, value.sign_extend(&Mac::REG::from_u8(8)));
    Ok(())
}

pub fn lh<Mac: Machine>(
    machine: &mut Mac,
    rd: RegisterIndex,
    rs1: RegisterIndex,
    imm: Immediate,
) -> Result<(), Error> {
    let address = machine.registers()[rs1 as usize].overflowing_add(&Mac::REG::from_i32(imm));
    let value = machine.memory_mut().load16(&address)?;
    // sign-extened
    update_register(machine, rd, value.sign_extend(&Mac::REG::from_u8(16)));
    Ok(())
}

pub fn lw<Mac: Machine>(
    machine: &mut Mac,
    rd: RegisterIndex,
    rs1: RegisterIndex,
    imm: Immediate,
) -> Result<(), Error> {
    let address = machine.registers()[rs1 as usize].overflowing_add(&Mac::REG::from_i32(imm));
    let value = machine.memory_mut().load32(&address)?;
    update_register(machine, rd, value.sign_extend(&Mac::REG::from_u8(32)));
    Ok(())
}

pub fn ld<Mac: Machine>(
    machine: &mut Mac,
    rd: RegisterIndex,
    rs1: RegisterIndex,
    imm: Immediate,
) -> Result<(), Error> {
    let address = machine.registers()[rs1 as usize].overflowing_add(&Mac::REG::from_i32(imm));
    let value = machine.memory_mut().load64(&address)?;
    update_register(machine, rd, value.sign_extend(&Mac::REG::from_u8(64)));
    Ok(())
}

pub fn lbu<Mac: Machine>(
    machine: &mut Mac,
    rd: RegisterIndex,
    rs1: RegisterIndex,
    imm: Immediate,
) -> Result<(), Error> {
    let address = machine.registers()[rs1 as usize].overflowing_add(&Mac::REG::from_i32(imm));
    let value = machine.memory_mut().load8(&address)?;
    update_register(machine, rd, value);
    Ok(())
}

pub fn lhu<Mac: Machine>(
    machine: &mut Mac,
    rd: RegisterIndex,
    rs1: RegisterIndex,
    imm: Immediate,
) -> Result<(), Error> {
    let address = machine.registers()[rs1 as usize].overflowing_add(&Mac::REG::from_i32(imm));
    let value = machine.memory_mut().load16(&address)?;
    update_register(machine, rd, value);
    Ok(())
}

pub fn lwu<Mac: Machine>(
    machine: &mut Mac,
    rd: RegisterIndex,
    rs1: RegisterIndex,
    imm: Immediate,
) -> Result<(), Error> {
    let address = machine.registers()[rs1 as usize].overflowing_add(&Mac::REG::from_i32(imm));
    let value = machine.memory_mut().load32(&address)?;
    update_register(machine, rd, value);
    Ok(())
}

// ========================
// #  STORE instructions  #
// ========================
pub fn sb<Mac: Machine>(
    machine: &mut Mac,
    rs1: RegisterIndex,
    rs2: RegisterIndex,
    imm: Immediate,
) -> Result<(), Error> {
    let address = machine.registers()[rs1 as usize].overflowing_add(&Mac::REG::from_i32(imm));
    let value = machine.registers()[rs2 as usize].clone();
    machine.memory_mut().store8(&address, &value)?;
    Ok(())
}

pub fn sh<Mac: Machine>(
    machine: &mut Mac,
    rs1: RegisterIndex,
    rs2: RegisterIndex,
    imm: Immediate,
) -> Result<(), Error> {
    let address = machine.registers()[rs1 as usize].overflowing_add(&Mac::REG::from_i32(imm));
    let value = machine.registers()[rs2 as usize].clone();
    machine.memory_mut().store16(&address, &value)?;
    Ok(())
}

pub fn sw<Mac: Machine>(
    machine: &mut Mac,
    rs1: RegisterIndex,
    rs2: RegisterIndex,
    imm: Immediate,
) -> Result<(), Error> {
    let address = machine.registers()[rs1 as usize].overflowing_add(&Mac::REG::from_i32(imm));
    let value = machine.registers()[rs2 as usize].clone();
    machine.memory_mut().store32(&address, &value)?;
    Ok(())
}

pub fn sd<Mac: Machine>(
    machine: &mut Mac,
    rs1: RegisterIndex,
    rs2: RegisterIndex,
    imm: Immediate,
) -> Result<(), Error> {
    let address = machine.registers()[rs1 as usize].overflowing_add(&Mac::REG::from_i32(imm));
    let value = machine.registers()[rs2 as usize].clone();
    machine.memory_mut().store64(&address, &value)?;
    Ok(())
}

// =========================
// #  BIT-OP instructions  #
// =========================
pub fn and<Mac: Machine>(
    machine: &mut Mac,
    rd: RegisterIndex,
    rs1: RegisterIndex,
    rs2: RegisterIndex,
) {
    let rs1_value = machine.registers()[rs1 as usize].clone();
    let rs2_value = machine.registers()[rs2 as usize].clone();
    let value = rs1_value & rs2_value;
    update_register(machine, rd, value);
}

pub fn xor<Mac: Machine>(
    machine: &mut Mac,
    rd: RegisterIndex,
    rs1: RegisterIndex,
    rs2: RegisterIndex,
) {
    let rs1_value = machine.registers()[rs1 as usize].clone();
    let rs2_value = machine.registers()[rs2 as usize].clone();
    let value = rs1_value ^ rs2_value;
    update_register(machine, rd, value);
}

pub fn or<Mac: Machine>(
    machine: &mut Mac,
    rd: RegisterIndex,
    rs1: RegisterIndex,
    rs2: RegisterIndex,
) {
    let rs1_value = machine.registers()[rs1 as usize].clone();
    let rs2_value = machine.registers()[rs2 as usize].clone();
    let value = rs1_value | rs2_value;
    update_register(machine, rd, value);
}

pub fn andi<Mac: Machine>(
    machine: &mut Mac,
    rd: RegisterIndex,
    rs1: RegisterIndex,
    imm: Immediate,
) {
    let value = machine.registers()[rs1 as usize].clone() & Mac::REG::from_i32(imm);
    update_register(machine, rd, value);
}

pub fn xori<Mac: Machine>(
    machine: &mut Mac,
    rd: RegisterIndex,
    rs1: RegisterIndex,
    imm: Immediate,
) {
    let value = machine.registers()[rs1 as usize].clone() ^ Mac::REG::from_i32(imm);
    update_register(machine, rd, value);
}

pub fn ori<Mac: Machine>(machine: &mut Mac, rd: RegisterIndex, rs1: RegisterIndex, imm: Immediate) {
    let value = machine.registers()[rs1 as usize].clone() | Mac::REG::from_i32(imm);
    update_register(machine, rd, value);
}

pub fn slli<Mac: Machine>(
    machine: &mut Mac,
    rd: RegisterIndex,
    rs1: RegisterIndex,
    shamt: UImmediate,
) {
    let value = machine.registers()[rs1 as usize].clone() << Mac::REG::from_u32(shamt);
    update_register(machine, rd, value);
}

pub fn srli<Mac: Machine>(
    machine: &mut Mac,
    rd: RegisterIndex,
    rs1: RegisterIndex,
    shamt: UImmediate,
) {
    let value = machine.registers()[rs1 as usize].clone() >> Mac::REG::from_u32(shamt);
    update_register(machine, rd, value);
}

pub fn srai<Mac: Machine>(
    machine: &mut Mac,
    rd: RegisterIndex,
    rs1: RegisterIndex,
    shamt: UImmediate,
) {
    let value = machine.registers()[rs1 as usize].signed_shr(&Mac::REG::from_u32(shamt));
    update_register(machine, rd, value);
}

pub fn slliw<Mac: Machine>(
    machine: &mut Mac,
    rd: RegisterIndex,
    rs1: RegisterIndex,
    shamt: UImmediate,
) {
    let value = machine.registers()[rs1 as usize].clone() << Mac::REG::from_u32(shamt);
    update_register(machine, rd, value.sign_extend(&Mac::REG::from_u8(32)));
}

pub fn srliw<Mac: Machine>(
    machine: &mut Mac,
    rd: RegisterIndex,
    rs1: RegisterIndex,
    shamt: UImmediate,
) {
    let value = machine.registers()[rs1 as usize].zero_extend(&Mac::REG::from_u8(32))
        >> Mac::REG::from_u32(shamt);
    update_register(machine, rd, value.sign_extend(&Mac::REG::from_u8(32)));
}

pub fn sraiw<Mac: Machine>(
    machine: &mut Mac,
    rd: RegisterIndex,
    rs1: RegisterIndex,
    shamt: UImmediate,
) {
    let value = machine.registers()[rs1 as usize]
        .sign_extend(&Mac::REG::from_u8(32))
        .signed_shr(&Mac::REG::from_u32(shamt));
    update_register(machine, rd, value.sign_extend(&Mac::REG::from_u8(32)));
}

// =======================
// #  JUMP instructions  #
// =======================
pub fn jal<Mac: Machine>(
    machine: &mut Mac,
    rd: RegisterIndex,
    imm: Immediate,
    xbytes: u8,
) -> Option<Mac::REG> {
    let link = machine.pc().overflowing_add(&Mac::REG::from_u8(xbytes));
    update_register(machine, rd, link);
    Some(machine.pc().overflowing_add(&Mac::REG::from_i32(imm)))
}

// ==============================
// #  B-extension instructions  #
// ==============================
pub fn slo32(rs1: u32, rs2: u32) -> u32 {
    let shamt = rs2 & 31;
    return !(!rs1 << shamt);
}

pub fn slo<Mac: Machine>(rs1: Mac::REG, rs2: Mac::REG) -> Mac::REG {
    let shamt = rs2 & (Mac::REG::from_u8(Mac::REG::BITS - 1));
    return !(!rs1 << shamt);
}

pub fn sro32(rs1: u32, rs2: u32) -> u32 {
    let shamt = rs2 & 31;
    return !(!rs1 >> shamt);
}

pub fn sro<Mac: Machine>(rs1: Mac::REG, rs2: Mac::REG) -> Mac::REG {
    let shamt = rs2 & (Mac::REG::from_u8(Mac::REG::BITS - 1));
    return !(!rs1 >> shamt);
}

pub fn grev32(rs1: u32, rs2: u32) -> u32 {
    let mut x = rs1;
    let shamt = rs2 & 31;
    if (shamt & 1) != 0 {
        x = ((x & 0x55555555) << 1) | ((x & 0xAAAAAAAA) >> 1);
    }
    if (shamt & 2) != 0 {
        x = ((x & 0x33333333) << 2) | ((x & 0xCCCCCCCC) >> 2);
    }
    if (shamt & 4) != 0 {
        x = ((x & 0x0F0F0F0F) << 4) | ((x & 0xF0F0F0F0) >> 4);
    }
    if (shamt & 8) != 0 {
        x = ((x & 0x00FF00FF) << 8) | ((x & 0xFF00FF00) >> 8);
    }
    if (shamt & 16) != 0 {
        x = ((x & 0x0000FFFF) << 16) | ((x & 0xFFFF0000) >> 16);
    }
    return x;
}

pub fn grev64(rs1: u64, rs2: u64) -> u64 {
    let mut x = rs1;
    let shamt = rs2 & 63;
    if (shamt & 1) != 0 {
        x = ((x & 0x5555555555555555u64) << 1) | ((x & 0xAAAAAAAAAAAAAAAAu64) >> 1);
    }
    if (shamt & 2) != 0 {
        x = ((x & 0x3333333333333333u64) << 2) | ((x & 0xCCCCCCCCCCCCCCCCu64) >> 2);
    }
    if (shamt & 4) != 0 {
        x = ((x & 0x0F0F0F0F0F0F0F0Fu64) << 4) | ((x & 0xF0F0F0F0F0F0F0F0u64) >> 4);
    }
    if (shamt & 8) != 0 {
        x = ((x & 0x00FF00FF00FF00FFu64) << 8) | ((x & 0xFF00FF00FF00FF00u64) >> 8);
    }
    if (shamt & 16) != 0 {
        x = ((x & 0x0000FFFF0000FFFFu64) << 16) | ((x & 0xFFFF0000FFFF0000u64) >> 16);
    }
    if (shamt & 32) != 0 {
        x = ((x & 0x00000000FFFFFFFFu64) << 32) | ((x & 0xFFFFFFFF00000000u64) >> 32);
    }
    return x;
}

fn shuffle32_stage(src: u32, maskl: u32, maskr: u32, n: u32) -> u32 {
    let mut x = src & !(maskl | maskr);
    x |= ((src << n) & maskl) | ((src >> n) & maskr);
    return x;
}

pub fn shfl32(rs1: u32, rs2: u32) -> u32 {
    let mut x = rs1;
    let shamt = rs2 & 15;
    if (shamt & 8) != 0 {
        x = shuffle32_stage(x, 0x00ff0000, 0x0000ff00, 8);
    }
    if (shamt & 4) != 0 {
        x = shuffle32_stage(x, 0x0f000f00, 0x00f000f0, 4);
    }
    if (shamt & 2) != 0 {
        x = shuffle32_stage(x, 0x30303030, 0x0c0c0c0c, 2);
    }
    if (shamt & 1) != 0 {
        x = shuffle32_stage(x, 0x44444444, 0x22222222, 1);
    }
    return x;
}

pub fn unshfl32(rs1: u32, rs2: u32) -> u32 {
    let mut x = rs1;
    let shamt = rs2 & 15;
    if (shamt & 1) != 0 {
        x = shuffle32_stage(x, 0x44444444, 0x22222222, 1);
    }
    if (shamt & 2) != 0 {
        x = shuffle32_stage(x, 0x30303030, 0x0c0c0c0c, 2);
    }
    if (shamt & 4) != 0 {
        x = shuffle32_stage(x, 0x0f000f00, 0x00f000f0, 4);
    }
    if (shamt & 8) != 0 {
        x = shuffle32_stage(x, 0x00ff0000, 0x0000ff00, 8);
    }
    return x;
}

fn shuffle64_stage(src: u64, maskl: u64, maskr: u64, n: u64) -> u64 {
    let mut x = src & !(maskl | maskr);
    x |= ((src << n) & maskl) | ((src >> n) & maskr);
    return x;
}

pub fn shfl64(rs1: u64, rs2: u64) -> u64 {
    let mut x = rs1;
    let shamt = rs2 & 31;
    if (shamt & 16) != 0 {
        x = shuffle64_stage(x, 0x0000ffff00000000, 0x00000000ffff0000, 16);
    }
    if (shamt & 8) != 0 {
        x = shuffle64_stage(x, 0x00ff000000ff0000, 0x0000ff000000ff00, 8);
    }
    if (shamt & 4) != 0 {
        x = shuffle64_stage(x, 0x0f000f000f000f00, 0x00f000f000f000f0, 4);
    }
    if (shamt & 2) != 0 {
        x = shuffle64_stage(x, 0x3030303030303030, 0x0c0c0c0c0c0c0c0c, 2);
    }
    if (shamt & 1) != 0 {
        x = shuffle64_stage(x, 0x4444444444444444, 0x2222222222222222, 1);
    }
    return x;
}

pub fn unshfl64(rs1: u64, rs2: u64) -> u64 {
    let mut x = rs1;
    let shamt = rs2 & 31;
    if (shamt & 1) != 0 {
        x = shuffle64_stage(x, 0x4444444444444444, 0x2222222222222222, 1);
    }
    if (shamt & 2) != 0 {
        x = shuffle64_stage(x, 0x3030303030303030, 0x0c0c0c0c0c0c0c0c, 2);
    }
    if (shamt & 4) != 0 {
        x = shuffle64_stage(x, 0x0f000f000f000f00, 0x00f000f000f000f0, 4);
    }
    if (shamt & 8) != 0 {
        x = shuffle64_stage(x, 0x00ff000000ff0000, 0x0000ff000000ff00, 8);
    }
    if (shamt & 16) != 0 {
        x = shuffle64_stage(x, 0x0000ffff00000000, 0x00000000ffff0000, 16);
    }
    return x;
}

pub fn crc32<Mac: Machine>(machine: &mut Mac, rs1: RegisterIndex, rd: RegisterIndex, nbits: u32) {
    let mut x = machine.registers()[rs1 as usize].clone();
    for _ in 0..nbits {
        x = (x.clone() >> Mac::REG::from_u32(1))
            ^ (Mac::REG::from_u32(0xEDB88320)
                & !((x & Mac::REG::from_u32(1)).overflowing_sub(&Mac::REG::from_u32(1))));
    }
    update_register(machine, rd, x);
}

pub fn crc32c<Mac: Machine>(machine: &mut Mac, rs1: RegisterIndex, rd: RegisterIndex, nbits: u32) {
    let mut x = machine.registers()[rs1 as usize].clone();
    for _ in 0..nbits {
        x = (x.clone() >> Mac::REG::from_u32(1))
            ^ (Mac::REG::from_u32(0x82F63B78)
                & !((x & Mac::REG::from_u32(1)).overflowing_sub(&Mac::REG::from_u32(1))));
    }
    update_register(machine, rd, x);
}

pub fn bext32(rs1: u32, rs2: u32) -> u32 {
    let mut r: u32 = 0;
    let mut j = 0;
    for i in 0..32 {
        if ((rs2 >> i) & 1) != 0 {
            if ((rs1 >> i) & 1) != 0 {
                r |= 1 << j;
            }
            j += 1;
        }
    }
    return r;
}

pub fn bext64(rs1: u64, rs2: u64) -> u64 {
    let mut r: u64 = 0;
    let mut j = 0;
    for i in 0..64 {
        if ((rs2 >> i) & 1) != 0 {
            if ((rs1 >> i) & 1) != 0 {
                r |= 1 << j;
            }
            j += 1;
        }
    }
    r
}

pub fn bdep32(rs1: u32, rs2: u32) -> u32 {
    let mut r: u32 = 0;
    let mut j = 0;
    for i in 0..32 {
        if ((rs2 >> i) & 1) != 0 {
            if ((rs1 >> j) & 1) != 0 {
                r |= 1 << i;
            }
            j += 1;
        }
    }
    return r;
}

pub fn bdep64(rs1: u64, rs2: u64) -> u64 {
    let mut r: u64 = 0;
    let mut j = 0;
    for i in 0..64 {
        if ((rs2 >> i) & 1) != 0 {
            if ((rs1 >> j) & 1) != 0 {
                r |= 1 << i;
            }
            j += 1;
        }
    }
    return r;
}

pub fn gorc32(rs1: u32, rs2: u32) -> u32 {
    let mut x = rs1;
    let shamt = rs2 & 31;
    if (shamt & 1) != 0 {
        x |= ((x & 0x55555555) << 1) | ((x & 0xAAAAAAAA) >> 1);
    }
    if (shamt & 2) != 0 {
        x |= ((x & 0x33333333) << 2) | ((x & 0xCCCCCCCC) >> 2);
    }
    if (shamt & 4) != 0 {
        x |= ((x & 0x0F0F0F0F) << 4) | ((x & 0xF0F0F0F0) >> 4);
    }
    if (shamt & 8) != 0 {
        x |= ((x & 0x00FF00FF) << 8) | ((x & 0xFF00FF00) >> 8);
    }
    if (shamt & 16) != 0 {
        x |= ((x & 0x0000FFFF) << 16) | ((x & 0xFFFF0000) >> 16);
    }
    return x;
}

pub fn gorc64(rs1: u64, rs2: u64) -> u64 {
    let mut x = rs1;
    let shamt = rs2 & 63;
    if (shamt & 1) != 0 {
        x |= ((x & 0x5555555555555555) << 1) | ((x & 0xAAAAAAAAAAAAAAAA) >> 1);
    }
    if (shamt & 2) != 0 {
        x |= ((x & 0x3333333333333333) << 2) | ((x & 0xCCCCCCCCCCCCCCCC) >> 2);
    }
    if (shamt & 4) != 0 {
        x |= ((x & 0x0F0F0F0F0F0F0F0F) << 4) | ((x & 0xF0F0F0F0F0F0F0F0) >> 4);
    }
    if (shamt & 8) != 0 {
        x |= ((x & 0x00FF00FF00FF00FF) << 8) | ((x & 0xFF00FF00FF00FF00) >> 8);
    }
    if (shamt & 16) != 0 {
        x |= ((x & 0x0000FFFF0000FFFF) << 16) | ((x & 0xFFFF0000FFFF0000) >> 16);
    }
    if (shamt & 32) != 0 {
        x |= ((x & 0x00000000FFFFFFFF) << 32) | ((x & 0xFFFFFFFF00000000) >> 32);
    }
    return x;
}

pub fn bmatflip(rs1: u64) -> u64 {
    let mut x = rs1;
    x = shfl64(x, 31);
    x = shfl64(x, 31);
    x = shfl64(x, 31);
    return x;
}

pub fn bmatxor(rs1: u64, rs2: u64) -> u64 {
    let rs2t = bmatflip(rs2);
    let mut u: [u8; 8] = [0u8; 8];
    let mut v: [u8; 8] = [0u8; 8];

    for i in 0..8 {
        u[i] = (rs1 >> (i * 8)) as u8;
        v[i] = (rs2t >> (i * 8)) as u8;
    }
    let mut x = 0;
    for i in 0..64 {
        if (u[i / 8] & v[i % 8]).count_ones() & 1 != 0 {
            x |= 1 << i;
        }
    }
    return x;
}

pub fn bmator(rs1: u64, rs2: u64) -> u64 {
    let rs2t = bmatflip(rs2);
    let mut u: [u8; 8] = [0u8; 8];
    let mut v: [u8; 8] = [0u8; 8];

    for i in 0..8 {
        u[i] = (rs1 >> (i * 8)) as u8;
        v[i] = (rs2t >> (i * 8)) as u8;
    }
    let mut x = 0;
    for i in 0..64 {
        if (u[i / 8] & v[i % 8]) != 0 {
            x |= 1 << i;
        }
    }
    return x;
}
