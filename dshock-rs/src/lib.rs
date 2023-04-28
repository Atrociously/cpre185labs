mod flags;
mod mode;

use std::{ops::{Deref, DerefMut}, marker::PhantomData, time::{Instant, Duration}, sync::{atomic::{AtomicBool, Ordering}, Arc, Mutex, RwLock}, thread::JoinHandle};

use flags::flags;
use hidapi::{HidError, HidApi, HidDevice};
use mode::Mode;
pub use mode::{Bt as BtMode, Usb as UsbMode, SenseUsb as SenseUsbMode};

pub const SONY_VID: u16 = 0x054C;
pub const DS4_PID: u16 = 0x05C4;
pub const DS5_PID: u16 = 0x0CE6;

flags!(Buttons {
    PS = 0x40,
    OPTION = 0x20,
    SHARE = 0x10,
    TRIANGLE = 0x08,
    CIRCLE = 0x04,
    CROSS = 0x02,
    SQUARE = 0x01,
    NONE = 0,
});

flags!(DPad {
    UP = 0x08,
    RIGHT = 0x04,
    DOWN = 0x02,
    LEFT = 0x01,
    NONE = 0,
});

flags!(Triggers {
    R2 = 0x08,
    L2 = 0x04,
    R1 = 0x02,
    L1 = 0x01,
    NONE = 0,
});

flags!(Sticks {
    RSTICK = 0x02,
    LSTICK = 0x01,
    NONE = 0,
});

#[derive(Clone, Copy, Debug, Default, PartialEq)]
pub struct Vec3 {
    pub x: f32,
    pub y: f32,
    pub z: f32,
}

/// Position of sticks
#[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
pub struct Pos {
    pub x: u8,
    pub y: u8,
}

pub struct Controller<M> {
    state: Arc<Mutex<ControllerState>>,
    handle: JoinHandle<()>,
    alive: Arc<AtomicBool>,
    _mode: PhantomData<M>,
}

#[doc(hidden)]
#[derive(Clone, Debug, Default)]
pub struct ControllerState {
    pub stick_left: Pos,
    pub stick_right: Pos,
    pub direction: DPad,
    pub buttons: Buttons,
    pub triggers: Triggers,
    pub sticks: Sticks,
    pub trigger_z_left: u8,
    pub trigger_z_right: u8,
    pub battery: u8,
}

impl<M: Mode> Controller<M> {
    pub fn new(_: M, vid: u16, pid: u16) -> Result<Self, HidError> {
        let device = HidApi::new()?.open(vid, pid)?;
        device.set_blocking_mode(false)?;
        let state = Arc::<Mutex<ControllerState>>::default();

        let st = Arc::clone(&state);
        let alive = Arc::new(AtomicBool::new(true));
        let alive_th = Arc::clone(&alive);
        let handle = std::thread::spawn(move || {
            while alive_th.load(Ordering::Relaxed) {
                let mut buf = [0u8; mode::PACKET_SIZE];
                let amt = device.read(&mut buf).unwrap_or(0);
                if amt < mode::PACKET_SIZE {
                    continue;
                }
                let mut stlock = st.lock().unwrap();
                M::parse(&mut stlock, buf);
            }
        });

        Ok(Self {
            state,
            handle,
            alive,
            _mode: PhantomData,
        })
    }

    pub fn get_state(&self) -> ControllerState {
        let state = self.state.lock().unwrap();
        state.deref().clone()
    }

    pub fn update(&mut self) -> Result<(), HidError> {
        // read the whole 64 byte hid device report packet
        let packet = {
            //let mut packet = [0u8; mode::PACKET_SIZE];
            //self.device.read(&mut packet)?;
            //packet
        };
        //M::parse(&mut self.state, packet);
        Ok(())
    }

    pub fn wait(&mut self, duration: Duration) -> Result<(), HidError> {
        let start = Instant::now();
        let mut packet = [0u8; mode::PACKET_SIZE];
        while start.elapsed() < duration {
            //let amt = self.device.read(&mut packet)?;
            //if amt < mode::PACKET_SIZE {
            //    return Ok(());
            //}
            //M::parse(&mut self.state, packet);
        }
        Ok(())
    }
}

impl From<u8> for Buttons {
    fn from(value: u8) -> Self {
        Self(value & 0x7F)
    }
}

impl From<u8> for DPad {
    fn from(value: u8) -> Self {
        match value & 0x0F {
            0 => DPad::UP,
            1 => DPad::UP | DPad::RIGHT,
            2 => DPad::RIGHT,
            3 => DPad::DOWN | DPad::RIGHT,
            4 => DPad::DOWN,
            5 => DPad::DOWN | DPad::LEFT,
            6 => DPad::LEFT,
            7 => DPad::UP | DPad::LEFT,
            8 => DPad::default(),
            _ => unreachable!("invalid controller response")
        }
    }
}

impl From<u8> for Triggers {
    fn from(value: u8) -> Self {
        Self(value & 0xF)
    }
}

impl From<u8> for Sticks {
    fn from(value: u8) -> Self {
        Self(value & 0x03)
    }
}

impl<M> Drop for Controller<M> {
    fn drop(&mut self) {
        self.alive.store(false, Ordering::Relaxed);

        // I actually don't know if this is necessary
        let empty = std::thread::spawn(|| {});
        let handle = std::mem::replace(&mut self.handle, empty);
        #[allow(unused_must_use)]
        {
            handle.join();
        }
    }
}

impl<M> std::fmt::Debug for Controller<M> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        self.state.fmt(f)
    }
}
