#include "pngparser.h"
#include <math.h>
#include <string.h>

int main(int argc, char *argv[]) {
  struct image *img;

  /* Check if the number of arguments is correct */
  if (argc != 7) {
    printf("Usage: %s input_image output_image center_x center_y radius "
           "hex_color\n",
           argv[0]);
    return 1;
  }

  /* Rename arguments for easier reference */
  char *input = argv[1];
  char *output = argv[2];

  //[BUG FOUND] String Vun(atoi)
  char *end_ptr;
  /* Decode the center of the circle. Invalid values are decoded as 0 */
  // int center_x = atoi(argv[3]);
  // int center_y = atoi(argv[4]);
  int center_x = strtol(argv[3], &end_ptr, 10);
  int center_y = strtol(argv[4], &end_ptr, 10);
  /* Invalid radius will just be interpretted as 0 */
  // int radius = atoi(argv[5]);
  int radius = strtol(argv[5], &end_ptr, 10);
  /* Invalid color will be interpretted as black */
  // [BUG FIXED] Wrong Operator -> argv[6]
  // [BUG FIXED] Unchecked system call returning code -> hex_color < 0xFFFFFF

  long hex_color = strtol(argv[6], &end_ptr, 16);
  if (*end_ptr || strlen(argv[6]) != 6 || hex_color < 0) {
    hex_color = 0;
  }

  if (load_png(input, &img)) {
    return 1;
  }

  unsigned height = img->size_y;
  unsigned width = img->size_x;

  struct pixel(*image_data)[width] = (struct pixel(*)[width])img->px;

  if ((center_x >= width) || (center_x < 0) || (center_y >= height) ||
      (center_y < 0)) {
    printf("Error!! Center not in the picture.\n");
    return 1;
  }
  int diff_x = width - center_x;
  diff_x = diff_x > center_x ? center_x : diff_x;
  int diff_y = height - center_y;
  diff_y = diff_y > center_y ? center_y : diff_y;

  if (radius >= diff_x || radius >= diff_y) {
    printf("Error!! Radius is too big.\n");
    return 1;
  }
  /* We will iterate through all the x coordinate values in the pixel and
   * calculate the y values for the pixels. Every circle has two points
   * corresponding to every x coordinate.
   *
   * The coordinates were obtained by solving the equation:
   * (x - center_x)^2 + (y - center_y)^2 = radius^2
   *
   * A radius of 0 means a single pixel in the center
   */

  //[BUG FIXED] - heap overflow
  for (int x = center_x - radius; x <= center_x + radius; x++) {
    long long int y = round(center_y + sqrt((long long)radius * radius -
                                            (x - center_x) * (x - center_x)));

    image_data[y][x].red = (hex_color & 0xff0000) >> 16;
    image_data[y][x].green = (hex_color & 0x00ff00) >> 8;
    image_data[y][x].blue = (hex_color & 0x0000ff);
    image_data[y][x].alpha = 0xff;

    //[BUG FIXED] - Wrong Operator
    y = round(center_y -
              sqrt(radius * radius - (x - center_x) * (x - center_x)));

    image_data[y][x].red = (hex_color & 0xff0000) >> 16;
    image_data[y][x].green = (hex_color & 0x00ff00) >> 8;
    image_data[y][x].blue = (hex_color & 0x0000ff);
    image_data[y][x].alpha = 0xff;
  }

  /* There are going to be some ugly gaps in the image, so we will repeat the
   * procedure for the y axis.
   *
   * In practice a more efficient rasterization algorithm is used.
   */
  for (int y = center_y - radius; y <= center_y + radius; y++) {
    long long int x = round(center_x + sqrt((long long)radius * radius -
                                            (y - center_y) * (y - center_y)));

    image_data[y][x].red = (hex_color & 0xff0000) >> 16;
    image_data[y][x].green = (hex_color & 0x00ff00) >> 8;
    image_data[y][x].blue = (hex_color & 0x0000ff);
    image_data[y][x].alpha = 0xff;

    //[BUG FIXED] - Wrong Operator
    x = round(center_x -
              sqrt(radius * radius - (y - center_y) * (y - center_y)));

    image_data[y][x].red = (hex_color & 0xff0000) >> 16;
    image_data[y][x].green = (hex_color & 0x00ff00) >> 8;
    image_data[y][x].blue = (hex_color & 0x0000ff);
    image_data[y][x].alpha = 0xff;
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
}
