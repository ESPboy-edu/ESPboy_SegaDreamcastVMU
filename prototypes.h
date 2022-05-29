#include <Arduino.h>

void resetcpu( void );
void run_cpu( void );

void waitforevents(struct timeval *);
void checkevents( void );
void redrawlcd( void );
void vmputpixel(int, int, int);
void keypress(int i);
void keyrelease(int i);
int do_vmsgame(char *filename, char *biosname);
int do_lcdimg(char *filename);
void sound(int freq);
void noSound();
int gettimeofday(struct timeval *);
#define GETTIMEOFDAY(tp) gettimeofday(tp)
extern void error_msg(char *fmt, ...);
