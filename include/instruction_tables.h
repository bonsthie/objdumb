#ifndef INSTRUCTION_TABLE_H
#define INSTRUCTION_TABLE_H

#include <instruction.h>

#define INSTRUCTION_INPUT(enum_value, value, definition) [enum_value] = value,

/* ODR crampte */
char *instruction_table[] = {
#include "instruction_tmp.h"
};

#undef INSTRUCTION_INPUT

#define INSTRUCTION_INPUT(enum_value, value, definition) [enum_value] = definition,
char *instruction_definition[] = {
#include "instruction_tmp.h"
};

#endif	// INSTRUCTION_TABLE_H
