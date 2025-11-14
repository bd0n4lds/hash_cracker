#ifndef RULES_H
#define RULES_H

#include <stdbool.h>
#include <stddef.h>

/*
TODO List for rules.h:

1. Rule Types:
   - Define rule_type_t enum:
     * UPPERCASE
     * LOWERCASE
     * CAPITALIZE
     * TOGGLE_CASE
     * REVERSE
     * DUPLICATE
     * APPEND_NUM
     * PREPEND_NUM

2. Public API:
   - rule_compile(rule_string) -> rule_t
   - rule_apply(rule, input, output, outsize)
   - rule_free(rule)
   - is_valid_rule(rule_string)

3. Error Handling:
   - Status codes
   - Error messages
*/

#endif // RULES_H
