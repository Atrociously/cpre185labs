use std::path::Path;

use ncurses::*;

#[derive(Clone, Copy, Debug, Default)]
pub struct Point {
    pub x: i32,
    pub y: i32,
}

#[derive(Clone, Copy, Debug, Default)]
pub struct Rect {
    pub top_left: Point,
    pub bottom_right: Point,
}

fn load_file(path: impl AsRef<Path>) -> String {
    std::fs::read_to_string(path.as_ref()).unwrap()
}

fn create_wordlist(input: &str) -> Vec<&str> {
    input.split('\n')
        .collect()
}

fn draw_boxed(word: &str, correct: usize, has_incorrect: bool, center: Point) {
    let width = word.len() as i32;
    let left = center.x - (width / 2);
    let right = left + width + 1;
    let rect = Rect {
        top_left: Point { x: left, y: center.y - 1 },
        bottom_right: Point { x: right, y: center.y + 1 },
    };
    rect.draw();
    for (idx, ch) in word.char_indices() {
        if idx < correct {
            attron(COLOR_PAIR(1));
        }
        if idx == correct && has_incorrect {
            attron(COLOR_PAIR(2));
        }
        mvaddch(rect.top_left.y+1, rect.top_left.x + 1 + idx as i32, ch.into());
        attroff(COLOR_PAIR(1));
        attroff(COLOR_PAIR(2));
    }
}

fn main() {
    const WORDS: &str = include_str!("../../words.txt");
    let words = create_wordlist(&WORDS);
    initscr();
    start_color();
    curs_set(CURSOR_VISIBILITY::CURSOR_INVISIBLE);
    nodelay(stdscr(), true);
    noecho();
    refresh();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);

    let mut word: &str = words[rand::random::<usize>() % words.len()];

    let mut current_idx = 0;
    let mut last_incorrect = false;
    loop {
        let ch_code = getch();
        let ch = char::from_u32(ch_code as u32);

        if ch.is_some() && ch.unwrap() == word.chars().nth(current_idx).unwrap() {
            current_idx += 1;
            last_incorrect = false;
        } else if ch.is_some() {
            last_incorrect = true;
        }
        if current_idx >= word.len() {
            clear();
            current_idx = 0;
            word = words[rand::random::<usize>() % words.len()];
        }

        draw_boxed(word, current_idx, last_incorrect, Point { x: 20, y: 5});
        refresh();
    }
}


impl Rect {
    pub fn draw(&self) {
        // draw horizontal lines
        mvhline(self.top_left.y, self.top_left.x, 0, self.bottom_right.x - self.top_left.x);
        mvhline(self.bottom_right.y, self.top_left.x, 0, self.bottom_right.x - self.top_left.x);
        // draw vertical lines
        mvvline(self.top_left.y, self.top_left.x, 0, self.bottom_right.y - self.top_left.y);
        mvvline(self.top_left.y, self.bottom_right.x, 0, self.bottom_right.y - self.top_left.y);
        
        // draw corners
        mvaddch(self.top_left.y, self.top_left.x, ACS_ULCORNER());
        mvaddch(self.bottom_right.y, self.top_left.x, ACS_LLCORNER());
        mvaddch(self.top_left.y, self.bottom_right.x, ACS_URCORNER());
        mvaddch(self.bottom_right.y, self.bottom_right.x, ACS_LRCORNER());
    }
}
