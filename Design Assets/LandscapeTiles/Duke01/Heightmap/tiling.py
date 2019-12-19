import os

size = 8

for x in range(size):
    for y in range(size):
        os.rename(("tiles/terrain_" + str(x * size + y) + ".raw"), ("tiles/terrain_x" + str(x) + "_y" + str(y) + ".r16"))

# 1017 tiles
# $ convert heightmap.png -extent 8136x8136 -background black -endian LSB -depth 16 gray:output.raw -crop 8x8@ -rotate -90 +repage -endian LSB -depth 16 gray:tiles/terrain_%d.raw

# 1009 tiles (use this)
# $ convert heightmap.png -extent 8072x8072 -background black -endian LSB -depth 16 gray:output.raw -crop 8x8@ -rotate -90 +repage -endian LSB -depth 16 gray:tiles/terrain_%d.raw