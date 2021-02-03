#ifndef FIELD_HANDLER_H
#define FIELD_HANDLER_H

unsigned int get_border_width();
unsigned int get_max_field_width();
unsigned int get_max_field_depth();

void set_next_field_size();

void set_field_L();
void set_field_M();
void set_field_S();

unsigned int get_cell(unsigned char * data, unsigned int x, unsigned int y);

void set_cell_high(unsigned char * data, unsigned int x, unsigned int y);

void set_cell_low(unsigned char * data, unsigned int x, unsigned int y);
#endif