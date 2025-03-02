//
// Created by Matas Lekavičius on 26/06/2024.
//

#pragma once

#include "types.hpp"
#include <vector>

namespace cpp_vm {
    class VM {
    public:
        VM();

        void run(const std::vector<types::u32> &bytecode);

        void setRegisterValue(types::u8 reg, types::i16 val);

        types::i16 getRegisterValue(types::u8 reg) const;

    private:
        std::vector<types::i16> registers;
    };
}
