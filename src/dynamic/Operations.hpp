#pragma once

#include <QString>

enum class Operation {
    All,
    Square,
    Sine
};

inline QString toString(const Operation operation) {
    switch (operation) {
    case Operation::All:
        return "All";
    case Operation::Square:
        return "Square";
    case Operation::Sine:
        return "Sine";
    }

    return {};
}
