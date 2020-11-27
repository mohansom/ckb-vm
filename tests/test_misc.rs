extern crate ckb_vm;

use bytes::Bytes;
use ckb_vm::{
    registers::{A0, A1, A2, A3, A4, A5, A7},
    run, Debugger, DefaultCoreMachine, DefaultMachine, DefaultMachineBuilder, Error, FlatMemory,
    Register, SparseMemory, SupportMachine, Syscalls,
};
use std::fs;
use std::sync::atomic::{AtomicU8, Ordering};
use std::sync::Arc;

#[test]
pub fn test_andi() {
    let program_path = "tests/programs/andi";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let result = run::<u32, SparseMemory<u32>>(&program, &vec![program_path.into()]);
    assert!(result.is_ok());
    assert_eq!(result.unwrap(), 0);
}

#[test]
pub fn test_nop() {
    let program_path = "tests/programs/nop";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let result = run::<u32, SparseMemory<u32>>(&program, &vec![program_path.into()]);
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
pub fn test_custom_syscall() {
    let program_path = "tests/programs/syscall64";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let mut machine =
        DefaultMachineBuilder::<DefaultCoreMachine<u64, SparseMemory<u64>>>::default()
            .syscall(Box::new(CustomSyscall {}))
            .build();
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
pub fn test_ebreak() {
    let program_path = "tests/programs/ebreak64";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let value = Arc::new(AtomicU8::new(0));
    let mut machine =
        DefaultMachineBuilder::<DefaultCoreMachine<u64, SparseMemory<u64>>>::default()
            .debugger(Box::new(CustomDebugger {
                value: Arc::clone(&value),
            }))
            .build();
    machine
        .load_program(&program, &vec![program_path.into()])
        .unwrap();
    assert_eq!(value.load(Ordering::Relaxed), 1);
    let result = machine.run();
    assert!(result.is_ok());
    assert_eq!(value.load(Ordering::Relaxed), 2);
}

#[test]
pub fn test_trace() {
    let program_path = "tests/programs/trace64";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let result = run::<u64, SparseMemory<u64>>(&program, &vec![program_path.into()]);
    assert!(result.is_err());
    assert_eq!(result.err(), Some(Error::InvalidPermission));
}

#[test]
pub fn test_jump0() {
    let program_path = "tests/programs/jump0_64";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let result = run::<u64, SparseMemory<u64>>(&program, &vec![program_path.into()]);
    assert!(result.is_err());
    assert_eq!(result.err(), Some(Error::InvalidPermission));
}

#[test]
pub fn test_misaligned_jump64() {
    let program_path = "tests/programs/misaligned_jump64";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let result = run::<u64, SparseMemory<u64>>(&program, &vec![program_path.into()]);
    assert!(result.is_ok());
}

#[test]
pub fn test_mulw64() {
    let program_path = "tests/programs/mulw64";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let result = run::<u64, SparseMemory<u64>>(&program, &vec![program_path.into()]);
    assert!(result.is_ok());
}

#[test]
pub fn test_invalid_file_offset64() {
    let program_path = "tests/programs/invalid_file_offset64";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let result = run::<u64, SparseMemory<u64>>(&program, &vec![program_path.into()]);
    assert_eq!(result.err(), Some(Error::OutOfBound));
}

#[test]
pub fn test_op_rvc_srli_crash_32() {
    let program_path = "tests/programs/op_rvc_srli_crash_32";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let result = run::<u32, SparseMemory<u32>>(&program, &vec![program_path.into()]);
    assert_eq!(result.err(), Some(Error::InvalidPermission));
}

#[test]
pub fn test_op_rvc_srai_crash_32() {
    let program_path = "tests/programs/op_rvc_srai_crash_32";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let result = run::<u32, SparseMemory<u32>>(&program, &vec![program_path.into()]);
    assert!(result.is_ok());
}

#[test]
pub fn test_op_rvc_slli_crash_32() {
    let program_path = "tests/programs/op_rvc_slli_crash_32";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let result = run::<u32, SparseMemory<u32>>(&program, &vec![program_path.into()]);
    assert!(result.is_ok());
}

#[test]
pub fn test_load_elf_crash_64() {
    let program_path = "tests/programs/load_elf_crash_64";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let result = run::<u64, SparseMemory<u64>>(&program, &vec![program_path.into()]);
    assert_eq!(result.err(), Some(Error::InvalidPermission));
}

#[test]
pub fn test_wxorx_crash_64() {
    let program_path = "tests/programs/wxorx_crash_64";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let result = run::<u64, SparseMemory<u64>>(&program, &vec![program_path.into()]);
    assert_eq!(result.err(), Some(Error::OutOfBound));
}

#[test]
pub fn test_flat_crash_64() {
    let program_path = "tests/programs/flat_crash_64";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let mut machine = DefaultMachine::<DefaultCoreMachine<u64, FlatMemory<u64>>>::default();
    let result = machine.load_program(&program, &vec![program_path.into()]);
    assert_eq!(result.err(), Some(Error::OutOfBound));
}
