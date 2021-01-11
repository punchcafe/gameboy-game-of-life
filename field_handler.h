#define MAX_FIELD_WIDTH 32
#define MAX_FIELD_DEPTH 32

unsigned int get_cell(unsigned char * data, unsigned int x, unsigned int y);

void set_cell_high(unsigned char * data, unsigned int x, unsigned int y);

void set_cell_low(unsigned char * data, unsigned int x, unsigned int y);