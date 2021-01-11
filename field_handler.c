#include "C:\Users\punchcafe\Projects\gamboy-game-of-life\field_handler.h"

#define MAX_FIELD_WIDTH 10
#define MAX_FIELD_DEPTH 10

#define MASK_00000001 0x01
#define MASK_00000010 0x02
#define MASK_00000100 0x04
#define MASK_00001000 0x08
#define MASK_00010000 0x10
#define MASK_00100000 0x20
#define MASK_01000000 0x40
#define MASK_10000000 0x80

#define MASK_11111110 0xFE
#define MASK_11111101 0xFD
#define MASK_11111011 0xFB
#define MASK_11110111 0xF7
#define MASK_11101111 0xEF
#define MASK_11011111 0xDF
#define MASK_10111111 0xBF
#define MASK_01111111 0x7F

typedef struct coords {
    unsigned int x;
    unsigned int y;
} Coords;

void assign_coords(unsigned int x, unsigned int y,  Coords * coords)
{
    coords->x = x;
    coords->y = y;
}

void adjust_coordinates_for_limits( Coords * coords)
{
    coords->x = coords->x % MAX_FIELD_WIDTH;
    coords->y = coords->y % MAX_FIELD_WIDTH;
}

unsigned int calculate_cell_block(unsigned int coord){
    // Since cell blocks are 4x4 (square), the same method may be used to calculate 
    // their block reguardless of whether x or y
    return coord / 4;
}

/*
Returns the index of the beginning of the array
*/ 
unsigned int get_block_index(unsigned int x, unsigned int y){
    short x_cell_block = calculate_cell_block(x);
    short y_cell_block = calculate_cell_block(y);
    short cell_index = (y_cell_block * 8 * 2) + x_cell_block * 2;
    return cell_index;
}

unsigned int offset_from_block(unsigned int coord){
    return coord % 4;
}

unsigned int get_single_bit_mask(unsigned int x_off, unsigned int y_off){
    unsigned int mask;
    if(x_off == 0u){
        mask = MASK_10000000;
    } else if(x_off == 1u){
        mask = MASK_01000000;
    } else if(x_off == 2u){
        mask = MASK_00100000;
    } else if(x_off == 3u){
        mask = MASK_00010000;
    }
    if(y_off == 0x01 || y_off == 0x03){
        mask = mask >> 4;
    }
    return mask;
}

unsigned int get_seven_bit_mask(unsigned int x_off, unsigned int y_off){
    unsigned int mask;
    if(x_off == 0u){
        mask = MASK_01111111;
    } else if(x_off == 1u){
        mask = MASK_10111111;
    } else if(x_off == 2u){
        mask = MASK_11011111;
    } else if(x_off == 3u){
        mask = MASK_11101111;
    }
    if(y_off == 0x01 || y_off == 0x03){
        // In second half of char
        mask = mask >> 4;
    }
    return mask;
}

unsigned int get_cell_for_block(unsigned char * block_start, unsigned int x_off, unsigned int y_off)
{
    // GBDK note, seem to need to declare scope variables at top, otherwise breaks
    unsigned int cell_index;
    unsigned int result;
    unsigned int mask = get_single_bit_mask(x_off, y_off);

    // Top half or bottom half of Block
    cell_index = y_off < 0x02 ? 0x00 : 0x01;

    result = block_start[cell_index] & mask;
    return result != 0x00;
}

unsigned int get_cell(unsigned char * data, unsigned int x, unsigned int y)
{
    Coords coords;
    assign_coords(x, y, &coords);
    adjust_coordinates_for_limits(&coords);
    unsigned int block_index = get_block_index(coords.x, coords.y);
    unsigned int x_off = offset_from_block(coords.x);
    unsigned int y_off = offset_from_block(coords.y);
    return get_cell_for_block(&data[block_index], x_off, y_off);
}


void set_cell_high(unsigned char * data, unsigned int x, unsigned int y){
    int block_index = get_block_index(x,y);
    unsigned int x_off = offset_from_block(x);
    unsigned int y_off = offset_from_block(y);
    unsigned int mask = get_single_bit_mask(x_off, y_off);
    unsigned char existingData;
    unsigned char result;

    if(y_off >= 2u){
        block_index = block_index + 1u;
    }
    existingData = data[block_index];
    result = existingData | mask;

    data[block_index] = result;
}

void set_cell_low(unsigned char * data, unsigned int x, unsigned int y){
    int block_index = get_block_index(x,y);
    unsigned int x_off = offset_from_block(x);
    unsigned int y_off = offset_from_block(y);
    unsigned int mask =  get_seven_bit_mask(x_off, y_off);
    unsigned char existingData;
    unsigned char result;

    if(y_off >= 2u){
        block_index = block_index + 1u;
    }
    existingData = data[block_index];
    result = existingData & mask;

    data[block_index] = result;
}