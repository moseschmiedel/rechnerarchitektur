#include "eisvogel.h"
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1

const int S_x[3][3] = {{1, 0, -1}, {2, 0, -2}, {1, 0, -1}};
const int S_y[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};

/**
 * `in_buffer` is rgb image with `height` and `width`
 * `out_buffer` needs to be as big as `height * width` of `in_buffer`
 */
void sobel(const unsigned char *in_buffer, size_t width, size_t height,
           unsigned char *out_buffer) {
    for (unsigned int idx = 0; idx < height * width; ++idx) {
        const size_t in_idx = idx * 3;
        const unsigned char G_x =
            abs((S_x[0][0] * in_buffer[in_idx]) +
                (S_x[0][1] * in_buffer[in_idx + 3]) +
                (S_x[0][2] * in_buffer[in_idx + 6]) +
                (S_x[1][0] * in_buffer[in_idx + (width * 3)]) +
                (S_x[1][1] * in_buffer[in_idx + (width * 3) + 3]) +
                (S_x[1][2] * in_buffer[in_idx + (width * 3) + 6]) +
                (S_x[2][0] * in_buffer[in_idx + (width * 6)]) +
                (S_x[2][1] * in_buffer[in_idx + (width * 6) + 3]) +
                (S_x[2][2] * in_buffer[in_idx + (width * 6) + 6]));

        const unsigned char G_y =
            abs((S_y[0][0] * in_buffer[in_idx]) +
                (S_y[0][1] * in_buffer[in_idx + 3]) +
                (S_y[0][2] * in_buffer[in_idx + 6]) +
                (S_y[1][0] * in_buffer[in_idx + (width * 3)]) +
                (S_y[1][1] * in_buffer[in_idx + (width * 3) + 3]) +
                (S_y[1][2] * in_buffer[in_idx + (width * 3) + 6]) +
                (S_y[2][0] * in_buffer[in_idx + (width * 6)]) +
                (S_y[2][1] * in_buffer[in_idx + (width * 6) + 3]) +
                (S_y[2][2] * in_buffer[in_idx + (width * 6) + 6]));

        out_buffer[idx] = (unsigned char)sqrt(pow(G_x, 2) + pow(G_y, 2));
    }
}

#ifdef DEBUG
void write_ppm_file(char *path, unsigned char *img_buffer, unsigned int width,
                    unsigned int height) {
    FILE *fp;
    fp = fopen(path, "wb");
    if (fp == NULL) {
        perror("Error while opening output file");
        exit(1);
    }
    const char *comment = "# image with sobel filter applied";
    fprintf(fp, "P5\n%s\n%d %d\n%d\n", comment, width, height, 255);
    fwrite(img_buffer, width * height, 1, fp);
    if (ferror(fp)) {
        perror("Error while writing output file");
    }
    fclose(fp);
}
#endif

int main(int argc, char *argv[]) {
    unsigned char final_image[eisvogel.width * eisvogel.height];

    double start;
    double end;
    start = omp_get_wtime();
    for (size_t i = 0; i < 100; ++i) {
        sobel(eisvogel.pixel_data, eisvogel.width, eisvogel.height,
              final_image);
    }
    end = omp_get_wtime();
    printf("%.9f,omp_wtime\n", end-start);

#ifdef DEBUG
    printf("Writing output file...\n");
    char* filename = "sobel.ppm";
    if (argc >= 2) {
        filename = argv[1];
    }
    write_ppm_file(filename, final_image, eisvogel.width, eisvogel.height);
    printf("Wrote output file.\n");
#endif

    return EXIT_SUCCESS;
}
