#include "dialog-generator.h"
#include <vector>
#include <string>

int main() {
    dialog_generator();

    std::vector<std::string> vec;
    vec.push_back("test_package");

    dialog_generator_print_vector(vec);
}
