#pragma once

#include<cstdint>
#include<memory>
#include<vector>

namespace synacor {

using memory_t = std::uint16_t;
using addr_t = std::uint16_t;
using reg_t = std::uint8_t;

/* Numbers */
constexpr auto MAX_NUM = 32767;

/* Registers */
constexpr auto N_REGS = 8;
constexpr auto REG_START = MAX_NUM + 1;
constexpr auto REG_END = REG_START + N_REGS;

/* Memory (registers are stored alongside memory) */
constexpr auto VM_MEMORY_SIZE = REG_END + 1;

struct vm {
    std::unique_ptr<memory_t[]> memory;
    std::vector<memory_t> stack;

    vm(): memory{new memory_t[VM_MEMORY_SIZE]} {}
};

constexpr memory_t reg(memory_t n)
{
    return REG_START + n;
}

constexpr bool is_register(memory_t num)
{
    return num >= REG_START && num <= REG_END;
}

constexpr reg_t as_register(memory_t num)
{
    return (num % MAX_NUM);
}

}
