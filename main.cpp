#include "lodepng.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>
#include <fstream>

using namespace std;

// Change these to your liking
#define WIDTH 128
#define HEIGHT 128
#define START 32
#define END 127 // <
#define SIZE 16 // font size in px

int main(int argc, char **argv)
{
    FT_Library ft;
    FT_Face face;
    FT_GlyphSlot slot;
    FT_Error error;

    if (argc < 2)
        return 1;

    // TODO: error handling
    error = FT_Init_FreeType(&ft);
    error = FT_New_Face(ft, argv[1], 0, &face);
    error = FT_Set_Pixel_Sizes(face, 0, SIZE);

    // Allocate image
    vector<unsigned char> image;
    image.resize(WIDTH * HEIGHT);

    FT_Int x = 0;
    FT_Int y = 0;
    FT_Int m_height = 0;

    // Alias
    slot = face->glyph;

    // Write header
    ofstream out{"out.csv"};
    out << "charcode,x,y,width,height,advance,bearingx,bearingy\n";

    for (int c = START; c < END; ++c)
    {
        error = FT_Load_Char(face, c, FT_LOAD_RENDER);
        if (error)
            continue;

        FT_Int i, j, p, q;

        int width = slot->bitmap.width;
        int height = slot->bitmap.rows;

        FT_Int x_max = x + width;
        if (x_max >= WIDTH)
        {
            x_max -= x;
            x = 0;
            y += m_height;
            m_height = 0;
        }

        if (height > m_height)
            m_height = height;

        FT_Int y_max = y + height;
        if (y_max >= HEIGHT)
        {
            cout << "Too much text!\n";
            break;
        }

        for (i = x, p = 0; i < x_max; ++i, ++p)
            for (j = y, q = 0; j < y_max; ++j, ++q)
                image[j * WIDTH + i] =
                    slot->bitmap.buffer[q * width + p];

        // x, y: tex pos
        // width, height: tex/glyph width, height
        // advance: pixels to the next value
        long advance = slot->advance.x / 64;

        // bearing: offset from origin on baseline
        int bearingX = slot->bitmap_left;
        int bearingY = slot->bitmap_top;

        // Write to file
        out << c << ',' << x << ',' << y << ',' << width << ','
            << height << ',' << advance << ',' << bearingX << ','
            << bearingY << '\n';

        // goto next glyph
        x += width;
    }

    unsigned pngerr = lodepng::encode("out.png", image, WIDTH, HEIGHT,
                                     LCT_GREY);
    if(pngerr)
    {
        std::cout << "encoder error " << error << ": "
                  << lodepng_error_text(error) << std::endl;
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}
