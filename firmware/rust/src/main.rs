#![no_std]
#![no_main]
#![feature(abi_avr_interrupt)]

use panic_halt as _; // Import panic handler

#[unsafe(no_mangle)]
pub extern "C" fn main() -> ! {
    loop {}
}
