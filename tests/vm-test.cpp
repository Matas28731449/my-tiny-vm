//
// Created by Matas Lekavičius on 27/06/2024.
//

#include <gtest/gtest.h>
#include "compiler.hpp"
#include "vm.hpp"

TEST(VM, setRegisterCheck) {
    cpp_vm::VM vm;
    cpp_vm::Compiler c;

    constexpr types::u8 a_reg = 0;

    c.set(a_reg, 7);
    c.ret();

    vm.run(c.getByteCode());

    EXPECT_EQ(vm.getRegisterValue(a_reg), 7);
}

TEST(VM, addRegistersCheck) {
    cpp_vm::VM vm;
    cpp_vm::Compiler c;

    constexpr types::u8 a_reg = 0;
    constexpr types::u8 b_reg = 1;
    constexpr types::u8 res_reg = 2;

    c.set(a_reg, 1);
    c.set(b_reg, 2);

    c.add(res_reg, a_reg, b_reg);
    c.ret();

    vm.run(c.getByteCode());

    EXPECT_EQ(vm.getRegisterValue(res_reg), 3);
}

TEST(VM, incrementRegisterCheck) {
    cpp_vm::VM vm;
    cpp_vm::Compiler c;

    constexpr types::u8 a_reg = 0;

    c.set(a_reg, -3);
    c.inc(a_reg);

    vm.run(c.getByteCode());

    EXPECT_EQ(vm.getRegisterValue(a_reg), -2);
}

TEST(VM, equalRegistersCheck) {
    cpp_vm::VM vm;
    cpp_vm::Compiler c;

    constexpr types::u8 a_reg = 0;
    constexpr types::u8 b_reg = 1;
    constexpr types::u8 eq_reg = 2;

    c.set(a_reg, 100);
    c.set(b_reg, 100);
    c.eq(eq_reg, a_reg, b_reg);

    vm.run(c.getByteCode());

    EXPECT_EQ(vm.getRegisterValue(eq_reg), 1);
}
