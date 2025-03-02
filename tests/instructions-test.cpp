//
// Created by Matas Lekavičius on 28/06/2024.
//

#include <gtest/gtest.h>
#include "instructions.hpp"

TEST(Operations, encodeOperationSetCheck) {
    const cpp_vm::Instruction instr = {opcode::Type::SET, 0, 255};
    const types::u32 encoded = cpp_vm::Instruction::encode(instr);
    constexpr types::u32 expected = 0x00000FF;
    /*
     *  0x00    0x00    0x00FF  (hex)
     *  opcode  src     val     (type)
     *  0       0       255     (dec)
     */
    EXPECT_EQ(encoded, expected);
}

TEST(Operations, encodeOperationAddCheck) {
    const cpp_vm::Instruction instr = {opcode::Type::ADD, 3, 2, 1};
    const types::u32 encoded = cpp_vm::Instruction::encode(instr);
    constexpr types::u32 expected = 0x01030201;
    /*
     *  0x01    0x03    0x02    0x01    (hex)
     *  opcode  dest    reg1    reg2    (type)
     *  1       3       2       1       (dec)
     */
    EXPECT_EQ(encoded, expected);
}

TEST(Operations, decodeValueOperationCheck) {
    constexpr types::u32 encoded = 0x00040101;
    /*
     *  0x00    0x04    0x0101  (hex)
     *  opcode  dest    value   (type)
     *  0       4       257     (dec)
     */
    const cpp_vm::Instruction decoded = cpp_vm::Instruction::decode(encoded);
    const cpp_vm::Instruction expected = {opcode::Type::SET, 4, 257};
    EXPECT_EQ(decoded.opcode, expected.opcode);
    EXPECT_EQ(decoded.dest, expected.dest);
    EXPECT_EQ(decoded.val, expected.val);
}

TEST(Operations, decodeRegistersOperationCheck) {
    constexpr types::u32 encoded = 0x01040101;
    /*
     *  0x01    0x04    0x01    0x01    (hex)
     *  opcode  dest    reg1    reg2    (type)
     *  1       4       1       1       (dec)
     */
    const cpp_vm::Instruction decoded = cpp_vm::Instruction::decode(encoded);
    const cpp_vm::Instruction expected = {opcode::Type::ADD, 4, 1, 1};
    EXPECT_EQ(decoded.opcode, expected.opcode);
    EXPECT_EQ(decoded.dest, expected.dest);
    EXPECT_EQ(decoded.reg1, expected.reg1);
    EXPECT_EQ(decoded.reg2, expected.reg2);
}
