extern crate ckb_vm;

use bytes::Bytes;
use ckb_vm::{
    run, DefaultCoreMachine, DefaultMachine, DefaultMachineBuilder, Error, FlatMemory, Instruction,
    SparseMemory, SupportMachine,
};
use std::fs;

#[test]
pub fn test_simple_instructions() {
    let program_path = "tests/programs/simple";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let result = run::<u32, SparseMemory<u32>>(&program, &vec![program_path.into()]);
    assert!(result.is_ok());
    assert_eq!(result.unwrap(), 0);
}

#[test]
pub fn test_simple_instructions_64() {
    let program_path = "tests/programs/simple64";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let result = run::<u64, SparseMemory<u64>>(&program, &vec![program_path.into()]);
    assert!(result.is_ok());
    assert_eq!(result.unwrap(), 0);
}

#[test]
pub fn test_simple_instructions_flatmemory() {
    let program_path = "tests/programs/simple";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let result = run::<u32, FlatMemory<u32>>(&program, &vec![program_path.into()]);
    assert!(result.is_ok());
    assert_eq!(result.unwrap(), 0);
}

fn dummy_cycle_func(_i: Instruction) -> u64 {
    1
}

#[test]
pub fn test_simple_cycles() {
    let program_path = "tests/programs/simple64";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let core_machine = DefaultCoreMachine::<u64, SparseMemory<u64>>::new_with_max_cycles(517);
    let mut machine =
        DefaultMachineBuilder::<DefaultCoreMachine<u64, SparseMemory<u64>>>::new(core_machine)
            .instruction_cycle_func(Box::new(dummy_cycle_func))
            .build();
    machine
        .load_program(&program, &vec![program_path.into()])
        .unwrap();
    let result = machine.run();
    assert!(result.is_ok());
    assert_eq!(result.unwrap(), 0);
    assert_eq!(SupportMachine::cycles(&machine), 517);
}

#[test]
pub fn test_simple_max_cycles_reached() {
    let program_path = "tests/programs/simple64";
    let program: Bytes = fs::read(program_path).unwrap().into();
    // Running simple64 should consume 517 cycles using dummy cycle func
    let core_machine = DefaultCoreMachine::<u64, SparseMemory<u64>>::new_with_max_cycles(500);
    let mut machine =
        DefaultMachineBuilder::<DefaultCoreMachine<u64, SparseMemory<u64>>>::new(core_machine)
            .instruction_cycle_func(Box::new(dummy_cycle_func))
            .build();
    machine
        .load_program(&program, &vec![program_path.into()])
        .unwrap();
    let result = machine.run();
    assert!(result.is_err());
    assert_eq!(result.unwrap_err(), Error::InvalidCycles);
}

#[test]
pub fn test_simple_invalid_bits() {
    let program_path = "tests/programs/simple";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let result = run::<u64, SparseMemory<u64>>(&program, &vec![program_path.into()]);
    assert!(result.is_err());
    assert_eq!(result.unwrap_err(), Error::InvalidElfBits);
}

#[test]
pub fn test_simple_loaded_bytes() {
    let program_path = "tests/programs/simple64";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let mut machine = DefaultMachine::<DefaultCoreMachine<u64, SparseMemory<u64>>>::default();
    let bytes = machine
        .load_program(&program, &vec!["simple".into()])
        .unwrap();
    assert_eq!(bytes, 4055);
}
