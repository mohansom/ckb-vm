use bytes::Bytes;
use std::io::Read;

fn main() {
    let args: Vec<Bytes> = std::env::args().map(|a| a.into()).collect();

    let mut file = std::fs::File::open("/src/riscv-bitmanip/tests/tests").unwrap();
    let mut buffer = Vec::new();
    file.read_to_end(&mut buffer).unwrap();
    let buffer = Bytes::from(buffer);

    // let r = ckb_vm::run::<u64, ckb_vm::SparseMemory<u64>>(&buffer, &args[..]).unwrap();
    // println!("{:?}", r);

    let mut machine = ckb_vm::machine::asm::AsmMachine::default();
    machine
        .load_program(&buffer, &args[..])
        .unwrap();
    let r = machine.run();
    println!("{:?}", r);
}
