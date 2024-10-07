// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   regex_instr.c                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/10/07 14:43:19 by rgramati          #+#    #+#             //
//   Updated: 2024/10/07 16:13:35 by rgramati         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <stdint.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

// #include <objdumb.h>

#define OBJDUMB_SCRAP_PATTERN \
"<tr>\n *<td><a href=\"[A-Za-z0-9 -/:<>.]*\">([A-Za-z0-9 ]*)</a> (.*?)</td>\n *<td>(.*?)</td>\n *<td>(.*?)</td>\n *<td>(.*?)</td>\n *</tr>"

int	next_instruction(regex_t *reg, char *str, char **remain)
{
	uint32_t	i;
	uint32_t	err;
	regmatch_t	matches[7];

	i = 0;
	err = regexec(reg, str, 7, &matches[0], 0);
	if (err)
		return (1);
	else
	{
		printf("Match :\n");
		while (matches[i].rm_so != -1)
		{
			int len = matches[i].rm_eo - matches[i].rm_so;
			printf("group %d : [%*.*s]\n", i, len, len, str + matches[i].rm_so);
			i++;
		}
		*remain = str + matches[i - 1].rm_eo;
	}
	return (0);
}

uint32_t	parse_instructions(char *file)
{
	regex_t		reg = {0};
	uint32_t	err;

	err = regcomp(&reg, OBJDUMB_SCRAP_PATTERN, REG_EXTENDED);
	if (err)
	{
		printf("Regex pattern compilation failed.\n");
		exit(1);
	}

	while (!next_instruction(&reg, file, &file));

	return (0);
}

