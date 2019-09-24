# Stack
This program checks a sequence of brackets of different types to see if they're written in the right order

ITMO University homework, 2015.
Task: you have a sequence of opening and closing brackets of different types. Using a stack structure (implemented on array) find out whether the order is correct. If it's not, then print a message explaining the reason (brackets don't match, extra brackets in the sequence, missing the matching bracket) and saying which position causes the problem.

For example, we have a sequence: ({[]])) . Square bracket in position 4 (count starts from 0) doesn't match the curly bracket in position 1. We also have an extra round bracket at the end, but that doesn't matter since the program will exit as soon as it finds the first error.
