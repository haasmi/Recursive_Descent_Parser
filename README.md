# Recursive_Descent_Parser

This is a parser for the following grammer:

Prg -> event_declaration state_machine
event_declaration -> "event" id_list ";"
id_list -> id "," id_list | id
id -> [A-Z, a-z, _, 0-9]*
state_machine -> state_transition question1
state_transition -> "in" question2 "state" "id" ":" state_list
question2 -> "initial" | " "
state_list -> "on" id_list "goto" id ":" id_list ";"
question1 -> state_machine | " "

Words in " " are terminals

