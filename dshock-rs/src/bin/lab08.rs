use std::time::Duration;
use dshock_rs::{Controller, SenseUsbMode, SONY_VID, DS5_PID};

use ncurses::*;

#[derive(Clone, Copy)]
struct Point<T> {
    pub x: T,
    pub y: T,
}

struct Player {
    pub prev: Point<usize>,
    pub pos: Point<usize>,
}

struct Grid {
    inner: Vec<Vec<char>>,
    height: usize,
    width: usize,
}

struct GameState {
    pub player: Player,
    pub grid: Grid,
}

#[derive(Clone, Copy, PartialEq, Eq)]
enum EndState {
    Continue,
    GameOver,
    Win,
}

fn main() {
    let controller = Controller::new(SenseUsbMode, SONY_VID, DS5_PID).expect("creating controller");
    let mut ctrl = controller.get_state();
    let mut game = GameState::new();
    let mut end_state = EndState::Continue;
    while end_state == EndState::Continue {
        ctrl = controller.get_state();

        //print!("\r{} {}", controller.stick_left.x, controller.stick_left.y);
        let c = char::try_from(getch() as u32).ok();

        if c == Some('q') {
            return;
        }

        let mut movement = Point { x: 0, y: 0 };
        if ctrl.direction.is_left() {
            movement.x = -1;
        } else  if ctrl.direction.is_right() {
            movement.x = 1;
        }

        end_state = game.update::<()>(movement);
        game.draw();
        std::thread::sleep(Duration::from_millis(200));
    }

    game.clear();
    endwin();
    if end_state == EndState::GameOver {
        println!("You LOST!");
    } else {
        println!("You WON!");
    }
}

impl GameState {
    pub fn new() -> Self {
        initscr();
        curs_set(CURSOR_VISIBILITY::CURSOR_INVISIBLE);
        nodelay(stdscr(), true);
        noecho();
        refresh();

        let mut screen_size = Point { x: 0, y: 0 };
        getmaxyx(stdscr(), &mut screen_size.y, &mut screen_size.x);
        let screen_size = Point {
            x: screen_size.x.try_into().unwrap(),
            y: screen_size.y.try_into().unwrap()
        };

        let player = Player::new(Point { x: screen_size.x / 2, y: 0 });
        let grid = Grid::new(screen_size.x, screen_size.y);

        Self {
            player,
            grid,
        }
    }

    pub fn update<T>(&mut self, input: Point<i32>) -> EndState {
        let mut next = self.player.pos;

        if input.x < 0 {
            if next.x - 1 < self.grid.width() && self.grid[next.y][next.x - 1] != Grid::WALL {
                next.x -= 1;
            }
        } else if input.x > 0 {
            if next.x + 1 < self.grid.width() && self.grid[next.y][next.x + 1] != Grid::WALL {
                next.x += 1;
            }
        }

        if next.y + 1 < self.grid.height() && self.grid[next.y + 1][next.x] != Grid::WALL {
            next.y += 1;
        }
        self.player.prev = self.player.pos;
        self.player.pos = next;

        // get the walls directly to the left and right of the player
        let mut left_wall = None;
        let mut right_wall = None;
        for (i, &col) in self.grid[next.y].iter().enumerate() {
            if i < next.x && col == Grid::WALL {
                left_wall = Some(i);
            } else if right_wall.is_none() && col == Grid::WALL {
                right_wall = Some(i);
                break;
            }
        }
        let left = left_wall.unwrap_or(0);
        let right = right_wall.unwrap_or(self.grid.width() - 1);

        let mut all_walls = true;
        if next.y + 1 >= self.grid.height() {
            return EndState::Win;
        }
        for &col in self.grid[next.y + 1].iter().skip(left + 1).take(right - left - 1) {
            if col != Grid::WALL {
                all_walls = false;
                break;
            }
        }

        if all_walls {
            return EndState::GameOver;
        } else {
            return EndState::Continue;
        }
    }

    pub fn draw(&self) {
        // draw the grid an O(rows*cols) operation
        /*for (y, row) in self.grid.iter().enumerate() {
            for (x, col) in row.iter().enumerate() {
                let p = Point { x, y };
                p.try_draw_char(*col).unwrap();
            }
        }*/

        // redraw the players previous position
        // an O(1) operation
        let player_prev = self.grid[self.player.prev.y][self.player.prev.x];
        self.player.prev.try_draw_char(player_prev).unwrap();

        // draw the player
        self.player.pos.try_draw_char(Player::AVATAR).unwrap();
        refresh();
    }

    pub fn clear(&self) {
        for (y, row) in self.grid.iter().enumerate() {
            for (x, _) in row.iter().enumerate() {
                let p = Point { x, y };
                p.try_draw_char(Grid::EMPTY).unwrap();
            }
        }
        Point { x: -1, y: 0 }.try_draw_char(Grid::EMPTY).unwrap();
    }
}

impl Player {
    const AVATAR: char = 'A';

    pub fn new(pos: Point<usize>) -> Self {
        Self {
            prev: pos,
            pos,
        }
    }
}

impl Grid {
    const WALL: char = '*';
    const EMPTY: char = ' ';

    pub fn new(width: usize, height: usize) -> Self {
        let mut inner = vec![vec![Self::EMPTY; width]; height]; // allocate memory
        
        // fill the grid
        for row in inner.iter_mut() {
            for col in row.iter_mut() {
                if Self::distrubuted_rand(0.4) == 0 {
                    *col = Self::WALL;
                }
            }
        }

        for (y, row) in inner.iter().enumerate() {
            for (x, col) in row.iter().enumerate() {
                let p = Point { x, y };
                p.try_draw_char(*col).unwrap();
            }
        }
        Self {
            inner,
            width,
            height
        }
    }

    pub fn set_width(&mut self, new_width: usize) {
        self.width = new_width;
    }

    pub fn set_height(&mut self, new_height: usize) {
        self.height = new_height;
    }

    pub fn width(&self) -> usize {
        self.width
    }

    pub fn height(&self) -> usize {
        self.height
    }

    fn distrubuted_rand(bias: f64) -> u8 {
        const R: u8 = 100;
        const RF: f64 = 100.0;

        let bias = bias.min(1.0).max(0.0);
        let val = rand::random::<u8>() % R + 1;
        let bias_point = (RF - RF * bias) as u8; // casting is fine here
        if val <= bias_point {
            1
        } else {
            0
        }
    }
}

impl<T: Into<i32> + Copy> Point<T> {
    pub fn draw_char(&self, ch: char) {
        mvaddch(self.y.into(), self.x.into(), ch.into());
    }
}

impl<T: TryInto<i32> + Copy> Point<T> {
    pub fn try_draw_char(&self, ch: char) -> Result<(), T::Error> {
        mvaddch(self.y.try_into()?, self.x.try_into()?, ch.into());
        Ok(())
    }
}

impl std::ops::Deref for Grid {
    type Target = [Vec<char>];

    fn deref(&self) -> &Self::Target {
        self.inner.deref()
    }
}
