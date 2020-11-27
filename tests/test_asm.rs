#![cfg(has_asm)]

use bytes::Bytes;
use ckb_vm::{
    machine::asm::{AsmCoreMachine, AsmMachine},
    registers::{A0, A1, A2, A3, A4, A5, A7},
    Debugger, DefaultMachineBuilder, Error, Instruction, Register, SupportMachine, Syscalls,
};
use std::fs;
use std::sync::atomic::{AtomicU8, Ordering};
use std::sync::Arc;

#[test]
pub fn test_asm_simple64() {
    let program_path = "tests/programs/simple64";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let mut machine = AsmMachine::default();
    machine
        .load_program(&program, &vec![program_path.into()])
        .unwrap();
    let result = machine.run();
    assert!(result.is_ok());
    assert_eq!(result.unwrap(), 0);
}

pub struct CustomSyscall {}

impl<Mac: SupportMachine> Syscalls<Mac> for CustomSyscall {
    fn initialize(&mut self, _machine: &mut Mac) -> Result<(), Error> {
        Ok(())
    }

    fn ecall(&mut self, machine: &mut Mac) -> Result<bool, Error> {
        let code = &machine.registers()[A7];
        if code.to_i32() != 1111 {
            return Ok(false);
        }
        let result = machine.registers()[A0]
            .overflowing_add(&machine.registers()[A1])
            .overflowing_add(&machine.registers()[A2])
            .overflowing_add(&machine.registers()[A3])
            .overflowing_add(&machine.registers()[A4])
            .overflowing_add(&machine.registers()[A5]);
        machine.set_register(A0, result);
        Ok(true)
    }
}

#[test]
pub fn test_asm_with_custom_syscall() {
    let program_path = "tests/programs/syscall64";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let core = DefaultMachineBuilder::<Box<AsmCoreMachine>>::default()
        .syscall(Box::new(CustomSyscall {}))
        .build();
    let mut machine = AsmMachine::new(core, None);
    machine
        .load_program(&program, &vec![program_path.into()])
        .unwrap();
    let result = machine.run();
    assert!(result.is_ok());
    assert_eq!(result.unwrap(), 39);
}

pub struct CustomDebugger {
    pub value: Arc<AtomicU8>,
}

impl<Mac: SupportMachine> Debugger<Mac> for CustomDebugger {
    fn initialize(&mut self, _machine: &mut Mac) -> Result<(), Error> {
        self.value.store(1, Ordering::Relaxed);
        Ok(())
    }

    fn ebreak(&mut self, _machine: &mut Mac) -> Result<(), Error> {
        self.value.store(2, Ordering::Relaxed);
        Ok(())
    }
}

#[test]
pub fn test_asm_ebreak() {
    let program_path = "tests/programs/ebreak64";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let value = Arc::new(AtomicU8::new(0));
    let core = DefaultMachineBuilder::<Box<AsmCoreMachine>>::default()
        .debugger(Box::new(CustomDebugger {
            value: Arc::clone(&value),
        }))
        .build();
    let mut machine = AsmMachine::new(core, None);
    machine
        .load_program(&program, &vec![program_path.into()])
        .unwrap();
    assert_eq!(value.load(Ordering::Relaxed), 1);
    let result = machine.run();
    assert!(result.is_ok());
    assert_eq!(value.load(Ordering::Relaxed), 2);
}

fn dummy_cycle_func(_i: Instruction) -> u64 {
    1
}

#[test]
pub fn test_asm_simple_cycles() {
    let program_path = "tests/programs/simple64";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let asm_core = AsmCoreMachine::new_with_max_cycles(517);
    let core = DefaultMachineBuilder::<Box<AsmCoreMachine>>::new(asm_core)
        .instruction_cycle_func(Box::new(dummy_cycle_func))
        .build();
    let mut machine = AsmMachine::new(core, None);
    machine
        .load_program(&program, &vec![program_path.into()])
        .unwrap();
    let result = machine.run();
    assert!(result.is_ok());
    assert_eq!(result.unwrap(), 0);

    assert_eq!(SupportMachine::cycles(&machine.machine), 517);
}

#[test]
pub fn test_asm_simple_max_cycles_reached() {
    let program_path = "tests/programs/simple64";
    let program: Bytes = fs::read(program_path).unwrap().into();
    // Running simple64 should consume 517 cycles using dummy cycle func
    let asm_core = AsmCoreMachine::new_with_max_cycles(500);
    let core = DefaultMachineBuilder::<Box<AsmCoreMachine>>::new(asm_core)
        .instruction_cycle_func(Box::new(dummy_cycle_func))
        .build();
    let mut machine = AsmMachine::new(core, None);
    machine
        .load_program(&program, &vec![program_path.into()])
        .unwrap();
    let result = machine.run();
    assert!(result.is_err());
    assert_eq!(result.unwrap_err(), Error::InvalidCycles);
}

#[test]
pub fn test_asm_trace() {
    let program_path = "tests/programs/trace64";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let mut machine = AsmMachine::default();
    machine
        .load_program(&program, &vec![program_path.into()])
        .unwrap();
    let result = machine.run();
    assert!(result.is_err());
    assert_eq!(result.err(), Some(Error::InvalidPermission));
}

#[test]
pub fn test_asm_jump0() {
    let program_path = "tests/programs/jump0_64";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let mut machine = AsmMachine::default();
    machine
        .load_program(&program, &vec![program_path.into()])
        .unwrap();
    let result = machine.run();
    assert!(result.is_err());
    assert_eq!(result.err(), Some(Error::InvalidPermission));
}

#[test]
pub fn test_asm_write_large_address() {
    let program_path = "tests/programs/write_large_address64";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let mut machine = AsmMachine::default();
    machine
        .load_program(&program, &vec![program_path.into()])
        .unwrap();
    let result = machine.run();
    assert!(result.is_err());
    assert_eq!(result.err(), Some(Error::OutOfBound));
}

#[test]
pub fn test_misaligned_jump64() {
    let program_path = "tests/programs/misaligned_jump64";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let mut machine = AsmMachine::default();
    machine
        .load_program(&program, &vec![program_path.into()])
        .unwrap();
    let result = machine.run();
    assert!(result.is_ok());
}

#[test]
pub fn test_mulw64() {
    let program_path = "tests/programs/mulw64";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let mut machine = AsmMachine::default();
    machine
        .load_program(&program, &vec![program_path.into()])
        .unwrap();
    let result = machine.run();
    assert!(result.is_ok());
    assert_eq!(result.unwrap(), 0);
}

#[test]
pub fn test_invalid_read64() {
    let program_path = "tests/programs/invalid_read64";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let mut machine = AsmMachine::default();
    machine
        .load_program(&program, &vec![program_path.into()])
        .unwrap();
    let result = machine.run();
    assert!(result.is_err());
    assert_eq!(result.err(), Some(Error::OutOfBound));
}

#[test]
pub fn test_asm_load_elf_crash_64() {
    let program_path = "tests/programs/load_elf_crash_64";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let mut machine = AsmMachine::default();
    machine
        .load_program(&program, &vec![program_path.into()])
        .unwrap();
    let result = machine.run();
    assert_eq!(result.err(), Some(Error::InvalidPermission));
}

#[test]
pub fn test_asm_wxorx_crash_64() {
    let program_path = "tests/programs/wxorx_crash_64";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let mut machine = AsmMachine::default();
    machine
        .load_program(&program, &vec![program_path.into()])
        .unwrap();
    let result = machine.run();
    assert_eq!(result.err(), Some(Error::OutOfBound));
}

#[test]
pub fn test_asm_alloc_many() {
    let program_path = "tests/programs/alloc_many";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let mut machine = AsmMachine::default();
    machine
        .load_program(&program, &vec![program_path.into()])
        .unwrap();
    let result = machine.run();
    assert_eq!(result.unwrap(), 0);
}
