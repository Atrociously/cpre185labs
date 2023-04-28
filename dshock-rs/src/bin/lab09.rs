use std::{io, time::Duration};

use dshock_rs::{Controller, SenseUsbMode, DS5_PID, SONY_VID, DPad};
use ncurses::*;

const CURSOR: char = '*';
const COL_WIDTH: i32 = 10;
const UCOL_WIDTH: usize = COL_WIDTH as usize;

// gets the wordlist from the file and 
fn get_wordlist() -> Result<Vec<Vec<String>>, io::Error> {
    let contents = std::fs::read_to_string("./word_list.txt")?;
    let lines: Vec<_> = contents
        .split('\n')
        .map(|s| s.trim().trim_matches('\u{feff}').to_string())
        .collect();

    Ok(lines.chunks(15).map(Vec::from).collect())
}

fn draw_wordlist(wl: &[Vec<String>]) {
    let mut offset = 0;
    for row in wl {
        for (i, col) in row.iter().enumerate() {
            mvprintw(i as i32, offset, col);
        }
        offset += COL_WIDTH;
    }
}

fn main() {
    // change the PID from ds5 to ds4 to get this to work with a dualshock instead
    // of a dualsense controller. I tested this with the ps5 controller because thats
    // what I had available at my home
    let controller = Controller::new(SenseUsbMode, SONY_VID, DS5_PID).unwrap();

    initscr();
    noecho();
    nodelay(stdscr(), true);
    curs_set(CURSOR_VISIBILITY::CURSOR_INVISIBLE);

    let wordlist = get_wordlist().unwrap();
    draw_wordlist(&wordlist);
    refresh();

    let mut append_history = Vec::new();
    let mut previous = (2, 0);
    let mut cursor = previous;
    let mut sentence = String::new();
    let bottom = wordlist.get(0).map(|v| v.len()).unwrap_or(0) + 1;

    // main loop
    loop {
        let ctrl = controller.get_state();
        // update stuff
        let input = char::from_u32(getch() as u32);
        let mut append = ctrl.buttons.is_square();
        let mut append_with_space = ctrl.buttons.is_triangle();
        let mut remove_last = ctrl.buttons.is_cross();

        previous = cursor;

        match ctrl.direction {
            DPad::UP if cursor.1 > 0 => cursor.1 -= 1,
            DPad::DOWN if cursor.1 < bottom - 2 => cursor.1 += 1,
            DPad::LEFT if cursor.0 > 0 => cursor.0 -= 1,
            DPad::RIGHT if cursor.0 < wordlist.len() - 2 => cursor.0 += 1,
            DPad::NONE => (),
            _ => (),
        }
        if ctrl.buttons.is_option() || ctrl.buttons.is_share() {
            break;
        }
        match input {
            Some('w') if cursor.1 > 0 => cursor.1 -= 1,
            Some('s') if cursor.1 < bottom - 2 => cursor.1 += 1,
            Some('a') if cursor.0 > 0 => cursor.0 -= 1,
            Some('d') if cursor.0 < wordlist.len() - 2 => cursor.0 += 1,
            Some('q') => break,
            Some('p') => append = true,
            Some('o') => append_with_space = true,
            Some('x') => remove_last = true,
            _ => ()
        }

        let previous_val = wordlist.get(previous.0).map(|v| v.get(previous.1)).flatten().unwrap();
        let cursor_val = wordlist.get(cursor.0).map(|v| v.get(cursor.1)).flatten().unwrap();

        if append {
            let last_add = cursor_val.clone();
            sentence.push_str(&last_add);
            append_history.push(last_add);
        }
        if append_with_space {
            let last_add = " ".to_owned() + cursor_val;
            sentence.push_str(&last_add);
            append_history.push(last_add);
        }
        if remove_last {
            match append_history.pop() {
                Some(s) => sentence = sentence.split_at(sentence.len() - s.len()).0.to_owned(),
                None => {}
            }
        }

        // draw stuff
        draw_wordlist(&wordlist);
        // erase previous cursor and draw new cursor
        draw_ch(previous.0 * UCOL_WIDTH + previous_val.len() + 1, previous.1, ' ');
        draw_ch(cursor.0 * UCOL_WIDTH + cursor_val.len() + 1, cursor.1, CURSOR);

        // draw sentence
        mv(bottom as i32, 0);
        clrtoeol();
        mvprintw(bottom as i32, 0, &sentence);
        refresh();
        std::thread::sleep(Duration::from_millis(150));
    }

    endwin();
}

pub fn draw_ch(x: usize, y: usize, ch: char) {
    mvaddch(y as i32, x as i32, ch.into());
}
