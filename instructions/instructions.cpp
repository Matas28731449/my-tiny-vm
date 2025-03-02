//
// Created by Matas Lekavičius on 02/07/2024.
//

#include "instructions.hpp"

#include <stdexcept>

bool operator==(const cpp_vm::Instruction lhs, const cpp_vm::Instruction rhs) {
    return lhs.opcode == rhs.opcode &&
           lhs.dest == rhs.dest &&
           lhs.reg1 == rhs.reg1 &&
           lhs.reg2 == rhs.reg2 &&
           lhs.val == rhs.val;
}

types::u32 cpp_vm::Instruction::encode(Instruction instr) {
    switch (instr.format) {
        case operation::Encoding::ASSIGN: {
            return (static_cast<types::u32>(instr.opcode) << 24) |
                   (static_cast<types::u32>(instr.dest) << 16) |
                   (static_cast<types::u32>(instr.val) & 0xFFFF);
        }
        case operation::Encoding::STANDARD: {
            return (static_cast<types::u32>(instr.opcode) << 24) |
                   (static_cast<types::u32>(instr.dest) << 16) |
                   (static_cast<types::u32>(instr.reg1) << 8) |
                   static_cast<types::u32>(instr.reg2);
        }
        default:
            throw std::runtime_error("There is no such encoding format");
    }
}

cpp_vm::Instruction cpp_vm::Instruction::decode(const types::u32 bytecode) {
    auto opcode = static_cast<opcode::Type>(bytecode >> 24);

    operation::Encoding format;
    switch (opcode) {
        case opcode::Type::SET:
        case opcode::Type::INC:
        case opcode::Type::OUT:
        case opcode::Type::JMP:
        case opcode::Type::JNE:
        case opcode::Type::RET:
            format = operation::Encoding::ASSIGN;
            break;
        default:
            format = operation::Encoding::STANDARD;
            break;
    }

    if (format != operation::Encoding::STANDARD) {
        auto dest = static_cast<types::u8>((bytecode >> 16) & 0xFF);
        auto val = static_cast<types::i16>((bytecode >> 0) & 0xFFFF);

        return {opcode, dest, val};
    } else {
        auto dest = static_cast<types::u8>((bytecode >> 16) & 0xFF);
        auto reg1 = static_cast<types::u8>((bytecode >> 8) & 0xFF);
        auto reg2 = static_cast<types::u8>(bytecode & 0xFF);

        return {opcode, dest, reg1, reg2};
    }
}
