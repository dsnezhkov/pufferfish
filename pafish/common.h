
#ifndef COMM_H
#define COMM_H

unsigned short init_cmd_colors();

void restore_cmd_colors(unsigned short);

void print_header();

void print_traced();

void print_not_traced();

void print_warning(char * msg);

void write_log(char msg[]);

void write_trace(char product[]);

void write_trace_dns(char product[]);

void print_check_group(char * text);

BOOL exec_check(int (*callback)(), int plugLog);

#endif
