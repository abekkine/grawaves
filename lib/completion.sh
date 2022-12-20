#!/bin/bash

CODE_TODO=$(grep -r "\/\/ TODO :" * | wc -l)
CODE_DONE=$(grep -r "\/\/ DONE :" * | wc -l)
CODE_TOTAL=$((CODE_TODO+CODE_DONE))
CODE_PERCENT=$((100*CODE_DONE/CODE_TOTAL))

TODO_CLOSED=$(grep "| OPEN |" doc/todo.txt | wc -l)
TODO_OPEN=$(grep "| CLOSED |" doc/todo.txt | wc -l)
TODO_TOTAL=$((TODO_OPEN+TODO_CLOSED))
TODO_PERCENT=$((100*TODO_CLOSED/TODO_TOTAL))

echo "CODE : Completed/Total : $CODE_DONE/$CODE_TOTAL"
echo "CODE : Completion Percentage : %$CODE_PERCENT"

echo "TODO : Completed/Total : $TODO_CLOSED/$TODO_TOTAL"
echo "TODO : Completion Percentage : %$TODO_PERCENT"

