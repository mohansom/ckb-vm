extern crate ckb_vm;

use bytes::Bytes;
use ckb_vm::{DefaultCoreMachine, DefaultMachineBuilder, SparseMemory, TraceMachine, WXorXMemory};
use std::fs::File;
use std::io::Read;

#[test]
pub fn test_minimal_with_no_args() {
    let mut file = File::open("tests/programs/minimal").unwrap();
    let mut buffer = Vec::new();
    file.read_to_end(&mut buffer).unwrap();
    let buffer: Bytes = buffer.into();

    let core_machine = DefaultCoreMachine::<u32, WXorXMemory<u32, SparseMemory<u32>>>::latest();
    let mut machine = DefaultMachineBuilder::new(core_machine).build();
    machine.enable_args_initialize(true);
    let mut trace_machine = TraceMachine::new(machine);
    trace_machine
        .load_program(&buffer, &vec!["minimal".into()])
        .unwrap();
    let result = trace_machine.run();

    assert!(result.is_ok());
    assert_eq!(result.unwrap(), 1);
}

#[test]
pub fn test_minimal_with_a() {
    let mut file = File::open("tests/programs/minimal").unwrap();
    let mut buffer = Vec::new();
    file.read_to_end(&mut buffer).unwrap();
    let buffer: Bytes = buffer.into();

    let core_machine = DefaultCoreMachine::<u32, WXorXMemory<u32, SparseMemory<u32>>>::latest();
    let mut machine = DefaultMachineBuilder::new(core_machine).build();
    machine.enable_args_initialize(true);
    let mut trace_machine = TraceMachine::new(machine);
    trace_machine
        .load_program(&buffer, &vec!["minimal".into(), "a".into()])
        .unwrap();
    let result = trace_machine.run();

    assert!(result.is_ok());
    assert_eq!(result.unwrap(), 2);
}

#[test]
pub fn test_minimal_with_b() {
    let mut file = File::open("tests/programs/minimal").unwrap();
    let mut buffer = Vec::new();
    file.read_to_end(&mut buffer).unwrap();
    let buffer: Bytes = buffer.into();

    let core_machine = DefaultCoreMachine::<u32, WXorXMemory<u32, SparseMemory<u32>>>::latest();
    let mut machine = DefaultMachineBuilder::new(core_machine).build();
    machine.enable_args_initialize(true);
    let mut trace_machine = TraceMachine::new(machine);
    trace_machine
        .load_program(&buffer, &vec!["minimal".into(), "".into()])
        .unwrap();
    let result = trace_machine.run();

    assert!(result.is_ok());
    assert_eq!(result.unwrap(), 0);
}
