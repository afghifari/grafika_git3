from PIL import Image, ImageEnhance, ImageFont
import string


img = Image.open("credit.png")
img = img.convert('RGB')
px = img.load()
strttf = ""

for x in range(img.width):
    for y in range(img.height):
        r,g,b = px[x,y]
        strttf += chr(r) + chr(g) + chr(b)
            
fttf = open('credit','w')
fttf.write(strttf)
fttf.close()
