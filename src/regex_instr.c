// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   regex_instr.c                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/10/07 14:43:19 by rgramati          #+#    #+#             //
//   Updated: 2024/10/07 20:17:07 by rgramati         ###   ########.fr       //
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

void	instr_push(t_instruction **list, t_instruction *new)
{
	if (!list || !new)
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	t_instruction	*tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_instruction	*new_instr(char *name, char *instr, char *desc)
{
	t_instruction	*new;

	new = malloc(sizeof(t_instruction));
	if (new)
	{
		new->name = name;
		new->instr = instr;
		new->desc = desc;
		new->next = NULL;
	}
	return (new);
}

char	*strjoin(char const *s1, char const *s2);

int	next_instruction(regex_t *reg, char *str, char **remain, t_instruction **list)
{
	uint32_t	err;
	regmatch_t	matches[7];

	err = regexec(reg, str, 7, matches, 0);
	if (err)
		return (1);
	else
	{
		str[matches[1].rm_eo] = 0;
		str[matches[2].rm_eo] = 0;
		str[matches[3].rm_eo] = 0;
		str[matches[5].rm_eo] = 0;

		t_instruction	*new = new_instr(strjoin(str + matches[1].rm_so, str + matches[2].rm_so), str + matches[3].rm_so, str + matches[5].rm_so);

		instr_push(list, new);
		*remain = str + matches[5].rm_eo + 1;
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

	t_instruction	*tmp = instr;
	while (tmp)
	{
		printf("INSTRUCTION (\n  name: [%s],\n instr: [%s],\n  desc: [%s]\n)", tmp->name, tmp->instr, tmp->desc);
		tmp = tmp->next;
	}

	return (instr);
}
