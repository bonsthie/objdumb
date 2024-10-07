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

extern char	*instruction_table[];

extern char	*instruction_definition[];

#define INSTRUCTION_INPUT(enum_value, bitcode, value, definition) enum_value = bitcode,

enum e_instruction
{
#include "instruction_tmp.h"
	INSTR_END,
};

#undef INSTRUCTION_INPUT

#endif /* INSTRUCTION_H */


