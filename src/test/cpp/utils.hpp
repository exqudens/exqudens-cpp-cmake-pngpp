#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <iostream>
#include <initializer_list>
#include <vector>

namespace utils {

  template <typename T>
  std::string to_string(T object) {
    std::stringstream s;
    s << object;
    return s.str();
  }

  template <typename F, typename... T>
  void sequential_foreach(F function, T... args) {
    (void) std::initializer_list<int> {
        [&](const auto& arg) {
          function(arg);
          return 0;
        } (args)...
    };
  }

  template <typename... T>
  std::vector<std::string> to_vector_string(T... args) {
    std::vector<std::string> v1;
    sequential_foreach([&](const auto& arg) { v1.push_back(to_string(arg)); }, args...);
    return v1;
  }

  template <typename... T>
  void println(T... args) {
    std::vector<std::string> v1 = to_vector_string(args...);
    for (int i = 0; i < v1.size(); i++) {
      std::cout << v1.at(i);
    }
    std::cout << std::endl;
  }

}

#endif // UTILS_HPP
