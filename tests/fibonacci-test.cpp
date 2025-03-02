//
// Created by Matas Lekavičius on 27/06/2024.
//

#include <gtest/gtest.h>
#include "compiler.hpp"
#include "vm.hpp"

TEST(Program, fibonacciSequence) {
    cpp_vm::VM vm;
    cpp_vm::Compiler c;

    constexpr types::u8 a_reg = 0;
    constexpr types::u8 b_reg = 1;
    constexpr types::u8 c_reg = 2;
    constexpr types::u8 eq_reg = 3;
    constexpr types::u8 res_reg = 4;

    c.set(a_reg, 1);
    c.set(b_reg, 1);
    c.set(res_reg, 34);

    c.label("loop");
    c.add(c_reg, a_reg, b_reg);
    c.cp(a_reg, b_reg); // copy
    c.cp(b_reg, c_reg); // copy
    c.eq(eq_reg, b_reg, res_reg); // equal
    c.jne(eq_reg, "loop"); // jump-if-not-equal-to-1 (eq != 1)

    c.out(b_reg);
    c.ret();

    vm.run(c.getByteCode());

    ASSERT_EQ(vm.getRegisterValue(res_reg), 34);
}

TEST(Program, fibonacciSequenceCase2) {
    cpp_vm::VM vm;
    cpp_vm::Compiler c;

    constexpr types::u8 i_reg = 0;
    constexpr types::u8 n_reg = 1;
    constexpr types::u8 a_reg = 2;
    constexpr types::u8 b_reg = 3;
    constexpr types::u8 eq_reg = 4;
    constexpr types::u8 res_reg = 5;

    c.set(a_reg, 0);
    c.set(b_reg, 1);

    // while (i != n):
    c.set(i_reg, 0);
    c.set(n_reg, 8);

    c.label("loop");
    c.add(res_reg, a_reg, b_reg);
    c.cp(a_reg, b_reg);
    c.cp(b_reg, res_reg);
    c.inc(i_reg);
    c.eq(eq_reg, i_reg, n_reg);
    c.jmp("loop");

    c.ret();

    vm.run(c.getByteCode());

    ASSERT_EQ(vm.getRegisterValue(i_reg), 8);
}

TEST(Program, fibonacciSequenceLoopCount) {
    cpp_vm::VM vm;
    cpp_vm::Compiler c;

    constexpr types::u8 i_reg = 0;
    constexpr types::u8 n_reg = 1;
    constexpr types::u8 a_reg = 2;
    constexpr types::u8 b_reg = 3;
    constexpr types::u8 res_reg = 4;
    constexpr types::u8 eq_reg = 5;

    c.set(a_reg, 0);
    c.set(b_reg, 1);
    c.set(i_reg, 0);
    c.set(n_reg, 10);

    c.label("loop");
    c.add(res_reg, a_reg, b_reg);
    c.cp(a_reg, b_reg);
    c.cp(b_reg, res_reg);
    c.eq(eq_reg, i_reg, n_reg);
    c.jne(eq_reg, "loop");

    c.ret();

    vm.run(c.getByteCode());

    // After 10 iterations, starting with 0,1 the sequence is:
    // 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 => b_reg should be 89
    ASSERT_EQ(vm.getRegisterValue(b_reg), 89);
}

TEST(Program, maxLimitHandling) {
    cpp_vm::VM vm;
    cpp_vm::Compiler c;

    constexpr types::u8 max_reg = 0;
    constexpr types::u8 min_reg = 1;
    constexpr types::u8 temp_reg = 2;
    constexpr types::u8 eq_reg = 3;

    c.set(max_reg, 32767);
    c.set(min_reg, -32768);

    c.add(temp_reg, max_reg, 1);
    c.eq(eq_reg, temp_reg, min_reg);
    c.out(temp_reg);

    c.sub(temp_reg, min_reg, 1);
    c.eq(eq_reg, temp_reg, max_reg);
    c.out(temp_reg);

    c.ret();

    vm.run(c.getByteCode());

    ASSERT_EQ(vm.getRegisterValue(temp_reg), max_reg);
}
