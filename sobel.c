#include <math.h>
#include <stdlib.h>
#include <string.h>

#define ENABLE_LOCAL_MAIN
#define DEBUG

#ifdef DEBUG
#include <stdio.h>
#endif

#define IMG_INDEX(w_idx, h_idx) (h_idx * width) + w_idx
#define RED(w_idx, h_idx) (h_idx * width * 3) + (w_idx * 3) + 0
#define GREEN(w_idx, h_idx) (h_idx * width * 3) + (w_idx * 3) + 1
#define BLUE(w_idx, h_idx) (h_idx * width * 3) + (w_idx * 3) + 2

double S_x[3][3] = {{1.0, 0.0, -1.0}, {2.0, 0.0, -2.0}, {1.0, 0.0, -1.0}};
double S_y[3][3] = {{1.0, 2.0, 1.0}, {0.0, 0.0, 0.0}, {-1.0, -2.0, -1.0}};

/**
 * `in_buffer` is rgb image with `height` and `width`
 * `out_buffer` needs to be as big as `height * width` of `in_buffer`
 */
void sobel(unsigned char *in_buffer, size_t width, size_t height,
           unsigned char *out_buffer) {
    for (unsigned int width_idx = 0; width_idx < width - 0; ++width_idx) {
        for (unsigned int height_idx = 0; height_idx < height - 0;
             ++height_idx) {
            double G_x =
                (S_x[0][0] * in_buffer[RED(width_idx, height_idx)]) +
                (S_x[0][1] * in_buffer[RED(width_idx, height_idx + 1)]) +
                (S_x[0][2] * in_buffer[RED(width_idx, height_idx + 2)]) +
                (S_x[1][0] * in_buffer[RED(width_idx + 1, height_idx)]) +
                (S_x[1][1] * in_buffer[RED(width_idx + 1, height_idx + 1)]) +
                (S_x[1][2] * in_buffer[RED(width_idx + 1, height_idx + 2)]) +
                (S_x[2][0] * in_buffer[RED(width_idx + 2, height_idx)]) +
                (S_x[2][1] * in_buffer[RED(width_idx + 2, height_idx + 1)]) +
                (S_x[2][2] * in_buffer[RED(width_idx + 2, height_idx + 2)]);

            double G_y =
                (S_y[0][0] * in_buffer[RED(width_idx, height_idx)]) +
                (S_y[0][1] * in_buffer[RED(width_idx, height_idx + 1)]) +
                (S_y[0][2] * in_buffer[RED(width_idx, height_idx + 2)]) +
                (S_y[1][0] * in_buffer[RED(width_idx + 1, height_idx)]) +
                (S_y[1][1] * in_buffer[RED(width_idx + 1, height_idx + 1)]) +
                (S_y[1][2] * in_buffer[RED(width_idx + 1, height_idx + 2)]) +
                (S_y[2][0] * in_buffer[RED(width_idx + 2, height_idx)]) +
                (S_y[2][1] * in_buffer[RED(width_idx + 2, height_idx + 1)]) +
                (S_y[2][2] * in_buffer[RED(width_idx + 2, height_idx + 2)]);

            out_buffer[IMG_INDEX(width_idx, height_idx)] =
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
    if (ferror(fp)) {
        perror("Error while writing output file");
    }
    fclose(fp);
}
#endif

#ifdef ENABLE_LOCAL_MAIN
int main(int argc, char *argv[]) {
    size_t width = 128;
    size_t height = 85;
    char *in_path = "eisvogel.data";
    char *out_path = "./sobel.ppm";
    if (argc == 4) {
        width = atoi(argv[1]);
        height = atoi(argv[2]);
        in_path = argv[3];
        out_path = argv[4];
    }

    unsigned char final_image[width * height];

    unsigned char img[width * height * 3];

    printf("Reading input file...\n");
    FILE *fp;
    fp = fopen(in_path, "rb");
    for (size_t idx = 0; idx < height; ++idx) {
        unsigned char img_line[width];
        fread(img_line, sizeof(unsigned char), width * 3, fp);
        if (ferror(fp)) {
            perror("Error while reading input file");
            break;
        }
        memcpy(&img[idx * width * 3], &img_line,
               sizeof(unsigned char) * width * 3);
    }
    fclose(fp);
    printf("Read input file.\n");

    printf("Compute sobel filter...\n");
    sobel(img, width, height, final_image);
    printf("Computed sobel filter.\n");

#ifdef DEBUG
    printf("Writing output file...\n");
    write_ppm_file(out_path, final_image, width, height);
    printf("Wrote output file.\n");
#endif

    return EXIT_SUCCESS;
}
#endif
