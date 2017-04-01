def Write_String( first_char, last_char ):
    s = ''
    for i in range(ord(first_char), ord(last_char)+1):
        s = s + chr(i)
    file = open('string.txt','w')
    file.write(s)
    file.close()
    return



class BitMap:
    def Load_File(self):
        file = open('./bitmaps/'+self.filename+'.bmp','rb')
        data = file.read()
        file.close()

        if 0: # print header info
            print('BitMapFileHeader:')
            for b in data[0:13]:
                 print( b )
            print('BitMapInfo:')
            for b in data[14:31]:
                print( b )

        # read header
        offset = data[10]
        if data[14] == 12: # core header
            width = data[18]+data[19]*256
            height = data[20]+data[21]*256
            bpp = data[26]
        else: # extended header
            width = data[18]+data[19]*256
            height = data[22]+data[23]*256
            bpp = data[28]

        if 1:
            print('  Width:', width)
            print(' Height:', height)
            print(' Bit/px:', bpp)
            print()

        self.width = width
        self.height = height
        self.bpp = bpp
        self.bitmap = [[0 for y in range(height)] for x in range(width)]

        if bpp == 1: # monochrome 

            bit_width = width # pending bytes compensation
            if bit_width % 32:
                bit_width = ((bit_width//32) + 1)*32
            byte_width = int(bit_width/8)
            for y in range(height):
                pixel_line = data[(offset+byte_width*y):(offset+byte_width*(y+1))]
                for x in range(width):
                    byte_num = x//8;
                    bit_num = x % 8;
                    if pixel_line[byte_num]  & ( (1<<7)>>bit_num ):
                        self.bitmap[x][height-y-1] = 1;
                    else:
                        self.bitmap[x][height-y-1] = 0;
                
        elif bpp == 24: # full-color
            
            byte_width = width*3 # pending bytes compensation
            if byte_width % 4:
                byte_width = ((byte_width//4) + 1)*4
            
            for y in range(height):
                s = ""
                for x in range(width):
                    ind = y*byte_width + x*3 + offset
                    if (data[ind] > 0) | (data[ind+1] > 0) | (data[ind+2] > 0):
                        self.bitmap[x][height-y-1] = 1;
                    else:
                        self.bitmap[x][height-y-1] = 0;
        else:
            print('Unknown image format')
            return

        
        if 0: # display loaded image
            for y in range(height):
                s = ''
                for x in range(width):
                    if (self.bitmap[x][y]):
                        s = s + 'X'
                    else:
                        s = s + '-'
                print(s)
             
        return
        


    def Separate_Chars(self):
        char_counter = 0
        char_width = 0
        list_char_bitmap = []
        list_char_width = []
        char_bitmap = []
        
        for col in self.bitmap:
            col_not_empty = 0
            if col.count(1) > 0:
                col_not_empty = 1
            if col_not_empty == 1:
                char_bitmap.append(col)
                char_width = char_width + 1
            else:
                if char_bitmap != []: # char bitmap done
                    list_char_bitmap.append(char_bitmap)
                    list_char_width.append(char_width)
                    char_counter = char_counter + 1
                    char_bitmap = []
                    char_width = 0

        list_char_position = [0]
        for i in range(1,len(list_char_width)+1):
            list_char_position.append( list_char_position[i-1] + list_char_width[i-1] )

        self.char_bitmap = list_char_bitmap
        self.char_width = list_char_width
        self.char_position = list_char_position

        self.height_bytes = ((self.height-1)//8) # fonts have one invisible line at the bottom
        if ((self.height-1)%8):
            self.height_bytes = self.height_bytes + 1


        return

    def Save_Font(self):

        file = open('./c_files/font_'+self.filename+'.c','w')

        file.write('const uint16_t '+self.filename+'_indexes[] = {\n')
        for i in range(len(self.char_position)):
            s = '  ' + str(self.char_position[i]) + ', // \'' + chr( ord(self.first_char)+i ) + '\''
            file.write(s + '\n')
        file.write('};\n\n') 

        self.last_char = chr( ord(self.first_char) + len(self.char_width) - 1 )

        file.write('const char '+self.filename+'_first_char' + ' = ')
        file.write( '\'' + self.first_char + '\'' + ';\n')
        file.write('const char '+self.filename+'_last_char' + ' = ')
        file.write( '\'' + self.last_char + '\'' + ';\n')
        file.write('const uint8_t '+self.filename+'_height' + ' = ' + str(self.height_bytes) + ';\n\n')

        file.write('const uint8_t '+self.filename+'_bitmaps[] = {\n')
  
        i = 0;
        for single_char_bitmap in self.char_bitmap:
            # process single char
            s = '  //  \'' + chr( ord(self.first_char)+i ) + '\' - '
            s = s + str(self.char_position[i])
            print(s);  file.write(s + '\n')
            for col in single_char_bitmap:
                col.reverse()
                col.pop(0)
                s = ''
                s0 = '  '
                hex_value = 0

  
                for d in range(len(col)):
                    if col[d] == 1:
                        hex_value = hex_value+(1<<d)
                        s = s + 'x'
                    else:
                        s = s + '.'
                for b in range(self.height_bytes):
                    hex_byte = hex_value % 256;
                    hex_value = hex_value // 256
                    s0 = s0 + '0x{:02X},'.format(hex_byte)
                s = s0 + ' // ' + s      
                
                print(s);  file.write(s + '\n')
            i = i + 1

        file.write('};\n\n')

        s = ''

        s = s + 'const Font_TypeDef font_' + self.filename + ' = {\n'
        s = s + '\t' + self.filename +'_first_char,\n'
        s = s + '\t' + self.filename +'_last_char,\n'
        s = s + '\t' + self.filename +'_height,\n'
        s = s + '\t' + self.filename +'_indexes,\n'
        s = s + '\t' + self.filename +'_bitmaps,\n'
        s = s + '};\n\n'

        file.write(s)
        file.close()
        

    def Save_Image(self):

        file = open('./c_files/image_'+self.filename+'.c','w')
        file.write('const uint8_t image_'+self.filename+'[] = {\n')
  
        self.height_bytes = (self.height//8)
        if (self.height%8):
            self.height_bytes = self.height_bytes + 1

        s = '  ' + str(self.width) + ', // width \n'
        file.write(s)
        s = '  ' + str(self.height_bytes) + ', // height(bytes) \n'
        file.write(s)

        for col in self.bitmap:
            col.reverse()
            s = ''
            s0 = '  '
            hex_value = 0
            for d in range(len(col)):
                if col[d] == 1:
                    hex_value = hex_value+(1<<d)
                    s = s + 'x'
                else:
                    s = s + '.'
            for b in range(self.height_bytes):
                hex_byte = hex_value % 256;
                hex_value = hex_value // 256
                s0 = s0 + '0x{:02X},'.format(hex_byte)
            s = s0 + ' // ' + s      
                
            print(s);  file.write(s + '\n')
   
        s = '};\n\n'

        file.write(s)
        file.close()














