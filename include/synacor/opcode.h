#pragma once

#include<cstdint>

#include<synacor/vm.h>

namespace synacor {

enum opcode : memory_t {
    HALT = 0,
    SET,
    PUSH,
    POP,
    EQ,
    GT,
    JMP,
    JT,
    JF,
    ADD,
    MULT,
    MOD,
    AND,
    OR,
    NOT,
    RMEM,
    WMEM,
    CALL,
    RET,
    OUT,
    IN,
    NOOP,
    MAX
};

};
