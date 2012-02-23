from Code128 import Code128

# mm = (pixels * 25.4) / dpi
# px = (mm * dpi) / 25.4

if __name__ == "__main__":
    fmt = "png"
    width, height = 142, 74 # 50 x 26 mm

    str_fmt = "0000{0}LV"

    range_begin = 62519
    range_end   = 63619 + 1

    for i in range(range_begin, range_end):
        code = str_fmt.format(i)
        bar = Code128()
        bar.getImage(code, width, height, fmt)

