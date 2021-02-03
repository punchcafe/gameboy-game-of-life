
#include <gb/gb.h>
#include <gb/console.h>
#include<stdio.h>
#include <gb/font.h>
#include "C:\Users\punchcafe\Projects\gamboy-game-of-life\field_handler.h"

/*
refactor notes:
hide all cell data behind field handler, rename field?
*/

const unsigned char background_data [] = {
    //white-tile
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    // No Life (index 0)
    0xFF,0xFF,0x7F,0xFF,0xFE,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xBF,0xFD,0xFF,0xFF,
    // Life (index 16)
    0xC7,0xEF,0x0F,0xA7,0xE4,0xC3,0x40,0x80,
    0x02,0x01,0x27,0xC3,0xB1,0xE5,0xE3,0xF7,
    // No Life selected (index 32)
    0x18,0x18,0x76,0x7E,0x7A,0x7E,0xFF,0xFF,
    0xFF,0xFF,0x5E,0x7E,0x7E,0x7E,0x18,0x18,
    // Life selected (index 32)
    0x18,0x18,0x66,0x6E,0x42,0x66,0x81,0xC1,
    0x81,0x83,0x42,0x66,0x66,0x76,0x18,0x18
};

#define DATA_BLOCK_SIZE 128

unsigned char data_block_1 [DATA_BLOCK_SIZE];
unsigned char data_block_2 [DATA_BLOCK_SIZE];

void clear_data_block(char * data_block){
    int i;
    for(i = 0; i <DATA_BLOCK_SIZE; i++)
    {
        data_block[i] = 0x00;
    }
}

void clear_data_block_1()
{
    clear_data_block(data_block_1);
}

void clear_data_block_2()
{
    clear_data_block(data_block_2);
}

unsigned char * present_data = data_block_1;
unsigned char * next_data = data_block_2;


unsigned char cells_data [] = {

    /*
    Cells come as 4x4 blocks, represented by two bytes. For example,
                0010
                0100
                1100
                0011 
    may be represented as 0010_0100 1100_0011, or 0x24 0xC3.

    Since the gameboy has 32x32 tiles,
    */

   // First block row, 0 <= i <= (7 * 2 + 1)
   // Block 0
    0x00,0x00, // cells 0,0 -> 3,3
    0x00,0x00, // cells 4,0 -> 7,3
    0x00,0x00, // cells 8,0 -> 11,3
    0x00,0x00, // cells 12,0 -> 15,3
    0x00,0x00, // cells 16,0 -> 19,3
    0x00,0x00, // cells 20,0 -> 23,3
    0x00,0x00, // cells 24,0 -> 27,3
    0x00,0x00, // cells 28,0 -> 31,3

    // Second block row, 8 * 2 <= i <= (15 * 2 + 1)
    // Block 8
    0x00,0x00, // cells 0,4 -> 3,7
    0x00,0x00, // cells 4,4 -> 7,7
    0x00,0x00, // cells 8,4 -> 11,7
    0x00,0x00, // cells 12,4 -> 15,7
    0x00,0x00, // cells 16,4 -> 19,7
    0x00,0x00, // cells 20,4 -> 23,7
    0x00,0x00, // cells 24,4 -> 27,7
    0x00,0x00, // cells 28,4 -> 31,7

    // Third block row, 16 * 2 <= i <= (23 * 2 + 1)
    // Block 16
    0x00,0x00, // cells 0,8 -> 3,11
    0x00,0x00, // cells 4,8 -> 7,11
    0x00,0x00, // cells 8,8 -> 11,11
    0x00,0x05, // cells 12,8 -> 15,11
    0x00,0x00, // cells 16,8 -> 19,11
    0x00,0x00, // cells 20,8 -> 23,11
    0x00,0x00, // cells 24,8 -> 27,11
    0x00,0x00, // cells 28,8 -> 31,11

    // Fourt block row, 24 * 2 <= i <= (31 * 2 + 1)
    // Block 24
    0x00,0x00, // cells 0,12 -> 3,15
    0x22,0x00, // cells 4,12 -> 7,15
    0x00,0x00, // cells 8,12 -> 11,15
    0x00,0x00, // cells 12,12 -> 15,15
    0x00,0x00, // cells 16,12 -> 19,15
    0x0a,0x00, // cells 20,12 -> 23,15
    0x00,0x00, // cells 24,12 -> 27,15
    0x00,0x00, // cells 28,12 -> 31,15

    // Fifth block row, 32 * 2 <= i <= (39 * 2 + 1)
    // Block 32
    0x00,0x00, // cells 0,16 -> 3,19
    0x00,0x00, // cells 4,16 -> 7,19
    0x00,0x00, // cells 8,16 -> 11,19
    0x00,0x00, // cells 12,16 -> 15,19
    0x00,0x00, // cells 16,16 -> 19,19
    0x20,0x00, // cells 20,16 -> 23,19
    0x00,0x00, // cells 24,16 -> 27,19
    0x00,0x00, // cells 28,16 -> 31,19

    // Sixth block row, 40 * 2 <= i <= (47 * 2 + 1)
    // Block 40
    0x00,0x00, // cells 0,20 -> 3,23
    0x00,0x00, // cells 4,20 -> 7,23
    0x00,0x00, // cells 8,20 -> 11,23
    0x00,0x00, // cells 12,20 -> 15,23
    0x00,0x00, // cells 16,20 -> 19,23
    0x00,0x00, // cells 20,20 -> 23,23
    0x00,0x00, // cells 24,20 -> 27,23
    0x00,0x00, // cells 28,20 -> 31,23
    
    // Seventh block row, 48 * 2 <= i <= (55 * 2 + 1)
    // Block 48
    0x00,0x00, // cells 0,24 -> 3,27
    0x00,0x00, // cells 4,24 -> 7,27
    0x00,0x00, // cells 8,24 -> 11,27
    0x00,0x00, // cells 12,24 -> 15,27
    0x00,0x00, // cells 16,24 -> 19,27
    0x00,0x00, // cells 20,24 -> 23,27
    0x00,0x00, // cells 24,24 -> 27,27
    0x00,0x00, // cells 28,24 -> 31,27

    // Eigth block row, 56 * 2 <= i <= (63 * 2 + 1)
    // Block 56
    0x00,0x00, // cells 0,28 -> 3,31
    0x00,0x00, // cells 4,28 -> 7,31
    0x00,0x00, // cells 8,28 -> 11,31
    0x00,0x00, // cells 12,28 -> 15,31
    0x00,0x00, // cells 16,28 -> 19,31
    0x00,0x00, // cells 20,28 -> 23,31
    0x00,0x00, // cells 24,28 -> 27,31
    0x00,0x00 // cells 28,28 -> 31,31
};

// convert to directive
const unsigned char blank_tile_index [] = { 0x00 };
const unsigned char no_life_tile_index [] = { 0x01 };
const unsigned char life_tile_index [] = { 0x02 };
const unsigned char no_life_selected_tile_index [] = { 0x03 };
const unsigned char life_selected_tile_index [] = { 0x04 };

int cursor_x = 0;
int cursor_y = 0;

int i = 0;
int j = 0;

unsigned char input = 0;
unsigned int x_input = 0;
unsigned int y_input = 0;
// needed because of mid scope initialisation bugs

enum game_state_enum {edit_mode, play_mode} game_state;

/*
    Sets a tile in the 'pitch', allowing rendering pitch dimensions without considering border.
*/
void set_pitch_tile(unsigned int x, unsigned int y, unsigned char * tile_table_index)
{
    unsigned int x_offset = x + get_border_width();
    unsigned int y_offset = y + get_border_width();
    set_win_tiles(x_offset, y_offset, 1, 1, tile_table_index);
}

void clamp_value( int * value,  int min,  int max )
{
    if(*value < min)
    {
        *value = min;
    } else if (*value > max)
    {
         *value  = max;
    }
}

void move_cursor(int x_move, int y_move){
    unsigned int is_destination_cell_alive;
    unsigned int is_origin_cell_alive = get_cell(present_data, cursor_x, cursor_y);
    if(is_origin_cell_alive){
        set_pitch_tile(cursor_x, cursor_y, life_tile_index);
    } else {
        set_pitch_tile(cursor_x, cursor_y, no_life_tile_index);
    }
    cursor_x += x_move;
    cursor_y += y_move;
    clamp_value(&cursor_x, 0, get_max_field_width() - 1);
    clamp_value(&cursor_y, 0, get_max_field_depth() - 1);
    is_destination_cell_alive = get_cell(present_data, cursor_x, cursor_y);
    if(is_destination_cell_alive){
        set_pitch_tile(cursor_x, cursor_y, life_selected_tile_index);
    } else {
        set_pitch_tile(cursor_x, cursor_y, no_life_selected_tile_index);
    }
}



void render_cursor_to_current(){
    if(get_cell(present_data, cursor_x, cursor_y))
    {
        set_pitch_tile(cursor_x, cursor_y, life_selected_tile_index);
    } else 
    {
        set_pitch_tile(cursor_x, cursor_y, no_life_selected_tile_index);
    }
}

void invert_cell(){
    if(get_cell(present_data, cursor_x, cursor_y))
    {
        // Cell is set high
        set_cell_low(present_data, cursor_x, cursor_y);
        // Consider having a reader/writer method, instead of letting draw directly, so that 
        // screen is always consistent with model at low CPU expense
        set_pitch_tile(cursor_x, cursor_y, no_life_selected_tile_index);
    } else {
        // Cell is set low
        set_cell_high(present_data, cursor_x, cursor_y);
        set_pitch_tile(cursor_x, cursor_y, life_selected_tile_index);
    }
}



void render_field(unsigned char * data){
    int i;
    int j;
    for(i; i < get_max_field_width(); i++)
    {
        for(j; j < get_max_field_depth(); j++)
        {
            if(get_cell(data, i,j))
            {   
                set_pitch_tile(i,j,life_tile_index);
            } else {
                set_pitch_tile(i,j,no_life_tile_index);
            }
        };
        j = 0;
    };
    i = 0;
}

void clear_canvas(){
    int i;
    int j;
    for(i; i < 32; i++)
    {
        for(j; j < 32; j++)
        {
            set_win_tiles(i,j,1,1,blank_tile_index);
        };
        j = 0;
    };
    i = 0;
}

void run_edit_mode()
{
    render_cursor_to_current();
    x_input = 0;
    y_input = 0;
    input = joypad();
    if(input & J_SELECT)
        {
            set_next_field_size();
            clear_data_block_1();
            clear_data_block_2();
            clear_canvas();
            render_field(present_data);
            delay(100u);
            return;
        }
    if(input & J_A){
        delay(80u);
        invert_cell();
    } else{
        if(input & J_UP)
        {
            y_input -= 1;
        }
        if (input & J_DOWN)
        {
            y_input += 1;
        }
        if(input & J_LEFT)
        {
            x_input -= 1;
        }
        if (input & J_RIGHT)
        {
            x_input += 1;
        }
        if(x_input || y_input){
            move_cursor(x_input, y_input);
        }
    }
    delay(60u);
}

int survives(unsigned int x, unsigned int y, char* data)
{
    unsigned int x_nw, x_n, x_ne, x_e, x_se, x_s, x_sw, x_w;
    unsigned int y_nw, y_n, y_ne, y_e, y_se, y_s, y_sw, y_w;
    int i = 0;
    if(x == 0u)
    {
        x_sw = get_max_field_width() - 1u;
        x_nw = get_max_field_width() - 1u;
        x_w = get_max_field_width() - 1u; 
    } else {
        x_sw = x - 1u;
        x_nw = x - 1u;
        x_w = x - 1u; 
    }
    x_n = x;
    x_s = x;

    x_ne = x + 1u;
    x_e = x + 1u;
    x_se = x + 1u;

    if(y == 0u)
    {
        y_nw = get_max_field_depth() - 1u; 
        y_n = get_max_field_depth() - 1u;
        y_ne = get_max_field_depth() - 1u;
    } else {
        y_nw = y - 1u;
        y_n = y - 1u;
        y_ne = y - 1u;
    }
    y_w = y;
    y_e = y;

    y_sw = y + 1u;
    y_s = y + 1u; 
    y_se = y + 1u;

    unsigned int neighbours [][] = {
        {x_nw, y_nw}, {x_n, y_n}, {x_ne, y_ne},
        {x_w, y_w},/*            */{x_e, y_e},
        {x_sw, y_sw}, {x_s, y_s}, {x_se, y_se}
    };
    int living_neighbors = 0;
    for(i = 0; i < 8; i++)
    {
        if(get_cell(data, neighbours[i][0], neighbours[i][1]) > 0)
        {
            living_neighbors++;
        }
    }

    if(living_neighbors > 0){
        //printf("location: %u,%u, living neightbors: %d", x, y, living_neighbors);
    }
    
    if(get_cell(data, x, y) > 0u)
    {
        // original cell is alive
        if(living_neighbors == 2 || living_neighbors == 3){
            //printf("survive");
            return 1;
        }
        return 0;
    } else {
        // Original cell is dead
        if(living_neighbors == 3){
            //printf("back from the dead");
            return 1;
        };
        return 0;
    };

}

void iterate_life(unsigned char * present, unsigned char * next)
{
    int i = 0;
    int j = 0;
    for(i; i < get_max_field_width(); i++)
    {
        for(j; j < get_max_field_depth(); j++)
        {
            if(joypad() & J_START){
                switch_game_mode();
                delay(100u);
                return;
            }
            if(survives(i,j, present))
            {   
                set_cell_high(next, i,j);
            } else {
                set_cell_low(next, i,j);
            }
        };
        j = 0;
    };
}


void run_play_mode()
{
    //printf("next: %d present %d", next_data, present_data);
    unsigned char * temp;
    render_field(present_data);
    iterate_life(present_data, next_data);
    if(game_state == edit_mode)
    {
        // Gamestate has been exited early due to player input, and we want to abandon the current game
        return;
    }
    temp = present_data;
    present_data = next_data;
    next_data = temp;
}

void switch_game_mode() 
{
    if(game_state == play_mode)
    {
        game_state = edit_mode;
    } else {
        game_state = play_mode;
    }
    render_field(present_data);
}

void main(void)
{
    int i;
    game_state = edit_mode;
    for(i = 0; i< 128; i++)
    {
        data_block_1[i] = 0x00;
        data_block_2[i] = 0x00;
    }
    set_win_data(0x00, 0x05, background_data);
    render_field(present_data);
    SHOW_BKG;
    SHOW_WIN;
    //gotoxy(0x01, 0x10);
    //setchar('k');
    //printf("lol!%d", 1);
    while(1){
        if(joypad() & J_START)
        {
            switch_game_mode();
        }
        switch (game_state)
        {
        case edit_mode:
            run_edit_mode();
            break;
        
        case play_mode:
            run_play_mode();
            break;
        }
    }
}