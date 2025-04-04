#![no_std]
#![no_main]
#![feature(abi_avr_interrupt)]

#[unsafe(no_mangle)]
pub extern "C" fn main() -> ! {
    loop {}
}
