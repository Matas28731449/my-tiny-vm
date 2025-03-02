# C++ virtual machine

Prerequisites:

- Conan version 1.62.0

## Installation process

1. Clone the GitHub repository:

    ```
    git clone https://github.com/Matas28731449/my-tiny-vm.git
    ```
   
2. Open the project with an IDE of your choice:

3. If CMake project does not build itself, go to the CMakeLists.txt file and click `Load CMake project`.

## Design goals

1. I decided to take on a Test-Driven Development approach by implementing tests first.

2. Since the instructions had to fit into 32 bits, I made my own (non-conventional) instruction format:

![instr-format](https://github.com/digitalai-security/onboarding-task-2/assets/116190079/ab6aef9d-5382-4a66-9add-9b0f533e4be5)

## References

[Build a simple CMake project using Conan](https://docs.conan.io/2/tutorial/consuming_packages/build_simple_cmake_project.html)

[Writing a simple 16 bit VM in less than 125 lines of C](https://www.andreinc.net/2021/12/01/writing-a-simple-vm-in-less-than-125-lines-of-c)

[Simple Virtual Machine by Bartosz Sypytkowski](https://www.bartoszsypytkowski.com/simple-virtual-machine/)