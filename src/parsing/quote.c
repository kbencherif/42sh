/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** quote
*/

#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "parsing.h"
#include "operator_abstract.h"

void is_quote(char c, bool *in_quote)
{
    if (c == '\'' || c == '"') {
        if (*in_quote == false)
            *in_quote = true;
        else
            *in_quote = false;
    }
}
