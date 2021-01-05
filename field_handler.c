#include <gb/gb.h>
#include<stdio.h>
#include <gb/font.h>


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

const unsigned char background_data [] = {
    // No Life (index 0)
    0xFF,0xFF,0x7F,0xFF,0xFE,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xBF,0xFD,0xFF,0xFF,
    // Life (index 16)
    0xC7,0xEF,0x0F,0xA7,0xE4,0xC3,0x40,0x80,
    0x02,0x01,0x27,0xC3,0xB1,0xE5,0xE3,0xF7
};

const unsigned char cells_data [] = {

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
    0x00,0x01, // cells 0,0 -> 3,3
    0x02,0x03, // cells 4,0 -> 7,3
    0x04,0x05, // cells 8,0 -> 11,3
    0x06,0x07, // cells 12,0 -> 15,3
    0x08,0x09, // cells 16,0 -> 19,3
    0x0a,0x0b, // cells 20,0 -> 23,3
    0x0c,0x0d, // cells 24,0 -> 27,3
    0x0e,0x0f, // cells 28,0 -> 31,3

    // Second block row, 8 * 2 <= i <= (15 * 2 + 1)
    // Block 8
    0xFe,0x09, // cells 0,4 -> 3,7
    0x0a,0x0b, // cells 4,4 -> 7,7
    0x0c,0x0d, // cells 8,4 -> 11,7
    0x0e,0x0f, // cells 12,4 -> 15,7
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
    0x00,0x00, // cells 4,12 -> 7,15
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

const unsigned char no_life_tile_index [] = { 0x00 };
const unsigned char life_tile_index [] = { 0x01 };


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
    // treating cell data as 2D array, y * 8 gives us the number of cell block rows to skip, *2 since theres two bytes per cell block
    short cell_index = (y_cell_block * 8 * 2) + x_cell_block * 2;
    return cell_index;
}

unsigned int offset_from_block(unsigned int coord){
    return coord % 4;
}

unsigned int get_cell_for_block(unsigned char * block_start, unsigned int x_off, unsigned int y_off)
{
    // GBDK note, seem to need to declare scope variables at top, otherwise breaks
    unsigned int cell_index;
    unsigned int result;
    unsigned int mask;

    //printf("from inside, xoff is %u", x_off);
    if(x_off == 0u){
        mask = MASK_10000000;
    } else if(x_off == 1u){
        mask = MASK_01000000;
    } else if(x_off == 2u){
        mask = MASK_00100000;
    } else if(x_off == 3u){
        //printf("gotcha");
        mask = MASK_00010000;
    }
    /*
    switch(x_off) {
        case 0x00:
            mask = MASK_10000000;
            break;
        case 0x01:
        printf("nuber 3");
            mask = MASK_01000000;
            break;
        case 0x02:
        printf("nuber 2");
            mask = MASK_00100000;
            break;
        case 3u:
        printf("yeah it's me");
            mask = MASK_00010000;
            break;
        default:
        printf("howd you get here? %u", x_off == 3u);
            break;
    };
    */

    if(y_off == 0x01 || y_off == 0x03)
    {
        // In second half of char
        //printf("computed mask: %u \n", mask >> 4);
        mask = mask >> 4;
    }

    // Top half or bottom half of Block
    cell_index = y_off < 0x02 ? 0x00 : 0x01;

    //printf("half-block cell index: %u \n", cell_index);
    //printf("mask: %u \n", mask);
    //printf("try get y off: %u \n", y_off);
    //printf("try get x off: %u \n", x_off);

    result = block_start[cell_index] & mask;
    //printf("result: %u \n", result);
    //printf("result bool: %u \n", result != 0x00);
    return result != 0x00;
}

unsigned int get_cell(unsigned char * data, unsigned int x, unsigned int y)
{
    unsigned int block_index = get_block_index(x,y);
    unsigned int x_off = offset_from_block(x);
    unsigned int y_off = offset_from_block(y);
    //printf("try get cell index: %u \n", block_index);
    //printf("try get x off: %u \n", x_off);
    //printf("try get y off: %u \n", y_off);
    return get_cell_for_block(&data[block_index], x_off, y_off);
}

int i = 0;
int j = 0;
// needed because of mid scope initialisation bugs



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
    set_bkg_data(0x00, 0x02, background_data);
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
    block_index = get_block_index(0,0);


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
    i = 0;
    
    
    HIDE_SPRITES;
    SHOW_BKG;
    //printf("try get cell : %u   \n", get_cell(cells_data, 7,3));
    SHOW_BKG;
}