#include "pngparser.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define ARG_SIZE 255

/* This filter iterates over the image and calculates the average value of the
 * color channels for every pixel This value is then written to all the channels
 * to get the grayscale representation of the image
 */
void filter_grayscale(struct image *img, void *weight_arr) {
  // printf("[exec grayscale]\n");
  struct pixel(*image_data)[img->size_x] =
      (struct pixel(*)[img->size_x])
          img->px; // a pointer of an array of pixel of size_x
  double *weights = (double *)weight_arr;

  /* BUG!
   * This bug isn't graded.
   *
   * FIX: Initialize both variables to 0.
   * YHY: Fixed! (but receives a TIME_OUT??)
   */
  for (unsigned short i = 0; i < img->size_y; i++) {
    for (unsigned short j = 0; j < img->size_x; j++) {
      // printf("[filter_grayscale] i = %d, j = %d\n", i , j);
      double luminosity = 0;

      luminosity += weights[0] * image_data[i][j].red;
      luminosity += weights[1] * image_data[i][j].green;
      luminosity += weights[2] * image_data[i][j].blue;

      image_data[i][j].red = (uint8_t)luminosity;
      image_data[i][j].green = (uint8_t)luminosity;
      image_data[i][j].blue = (uint8_t)luminosity;
    }
  }
}

/* This filter blurs an image. The larger the radius, the more noticeable the
 * blur.
 *
 * For every pixel we define a square of side 2*radius+1 centered around it.
 * The new value of the pixel is the average value of all pixels in the square.
 *
 * Pixels of the square which fall outside the image do not count towards the
 * average. They are ignored (e.g. 5x5 box will turn into a 3x3 box in the
 * corner).
 *
 */
void filter_blur(struct image *img, void *r) {
  struct pixel(*image_data)[img->size_x] =
      (struct pixel(*)[img->size_x])img->px;
  int num_pixels = 0;

  int radius = *((int *)r);
  if (radius < 0) {
    radius = 0;
  }

  if (radius >= img->size_x && radius >= img->size_y) {
    if (img->size_x > img->size_y)
      radius = img->size_x;
    else
      radius = img->size_y;
  }

  struct pixel(*new_data)[img->size_x] =
      malloc(sizeof(struct pixel) * img->size_x *
             img->size_y); // new_data is a pointer to an array of row_size =
                           // img->size_x number of pixels

  if (!new_data) {
    return;
  }

  /* We iterate over all pixels */
  for (long i = 0; (i < img->size_y); i++) {
    for (long j = 0; j < img->size_x; j++) {

      unsigned red = 0, green = 0, blue = 0, alpha = 0;
      /* We iterate over all pixels in the square */

      // [BUG FOUND - HEAP UNDERFLOW]
      num_pixels = 0;

      for (long y_offset = -radius; y_offset <= radius; y_offset++) {
        for (long x_offset = -radius; x_offset <= radius; x_offset++) {
          int inFlag = 1; // check whether this pixel is in the image or not
          long yi = i + y_offset;
          long xi = j + x_offset;

          if (yi < 0) {
            yi = 0;
            inFlag = 0;
          } else if (yi >= img->size_y) {
            yi = img->size_y - 1;
            inFlag = 0;
          }

          if (xi < 0) {
            xi = 0;
            inFlag = 0;
          } else if (xi >= img->size_x) {
            xi = img->size_x - 1;
            inFlag = 0;
          }

          /* BUG!
           * This bug isn't graded.
           *
           * FIX: Limit reads only to valid memory
           */
          struct pixel current = image_data[yi][xi];

          if (inFlag) {
            num_pixels++;
            red += current.red;
            blue += current.blue;
            green += current.green;
            alpha += current.alpha;
          }
        }
      }

      /* Calculate the average */
      red /= num_pixels;
      green /= num_pixels;
      blue /= num_pixels;
      alpha /= num_pixels;

      /* Assign new values */
      new_data[i][j].red = red;
      new_data[i][j].green = green;
      new_data[i][j].blue = blue;
      new_data[i][j].alpha = alpha;
    }
  }

  /* [Bug FOUND] - Local persistence */
  free(img->px);
  img->px = (struct pixel *)new_data;
  return;
}

/* We allocate and return a pixel */
// [BUG FIXED] Local Persistent
struct pixel *get_pixel() {

  struct pixel *px = malloc(sizeof(struct pixel));
  if (px == NULL) {
    printf("Couldn't allocate memory");
  }
  return px;

  // struct pixel px;
  // return &px;
}

/* This filter just negates every color in the image */
// void filter_negative(struct image *img, void *noarg) {
void filter_negative(struct image *img) {
  struct pixel(*image_data)[img->size_x] =
      (struct pixel(*)[img->size_x])img->px;

  /* Iterate over all the pixels */
  //[BUG FIXED] - Iteration error
  //[BUG FIXED] - Heap overflow/ Memory Leak
  struct pixel *neg = get_pixel();
  for (long i = 0; i < img->size_y; i++) {
    for (long j = 0; j < img->size_x; j++) {

      struct pixel current = image_data[i][j];

      /* The negative is just the maximum minus the current value */
      neg->red = 255 - current.red;
      neg->green = 255 - current.green;
      neg->blue = 255 - current.blue;
      neg->alpha = current.alpha;

      /* Write it back */
      image_data[i][j] = *neg;
    }
  }
  free(neg);
}

/* Set the transparency of the picture to the value (0-255) passed as argument
 */
void filter_transparency(struct image *img, void *transparency) {
  struct pixel(*image_data)[img->size_x] =
      (struct pixel(*)[img->size_x])img->px;
  uint8_t local_alpha = *((uint8_t *)transparency);

  /* Iterate over all pixels */
  for (long i = 0; i < img->size_y; i++) {
    for (long j = 0; j < img->size_x; j++) {

      image_data[i][j].alpha = local_alpha;
    }
  }
}

/* This filter is used to detect edges by computing the gradient for each
 * pixel and comparing it to the threshold argument. When the gradient exceeds
 * the threshold, the pixel is replaced by black, otherwise white.
 * Alpha is unaffected.
 *
 * For each pixel and channel, the x-gradient and y-gradient are calculated
 * by using the following convolution matrices:
 *     Gx            Gy
 *  -1  0  +1     +1 +2 +1
 *  -2  0  +2      0  0  0
 *  -1  0  +1     -1 -2 -1
 * The convolution matrix are multiplied with the neighbouring pixels'
 * channel values. At edges, the indices are bounded.
 * Suppose the red channel values for the pixel and its neighbors are as
 * follows: 11 22 33 44 55 66 77 88 99 the x-gradient for red is: (-1*11 + 1*33
 * + -2*44 + 2*66 + -1*77 + 1*99).
 *
 * The net gradient for each channel = sqrt(g_x^2 + g_y^2)
 * For the pixel, the net gradient = sqrt(g_red^2 + g_green^2 + g_blue_2)
 */
// [-1][-1] -> [0][0]
void filter_edge_detect(struct image *img, void *threshold_arg) {
  struct pixel(*image_data)[img->size_x] =
      (struct pixel(*)[img->size_x])img->px;
  uint8_t threshold = *(uint8_t *)threshold_arg;
  double weights_x[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
  double weights_y[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};
  long offset_x[3][3] = {{-1, 0, 1}, {-1, 0, 1}, {-1, 0, 1}}; // neighbor
  long offset_y[3][3] = {{-1, -1, -1}, {0, 0, 0}, {1, 1, 1}}; // neighbor
  /* Iterate over all pixels */

  int(*is_edge)[img->size_x] = malloc(img->size_x * img->size_y * sizeof(int));
  // memset(is_edge, 0, img->size_x * img->size_y * sizeof(int));

  for (long i = 0; i < img->size_y; i++) {
    for (long j = 0; j < img->size_x; j++) {
      /* TODO: Implement */

      double g_net = 0;
      double gx_red = 0, gx_green = 0, gx_blue = 0;
      double gy_red = 0, gy_green = 0, gy_blue = 0;
      double g_red = 0, g_green = 0, g_blue = 0;

      for (long y = 0; y < 3; y++) {
        for (long x = 0; x < 3; x++) {
          long xi = j + offset_x[y][x];
          long yi = i + offset_y[y][x];

          xi = (xi < 0) ? 0 : xi;
          xi = (xi >= img->size_x) ? (img->size_x - 1) : xi;
          yi = (yi < 0) ? 0 : yi;
          yi = (yi >= img->size_y) ? (img->size_y - 1) : yi;

          // printf("i = %ld, j = %ld, xi = %ld, yi = %ld\n", i, j, xi, yi);
          gx_red += image_data[yi][xi].red * weights_x[y][x];
          gx_green += image_data[yi][xi].green * weights_x[y][x];
          gx_blue += image_data[yi][xi].blue * weights_x[y][x];

          gy_red += image_data[yi][xi].red * weights_y[y][x];
          gy_green += image_data[yi][xi].green * weights_y[y][x];
          gy_blue += image_data[yi][xi].blue * weights_y[y][x];
        }
      }
      g_red = sqrt(pow(gx_red, 2) + pow(gy_red, 2));
      g_green = sqrt(pow(gx_green, 2) + pow(gy_green, 2));
      g_blue = sqrt(pow(gx_blue, 2) + pow(gy_blue, 2));

      g_net = sqrt(pow(g_red, 2) + pow(g_green, 2) + pow(g_blue, 2));
      is_edge[i][j] = (g_net > (double)threshold) ? 1 : 0;
    }
  }

  for (long i = 0; i < img->size_y; i++) {
    for (long j = 0; j < img->size_x; j++) {
      if (is_edge[i][j]) {
        image_data[i][j].red = 0;
        image_data[i][j].green = 0;
        image_data[i][j].blue = 0;
      } else {
        image_data[i][j].red = 255;
        image_data[i][j].green = 255;
        image_data[i][j].blue = 255;
      }
    }
  }
  free(is_edge);
}

/* The filter structure comprises the filter function, its arguments and the
 * image we want to process */
struct filter {
  void (*filter)(struct image *img, void *arg);
  void *arg;
  struct image *img;
};

void execute_filter(struct filter *fil) { fil->filter(fil->img, fil->arg); }

int __attribute__((weak)) main(int argc, char *argv[]) {
  struct filter fil;
  char input[ARG_SIZE];
  char output[ARG_SIZE];
  char command[ARG_SIZE];
  char arg[ARG_SIZE];
  long int radius;
  struct pixel px;
  uint8_t alpha, depth, threshold;
  uint32_t key;
  struct image *img = NULL;
  double weights[] = {0.2125, 0.7154, 0.0721};

  /* Some filters take no arguments, while others have 1 */
  if (argc != 4 && argc != 5) {
    goto error_usage;
  }

  fil.filter = NULL;
  fil.arg = NULL;

  //[BUG FIXED] String Vun
  /* Copy arguments for easier reference */
  strncpy(input, argv[1], ARG_SIZE);
  // if(input[sizeof(input) - 1] == '\0') puts("null in \n");
  input[sizeof(input) - 1] = '\0';
  strncpy(output, argv[2], ARG_SIZE);
  // if(output[sizeof(output) - 1] == '\0') puts("null out \n");
  output[sizeof(output) - 1] = '\0';
  strncpy(command, argv[3], ARG_SIZE);
  // if(command[sizeof(command) - 1] == '\0') puts("null cmd \n");
  command[sizeof(command) - 1] = '\0';

  //[BUG FIXED] Stack Buffer overflow
  /* If the filter takes an argument, copy it */
  if (argv[4]) {
    strncpy(arg, argv[4], ARG_SIZE);
    arg[sizeof(arg) - 1] = '\0';
    // strcpy(arg, argv[4]);
  }

  /* Error when loading a png image */
  if (load_png(input, &img)) {
    //[BUG FIXED] - String Vulnerability

    // printf(input);
    printf("%s", input);
    printf(" PNG file cannot be loaded\n");
    exit(1);
  }

  /* Set up the filter structure */
  fil.img = img;

  /* Decode the filter */
  if (!strcmp(command, "grayscale")) {
    fil.filter = filter_grayscale;
    fil.arg = weights;
  } else if (!strcmp(command, "negative")) {
    fil.arg = NULL;
    fil.filter = filter_negative;
  } else if (!strcmp(command, "blur")) {
    /* Bad filter radius will just be interpretted as 0 - no change to the image
     */

    // [BUG FIXED] String Vulnerability

    char *end_ptr;
    radius = strtol(arg, &end_ptr, 10);
    // radius = atoi(arg);
    // printf("radius = %ld\n", radius);

    fil.filter = filter_blur;
    fil.arg = &radius;
  } else if (!strcmp(command, "alpha")) {

    char *end_ptr;
    long tmp_alpha = strtol(arg, &end_ptr, 16);

    if (tmp_alpha < 0 || tmp_alpha > 255) {
      goto error_usage;
    } else {
      alpha = tmp_alpha;
    }

    if (*end_ptr) {
      goto error_usage;
    }

    fil.filter = filter_transparency;
    fil.arg = &alpha;
  } else if (!strcmp(command, "edge")) {
    char *end_ptr;
    threshold = strtol(arg, &end_ptr, 16);

    if (*end_ptr) {
      goto error_usage;
    }

    fil.filter = filter_edge_detect;
    fil.arg = &threshold;
  }

  /* Invalid filter check */
  if (fil.filter) {
    execute_filter(&fil);
  } else {
    goto error_filter;
  }

  if (store_png(output, img, NULL, 0)) {
    goto error;
  }
  free(img->px);
  free(img);
  return 0;

error:
  printf("Couldn't store png file\n");
  return 1;
error_filter:
  free(img->px);
  free(img);
error_usage:
  printf("Usage: %s input_image output_image filter_name [filter_arg]\n",
         argv[0]);
  printf("Filters:\n");
  printf("grayscale\n");
  printf("negative\n");
  printf("blur radius_arg\n");
  printf("alpha hex_alpha\n");
  printf("edge hex_threshold\n");
  return 1;
}
