#include "instruction.h"
#include <stdio.h>

int generate_instruction_file(t_instruction *instructions)
{
	 FILE *file = fopen("include/instruction_tmp.h", "w");

    if (!file) {
        perror("Error opening file");
        return (1);
    }

    t_instruction *current = instructions;
    while (current) {
        fprintf(file, "INSTRUCTION_INPUT(%s, \"%s\", \"%s\")\n",
                current->name, current->instr, current->desc);
        current = current->next;
    }

    fclose(file);
	return (0);
}
