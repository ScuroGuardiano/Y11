#pragma once

#include "src/backend.hpp"
#include <memory>

namespace y11 {

class Cursor {
public:
    Cursor();
    ~Cursor();

    void evaluate(const std::unique_ptr<y11::Backend>&);
    short getPosX();
    short getPosY();

private:
    short posX{};
    short posY{};
};

}
