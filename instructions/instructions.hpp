//
// Created by Matas Lekavičius on 28/06/2024.
//

#pragma once

#include "types.hpp"

namespace operation {
    enum class Encoding : types::u8 {
        ASSIGN,
        STANDARD
    };
}

namespace opcode {
    enum class Type : types::u8 {
        SET,
        ADD,
        SUB,
        INC,
        EQ,
        CP,
        OUT,
        JMP,
        JNE, // jump-if-not-equal instruction
        RET,
    };
}

namespace cpp_vm {
    struct Instruction {
        operation::Encoding format;
        opcode::Type opcode;
        types::u8 dest;
        types::u8 reg1{};
        types::u8 reg2{};
        types::i16 val{};

        Instruction(const opcode::Type opcode, const types::u8 dest, const types::i16 val)
            : format(operation::Encoding::ASSIGN), opcode(opcode), dest(dest), val(val) {
        }

        Instruction(const opcode::Type opcode, const types::u8 dest, const types::u8 reg1, const types::u8 reg2)
            : format(operation::Encoding::STANDARD), opcode(opcode), dest(dest), reg1(reg1), reg2(reg2) {
        }

        static types::u32 encode(Instruction instr);

        static Instruction decode(types::u32 bytecode);
    };

    bool operator==(Instruction lhs, Instruction rhs);
}
