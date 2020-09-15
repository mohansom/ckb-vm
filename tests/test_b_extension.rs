#[cfg(has_asm)]
use ckb_vm::machine::{aot::AotCompilingMachine, asm::AsmMachine, VERSION0};
use ckb_vm::{run, SparseMemory};

use bytes::Bytes;
use std::fs::File;
use std::io::Read;

#[cfg(has_asm)]
#[test]
pub fn test_b_extension_asm() {
    let mut file = File::open("tests/programs/b_extension").unwrap();
    let mut buffer = Vec::new();
    file.read_to_end(&mut buffer).unwrap();
    let buffer = Bytes::from(buffer);

    let mut machine = AsmMachine::default();
    machine
        .load_program(&buffer, &["b_extension".into()])
        .unwrap();
    let result = machine.run();
    assert!(result.is_ok());
    assert_eq!(result.unwrap(), 0);
}

#[cfg(has_asm)]
#[test]
pub fn test_b_extension_aot() {
    let mut file = File::open("/src/riscv-bitmanip/tests/tests").unwrap();
    let mut buffer = Vec::new();
    file.read_to_end(&mut buffer).unwrap();
    let buffer = Bytes::from(buffer);

    let mut aot_machine = AotCompilingMachine::load(&buffer, None, VERSION0).unwrap();
    let code = aot_machine.compile().unwrap();
    let mut machine = AsmMachine::default_with_aot_code(&code);
    machine
        .load_program(&buffer, &vec!["b_extension".into()])
        .unwrap();
    let result = machine.run();
    assert!(result.is_ok());
    assert_eq!(result.unwrap(), 0);
}

#[test]
pub fn test_b_extension_rust() {
    let mut file = File::open("tests/programs/b_extension").unwrap();
    let mut buffer = Vec::new();
    file.read_to_end(&mut buffer).unwrap();
    let buffer = Bytes::from(buffer);

    let result = run::<u64, SparseMemory<u64>>(&buffer, &vec!["b_extension".into()]);
    assert!(result.is_ok());
    assert_eq!(result.unwrap(), 0);
}
