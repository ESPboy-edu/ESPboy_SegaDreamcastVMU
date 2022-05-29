#define SPEED_DELAY 2

/*
SEGA Dreamcast VMU emulator for ESPboy by RomanS www.espboy.com
based on Potatochip emulator by SoftVMS by Marcus Comstedt http://mc.pp.se/dc/,
ported for Pokitto by Felipe Manga https://os.mbed.com/users/fmanga/code/SoftVMS/

For every game please adjust SPEED_DELAY
In file "flash.h" uncomment one desired game and compile
check more games here http://www.bucanero.com.ar/dreamcast/vmu/minigames/
convert to C++ array with web tool https://tomeko.net/online_tools/file_to_hex.php?lang=en
No saves, sorry :(

Tests passed for:

IDOUDO
ALIENFIGHTER
POWERSTONE
SOULCALIBUR
CHAO_ADVENTURE
POCKETGT_JP
POCKETGT
SAKURA_CLOCK
SPACE_INVIDERS
MINI_PACMAN
PAPER_ATTACK
SWAMPY
TINY_TETRIS
GODZILLA
RPG
FREAK_SKATER
*/


#include "lib/ESPboyInit.h"
#include "lib/ESPboyInit.cpp"

extern void keypress(int);
extern void keyrelease(int);
extern void resetcpu();
extern void run_cpu( void );

ESPboyInit myESPboy;
TFT_eSprite bufLCD = TFT_eSprite(&myESPboy.tft);

void waitforevents(timeval *){
}

void checkevents(){
  static uint8_t prevKeys = 0;
  uint8_t keys = myESPboy.getKeys();
  delay(SPEED_DELAY);
  //Serial.print(keys);  Serial.print("    ");  Serial.println(prevKeys); 
  
  if (((keys&PAD_UP) && !(prevKeys&PAD_UP)))
    if(myESPboy.getKeys()&PAD_UP) keypress(0);
    
  if ((!(keys&PAD_UP) && (prevKeys&PAD_UP))) 
    if(!(myESPboy.getKeys()&PAD_UP)) keyrelease(0);
  
  if (((keys&PAD_DOWN) && !(prevKeys&PAD_DOWN))) 
    if (myESPboy.getKeys()&PAD_DOWN)keypress(1);
  
  if ((!(keys&PAD_DOWN) && (prevKeys&PAD_DOWN))) 
    if(!(myESPboy.getKeys()&PAD_DOWN)) keyrelease(1);
  
  if (((keys&PAD_LEFT) && !(prevKeys&PAD_LEFT))) 
    if ((myESPboy.getKeys()&PAD_LEFT)) keypress(2);
  
  if ((!(keys&PAD_LEFT) && (prevKeys&PAD_LEFT))) 
    if (!(myESPboy.getKeys()&PAD_LEFT)) keyrelease(2);
  
  if (((keys&PAD_RIGHT) && !(prevKeys&PAD_RIGHT))) 
    if (myESPboy.getKeys()&PAD_RIGHT) keypress(3);
  
  if ((!(keys&PAD_RIGHT) && (prevKeys&PAD_RIGHT)))
    if (!(myESPboy.getKeys()&PAD_RIGHT)) keyrelease(3);
  
  if (((keys&PAD_ACT) && !(prevKeys&PAD_ACT)))
    if (myESPboy.getKeys()&PAD_ACT) keypress(4);
  
  if ((!(keys&PAD_ACT) && (prevKeys&PAD_ACT)))
    if(!(myESPboy.getKeys()&PAD_ACT)) keyrelease(4);

  if (((keys&PAD_ESC) && !(prevKeys&PAD_ESC)))
    if (myESPboy.getKeys()&PAD_ESC) keypress(5);
  
  if ((!(keys&PAD_ESC) && (prevKeys&PAD_ESC)))
    if (!(myESPboy.getKeys()&PAD_ESC)) keyrelease(5);
  
  prevKeys = keys;
}


void redrawlcd(){
  bufLCD.pushSprite((128-48*2)/2, (128-32*2)/2);
}



//48x32
//+(128-48*2)/2
//+(128-32*2)/2
void vmputpixel( int x, int y, int c ){
	//if (c&1) myESPboy.tft.drawPixel(x,y,TFT_YELLOW);
	//else myESPboy.tft.drawPixel(x,y,TFT_BLACK);
   uint16_t clr;
   if (c&1) clr = TFT_YELLOW;
   else clr = TFT_BLACK;
   bufLCD.fillRect(x*2, y*2, 2, 2, clr);
}





void sound(int freq){
  tone(D3,freq);
}

void noSound(){
  noTone(D3);
}


void gettimeofday(timeval *tm ){
    tm->tv_sec = millis()/1000;
    tm->tv_usec = millis();
}


void error_msg(char *fmt, ...){
 Serial.println();
 Serial.print("ERROR: "); Serial.println(fmt);
}


void setup(){
  Serial.begin(115200);
  myESPboy.begin("SEGA VMU");
  bufLCD.createSprite(48*2, 32*2);
}


void loop () {
    resetcpu();
    run_cpu();
}
