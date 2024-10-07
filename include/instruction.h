#ifndef INSTRUCTION_H
#define INSTRUCTION_H

typedef struct	s_instruction
{
	char					*name;
	char					*instr;
	char					*desc;
	struct s_instruction	*next;
}	t_instruction;

extern char	*instruction_table[];

extern char	*instruction_definition[];

#define INSTRUCTION_INPUT(enum_value, value, definition) enum_value,

enum e_instruction
{
#include "instruction_tmp.h"
};

#undef INSTRUCTION_INPUT

#endif /* INSTRUCTION_H */
