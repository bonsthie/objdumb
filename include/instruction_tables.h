// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   instruction_tables.h                               :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/10/07 19:21:55 by rgramati          #+#    #+#             //
//   Updated: 2024/10/07 19:25:29 by rgramati         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

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
