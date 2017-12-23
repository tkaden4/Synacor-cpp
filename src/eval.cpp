#include<iostream>
#include<cstring>

#include<synacor/eval.h>
#include<synacor/opcode.h>

namespace synacor {

constexpr auto MOD_VALUE = MAX_NUM + 1;

/* get the location of an argument, register/memory */
static inline auto loc_arg(vm &vm, const program_t &prog, std::size_t ip, std::size_t n)
{
    return &vm.memory[prog[ip + n]];
}

/* get a value argument */
static inline auto val_arg(vm &vm, const program_t &prog, std::size_t ip, std::size_t n)
{
    const auto value = prog[ip + n];
    if(is_register(value)){
        return vm.memory[value];
    }else{
        return static_cast<memory_t>(value);
    }
}


void eval(vm &vm, program_t &prog)
{
#define val(n) val_arg(vm, prog, ip, n)
#define loc(n) loc_arg(vm, prog, ip, n)

#define binary_op(op) \
        *loc(0) = val(1) op val(2); \
        ip += 3; \
        break

#define math_op(op) \
        *loc(0) = (val(1) op val(2)) % MOD_VALUE; \
        ip += 3; \
        break

#define handle break; case 
#define handle_else break; default

    /* instruction pointer */
    std::size_t ip = 0;

    /* make sure all memory is blanked */
    std::memset(vm.memory.get(), 0, VM_MEMORY_SIZE * sizeof(memory_t));

    while(ip < prog.size()){
        /* get opcode */
        const auto op = static_cast<opcode>(prog[ip]);
        /* move to arguments */
        ++ip;
        /* handle opcode */
        switch(op){
        /* Misc opcodes */
        handle opcode::NOOP:
        handle opcode::HALT:
            ip = prog.size();
        handle opcode::SET:
            *loc(0) = val(1);
            ip += 2;
        /* IO opcodes */
        handle opcode::OUT:
            std::printf("%c", val(0));
            ++ip;
        handle opcode::IN:
            *loc(0) = getchar();
            ++ip;
        handle opcode::RMEM:
            *loc(0) = prog[val(1)];
            ip += 2;
        handle opcode::WMEM:
            prog[val(0)] = val(1);
            ip += 2;
        /* Arithmetic opcodes */
        handle opcode::ADD:
            math_op(+);
        handle opcode::MOD:
            math_op(%);
        handle opcode::MULT:
            math_op(*);
        /* Comparison opcodes */
        handle opcode::EQ:
            binary_op(==);
        handle opcode::GT:
            binary_op(>);
        /* Bitwise Operators */
        handle opcode::AND:
            binary_op(&);
        handle opcode::OR:
            binary_op(|);
        handle opcode::NOT:
            *loc(0) = ~val(1) & MAX_NUM;
            ip += 2;
        /* Branching opcodes */
        handle opcode::CALL:
            vm.stack.push_back(ip + 1);
            ip = val(0);
        handle opcode::RET:
            ip = vm.stack.back();
            vm.stack.pop_back();
        handle opcode::JMP:
            ip = val(0);
        handle opcode::JT:
            if(val(0)){
                ip = val(1);
            }else{
                ip += 2;
            }
        handle opcode::JF:
            if(!val(0)){
                ip = val(1);
            }else{
                ip += 2;
            }
        /* Stack Opcodes */
        handle opcode::PUSH:
            vm.stack.push_back(val(0));
            ++ip;
        handle opcode::POP:
            *loc(0) = vm.stack.back();
            vm.stack.pop_back();
            ++ip;
        handle_else:
            std::cout << "unknown opcode " << op << '\n';
            return;
        }
    }
}

}
