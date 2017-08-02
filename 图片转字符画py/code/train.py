#!/usr/bin/env python
# coding=utf-8
from PIL import Image
import argparse

ascii_char = list(r"!^JKL23486_+)(>>\\<,/\‘\’\“)@#$%^&*(_+-=,.?/\":\;{}[]\\|\")")


def get_char(r,g,b, alpha = 256):
    if alpha == 0:
        return ' '
    length = len(ascii_char)
    # 灰度公式
    gray = int(0.216*r + 0.7152*g + 0.0722*b)

    unit = (256.0+1)/length;
    return ascii_char[int(gray/unit)]



def CIL():
    parser = argparse.ArgumentParser()
    parser.add_argument('file')
    parser.add_argument('-o', '--output')
    parser.add_argument('--width', type=int, default= 80)
    parser.add_argument('--height', type=int, default=80)    
    args = parser.parse_args()
    return args

def tran(args):
    IMG = args.file
    WIDTH = args.width
    HEIGHT = args.height
    OUTPUT = args.output

    im = Image.open(IMG)
    im = im.resize((WIDTH, HEIGHT), Image.NEAREST)

    txt = ""
    for i in range(HEIGHT):
        for j in range(WIDTH):
            txt += get_char(*im.getpixel((j,i)))
        txt += '\n'
    print(txt)

    if (OUTPUT):
        with open(OUTPUT, "w") as f:
            f.write(txt)
    else:
        with open('../result/output.txt', 'w') as f:
            f.write(txt)


tran(CIL())
