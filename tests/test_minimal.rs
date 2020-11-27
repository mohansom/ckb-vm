extern crate ckb_vm;

use bytes::Bytes;
use ckb_vm::{run, SparseMemory};
use std::fs;

#[test]
pub fn test_minimal_with_no_args() {
    let program_path = "tests/programs/minimal";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let result = run::<u32, SparseMemory<u32>>(&program, &vec![program_path.into()]);
    assert!(result.is_ok());
    assert_eq!(result.unwrap(), 1);
}

#[test]
pub fn test_minimal_with_a() {
    let program_path = "tests/programs/minimal";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let result = run::<u32, SparseMemory<u32>>(&program, &vec![program_path.into(), "a".into()]);
    assert!(result.is_ok());
    assert_eq!(result.unwrap(), 2);
}

#[test]
pub fn test_minimal_with_b() {
    let program_path = "tests/programs/minimal";
    let program: Bytes = fs::read(program_path).unwrap().into();
    let result = run::<u32, SparseMemory<u32>>(&program, &vec![program_path.into(), "".into()]);
    assert!(result.is_ok());
    assert_eq!(result.unwrap(), 0);
}
