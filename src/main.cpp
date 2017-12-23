/* Author: Kaden Thomas */
#include<cstdio>
#include<cstdlib>

#include<string>
#include<fstream>

#include<synacor/vm.h>
#include<synacor/opcode.h>
#include<synacor/eval.h>

int main(int argc, char **argv)
{
    if(argc != 2){
        std::puts("usage: synacore-vm <file>");
        return EXIT_FAILURE;
    }
    const std::string prog_file{argv[1]};


    std::ifstream fin(prog_file, std::ios::binary);
    fin.seekg(0, std::ios_base::end);

    const auto size = fin.tellg();
    synacor::memory_t *buffer = new synacor::memory_t[size];

    fin.seekg(0, std::ios_base::beg);
    fin.read( (char *) buffer, size);
    fin.close();

    std::vector<synacor::memory_t> program{buffer, buffer + size};
    delete[] buffer;

    /* test the program */
    synacor::vm vm;
    synacor::eval(vm, program);
    return EXIT_SUCCESS;
}
