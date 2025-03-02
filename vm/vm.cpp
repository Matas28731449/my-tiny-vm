//
// Created by Matas Lekavičius on 25/06/2024.
//

#include <iostream>
#include "instructions.hpp"
#include "vm.hpp"

cpp_vm::VM::VM() : registers(255, 0) {
}

void cpp_vm::VM::run(const std::vector<types::u32> &bytecode) {
    for (size_t pc = 0; pc < bytecode.size(); ++pc) {
        Instruction instr = Instruction::decode(bytecode[pc]);

        switch (instr.opcode) {
            case opcode::Type::SET:
                registers[instr.dest] = instr.val;
                break;
            case opcode::Type::ADD:
                registers[instr.dest] = registers[instr.reg1] + registers[instr.reg2];
                break;
            case opcode::Type::SUB:
                registers[instr.dest] = registers[instr.reg1] - registers[instr.reg2];
                break;
            case opcode::Type::INC:
                ++registers[instr.dest];
                break;
            case opcode::Type::EQ:
                registers[instr.dest] = registers[instr.reg1] == registers[instr.reg2];
                if (registers[instr.dest]) {
                    ++pc;
                }
                break;
            case opcode::Type::CP:
                registers[instr.reg1] = registers[instr.reg2];
                break;
            case opcode::Type::OUT:
                std::cout << registers[instr.dest] << std::endl;
                break;
            case opcode::Type::JMP:
                pc += instr.val;
                break;
            case opcode::Type::JNE:
                if (registers[instr.dest] != 1) {
                    pc += instr.val;
                }
                break;
            case opcode::Type::RET:
                return;
        }
    }
}

void cpp_vm::VM::setRegisterValue(const types::u8 reg, const types::i16 val) {
    registers[reg] = val;
}

types::i16 cpp_vm::VM::getRegisterValue(const types::u8 reg) const {
    return registers[reg];
}
