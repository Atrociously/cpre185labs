#![allow(clippy::upper_case_acronyms)]

use crate::{Buttons, DPad, ControllerState, Triggers, Sticks};

pub const PACKET_SIZE: usize = 64;

mod secret {
    pub trait Secret {}
}

pub trait Mode: secret::Secret {
    fn parse(state: &mut ControllerState, packet: [u8; PACKET_SIZE]);
}

pub struct Usb;
pub struct Bt;
pub struct SenseUsb;

impl secret::Secret for Usb {}
impl Mode for Usb {
    fn parse(state: &mut ControllerState, packet: [u8; PACKET_SIZE]) {
        state.stick_left.x = packet[1];
        state.stick_left.y = packet[2];
        state.stick_right.x = packet[3];
        state.stick_right.y = packet[4];
        
        state.buttons = Buttons(packet[5] >> 4);
        state.direction = DPad::from(packet[9]);
        state.triggers = Triggers::from(packet[10]);
    }
}

impl secret::Secret for Bt {}
impl Mode for Bt {
    // for implementation details see https://www.psdevwiki.com/ps4/DS4-BT#HID_Report_header_.26_footer
    fn parse(state: &mut ControllerState, packet: [u8; PACKET_SIZE]) {
        println!("Gyro X: {:x} {:x} Y: {:x} {:x}", packet[17], packet[18], packet[19], packet[20]);
        state.stick_left.x = packet[5];
        state.stick_left.y = packet[6];
        state.stick_right.x = packet[7];
        state.stick_right.y = packet[8];

        state.buttons = Buttons(packet[9] >> 4);
        state.direction = DPad::from(packet[9]);
        state.triggers = Triggers::from(packet[10]);
        state.sticks = Sticks((packet[10] & 0xC0) >> 6); // select only sticks and shift
        state.buttons |= Buttons(packet[10] & 0x30); // select only option and share bits
        state.buttons |= Buttons((packet[11] & 0x01) << 5); // select only ps button and shift

        state.trigger_z_left = packet[12];
        state.trigger_z_right = packet[13];
        state.battery = packet[16];
    }
}

impl secret::Secret for SenseUsb {}
impl Mode for SenseUsb {
    fn parse(state: &mut ControllerState, packet: [u8; PACKET_SIZE]) {
        state.stick_left.x = packet[1];
        state.stick_left.y = packet[2];
        state.stick_right.x = packet[3];
        state.stick_right.y = packet[4];

        state.trigger_z_left = packet[5];
        state.trigger_z_right = packet[6];

        state.direction = DPad::from(packet[8]);
        state.buttons = Buttons(packet[8] >> 4);
        state.triggers = Triggers::from(packet[9]);

        state.buttons |= Buttons(packet[9] & 0x30); // select only option and create bits
    }
}
