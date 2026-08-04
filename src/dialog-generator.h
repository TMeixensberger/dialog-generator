#pragma once

#include <vector>
#include <string>


#ifdef _WIN32
  #define DIALOG_GENERATOR_EXPORT __declspec(dllexport)
#else
  #define DIALOG_GENERATOR_EXPORT
#endif

DIALOG_GENERATOR_EXPORT void dialog_generator();
DIALOG_GENERATOR_EXPORT void dialog_generator_print_vector(const std::vector<std::string> &strings);
