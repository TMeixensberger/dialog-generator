#pragma once

#include <QString>

enum class OperationType {
    All,
    Square,
    Sine
};

inline QString toString(const OperationType operation) {
    switch (operation) {
    case OperationType::All:
        return "All";
    case OperationType::Square:
        return "Square";
    case OperationType::Sine:
        return "Sine";
    }

    return {};
}
