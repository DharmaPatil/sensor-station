import bitmap

b = bitmap.BitMap()
b.filename = 'times'
b.Load_File()

if 1: 
    b.Separate_Chars()
    b.first_char = '+' # '!' or '+'
    b.Save_Font()
else:
    b.Save_Image()

#bitmap.Write_String('!','~')
