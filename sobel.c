#include <bits/time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define IMG_INDEX(w_idx, h_idx) (((h_idx)*width) + (w_idx))
#define RED(w_idx, h_idx) (((h_idx)*width * 3) + ((w_idx)*3) + 0)
#define GREEN(w_idx, h_idx) (((h_idx)*width * 3) + ((w_idx)*3) + 1)
#define BLUE(w_idx, h_idx) (((h_idx)*width * 3) + ((w_idx)*3) + 2)

const int S_x[3][3] = {{1, 0, -1}, {2, 0, -2}, {1, 0, -1}};
const int S_y[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};

/**
 * `in_buffer` is rgb image with `height` and `width`
 * `out_buffer` needs to be as big as `height * width` of `in_buffer`
 */
void sobel(unsigned char *in_buffer, size_t width, size_t height,
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
    size_t width = 128;
    size_t height = 85;
    char *in_path = "eisvogel.data";
    char *out_path = "sobel.ppm";
    if (argc == 5) {
        width = atoi(argv[1]);
        height = atoi(argv[2]);
        in_path = argv[3];
        out_path = argv[4];
    }

    unsigned char *final_image = calloc(width * height, 1);

    unsigned char *img = calloc(width * height * 3, 1);

    printf("Reading input file...\n");
    FILE *fp;
    fp = fopen(in_path, "rb");
    for (size_t idx = 0; idx < height; ++idx) {
        unsigned char *img_line = calloc(width * 3, 1);
        if (img_line == NULL) {
            perror("Could not allocate 'img_line'");
            exit(1);
        }
        fread(img_line, sizeof(unsigned char), width * 3, fp);
        if (ferror(fp)) {
            perror("Error while reading input file");
            exit(1);
        }
        memcpy(img + (idx * width * 3), img_line,
               sizeof(unsigned char) * width * 3);
    }
    fclose(fp);
    printf("Read input file.\n");

    printf("Compute sobel filter...\n");
    struct timespec start;
    struct timespec end;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    sobel(img, width, height, final_image);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    printf("Computed sobel filter.\n");
    double time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;
    printf("sobel took %.9f seconds\n", time_taken);

#ifdef DEBUG
    printf("Writing output file...\n");
    write_ppm_file(out_path, final_image, width, height);
    printf("Wrote output file.\n");
#endif

    return EXIT_SUCCESS;
}
