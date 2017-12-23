#pragma once

#include<stdexcept>

#include<synacor/vm.h>

namespace synacor {

class synacore_error : public std::runtime_error {};

using program_t = std::vector<memory_t>;

void eval(vm &vm, program_t &program);

}
