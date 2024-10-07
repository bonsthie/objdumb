// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   regex_instr.c                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/10/07 14:43:19 by rgramati          #+#    #+#             //
//   Updated: 2024/10/07 19:26:01 by rgramati         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <stdint.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

#include <instruction.h>

#define CAPTURE(X)		"("X")"

#define MATCH_ALNUM		"[A-Za-z0-9]"

#define ZERO_OR_MORE(X)	X"*"

#define CAPTURE_INV(X)	CAPTURE(ZERO_OR_MORE("[^"X"]"))

#define OBJDUMB_SCRAP_PATTERN \
	"<tr>\n *<td><a href=\"\\./"ZERO_OR_MORE(MATCH_ALNUM)"\\.html\">"CAPTURE_INV("<")"</a> "CAPTURE_INV("<")"</td>\n"\
	" *<td>"CAPTURE_INV("<")"</td>\n"\
	" *<td>"CAPTURE_INV("<")"</td>\n"\
	" *<td>"CAPTURE_INV("<")"</td>"

int	next_instruction(regex_t *reg, char *str, char **remain, t_instruction **list)
{
	uint32_t	i;
	uint32_t	err;
	regmatch_t	matches[7];

	(void) list;
	i = 0;
	err = regexec(reg, str, 7, &matches[0], 0);
	if (err)
		return (1);
	else
	{
		for (int j = 0; j < 6; j++)
		{
			int len = matches[i].rm_eo - matches[i].rm_so;
			printf("group %d : [%*.*s]\n", i, len, len, str + matches[i].rm_so);
			i++;
		}
		*remain = str + matches[i - 1].rm_eo;
	}
	return (0);
}

t_instruction	*parse_instructions(char *file)
{
	regex_t			reg = {0};
	t_instruction	*instr = NULL;
	uint32_t		err;

	err = regcomp(&reg, OBJDUMB_SCRAP_PATTERN, REG_EXTENDED);
	if (err)
	{
		printf("Regex pattern compilation failed.\n");
		exit(1);
	}
	while (!next_instruction(&reg, file, &file, &instr));
	return (0);
}
