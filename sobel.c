#include <stdlib.h>
#include <string.h>

#include "eisvogel2.h"

#define ENABLE_LOCAL_MAIN
#define DEBUG

#ifdef DEBUG
#include <stdio.h>
#endif

/**
 * out_buffer needs to be as big as height * width of in_img
 */
void sobel(unsigned char *in_buffer, size_t width, size_t height,
           unsigned char *out_buffer) {
    size_t max_height = height * width;
    for (unsigned int height_idx = 0; height_idx < max_height;
         height_idx += width) {
        for (unsigned int width_idx = 0; width_idx < width; ++width_idx) {
            out_buffer[height_idx + width_idx] =
                (in_buffer[height_idx + (width_idx * 3) + 0] * 100 /
                 470) + // red
                (in_buffer[height_idx + (width_idx * 3) + 1] * 100 /
                 140) + // green
                (in_buffer[height_idx + (width_idx * 3) + 2] * 100 / 138) %
                    256; // blue
        }
    }
}

#ifdef DEBUG
void write_ppm_file(char *path, unsigned char *img_buffer, unsigned int width,
                    unsigned int height) {
    FILE *fp;
    fp = fopen(path, "wb");
    const char *comment = "# image with sobel filter applied";
    fprintf(fp, "P5\n %s\n %d %d\n %d\n", comment, width, height, 255);
    fwrite(img_buffer, width * height, 1, fp);
    fclose(fp);
}
#endif

#ifdef ENABLE_LOCAL_MAIN
int main() {
    size_t width = 128;
    size_t height = 85;

    unsigned char final_image[height * width];

    sobel(eisvogel_data, width, height, final_image);

#ifdef DEBUG
    write_ppm_file("./sobel.ppm", final_image, width, height);
#endif

    return EXIT_SUCCESS;
}
#endif
