# Simple (naive) font baking utility

Convert TrueType fonts to an image and store Glyph metrics fore easy rendering with OpenGL (or something else)

## Build
```
mkdir build
cd build
cmake ..
make
```

## Run
```
./baker font.ttf
```

## Output
* `out.png` font atlas image
* `out.csv` csv file with char code, texture postition and dimensions, advance and horizontal and vertical bearing.

## Dependencies
* `lodepng`: provided
* `FreeType2`: CMake will look for it. Install with your package manager or provide it manually in `CMakeLists.txt`
