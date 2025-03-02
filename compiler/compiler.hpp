//
// Created by Matas Lekavičius on 27/06/2024.
//

#pragma once

#include <unordered_map>
#include <vector>
#include "types.hpp"

namespace cpp_vm {
    class Compiler {
    public:
        Compiler() = default;

        void ret();

        void set(types::u8 dest, types::i16 value);

        void add(types::u8 dest, types::u8 reg1, types::u8 reg2);

        void sub(types::u8 dest, types::u8 reg1, types::u8 reg2);

        void inc(types::u8 src);

        void eq(types::u8 dest, types::u8 reg1, types::u8 reg2);

        void cp(types::u8 reg1, types::u8 reg2);

        void out(types::u8 reg);

        void jmp(const std::string &lab);

        void jne(types::u8 reg, const std::string &lab);

        void label(const std::string &lab);

        std::vector<types::u32> getByteCode() const;

    private:
        types::i16 diff(const std::string &lab) const;

    private:
        std::vector<types::u32> bytecode;
        std::unordered_map<std::string, size_t> labels;
    };
}
