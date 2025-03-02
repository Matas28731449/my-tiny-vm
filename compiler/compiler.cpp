//
// Created by Matas Lekavičius on 27/06/2024.
//

#include "instructions.hpp"
#include "compiler.hpp"

void cpp_vm::Compiler::ret() {
    Instruction instr = {opcode::Type::RET, 0, 0};
    bytecode.push_back(Instruction::encode(instr));
}

void cpp_vm::Compiler::set(types::u8 dest, types::i16 val) {
    Instruction instr = {opcode::Type::SET, dest, val};
    bytecode.push_back(Instruction::encode(instr));
}

void cpp_vm::Compiler::add(types::u8 dest, types::u8 reg1, types::u8 reg2) {
    Instruction instr = {opcode::Type::ADD, dest, reg1, reg2};
    bytecode.push_back(Instruction::encode(instr));
}

void cpp_vm::Compiler::sub(types::u8 dest, types::u8 reg1, types::u8 reg2) {
    Instruction instr = {opcode::Type::SUB, dest, reg1, reg2};
    bytecode.push_back(Instruction::encode(instr));
}

void cpp_vm::Compiler::inc(types::u8 src) {
    Instruction instr = {opcode::Type::INC, src, 0};
    bytecode.push_back(Instruction::encode(instr));
}

void cpp_vm::Compiler::eq(types::u8 dest, types::u8 reg1, types::u8 reg2) {
    Instruction instr = {opcode::Type::EQ, dest, reg1, reg2};
    bytecode.push_back(Instruction::encode(instr));
}

void cpp_vm::Compiler::cp(types::u8 reg1, types::u8 reg2) {
    Instruction instr = {opcode::Type::CP, 0, reg1, reg2};
    bytecode.push_back(Instruction::encode(instr));
}

void cpp_vm::Compiler::out(types::u8 src) {
    Instruction instr = {opcode::Type::OUT, src, 0};
    bytecode.push_back(Instruction::encode(instr));
}

void cpp_vm::Compiler::jmp(const std::string &lab) {
    Instruction instr = {opcode::Type::JMP, 0, diff(lab)};
    bytecode.push_back(Instruction::encode(instr));
}

void cpp_vm::Compiler::jne(types::u8 src, const std::string &lab) {
    Instruction instr = {opcode::Type::JNE, src, diff(lab)};
    bytecode.push_back(Instruction::encode(instr));
}

void cpp_vm::Compiler::label(const std::string &lab) {
    labels[lab] = bytecode.size();
}

types::i16 cpp_vm::Compiler::diff(const std::string &lab) const {
    size_t currentPos = bytecode.size();
    size_t labelPos = labels.at(lab);
    types::i16 diff = labelPos - (currentPos + 1);

    return diff;
}

std::vector<types::u32> cpp_vm::Compiler::getByteCode() const {
    return bytecode;
}
