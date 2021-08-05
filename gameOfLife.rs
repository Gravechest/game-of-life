use winapi::um::consoleapi;
use winapi::um::winbase::{STD_ERROR_HANDLE, STD_INPUT_HANDLE, STD_OUTPUT_HANDLE};
use winapi::um::wincon::COORD;
use winapi::um::processenv::GetStdHandle;
use winapi::um::winnt::HANDLE;
use winapi::um::wincon::SetConsoleCursorPosition;

use rand::prelude::*;

fn main() {
    let mut map = [[0u8;50];50];
    let mut mapbuffer = [[0u8;50];50];
    for x in 0..50{
        for y in 0..50{
            map[x][y] = rand::thread_rng().gen();
            map[x][y] %= 2;
        }
    }
    loop {
        mapbuffer = map.clone();
        for x in 0..50{
            for y in 0..50{
                let mut neighbours= 0;
                if(x > 0 && y > 0 && map[x - 1][y - 1] == 1){
                    neighbours+=1;
                }
                if(x > 0 && map[x - 1][y] == 1){
                    neighbours+=1;
                }
                if(x > 0 && y < 49 && map[x - 1][y + 1] == 1){
                    neighbours+=1;
                }
                if(y > 0 && map[x][y - 1] == 1){
                    neighbours+=1;
                }
                if(y < 49 && map[x][y + 1] == 1){
                    neighbours+=1;
                }
                if(x < 49 && y > 0 && map[x + 1][y - 1] == 1){
                    neighbours+=1;
                }
                if(x < 49 && map[x + 1][y] == 1){
                    neighbours+=1;
                }
                if(x < 49 && y < 49 && map[x + 1][y + 1] == 1){
                    neighbours+=1;
                }
                if(map[x][y] == 0 && neighbours == 3){
                    mapbuffer[x][y] = 1;
                }
                else if (neighbours != 2 && neighbours != 3){
                    mapbuffer[x][y] = 0;
                }
            }
        }
        map = mapbuffer.clone();
        for x in 0..50{
            for y in 0..50{
                if(map[x][y] == 0){
                    print!(".");
                }
                else {
                    print!("#");
                }
            }
            println!("");
        }
        let cursor = COORD { X: 0, Y: 0 };
        let handle = unsafe { GetStdHandle(STD_OUTPUT_HANDLE) };
        unsafe { SetConsoleCursorPosition(handle, cursor) };
    }
}
