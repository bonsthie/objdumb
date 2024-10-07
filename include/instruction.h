#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <stdint.h>

typedef struct	s_instruction
{
	char					*name;
	uint64_t				bitcode;
	char					*instr;
	char					*desc;
	struct s_instruction	*next;
}	t_instruction;

#define INSTRUCTION_INPUT(enum_value, bitcode, value, definition) enum_value = bitcode,

enum e_instruction
{
#include "instruction_tmp.h"
};

#undef INSTRUCTION_INPUT

#define INSTRUCTION_INPUT(enum_value, bitcode, value, definition) [enum_value] = value,

/* ODR crampte */
char *instruction_table[] = {
#include "instruction_tmp.h"
};

#undef INSTRUCTION_INPUT

#define INSTRUCTION_INPUT(enum_value, bitcode, value, definition) [enum_value] = definition,
char *instruction_definition[] = {
#include "instruction_tmp.h"
};


#endif /* INSTRUCTION_H */


