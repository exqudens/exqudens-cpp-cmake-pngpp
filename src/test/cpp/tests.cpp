#include <iostream>
#include <filesystem>
#include <string>
#include <stdexcept>

#include "utils.hpp"

#include "png++/types.hpp"
#include "png++/png.hpp"

void test_1() {
  std::filesystem::path p = std::filesystem::path(__FILE__)
      .append("..")
      .append("..")
      .append("resources")
      .append("png")
      .append("census-1.png");

  if (!std::filesystem::exists(p)) {
    throw std::runtime_error(std::string("not exists: ").append(p.string()));
  }

  utils::println("---");

  png::image<png::rgba_pixel> image(p.string(), png::require_color_space<png::rgba_pixel>());
  png::uint_32 width = image.get_width();
  png::uint_32 height = image.get_height();

  utils::println("size width/height:", width, "/", height);

  utils::println("-");

  int x = 0;
  int y = 0;
  png::rgba_pixel pixel = image.get_pixel(x, y);

  utils::println(
      "pixel (x/y) [r, g, b, a]: (",
      x,
      "/",
      y,
      ") [",
      (int) pixel.red,
      ", ",
      (int) pixel.green,
      ", ",
      (int) pixel.blue,
      ", ",
      (int) pixel.alpha,
      "]"
  );

  x = 100;
  y = 50;
  pixel = image.get_pixel(x, y);

  utils::println(
      "pixel (x/y) [r, g, b, a]: (",
      x,
      "/",
      y,
      ") [",
      (int) pixel.red,
      ", ",
      (int) pixel.green,
      ", ",
      (int) pixel.blue,
      ", ",
      (int) pixel.alpha,
      "]"
  );

  utils::println("---");

  /*png::rgba_pixel pixel = image.get_pixel(0, 0);

  utils::println("(", typeid(pixel.red).name(), ") ", pixel.red);
  utils::println(pixel.red, " ", pixel.green, " ", pixel.blue, " ", pixel.alpha);
  utils::println((int) pixel.red, " ", (int) pixel.green, " ", (int) pixel.blue, " ", (int) pixel.alpha);*/

  //utils::println("---");

  /*for (size_t y = 0; y < image.get_height(); ++y) {
    for (size_t x = 0; x < image.get_width(); ++x) {
      const png::rgb_pixel& pixel = image.get_pixel(x, y);
      image[y][x] = png::rgb_pixel(x, y, x + y);
    }
  }*/
}

int main(int argc, char** argv) {
  try {
    if (argc > 1) {
      std::string test_name = std::string();
      if ("test_1" == test_name) {
        test_1();
      }
    } else {
      test_1();
    }
    return 0;
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}
