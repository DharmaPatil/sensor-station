const uint16_t times_indexes[] = {
  0, // '+'
  19, // ','
  24, // '-'
  33, // '.'
  36, // '/'
  46, // '0'
  61, // '1'
  70, // '2'
  86, // '3'
  100, // '4'
  116, // '5'
  129, // '6'
  144, // '7'
  159, // '8'
  173, // '9'
  188, // ':'
};

const char times_first_char = '+';
const char times_last_char = '9';
const uint8_t times_height = 4;

const uint8_t times_bitmaps[] = {
  //  '+' - 0
  0x00,0x40,0x00,0x00, // ..............x...............
  0x00,0x40,0x00,0x00, // ..............x...............
  0x00,0x40,0x00,0x00, // ..............x...............
  0x00,0x40,0x00,0x00, // ..............x...............
  0x00,0x40,0x00,0x00, // ..............x...............
  0x00,0x40,0x00,0x00, // ..............x...............
  0x00,0x40,0x00,0x00, // ..............x...............
  0x00,0x40,0x00,0x00, // ..............x...............
  0x00,0x40,0x00,0x00, // ..............x...............
  0xE0,0xFF,0xFF,0x00, // .....xxxxxxxxxxxxxxxxxxx......
  0x00,0x40,0x00,0x00, // ..............x...............
  0x00,0x40,0x00,0x00, // ..............x...............
  0x00,0x40,0x00,0x00, // ..............x...............
  0x00,0x40,0x00,0x00, // ..............x...............
  0x00,0x40,0x00,0x00, // ..............x...............
  0x00,0x40,0x00,0x00, // ..............x...............
  0x00,0x40,0x00,0x00, // ..............x...............
  0x00,0x40,0x00,0x00, // ..............x...............
  0x00,0x40,0x00,0x00, // ..............x...............
  //  ',' - 19
  0x18,0x00,0x00,0x00, // ...xx.........................
  0x38,0x00,0x00,0x00, // ...xxx........................
  0x38,0x00,0x00,0x00, // ...xxx........................
  0x39,0x00,0x00,0x00, // x..xxx........................
  0x1E,0x00,0x00,0x00, // .xxxx.........................
  //  '-' - 24
  0x00,0x1C,0x00,0x00, // ..........xxx.................
  0x00,0x1C,0x00,0x00, // ..........xxx.................
  0x00,0x1C,0x00,0x00, // ..........xxx.................
  0x00,0x1C,0x00,0x00, // ..........xxx.................
  0x00,0x1C,0x00,0x00, // ..........xxx.................
  0x00,0x1C,0x00,0x00, // ..........xxx.................
  0x00,0x1C,0x00,0x00, // ..........xxx.................
  0x00,0x1C,0x00,0x00, // ..........xxx.................
  0x00,0x1C,0x00,0x00, // ..........xxx.................
  //  '.' - 33
  0x38,0x00,0x00,0x00, // ...xxx........................
  0x38,0x00,0x00,0x00, // ...xxx........................
  0x38,0x00,0x00,0x00, // ...xxx........................
  //  '/' - 36
  0x08,0x00,0x00,0x00, // ...x..........................
  0x70,0x00,0x00,0x00, // ....xxx.......................
  0x80,0x03,0x00,0x00, // .......xxx....................
  0x00,0x1C,0x00,0x00, // ..........xxx.................
  0x00,0xE0,0x00,0x00, // .............xxx..............
  0x00,0x80,0x03,0x00, // ...............xxx............
  0x00,0x00,0x1C,0x00, // ..................xxx.........
  0x00,0x00,0xE0,0x00, // .....................xxx......
  0x00,0x00,0x00,0x07, // ........................xxx...
  0x00,0x00,0x00,0x08, // ...........................x..
  //  '0' - 46
  0x00,0xFC,0x07,0x00, // ..........xxxxxxxxx...........
  0x00,0xFF,0x3F,0x00, // ........xxxxxxxxxxxxxx........
  0xC0,0xFF,0xFF,0x00, // ......xxxxxxxxxxxxxxxxxx......
  0xE0,0x01,0xE0,0x01, // .....xxxx............xxxx.....
  0x30,0x00,0x00,0x03, // ....xx..................xx....
  0x18,0x00,0x00,0x06, // ...xx....................xx...
  0x08,0x00,0x00,0x04, // ...x......................x...
  0x08,0x00,0x00,0x04, // ...x......................x...
  0x08,0x00,0x00,0x04, // ...x......................x...
  0x18,0x00,0x00,0x06, // ...xx....................xx...
  0x30,0x00,0x00,0x03, // ....xx..................xx....
  0xE0,0x01,0xE0,0x01, // .....xxxx............xxxx.....
  0xC0,0xFF,0xFF,0x00, // ......xxxxxxxxxxxxxxxxxx......
  0x00,0xFF,0x3F,0x00, // ........xxxxxxxxxxxxxx........
  0x00,0xFC,0x0F,0x00, // ..........xxxxxxxxxx..........
  //  '1' - 61
  0x08,0x00,0x00,0x01, // ...x....................x.....
  0x08,0x00,0x00,0x02, // ...x.....................x....
  0x08,0x00,0x00,0x03, // ...x....................xx....
  0xF8,0xFF,0xFF,0x03, // ...xxxxxxxxxxxxxxxxxxxxxxx....
  0xF8,0xFF,0xFF,0x07, // ...xxxxxxxxxxxxxxxxxxxxxxxx...
  0xF8,0xFF,0xFF,0x07, // ...xxxxxxxxxxxxxxxxxxxxxxxx...
  0x08,0x00,0x00,0x00, // ...x..........................
  0x08,0x00,0x00,0x00, // ...x..........................
  0x08,0x00,0x00,0x00, // ...x..........................
  //  '2' - 70
  0x08,0x00,0x00,0x00, // ...x..........................
  0x18,0x00,0x30,0x00, // ...xx...............xx........
  0x38,0x00,0xC0,0x00, // ...xxx................xx......
  0x78,0x00,0x80,0x01, // ...xxxx................xx.....
  0xF8,0x00,0x80,0x03, // ...xxxxx...............xxx....
  0xB8,0x01,0x00,0x07, // ...xxx.xx...............xxx...
  0x38,0x03,0x00,0x07, // ...xxx..xx..............xxx...
  0x38,0x06,0x00,0x07, // ...xxx...xx.............xxx...
  0x38,0x0C,0x00,0x07, // ...xxx....xx............xxx...
  0x38,0x18,0x80,0x07, // ...xxx.....xx..........xxxx...
  0x38,0x70,0x80,0x07, // ...xxx......xxx........xxxx...
  0x38,0xE0,0xC1,0x03, // ...xxx.......xxxx.....xxxx....
  0x38,0x80,0xFF,0x03, // ...xxx.........xxxxxxxxxxx....
  0x38,0x00,0xFF,0x01, // ...xxx..........xxxxxxxxx.....
  0x70,0x00,0x7C,0x00, // ....xxx...........xxxxx.......
  0xC0,0x00,0x00,0x00, // ......xx......................
  //  '3' - 86
  0x30,0x00,0x40,0x00, // ....xx................x.......
  0x38,0x00,0x80,0x00, // ...xxx.................x......
  0x38,0x00,0x00,0x01, // ...xxx..................x.....
  0x18,0x00,0x00,0x02, // ...xx....................x....
  0x18,0x80,0x00,0x06, // ...xx..........x.........xx...
  0x08,0x80,0x00,0x06, // ...x...........x.........xx...
  0x08,0x80,0x01,0x06, // ...x...........xx........xx...
  0x08,0xC0,0x01,0x06, // ...x..........xxx........xx...
  0x08,0xC0,0x03,0x07, // ...x..........xxxx......xxx...
  0x10,0xE0,0x87,0x07, // ....x........xxxxxx....xxxx...
  0x60,0xF8,0xFD,0x03, // .....xx....xxxxxx.xxxxxxxx....
  0xE0,0xFF,0xF8,0x01, // .....xxxxxxxxxxx...xxxxxx.....
  0xC0,0x7F,0xF0,0x00, // ......xxxxxxxxx.....xxxx......
  0x00,0x3F,0x00,0x00, // ........xxxxxx................
  //  '4' - 100
  0x00,0x0E,0x00,0x00, // .........xxx..................
  0x00,0x1E,0x00,0x00, // .........xxxx.................
  0x00,0x36,0x00,0x00, // .........xx.xx................
  0x00,0xC6,0x00,0x00, // .........xx...xx..............
  0x00,0x86,0x01,0x00, // .........xx....xx.............
  0x00,0x06,0x06,0x00, // .........xx......xx...........
  0x00,0x06,0x08,0x00, // .........xx........x..........
  0x00,0x06,0x30,0x00, // .........xx.........xx........
  0x00,0x06,0x40,0x00, // .........xx...........x.......
  0x00,0x06,0x80,0x01, // .........xx............xx.....
  0xF8,0xFF,0xFF,0x03, // ...xxxxxxxxxxxxxxxxxxxxxxx....
  0xF8,0xFF,0xFF,0x07, // ...xxxxxxxxxxxxxxxxxxxxxxxx...
  0xF8,0xFF,0xFF,0x07, // ...xxxxxxxxxxxxxxxxxxxxxxxx...
  0x00,0x06,0x00,0x00, // .........xx...................
  0x00,0x06,0x00,0x00, // .........xx...................
  0x00,0x06,0x00,0x00, // .........xx...................
  //  '5' - 116
  0x30,0x00,0x00,0x00, // ....xx........................
  0x38,0x00,0x0C,0x00, // ...xxx............xx..........
  0x38,0x00,0x3C,0x00, // ...xxx............xxxx........
  0x18,0x00,0xDC,0x00, // ...xx.............xxx.xx......
  0x18,0x00,0x1E,0x03, // ...xx............xxxx...xx....
  0x18,0x00,0x1E,0x07, // ...xx............xxxx...xxx...
  0x18,0x00,0x0E,0x07, // ...xx............xxx....xxx...
  0x10,0x00,0x0F,0x07, // ....x...........xxxx....xxx...
  0x30,0x80,0x07,0x07, // ....xx.........xxxx.....xxx...
  0x60,0xC0,0x07,0x07, // .....xx.......xxxxx.....xxx...
  0xC0,0xF1,0x03,0x07, // ......xxx...xxxxxx......xxx...
  0x80,0xFF,0x01,0x07, // .......xxxxxxxxxx.......xxx...
  0x00,0x7E,0x00,0x04, // .........xxxxxx...........x...
  //  '6' - 129
  0x00,0xFE,0x00,0x00, // .........xxxxxxx..............
  0x80,0xFF,0x07,0x00, // .......xxxxxxxxxxxx...........
  0xE0,0xFF,0x1F,0x00, // .....xxxxxxxxxxxxxxxx.........
  0xF0,0x00,0x3F,0x00, // ....xxxx........xxxxxx........
  0x30,0x00,0x71,0x00, // ....xx..........x...xxx.......
  0x18,0x00,0xE2,0x00, // ...xx............x...xxx......
  0x08,0x00,0x82,0x01, // ...x.............x.....xx.....
  0x08,0x00,0x82,0x01, // ...x.............x.....xx.....
  0x08,0x00,0x02,0x03, // ...x.............x......xx....
  0x08,0x00,0x03,0x02, // ...x............xx.......x....
  0x10,0x80,0x03,0x06, // ....x..........xxx.......xx...
  0x70,0xE0,0x01,0x04, // ....xxx......xxxx.........x...
  0xE0,0xFF,0x01,0x04, // .....xxxxxxxxxxxx.........x...
  0xC0,0xFF,0x00,0x04, // ......xxxxxxxxxx..........x...
  0x00,0x3F,0x00,0x00, // ........xxxxxx................
  //  '7' - 144
  0x00,0x00,0x60,0x00, // .....................xx.......
  0x00,0x00,0xC0,0x03, // ......................xxxx....
  0x00,0x00,0x80,0x07, // .......................xxxx...
  0x00,0x00,0x00,0x07, // ........................xxx...
  0x00,0x00,0x00,0x07, // ........................xxx...
  0x18,0x00,0x00,0x07, // ...xx...................xxx...
  0xF8,0x00,0x00,0x07, // ...xxxxx................xxx...
  0xF0,0x07,0x00,0x07, // ....xxxxxxx.............xxx...
  0x80,0x3F,0x00,0x07, // .......xxxxxxx..........xxx...
  0x00,0xFC,0x01,0x07, // ..........xxxxxxx.......xxx...
  0x00,0xE0,0x0F,0x07, // .............xxxxxxx....xxx...
  0x00,0x00,0x7F,0x07, // ................xxxxxxx.xxx...
  0x00,0x00,0xF8,0x07, // ...................xxxxxxxx...
  0x00,0x00,0xC0,0x07, // ......................xxxxx...
  0x00,0x00,0x00,0x06, // .........................xx...
  //  '8' - 159
  0xC0,0x07,0xF8,0x00, // ......xxxxx........xxxxx......
  0xE0,0x0F,0xFC,0x01, // .....xxxxxxx......xxxxxxx.....
  0xF0,0x1F,0xFE,0x03, // ....xxxxxxxxx....xxxxxxxxx....
  0x30,0x38,0x1F,0x03, // ....xx.....xxx..xxxxx...xx....
  0x18,0xE0,0x07,0x06, // ...xx........xxxxxx......xx...
  0x08,0xC0,0x03,0x04, // ...x..........xxxx........x...
  0x08,0xE0,0x01,0x04, // ...x.........xxxx.........x...
  0x08,0xE0,0x01,0x04, // ...x.........xxxx.........x...
  0x08,0xF0,0x03,0x06, // ...x........xxxxxx.......xx...
  0x18,0x78,0x06,0x03, // ...xx......xxxx..xx.....xx....
  0x30,0x3E,0xFE,0x03, // ....xx...xxxxx...xxxxxxxxx....
  0xF0,0x1F,0xFC,0x01, // ....xxxxxxxxx.....xxxxxxx.....
  0xE0,0x0F,0xF0,0x00, // .....xxxxxxx........xxxx......
  0x80,0x07,0x00,0x00, // .......xxxx...................
  //  '9' - 173
  0x00,0x00,0x3F,0x00, // ................xxxxxx........
  0x08,0xC0,0xFF,0x00, // ...x..........xxxxxxxxxx......
  0x08,0xE0,0xFF,0x01, // ...x.........xxxxxxxxxxxx.....
  0x08,0xE0,0x81,0x03, // ...x.........xxxx......xxx....
  0x18,0x70,0x00,0x02, // ...xx.......xxx..........x....
  0x10,0x30,0x00,0x04, // ....x.......xx............x...
  0x30,0x10,0x00,0x04, // ....xx......x.............x...
  0x60,0x10,0x00,0x04, // .....xx.....x.............x...
  0xE0,0x10,0x00,0x04, // .....xxx....x.............x...
  0xC0,0x11,0x00,0x06, // ......xxx...x............xx...
  0x80,0x23,0x00,0x03, // .......xxx...x..........xx....
  0x00,0x3F,0xC0,0x03, // ........xxxxxx........xxxx....
  0x00,0xFE,0xFF,0x01, // .........xxxxxxxxxxxxxxxx.....
  0x00,0xF8,0x7F,0x00, // ...........xxxxxxxxxxxx.......
  0x00,0xC0,0x1F,0x00, // ..............xxxxxxx.........
};

const Font_TypeDef font_times = {
	times_first_char,
	times_last_char,
	times_height,
	times_indexes,
	times_bitmaps,
};

