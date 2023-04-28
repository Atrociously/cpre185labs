use std::time::{Instant, Duration};

use dshock_rs::{Controller, SenseUsbMode, SONY_VID, DS5_PID, Buttons};

fn main() {
    let mut controller = Controller::new(SenseUsbMode, SONY_VID, DS5_PID).unwrap();

    let mut start = Instant::now();
    controller.update().unwrap();
    let mut state = controller.get_state();
    while state.buttons & Buttons::CROSS != Buttons::CROSS {
        print!("\r{:x?}", state.direction);
        start = Instant::now();
        state = controller.get_state();
    }
}
