#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#define INSTRUCTION_INPUT(enum_value, value) enum_value,

enum e_instruction
{
#include "instruction_tmp.h"
};

#undef INSTRUCTION_INPUT

#define INSTRUCTION_INPUT(enum_value, value) [enum_value] = value,

char *instruction_table[] = {
#include "instruction_tmp.h"
};


#endif /* INSTRUCTION_H */
