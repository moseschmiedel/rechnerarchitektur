#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "eisvogel.h"

#define ENABLE_LOCAL_MAIN
#define DEBUG

#ifdef DEBUG
#include <stdio.h>
#endif

#define RED(h_idx, w_idx) (h_idx * width * 3) + (w_idx * 3) + 0
#define GREEN(h_idx, w_idx) (h_idx * width * 3) + (w_idx * 3) + 1
#define BLUE(h_idx, w_idx) (h_idx * width * 3) + (w_idx * 3) + 2

double S_x[3][3] = {{-1.0, 0.0, 1.0}, {-2.0, 0.0, 2.0}, {-1.0, 0.0, 1.0}};
double S_y[3][3] = {{-1.0, -2.0, -1.0}, {0.0, 0.0, 0.0}, {1.0, 2.0, 1.0}};

/**
 * `in_buffer` is rgb image with `height` and `width`
 * `out_buffer` needs to be as big as `height * width` of `in_buffer`
 */
void sobel(unsigned char *in_buffer, size_t width, size_t height,
           unsigned char *out_buffer) {
    for (unsigned int height_idx = 0; height_idx < height - 2; ++height_idx) {
        for (unsigned int width_idx = 0; width_idx < width - 2; ++width_idx) {
            double G_x =
                (S_x[0][0] * in_buffer[RED(height_idx, width_idx)]) +
                (S_x[0][1] * in_buffer[RED(height_idx, width_idx + 1)]) +
                (S_x[0][2] * in_buffer[RED(height_idx, width_idx + 2)]) +
                (S_x[1][0] * in_buffer[RED(height_idx + 1, width_idx)]) +
                (S_x[1][1] * in_buffer[RED(height_idx + 1, width_idx + 1)]) +
                (S_x[1][2] * in_buffer[RED(height_idx + 1, width_idx + 2)]) +
                (S_x[2][0] * in_buffer[RED(height_idx + 2, width_idx)]) +
                (S_x[2][1] * in_buffer[RED(height_idx + 2, width_idx + 1)]) +
                (S_x[2][2] * in_buffer[RED(height_idx + 2, width_idx + 2)]);

            double G_y =
                (S_y[0][0] * in_buffer[RED(height_idx, width_idx)]) +
                (S_y[0][1] * in_buffer[RED(height_idx, width_idx + 1)]) +
                (S_y[0][2] * in_buffer[RED(height_idx, width_idx + 2)]) +
                (S_y[1][0] * in_buffer[RED(height_idx + 1, width_idx)]) +
                (S_y[1][1] * in_buffer[RED(height_idx + 1, width_idx + 1)]) +
                (S_y[1][2] * in_buffer[RED(height_idx + 1, width_idx + 2)]) +
                (S_y[2][0] * in_buffer[RED(height_idx + 2, width_idx)]) +
                (S_y[2][1] * in_buffer[RED(height_idx + 2, width_idx + 1)]) +
                (S_y[2][2] * in_buffer[RED(height_idx + 2, width_idx + 2)]);

            out_buffer[(height_idx * width) + width_idx] =
                (unsigned char)sqrt((G_x * G_x) + (G_y * G_y));
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

    unsigned char greyscale_image[height * width];

    sobel(eisvogel_data, width, height, greyscale_image);

#ifdef DEBUG
    write_ppm_file("./sobel.ppm", greyscale_image, width, height);
#endif

    return EXIT_SUCCESS;
}
#endif
