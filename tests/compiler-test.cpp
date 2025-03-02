//
// Created by Matas Lekavičius on 27/06/2024.
//

#include <gtest/gtest.h>
#include "compiler.hpp"

TEST(Compiler, setInstructionCheck) {
    cpp_vm::Compiler c;

    types::i8 a_reg = 0;

    c.set(a_reg, -255);

    std::vector<types::u32> expected = {
        0x0000FF01
        /*
         *  0x00    0x00    0x0001  (hex)
         *  opcode  dest    val     (type)
         *  0       0       1       (dec)
         */
    };

    EXPECT_EQ(c.getByteCode(), expected);
}

TEST(Compiler, addInstructionCheck) {
    cpp_vm::Compiler c;

    types::u8 a_reg = 0;
    types::u8 b_reg = 1;
    types::u8 res_reg = 2;

    c.set(a_reg, 9);
    c.set(b_reg, -2);
    c.add(res_reg, a_reg, b_reg);

    std::vector<types::u32> expected = {
        0x00000009,
        /*
         *  0x00    0x00    0x0009  (hex)
         *  opcode  dest    val     (type)
         *  0       0       9       (dec)
         */
        0x0001FFFE,
        /*
         *  0x00    0x01    0xFFFE  (hex)
         *  opcode  dest    val     (type)
         *  0       1       -2      (dec)
         *
         */
        0x01020001
        /*
         *  0x01    0x02    0x00    0x01 (hex)
         *  opcode  dest    reg1    reg2 (type)
         *  1       2       0       1    (dec)
         */
    };

    EXPECT_EQ(c.getByteCode(), expected);
}

TEST(Compiler, incrementInstructionCheck) {
    cpp_vm::Compiler c;

    types::u8 a_reg = 0;

    c.set(a_reg, 1);
    c.inc(a_reg);

    std::vector<types::u32> expected = {
        0x00000001,
        /*
         *  0x00    0x00    0x0001  (hex)
         *  opcode  src     val     (type)
         *  0       0       1       (dec)
         */
        0x03000000
        /*
         *  0x03    0x00    0x0000  (hex)
         *  opcode  src     val     (type)
         *  3       0       0       (dec)
         */
    };

    EXPECT_EQ(c.getByteCode(), expected);
}

TEST(Compiler, equalInstructionCheck) {
    cpp_vm::Compiler c;

    types::u8 a_reg = 0;
    types::u8 b_reg = 1;
    types::u8 res_reg = 2;

    c.set(a_reg, 4);
    c.set(b_reg, 4);
    c.eq(res_reg, a_reg, b_reg);

    std::vector<types::u32> expected = {
        0x00000004,
        /*
         *  0x00    0x00    0x0004
         *  opcode  dest    val
         *  0       0       4
         */
        0x00010004,
        /*
         *  0x00    0x01    0x00    0x04
         *  opcode  dest    --      val
         *  0       1       0       4
         */
        0x04020001
        /*
         *  0x03    0xFF    0x00    0x01
         *  opcode  dest    reg1    reg2
         *  3       255     0       1
         */
    };

    EXPECT_EQ(c.getByteCode(), expected);
}

TEST(Compiler, jumpInstructionCheck) {
    cpp_vm::Compiler c;

    c.label("start");
    c.jmp("start");

    std::vector<types::u32> expected = {
        0x0700FFFF
        /*
         *  0x07    0x00    0xFFFF      (hex)
         *  opcode  0       val(diff)   (type)
         *  7       0       -1          (dec)
         */
    };

    EXPECT_EQ(c.getByteCode(), expected);
}

TEST(Compiler, jumpIfNotEqualInstructionCheck) {
    cpp_vm::Compiler c;

    types::u8 a_reg = 6;

    c.label("start");
    c.set(a_reg, 7);
    c.jne(a_reg, "start"); // jump-if-not-equal-to-1

    std::vector<types::u32> expected = {
        0x00060007,
        /*
         *  0x00    0x06    0x0007
         *  opcode  dest    val
         *  0       6       7
         */
        0x0806FFFE
        /*
         *  0x06    0x06    0xFFFE
         *  opcode  src     diff
         *  6       6       -2
         */
    };

    EXPECT_EQ(c.getByteCode(), expected);
}

TEST(Compiler, printInstructionCheck) {
    cpp_vm::Compiler c;

    types::u8 a_reg = 0;

    c.set(a_reg, 3);
    c.out(a_reg);

    std::vector<types::u32> expected = {
        0x00000003,
        /*
         *  0x00    0x00    0x0003  (hex)
         *  opcode  dest    val     (type)
         *  0       0       3       (dec)
         */
        0x06000000
        /*
         *  0x05    0x00    0x00    0x00
         *  opcode  dest    --      --
         *  4       0       0       0
         */
    };

    EXPECT_EQ(c.getByteCode(), expected);
}

TEST(Compiler, addTwoMaxValueRegisters) {
    cpp_vm::Compiler c;

    types::u8 max_reg = 255;

    c.set(max_reg, 255);
    c.add(max_reg, max_reg, max_reg);
    c.out(max_reg);

    std::vector<types::u32> expected = {
        0x00FF00FF,
        /*
         *  0x00    0xFF    0x00    0xFF
         *  opcode  dest    --      val
         *  0       255     0       255
         */
        0x01FFFFFF,
        /*
         *  0x01    0xFF    0xFF    0xFF
         *  opcode  dest    reg1    reg2
         *  1       255     255     255
         */
        0x06FF0000
        /*
         *  0x04    0xFF    0x00    0x00
         *  opcode  dest    --      --
         *  4       255     0       0
         */
    };

    EXPECT_EQ(c.getByteCode(), expected);
}
