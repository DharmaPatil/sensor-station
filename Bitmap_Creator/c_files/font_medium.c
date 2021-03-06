const uint16_t medium_indexes[] = {
  0, // '!'
  1, // '"'
  5, // '#'
  14, // '$'
  21, // '%'
  33, // '&'
  42, // '''
  43, // '('
  46, // ')'
  49, // '*'
  54, // '+'
  61, // ','
  63, // '-'
  67, // '.'
  69, // '/'
  73, // '0'
  80, // '1'
  84, // '2'
  91, // '3'
  98, // '4'
  106, // '5'
  113, // '6'
  120, // '7'
  127, // '8'
  134, // '9'
  141, // ':'
  143, // ';'
  145, // '<'
  152, // '='
  159, // '>'
  166, // '?'
  173, // '@'
  188, // 'A'
  197, // 'B'
  206, // 'C'
  216, // 'D'
  226, // 'E'
  235, // 'F'
  243, // 'G'
  253, // 'H'
  262, // 'I'
  263, // 'J'
  269, // 'K'
  278, // 'L'
  285, // 'M'
  296, // 'N'
  305, // 'O'
  315, // 'P'
  324, // 'Q'
  334, // 'R'
  343, // 'S'
  352, // 'T'
  361, // 'U'
  370, // 'V'
  379, // 'W'
  392, // 'X'
  401, // 'Y'
  410, // 'Z'
  419, // '['
  422, // '\'
  426, // ']'
  429, // '^'
  436, // '_'
  444, // '`'
  446, // 'a'
  453, // 'b'
  460, // 'c'
  466, // 'd'
  473, // 'e'
  480, // 'f'
  484, // 'g'
  491, // 'h'
  497, // 'i'
  498, // 'j'
  501, // 'k'
  508, // 'l'
  509, // 'm'
  520, // 'n'
  526, // 'o'
  533, // 'p'
  540, // 'q'
  547, // 'r'
  551, // 's'
  557, // 't'
  561, // 'u'
  567, // 'v'
  574, // 'w'
  585, // 'x'
  592, // 'y'
  599, // 'z'
  606, // '{'
  611, // '|'
  612, // '}'
  617, // '~'
  621, // ''
};

const char medium_first_char = '!';
const char medium_last_char = '~';
const uint8_t medium_height = 2;

const uint8_t medium_bitmaps[] = {
  //  '!' - 0
  0xE8,0x7F, // ...x.xxxxxxxxxx.
  //  '"' - 1
  0x00,0x78, // ...........xxxx.
  0x00,0x00, // ................
  0x00,0x00, // ................
  0x00,0x78, // ...........xxxx.
  //  '#' - 5
  0x40,0x04, // ......x...x.....
  0x78,0x04, // ...xxxx...x.....
  0xC0,0x07, // ......xxxxx.....
  0x40,0x3C, // ......x...xxxx..
  0x40,0x04, // ......x...x.....
  0x78,0x04, // ...xxxx...x.....
  0xC0,0x07, // ......xxxxx.....
  0x40,0x3C, // ......x...xxxx..
  0x40,0x04, // ......x...x.....
  //  '$' - 14
  0x20,0x1C, // .....x....xxx...
  0x10,0x22, // ....x....x...x..
  0x08,0x42, // ...x.....x....x.
  0xFC,0xFF, // ..xxxxxxxxxxxxxx
  0x08,0x41, // ...x....x.....x.
  0x10,0x21, // ....x...x....x..
  0xE0,0x10, // .....xxx....x...
  //  '%' - 21
  0x00,0x3C, // ..........xxxx..
  0x00,0x42, // .........x....x.
  0x00,0x42, // .........x....x.
  0x18,0x42, // ...xx....x....x.
  0x60,0x3C, // .....xx...xxxx..
  0x80,0x01, // .......xx.......
  0x00,0x0E, // .........xxx....
  0xF0,0x30, // ....xxxx....xx..
  0x08,0x41, // ...x....x.....x.
  0x08,0x01, // ...x....x.......
  0x08,0x01, // ...x....x.......
  0xF0,0x00, // ....xxxx........
  //  '&' - 33
  0xE0,0x00, // .....xxx........
  0x10,0x39, // ....x...x..xxx..
  0x08,0x46, // ...x.....xx...x.
  0x08,0x43, // ...x....xx....x.
  0x88,0x44, // ...x...x..x...x.
  0x50,0x38, // ....x.x....xxx..
  0x20,0x00, // .....x..........
  0x50,0x00, // ....x.x.........
  0x88,0x00, // ...x...x........
  //  ''' - 42
  0x00,0x78, // ...........xxxx.
  //  '(' - 43
  0xF0,0x07, // ....xxxxxxx.....
  0x0E,0x38, // .xxx.......xxx..
  0x01,0x40, // x.............x.
  //  ')' - 46
  0x01,0x40, // x.............x.
  0x0E,0x38, // .xxx.......xxx..
  0xF0,0x07, // ....xxxxxxx.....
  //  '*' - 49
  0x00,0x28, // ...........x.x..
  0x00,0x10, // ............x...
  0x00,0x7C, // ..........xxxxx.
  0x00,0x10, // ............x...
  0x00,0x28, // ...........x.x..
  //  '+' - 54
  0x00,0x01, // ........x.......
  0x00,0x01, // ........x.......
  0x00,0x01, // ........x.......
  0xE0,0x0F, // .....xxxxxxx....
  0x00,0x01, // ........x.......
  0x00,0x01, // ........x.......
  0x00,0x01, // ........x.......
  //  ',' - 61
  0x1A,0x00, // .x.xx...........
  0x1C,0x00, // ..xxx...........
  //  '-' - 63
  0x40,0x00, // ......x.........
  0x40,0x00, // ......x.........
  0x40,0x00, // ......x.........
  0x40,0x00, // ......x.........
  //  '.' - 67
  0x18,0x00, // ...xx...........
  0x18,0x00, // ...xx...........
  //  '/' - 69
  0x18,0x00, // ...xx...........
  0xE0,0x01, // .....xxxx.......
  0x00,0x1E, // .........xxxx...
  0x00,0x60, // .............xx.
  //  '0' - 73
  0xE0,0x1F, // .....xxxxxxxx...
  0x10,0x20, // ....x........x..
  0x08,0x40, // ...x..........x.
  0x08,0x40, // ...x..........x.
  0x08,0x40, // ...x..........x.
  0x10,0x20, // ....x........x..
  0xE0,0x1F, // .....xxxxxxxx...
  //  '1' - 80
  0x00,0x08, // ...........x....
  0x00,0x10, // ............x...
  0x00,0x20, // .............x..
  0xF8,0x7F, // ...xxxxxxxxxxxx.
  //  '2' - 84
  0x08,0x10, // ...x........x...
  0x18,0x20, // ...xx........x..
  0x28,0x40, // ...x.x........x.
  0x48,0x40, // ...x..x.......x.
  0x88,0x40, // ...x...x......x.
  0x08,0x63, // ...x....xx...xx.
  0x08,0x1C, // ...x......xxx...
  //  '3' - 91
  0x30,0x10, // ....xx......x...
  0x10,0x20, // ....x........x..
  0x08,0x42, // ...x.....x....x.
  0x08,0x42, // ...x.....x....x.
  0x08,0x46, // ...x.....xx...x.
  0x10,0x3D, // ....x...x.xxxx..
  0xE0,0x00, // .....xxx........
  //  '4' - 98
  0xC0,0x00, // ......xx........
  0x40,0x01, // ......x.x.......
  0x40,0x02, // ......x..x......
  0x40,0x0C, // ......x...xx....
  0x40,0x10, // ......x.....x...
  0x40,0x20, // ......x......x..
  0xF8,0x7F, // ...xxxxxxxxxxxx.
  0x40,0x00, // ......x.........
  //  '5' - 106
  0x20,0x0E, // .....x...xxx....
  0x10,0x74, // ....x.....x.xxx.
  0x08,0x44, // ...x......x...x.
  0x08,0x44, // ...x......x...x.
  0x08,0x44, // ...x......x...x.
  0x10,0x42, // ....x....x....x.
  0xE0,0x41, // .....xxxx.....x.
  //  '6' - 113
  0xE0,0x1F, // .....xxxxxxxx...
  0x10,0x22, // ....x....x...x..
  0x08,0x44, // ...x......x...x.
  0x08,0x44, // ...x......x...x.
  0x08,0x44, // ...x......x...x.
  0x10,0x22, // ....x....x...x..
  0xE0,0x11, // .....xxxx...x...
  //  '7' - 120
  0x00,0x40, // ..............x.
  0x00,0x40, // ..............x.
  0x38,0x40, // ...xxx........x.
  0xC0,0x43, // ......xxxx....x.
  0x00,0x4C, // ..........xx..x.
  0x00,0x70, // ............xxx.
  0x00,0x40, // ..............x.
  //  '8' - 127
  0xE0,0x18, // .....xxx...xx...
  0x10,0x25, // ....x...x.x..x..
  0x08,0x42, // ...x.....x....x.
  0x08,0x42, // ...x.....x....x.
  0x08,0x42, // ...x.....x....x.
  0x10,0x25, // ....x...x.x..x..
  0xE0,0x18, // .....xxx...xx...
  //  '9' - 134
  0x20,0x1E, // .....x...xxxx...
  0x10,0x21, // ....x...x....x..
  0x88,0x40, // ...x...x......x.
  0x88,0x40, // ...x...x......x.
  0x88,0x40, // ...x...x......x.
  0x10,0x21, // ....x...x....x..
  0xE0,0x1F, // .....xxxxxxxx...
  //  ':' - 141
  0x18,0x0C, // ...xx.....xx....
  0x18,0x0C, // ...xx.....xx....
  //  ';' - 143
  0x1A,0x0C, // .x.xx.....xx....
  0x1C,0x0C, // ..xxx.....xx....
  //  '<' - 145
  0x00,0x01, // ........x.......
  0x80,0x02, // .......x.x......
  0x80,0x02, // .......x.x......
  0x40,0x04, // ......x...x.....
  0x40,0x04, // ......x...x.....
  0x40,0x04, // ......x...x.....
  0x20,0x08, // .....x.....x....
  //  '=' - 152
  0x40,0x04, // ......x...x.....
  0x40,0x04, // ......x...x.....
  0x40,0x04, // ......x...x.....
  0x40,0x04, // ......x...x.....
  0x40,0x04, // ......x...x.....
  0x40,0x04, // ......x...x.....
  0x40,0x04, // ......x...x.....
  //  '>' - 159
  0x20,0x08, // .....x.....x....
  0x40,0x04, // ......x...x.....
  0x40,0x04, // ......x...x.....
  0x40,0x04, // ......x...x.....
  0x80,0x02, // .......x.x......
  0x80,0x02, // .......x.x......
  0x00,0x01, // ........x.......
  //  '?' - 166
  0x00,0x18, // ...........xx...
  0x00,0x20, // .............x..
  0x00,0x40, // ..............x.
  0xE8,0x40, // ...x.xxx......x.
  0x00,0x41, // ........x.....x.
  0x00,0x22, // .........x...x..
  0x00,0x1C, // ..........xxx...
  //  '@' - 173
  0xF0,0x03, // ....xxxxxx......
  0x08,0x0C, // ...x......xx....
  0x04,0x10, // ..x.........x...
  0xE2,0x21, // .x...xxxx....x..
  0x12,0x22, // .x..x....x...x..
  0x09,0x44, // x..x......x...x.
  0x09,0x48, // x..x.......x..x.
  0x09,0x48, // x..x.......x..x.
  0x11,0x48, // x...x......x..x.
  0xF9,0x44, // x..xxxxx..x...x.
  0x09,0x4F, // x..x....xxxx..x.
  0x09,0x20, // x..x.........x..
  0x12,0x20, // .x..x........x..
  0x22,0x18, // .x...x.....xx...
  0xC4,0x07, // ..x...xxxxx.....
  //  'A' - 188
  0x18,0x00, // ...xx...........
  0xE0,0x00, // .....xxx........
  0x80,0x07, // .......xxxx.....
  0x80,0x38, // .......x...xxx..
  0x80,0x40, // .......x......x.
  0x80,0x38, // .......x...xxx..
  0x80,0x07, // .......xxxx.....
  0xE0,0x00, // .....xxx........
  0x18,0x00, // ...xx...........
  //  'B' - 197
  0xF8,0x7F, // ...xxxxxxxxxxxx.
  0x08,0x42, // ...x.....x....x.
  0x08,0x42, // ...x.....x....x.
  0x08,0x42, // ...x.....x....x.
  0x08,0x42, // ...x.....x....x.
  0x08,0x42, // ...x.....x....x.
  0x08,0x42, // ...x.....x....x.
  0x10,0x65, // ....x...x.x..xx.
  0xE0,0x18, // .....xxx...xx...
  //  'C' - 206
  0xC0,0x0F, // ......xxxxxx....
  0x20,0x10, // .....x......x...
  0x10,0x20, // ....x........x..
  0x08,0x40, // ...x..........x.
  0x08,0x40, // ...x..........x.
  0x08,0x40, // ...x..........x.
  0x08,0x40, // ...x..........x.
  0x08,0x40, // ...x..........x.
  0x10,0x20, // ....x........x..
  0x20,0x10, // .....x......x...
  //  'D' - 216
  0xF8,0x7F, // ...xxxxxxxxxxxx.
  0x08,0x40, // ...x..........x.
  0x08,0x40, // ...x..........x.
  0x08,0x40, // ...x..........x.
  0x08,0x40, // ...x..........x.
  0x08,0x40, // ...x..........x.
  0x08,0x40, // ...x..........x.
  0x10,0x20, // ....x........x..
  0x20,0x10, // .....x......x...
  0xC0,0x0F, // ......xxxxxx....
  //  'E' - 226
  0xF8,0x7F, // ...xxxxxxxxxxxx.
  0x08,0x42, // ...x.....x....x.
  0x08,0x42, // ...x.....x....x.
  0x08,0x42, // ...x.....x....x.
  0x08,0x42, // ...x.....x....x.
  0x08,0x42, // ...x.....x....x.
  0x08,0x42, // ...x.....x....x.
  0x08,0x42, // ...x.....x....x.
  0x08,0x40, // ...x..........x.
  //  'F' - 235
  0xF8,0x7F, // ...xxxxxxxxxxxx.
  0x00,0x41, // ........x.....x.
  0x00,0x41, // ........x.....x.
  0x00,0x41, // ........x.....x.
  0x00,0x41, // ........x.....x.
  0x00,0x41, // ........x.....x.
  0x00,0x41, // ........x.....x.
  0x00,0x40, // ..............x.
  //  'G' - 243
  0xC0,0x0F, // ......xxxxxx....
  0x20,0x10, // .....x......x...
  0x10,0x20, // ....x........x..
  0x08,0x40, // ...x..........x.
  0x08,0x40, // ...x..........x.
  0x08,0x41, // ...x....x.....x.
  0x08,0x41, // ...x....x.....x.
  0x10,0x21, // ....x...x....x..
  0x20,0x11, // .....x..x...x...
  0xC0,0x01, // ......xxx.......
  //  'H' - 253
  0xF8,0x7F, // ...xxxxxxxxxxxx.
  0x00,0x02, // .........x......
  0x00,0x02, // .........x......
  0x00,0x02, // .........x......
  0x00,0x02, // .........x......
  0x00,0x02, // .........x......
  0x00,0x02, // .........x......
  0x00,0x02, // .........x......
  0xF8,0x7F, // ...xxxxxxxxxxxx.
  //  'I' - 262
  0xF8,0x7F, // ...xxxxxxxxxxxx.
  //  'J' - 263
  0x70,0x00, // ....xxx.........
  0x08,0x00, // ...x............
  0x08,0x00, // ...x............
  0x08,0x00, // ...x............
  0x08,0x00, // ...x............
  0xF0,0x7F, // ....xxxxxxxxxxx.
  //  'K' - 269
  0xF8,0x7F, // ...xxxxxxxxxxxx.
  0x80,0x00, // .......x........
  0x00,0x01, // ........x.......
  0x00,0x02, // .........x......
  0x00,0x07, // ........xxx.....
  0x80,0x08, // .......x...x....
  0x60,0x10, // .....xx.....x...
  0x10,0x20, // ....x........x..
  0x08,0x40, // ...x..........x.
  //  'L' - 278
  0xF8,0x7F, // ...xxxxxxxxxxxx.
  0x08,0x00, // ...x............
  0x08,0x00, // ...x............
  0x08,0x00, // ...x............
  0x08,0x00, // ...x............
  0x08,0x00, // ...x............
  0x08,0x00, // ...x............
  //  'M' - 285
  0xF8,0x7F, // ...xxxxxxxxxxxx.
  0x00,0x30, // ............xx..
  0x00,0x0C, // ..........xx....
  0x00,0x03, // ........xx......
  0xE0,0x00, // .....xxx........
  0x18,0x00, // ...xx...........
  0xE0,0x00, // .....xxx........
  0x00,0x03, // ........xx......
  0x00,0x0C, // ..........xx....
  0x00,0x30, // ............xx..
  0xF8,0x7F, // ...xxxxxxxxxxxx.
  //  'N' - 296
  0xF8,0x7F, // ...xxxxxxxxxxxx.
  0x00,0x20, // .............x..
  0x00,0x18, // ...........xx...
  0x00,0x04, // ..........x.....
  0x00,0x03, // ........xx......
  0x80,0x00, // .......x........
  0x60,0x00, // .....xx.........
  0x10,0x00, // ....x...........
  0xF8,0x7F, // ...xxxxxxxxxxxx.
  //  'O' - 305
  0xC0,0x0F, // ......xxxxxx....
  0x20,0x10, // .....x......x...
  0x10,0x20, // ....x........x..
  0x08,0x40, // ...x..........x.
  0x08,0x40, // ...x..........x.
  0x08,0x40, // ...x..........x.
  0x08,0x40, // ...x..........x.
  0x10,0x20, // ....x........x..
  0x20,0x10, // .....x......x...
  0xC0,0x0F, // ......xxxxxx....
  //  'P' - 315
  0xF8,0x7F, // ...xxxxxxxxxxxx.
  0x00,0x41, // ........x.....x.
  0x00,0x41, // ........x.....x.
  0x00,0x41, // ........x.....x.
  0x00,0x41, // ........x.....x.
  0x00,0x41, // ........x.....x.
  0x00,0x41, // ........x.....x.
  0x00,0x22, // .........x...x..
  0x00,0x1C, // ..........xxx...
  //  'Q' - 324
  0xC0,0x0F, // ......xxxxxx....
  0x20,0x10, // .....x......x...
  0x10,0x20, // ....x........x..
  0x08,0x40, // ...x..........x.
  0x08,0x40, // ...x..........x.
  0x28,0x40, // ...x.x........x.
  0x28,0x40, // ...x.x........x.
  0x10,0x20, // ....x........x..
  0x38,0x10, // ...xxx......x...
  0xE8,0x0F, // ...x.xxxxxxx....
  //  'R' - 334
  0xF8,0x7F, // ...xxxxxxxxxxxx.
  0x00,0x41, // ........x.....x.
  0x00,0x41, // ........x.....x.
  0x00,0x41, // ........x.....x.
  0x00,0x41, // ........x.....x.
  0x80,0x41, // .......xx.....x.
  0x60,0x41, // .....xx.x.....x.
  0x10,0x22, // ....x....x...x..
  0x08,0x1C, // ...x......xxx...
  //  'S' - 343
  0x20,0x18, // .....x.....xx...
  0x10,0x24, // ....x.....x..x..
  0x08,0x42, // ...x.....x....x.
  0x08,0x42, // ...x.....x....x.
  0x08,0x42, // ...x.....x....x.
  0x08,0x41, // ...x....x.....x.
  0x08,0x41, // ...x....x.....x.
  0x10,0x21, // ....x...x....x..
  0xE0,0x10, // .....xxx....x...
  //  'T' - 352
  0x00,0x40, // ..............x.
  0x00,0x40, // ..............x.
  0x00,0x40, // ..............x.
  0x00,0x40, // ..............x.
  0xF8,0x7F, // ...xxxxxxxxxxxx.
  0x00,0x40, // ..............x.
  0x00,0x40, // ..............x.
  0x00,0x40, // ..............x.
  0x00,0x40, // ..............x.
  //  'U' - 361
  0xE0,0x7F, // .....xxxxxxxxxx.
  0x10,0x00, // ....x...........
  0x08,0x00, // ...x............
  0x08,0x00, // ...x............
  0x08,0x00, // ...x............
  0x08,0x00, // ...x............
  0x08,0x00, // ...x............
  0x10,0x00, // ....x...........
  0xE0,0x7F, // .....xxxxxxxxxx.
  //  'V' - 370
  0x00,0x60, // .............xx.
  0x00,0x1C, // ..........xxx...
  0x80,0x03, // .......xxx......
  0x60,0x00, // .....xx.........
  0x18,0x00, // ...xx...........
  0x60,0x00, // .....xx.........
  0x80,0x03, // .......xxx......
  0x00,0x1C, // ..........xxx...
  0x00,0x60, // .............xx.
  //  'W' - 379
  0x00,0x70, // ............xxx.
  0x00,0x0E, // .........xxx....
  0xC0,0x01, // ......xxx.......
  0x38,0x00, // ...xxx..........
  0xC0,0x01, // ......xxx.......
  0x00,0x0E, // .........xxx....
  0x00,0x70, // ............xxx.
  0x00,0x0E, // .........xxx....
  0xC0,0x01, // ......xxx.......
  0x38,0x00, // ...xxx..........
  0xC0,0x01, // ......xxx.......
  0x00,0x0E, // .........xxx....
  0x00,0x70, // ............xxx.
  //  'X' - 392
  0x18,0x40, // ...xx.........x.
  0x20,0x20, // .....x.......x..
  0xC0,0x18, // ......xx...xx...
  0x00,0x05, // ........x.x.....
  0x00,0x02, // .........x......
  0x00,0x05, // ........x.x.....
  0xC0,0x18, // ......xx...xx...
  0x20,0x20, // .....x.......x..
  0x18,0x40, // ...xx.........x.
  //  'Y' - 401
  0x00,0x40, // ..............x.
  0x00,0x30, // ............xx..
  0x00,0x08, // ...........x....
  0x00,0x06, // .........xx.....
  0xF8,0x01, // ...xxxxxx.......
  0x00,0x06, // .........xx.....
  0x00,0x08, // ...........x....
  0x00,0x30, // ............xx..
  0x00,0x40, // ..............x.
  //  'Z' - 410
  0x08,0x00, // ...x............
  0x18,0x40, // ...xx.........x.
  0x68,0x40, // ...x.xx.......x.
  0x88,0x40, // ...x...x......x.
  0x08,0x43, // ...x....xx....x.
  0x08,0x44, // ...x......x...x.
  0x08,0x58, // ...x.......xx.x.
  0x08,0x60, // ...x.........xx.
  0x08,0x40, // ...x..........x.
  //  '[' - 419
  0xFF,0x7F, // xxxxxxxxxxxxxxx.
  0x01,0x40, // x.............x.
  0x01,0x40, // x.............x.
  //  '\' - 422
  0x00,0x60, // .............xx.
  0x00,0x1E, // .........xxxx...
  0xE0,0x01, // .....xxxx.......
  0x18,0x00, // ...xx...........
  //  ']' - 426
  0x01,0x40, // x.............x.
  0x01,0x40, // x.............x.
  0xFF,0x7F, // xxxxxxxxxxxxxxx.
  //  '^' - 429
  0x00,0x02, // .........x......
  0x00,0x0C, // ..........xx....
  0x00,0x30, // ............xx..
  0x00,0x40, // ..............x.
  0x00,0x30, // ............xx..
  0x00,0x0C, // ..........xx....
  0x00,0x02, // .........x......
  //  '_' - 436
  0x02,0x00, // .x..............
  0x02,0x00, // .x..............
  0x02,0x00, // .x..............
  0x02,0x00, // .x..............
  0x02,0x00, // .x..............
  0x02,0x00, // .x..............
  0x02,0x00, // .x..............
  0x02,0x00, // .x..............
  //  '`' - 444
  0x00,0x40, // ..............x.
  0x00,0x20, // .............x..
  //  'a' - 446
  0x70,0x02, // ....xxx..x......
  0x88,0x04, // ...x...x..x.....
  0x88,0x08, // ...x...x...x....
  0x88,0x08, // ...x...x...x....
  0x08,0x09, // ...x....x..x....
  0x10,0x09, // ....x...x..x....
  0xF8,0x07, // ...xxxxxxxx.....
  //  'b' - 453
  0xF8,0x7F, // ...xxxxxxxxxxxx.
  0x10,0x04, // ....x.....x.....
  0x08,0x08, // ...x.......x....
  0x08,0x08, // ...x.......x....
  0x08,0x08, // ...x.......x....
  0x10,0x04, // ....x.....x.....
  0xE0,0x03, // .....xxxxx......
  //  'c' - 460
  0xE0,0x03, // .....xxxxx......
  0x10,0x04, // ....x.....x.....
  0x08,0x08, // ...x.......x....
  0x08,0x08, // ...x.......x....
  0x08,0x08, // ...x.......x....
  0x10,0x04, // ....x.....x.....
  //  'd' - 466
  0xE0,0x03, // .....xxxxx......
  0x10,0x04, // ....x.....x.....
  0x08,0x08, // ...x.......x....
  0x08,0x08, // ...x.......x....
  0x08,0x08, // ...x.......x....
  0x10,0x04, // ....x.....x.....
  0xF8,0x7F, // ...xxxxxxxxxxxx.
  //  'e' - 473
  0xE0,0x03, // .....xxxxx......
  0x90,0x04, // ....x..x..x.....
  0x88,0x08, // ...x...x...x....
  0x88,0x08, // ...x...x...x....
  0x88,0x08, // ...x...x...x....
  0x90,0x04, // ....x..x..x.....
  0xA0,0x03, // .....x.xxx......
  //  'f' - 480
  0x00,0x08, // ...........x....
  0xF8,0x3F, // ...xxxxxxxxxxx..
  0x00,0x48, // ...........x..x.
  0x00,0x48, // ...........x..x.
  //  'g' - 484
  0xE2,0x03, // .x...xxxxx......
  0x11,0x04, // x...x.....x.....
  0x09,0x08, // x..x.......x....
  0x09,0x08, // x..x.......x....
  0x09,0x08, // x..x.......x....
  0x12,0x04, // .x..x.....x.....
  0xFC,0x0F, // ..xxxxxxxxxx....
  //  'h' - 491
  0xF8,0x7F, // ...xxxxxxxxxxxx.
  0x00,0x04, // ..........x.....
  0x00,0x08, // ...........x....
  0x00,0x08, // ...........x....
  0x00,0x08, // ...........x....
  0xF8,0x07, // ...xxxxxxxx.....
  //  'i' - 497
  0xF8,0x4F, // ...xxxxxxxxx..x.
  //  'j' - 498
  0x01,0x00, // x...............
  0x01,0x00, // x...............
  0xFE,0x4F, // .xxxxxxxxxxx..x.
  //  'k' - 501
  0xF8,0x7F, // ...xxxxxxxxxxxx.
  0x40,0x00, // ......x.........
  0x80,0x00, // .......x........
  0x80,0x01, // .......xx.......
  0x60,0x02, // .....xx..x......
  0x10,0x04, // ....x.....x.....
  0x08,0x08, // ...x.......x....
  //  'l' - 508
  0xF8,0x7F, // ...xxxxxxxxxxxx.
  //  'm' - 509
  0xF8,0x0F, // ...xxxxxxxxx....
  0x00,0x04, // ..........x.....
  0x00,0x08, // ...........x....
  0x00,0x08, // ...........x....
  0x00,0x08, // ...........x....
  0xF8,0x07, // ...xxxxxxxx.....
  0x00,0x04, // ..........x.....
  0x00,0x08, // ...........x....
  0x00,0x08, // ...........x....
  0x00,0x08, // ...........x....
  0xF8,0x07, // ...xxxxxxxx.....
  //  'n' - 520
  0xF8,0x0F, // ...xxxxxxxxx....
  0x00,0x04, // ..........x.....
  0x00,0x08, // ...........x....
  0x00,0x08, // ...........x....
  0x00,0x08, // ...........x....
  0xF8,0x07, // ...xxxxxxxx.....
  //  'o' - 526
  0xE0,0x03, // .....xxxxx......
  0x10,0x04, // ....x.....x.....
  0x08,0x08, // ...x.......x....
  0x08,0x08, // ...x.......x....
  0x08,0x08, // ...x.......x....
  0x10,0x04, // ....x.....x.....
  0xE0,0x03, // .....xxxxx......
  //  'p' - 533
  0xFF,0x0F, // xxxxxxxxxxxx....
  0x10,0x04, // ....x.....x.....
  0x08,0x08, // ...x.......x....
  0x08,0x08, // ...x.......x....
  0x08,0x08, // ...x.......x....
  0x10,0x04, // ....x.....x.....
  0xE0,0x03, // .....xxxxx......
  //  'q' - 540
  0xE0,0x03, // .....xxxxx......
  0x10,0x04, // ....x.....x.....
  0x08,0x08, // ...x.......x....
  0x08,0x08, // ...x.......x....
  0x08,0x08, // ...x.......x....
  0x10,0x04, // ....x.....x.....
  0xFF,0x0F, // xxxxxxxxxxxx....
  //  'r' - 547
  0xF8,0x0F, // ...xxxxxxxxx....
  0x00,0x04, // ..........x.....
  0x00,0x08, // ...........x....
  0x00,0x08, // ...........x....
  //  's' - 551
  0x10,0x07, // ....x...xxx.....
  0x88,0x08, // ...x...x...x....
  0x88,0x08, // ...x...x...x....
  0x88,0x08, // ...x...x...x....
  0x88,0x08, // ...x...x...x....
  0x70,0x04, // ....xxx...x.....
  //  't' - 557
  0x00,0x08, // ...........x....
  0xF8,0x3F, // ...xxxxxxxxxxx..
  0x08,0x08, // ...x.......x....
  0x08,0x08, // ...x.......x....
  //  'u' - 561
  0xF0,0x0F, // ....xxxxxxxx....
  0x08,0x00, // ...x............
  0x08,0x00, // ...x............
  0x08,0x00, // ...x............
  0x10,0x00, // ....x...........
  0xF8,0x0F, // ...xxxxxxxxx....
  //  'v' - 567
  0x00,0x0C, // ..........xx....
  0x00,0x03, // ........xx......
  0xE0,0x00, // .....xxx........
  0x18,0x00, // ...xx...........
  0xE0,0x00, // .....xxx........
  0x00,0x03, // ........xx......
  0x00,0x0C, // ..........xx....
  //  'w' - 574
  0x00,0x0C, // ..........xx....
  0xE0,0x03, // .....xxxxx......
  0x18,0x00, // ...xx...........
  0xE0,0x00, // .....xxx........
  0x00,0x03, // ........xx......
  0x00,0x0C, // ..........xx....
  0x00,0x03, // ........xx......
  0xE0,0x00, // .....xxx........
  0x18,0x00, // ...xx...........
  0xE0,0x03, // .....xxxxx......
  0x00,0x0C, // ..........xx....
  //  'x' - 585
  0x08,0x08, // ...x.......x....
  0x10,0x04, // ....x.....x.....
  0x60,0x03, // .....xx.xx......
  0x80,0x00, // .......x........
  0x60,0x03, // .....xx.xx......
  0x10,0x04, // ....x.....x.....
  0x08,0x08, // ...x.......x....
  //  'y' - 592
  0x00,0x0E, // .........xxx....
  0x81,0x01, // x......xx.......
  0x71,0x00, // x...xxx.........
  0x0E,0x00, // .xxx............
  0x70,0x00, // ....xxx.........
  0x80,0x03, // .......xxx......
  0x00,0x0C, // ..........xx....
  //  'z' - 599
  0x08,0x08, // ...x.......x....
  0x18,0x08, // ...xx......x....
  0x68,0x08, // ...x.xx....x....
  0x88,0x08, // ...x...x...x....
  0x08,0x0B, // ...x....xx.x....
  0x08,0x0C, // ...x......xx....
  0x08,0x08, // ...x.......x....
  //  '{' - 606
  0x80,0x00, // .......x........
  0x80,0x00, // .......x........
  0x7E,0x3F, // .xxxxxx.xxxxxx..
  0x01,0x40, // x.............x.
  0x01,0x40, // x.............x.
  //  '|' - 611
  0xFF,0x7F, // xxxxxxxxxxxxxxx.
  //  '}' - 612
  0x01,0x40, // x.............x.
  0x01,0x40, // x.............x.
  0x7E,0x3F, // .xxxxxx.xxxxxx..
  0x80,0x00, // .......x........
  0x80,0x00, // .......x........
  //  '~' - 617
  0x00,0x30, // ............xx..
  0x00,0x48, // ...........x..x.
  0x00,0x48, // ...........x..x.
  0x00,0x30, // ............xx..
};

const Font_TypeDef font_medium = {
	medium_first_char,
	medium_last_char,
	medium_height,
	medium_indexes,
	medium_bitmaps,
};

