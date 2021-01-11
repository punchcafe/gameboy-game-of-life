
#include <gb/gb.h>
#include<stdio.h>
#include <gb/font.h>
#include "C:\Users\punchcafe\Projects\gamboy-game-of-life\field_handler.h"

const unsigned char background_data [] = {
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
const unsigned char no_life_tile_index [] = { 0x00 };
const unsigned char life_tile_index [] = { 0x01 };
const unsigned char no_life_selected_tile_index [] = { 0x02 };
const unsigned char life_selected_tile_index [] = { 0x03 };

int cursor_x = 10;
int cursor_y = 10;

int i = 0;
int j = 0;

unsigned char input = 0;
unsigned int x_input = 0;
unsigned int y_input = 0;
// needed because of mid scope initialisation bugs

//enum game_state {start_screen, cell_select, play};

void move_cursor(unsigned int x_move, unsigned int y_move){
    unsigned int is_destination_cell_alive;
    unsigned int is_origin_cell_alive = get_cell(cells_data, cursor_x, cursor_y);
    if(is_origin_cell_alive){
        set_bkg_tiles(cursor_x, cursor_y, 1, 1, life_tile_index);
    } else {
        set_bkg_tiles(cursor_x, cursor_y, 1, 1, no_life_tile_index);
    }
    cursor_x += x_move;
    cursor_y += y_move;
    is_destination_cell_alive = get_cell(cells_data, cursor_x, cursor_y);
    if(is_destination_cell_alive){
        set_bkg_tiles(cursor_x, cursor_y, 1, 1, life_selected_tile_index);
    } else {
        set_bkg_tiles(cursor_x, cursor_y, 1, 1, no_life_selected_tile_index);
    }
}

void invert_cell(){
    if(get_cell(cells_data, cursor_x, cursor_y))
    {
        // Cell is set high
        set_cell_low(cells_data, cursor_x, cursor_y);
        // Consider having a reader/writer method, instead of letting draw directly, so that 
        // screen is always consistent with model at low CPU expense
        set_bkg_tiles(cursor_x, cursor_y, 1, 1, no_life_selected_tile_index);
    } else {
        // Cell is set low
        set_cell_high(cells_data, cursor_x, cursor_y);
        set_bkg_tiles(cursor_x, cursor_y, 1, 1, life_selected_tile_index);
    }
}

void edit_mode()
{
    while(1){
        x_input = 0;
        y_input = 0;
        input = joypad();
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
        delay(120u);
    };
}

int survives(unsigned int x, unsigned int y, char* data)
{
    unsigned int x_nw, x_n, x_ne, x_e, x_se, x_s, x_sw, x_w;
    unsigned int y_nw, y_n, y_ne, y_e, y_se, y_s, y_sw, y_w;
    int i = 0;
    if(x == 0u)
    {
        x_sw = MAX_FIELD_WIDTH - 1u;
        x_nw = MAX_FIELD_WIDTH - 1u;
        x_w = MAX_FIELD_WIDTH - 1u; 
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
        y_nw = MAX_FIELD_DEPTH - 1u; 
        y_n = MAX_FIELD_DEPTH - 1u;
        y_ne = MAX_FIELD_DEPTH - 1u;
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
        if(get_cell(data, neighbours[i][0], neighbours[i][1]) != 0u)
        {
            living_neighbors++;
        }
    }
    
    if(get_cell(data, x, y))
    {
        // original cell is alive
        if(living_neighbors == 2u || living_neighbors == 3u){
            return 1;
        }
        return 0;
    } else {
        // Original cell is dead
        if(living_neighbors == 3u){
            return 1;
        };
        return 0;
    };

}

void main(void)
{
    unsigned int block_index;

    font_t ibm_font, italic_font, min_font;
    font_init();

    ibm_font = font_load(font_ibm);  /* 96 tiles */
    font_set(ibm_font);
    /* First, init the font system */

    //font_t ibm_font, italic_font, min_font;


    HIDE_WIN;
    //SPRITES_8x16;   
    set_bkg_data(0x00, 0x04, background_data);

    for(i = 0; i < 32; i++)
        for(j = 0; j < 32; j++)
            set_bkg_tiles(i, j, 1, 1, no_life_tile_index);
    i = 0;
    j=0;
    //set_bkg_data(0x00, 0x02, &background_data[16]);

    /* Load all the fonts that we can */
    //ibm_font = font_load(font_ibm);  /* 96 tiles */
    //italic_font = font_load(font_italic);   /* 93 tiles */
    
    /* Load this one with dk grey background and white foreground */
    //color(WHITE, DKGREY, SOLID);
    
    //line(0x04,0x04, 0x40, 0x04);
    //delay(100Lu);

    //min_font = font_load(font_min);

    /* Turn scrolling off (why not?) */
    //mode(get_mode() | M_NO_SCROLL);

    /* Print some text! */
    
    /* IBM font */
    //font_set(ibm_font);
    //printf("Font demo.\n\n");

    HIDE_BKG;

    set_cell_high(cells_data, 0,0);
    set_cell_high(cells_data, 0,1);
    set_cell_high(cells_data, 0,2);
    set_cell_high(cells_data, 0,3);
    set_cell_high(cells_data, 1,0);
    set_cell_high(cells_data, 1,1);
    set_cell_high(cells_data, 1,2);
    set_cell_high(cells_data, 3,3);
    set_cell_high(cells_data, 2,5);
    set_cell_high(cells_data, 5,2);
    set_cell_high(cells_data, 10,10);

    for(i; i < 32; i++)
    {
        for(j; j < 32; j++)
        {
            if(get_cell(cells_data, i,j))
            {
                set_bkg_tiles(i,j,1,1,life_tile_index);
            }
        };
        j = 0;
    };
    SHOW_BKG;
    delay(1000u);
    i = 0;
    HIDE_SPRITES;
    for(i; i < 32; i++)
    {
        for(j; j < 32; j++)
        {
            if(get_cell(cells_data, i,j))
            {   
                //printf("hi");
                set_bkg_tiles(i,j,1,1,life_tile_index);
            }
        };
        j = 0;
    };
    i = 0;

    survives(1,1,cells_data);

    for(i; i < 32; i++)
    {
        for(j; j < 32; j++)
        {
            if(survives(i,j, cells_data))
            {   
                set_bkg_tiles(i,j,1,1,life_tile_index);
            } else {
                set_bkg_tiles(i,j,1,1,no_life_tile_index);
            }
        };
        j = 0;
    };
    i = 0;

    //printf("out");
    move_cursor(1u,1u);
    SHOW_BKG;
    edit_mode();
}