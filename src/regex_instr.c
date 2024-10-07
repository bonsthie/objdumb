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

typedef struct	s_instruction
{
	char					*name;
	char					*instr;
	char					*desc;
	struct s_instruction	*next;
}	t_instruction;

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

int main(void)
{
	parse_instructions("    <tr>\n\
      <td><a href=\"./AAA.html\">AAA</a> </td>\n\
      <td>37</td>\n\
      <td></td>\n\
      <td>ASCII adjust AL after addition.</td>\n\
    </tr>\n\
    <tr>\n\
      <td><a href=\"./AAD.html\">AAD</a> </td>\n\
      <td>D5 0A</td>\n\
      <td></td>\n\
      <td>ASCII adjust AX before division.</td>\n\
    </tr>\n\
    <tr>\n\
      <td><a href=\"./AAD.html\">AAD</a> imm8</td>\n\
      <td>D5 ib</td>\n\
      <td></td>\n\
      <td>Adjust AX before division to number base imm8.</td>\n\
    </tr>\n\
    <tr>\n\
      <td><a href=\"./AAM.html\">AAM</a> </td>\n\
      <td>D4 0A</td>\n\
      <td></td>\n\
      <td>ASCII adjust AX after multiply.</td>\n\
    </tr>\n\
    <tr>\n\
      <td><a href=\"./AAM.html\">AAM</a> imm8</td>\n\
      <td>D4 ib</td>\n\
      <td></td>\n\
      <td>Adjust AX after multiply to number base imm8.</td>\n\
    </tr>\n\
");

	return (0);
}

