// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.c                                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/10/07 19:27:22 by rgramati          #+#    #+#             //
//   Updated: 2024/10/07 19:50:45 by rgramati         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <objdumb.h>



int generate_instruction_file(t_instruction *instructions);

int main()
{
	char *result = scrap_url("https://shell-storm.org/x86doc/");
	// printf("%s\n", result);
	t_instruction	*list = parse_instructions(result);

	generate_instruction_file(list);
}
