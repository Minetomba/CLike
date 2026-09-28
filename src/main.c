#include <string.h> /* for the strcpy() function */
#include <unistd.h> /* for the syscall() function */
#include <stdlib.h> /* for the atoi() function */

#define MAX_STRING_LENGTH 4096 /* configurable number specifying the total maximum amount of allowed characters in a single string */
#define MAX_VARIABLES 64
#define MAX_FUNCTIONS 64
#define MAX_TOKEN_BYTES 16384
#define MAX_DEBUG_LENGTH 16384

int putcharacter(char character) { /* prints a character */
	syscall(1, 1, &character, 1);
	return 0;
}

int print(char string[]) { /* prints a list of characters until the function hits a null terminator */
	int i = 0;
	while (string[i] != '\0') {
		putcharacter(string[i]);
		i += 1;
	}
	return 0;
}

int printd(int input_number) {
	char number[MAX_STRING_LENGTH];
	if (input_number == 0) {
		putcharacter('0');
		return 0;
	}
	if (input_number < 0) {
		putcharacter('-');
		input_number = -input_number;
	}
	int i = 0;
	while (input_number > 0) {
		number[i++] = '0' + input_number % 10;
		input_number /= 10;
	}
	while (i--) {
		putcharacter(number[i]);
	}
	return 0;
}

int length(char buffer[]) { /* returns the amount of items in a string before a null terminator */
	int i = 0;
	while (buffer[i] != '\0') i += 1;
	return i;
}

int eqnext(char string[], int* start_index, char compare[]) { /* returns 1 if equal, returns 0 if not */
	int current_index = 0;
	while (compare[current_index] != '\0') {
		if (string[current_index + *start_index] != compare[current_index]) {
			return 0;
		}
		current_index += 1;
	}
	*start_index += length(compare);
	return 1;
}

char* get_to_next_char(char string[], int* start_index, char end) { /* jump to the next character that appears and happens to be the specified end character, and get the characters between the start and end in a string */
	static char temp_string[MAX_STRING_LENGTH];
	int string_pointer = 0;
	temp_string[0] = '\0';
	while (string[*start_index + string_pointer] != end && string[*start_index + string_pointer] != '\0') {
		temp_string[string_pointer] = string[*start_index + string_pointer];
		temp_string[string_pointer + 1] = '\0';
		string_pointer += 1;
	}
	*start_index += length(temp_string) + 1;
	return temp_string;
}

char* get_to_next_string(char string[], int* start_index, char end[]) { /* jump to the next string that appears and happens to be the specified end character, and get the characters between the start and end in a string */
	static char temp_string[MAX_STRING_LENGTH];
	int string_pointer = 0;
	temp_string[0] = '\0';
	while (string[*start_index + string_pointer] != '\0') {
		int temp = *start_index + string_pointer;
		if (eqnext(string, &temp, end) == 1) {
			*start_index = temp;
			break;
		}
		temp_string[string_pointer] = string[*start_index + string_pointer];
		temp_string[string_pointer + 1] = '\0';
		string_pointer += 1;
	}
	return temp_string;
}

char tokens[MAX_TOKEN_BYTES];
int token_pointer = 0;
int stable_zero = 0;

int putcharacterv1(char c) {
	tokens[token_pointer] = c;
	token_pointer++;
	return 0;
}
int printv1(char string[]) {
	int i = 0;
	while (string[i] != '\0') {
		tokens[token_pointer] = string[i];
		token_pointer++;
		i++;
	}
	return 0;
}

char to_interpret[MAX_TOKEN_BYTES];
int interpret_pointer = 0;

int putcharacterv2(char c) {
	to_interpret[interpret_pointer] = c;
	interpret_pointer++;
	return 0;
}
int printv2(char string[]) {
	int i = 0;
	while (string[i] != '\0') {
		to_interpret[interpret_pointer] = string[i];
		interpret_pointer++;
		i++;
	}
	return 0;
}
int printdv2(int input_number) {
	char number[MAX_STRING_LENGTH];
	if (input_number == 0) {
		putcharacterv2('0');
		return 0;
	}
	if (input_number < 0) {
		putcharacterv2('-');
		input_number = -input_number;
	}
	int i = 0;
	while (input_number > 0) {
		number[i++] = '0' + input_number % 10;
		input_number /= 10;
	}
	while (i--) {
		putcharacterv2(number[i]);
	}
	return 0;
}

char v3[MAX_TOKEN_BYTES];
int v3p = 0;

int putcharacterv3(char c) {
	v3[v3p] = c;
	v3p++;
	return 0;
}
int printv3(char string[]) {
	int i = 0;
	while (string[i] != '\0') {
		v3[v3p] = string[i];
		v3p++;
		i++;
	}
	return 0;
}
int printdv3(int input_number) {
	char number[MAX_STRING_LENGTH];
	if (input_number == 0) {
		putcharacterv3('0');
		return 0;
	}
	if (input_number < 0) {
		putcharacterv3('-');
		input_number = -input_number;
	}
	int i = 0;
	while (input_number > 0) {
		number[i++] = '0' + input_number % 10;
		input_number /= 10;
	}
	while (i--) {
		putcharacterv3(number[i]);
	}
	return 0;
}

char debug[MAX_TOKEN_BYTES];
int debug_pointer = 0;

int putchardebug(char c) {
	debug[debug_pointer] = c;
	debug_pointer++;
	return 0;
}
int printdebug(char string[]) {
	int i = 0;
	while (string[i] != '\0') {
		debug[debug_pointer] = string[i];
		debug_pointer++;
		i++;
	}
	return 0;
}
int printdebugd(int input_number) {
	char number[MAX_STRING_LENGTH];
	if (input_number == 0) {
		putchardebug('0');
		return 0;
	}
	if (input_number < 0) {
		putchardebug('-');
		input_number = -input_number;
	}
	int i = 0;
	while (input_number > 0) {
		number[i++] = '0' + input_number % 10;
		input_number /= 10;
	}
	while (i--) {
		putchardebug(number[i]);
	}
	return 0;
}

typedef __INTPTR_TYPE__ st; /* Standard type */

int interpret() {
	st stack[MAX_VARIABLES];
	st stack_pointer = 0;
	st call_stack[MAX_FUNCTIONS];
	st call_pointer = 0;
	st labels[MAX_FUNCTIONS];
	st label_pointer = 0;
	st pc = 0;
	st last_construct = 0;
	while (to_interpret[pc] != '\0') {
		if (to_interpret[pc] == '#') {
			labels[label_pointer] = pc + 1;
			label_pointer += 1;
		}
		pc += 1;
	}
	pc = 0;
	while (to_interpret[pc] != '\0') {
		st c = to_interpret[pc];
		if (c == '|') { /* Pushing the constructed number */
			if (stack_pointer >= MAX_VARIABLES) {
				goto debug_zone;
			}
			stack_pointer += 1;
			stack[stack_pointer] = last_construct;
			last_construct = 0;
		} else if (c >= '0' && c <= '9') { /* Constructing the number */
			last_construct = last_construct * 10 + (int)c + -48;
		} else if (c == '@') { /* Get */
			stack[stack_pointer] = *(st*)stack[stack_pointer];
		} else if (c == '!') { /* Store */
			if (stack_pointer <= 1) {
				goto debug_zone;
			}
			*(st*)stack[stack_pointer] = stack[stack_pointer - 1];
			stack_pointer -= 2;
		} else if (c == '+') { /* Add */
			if (stack_pointer <= 0) {
				goto debug_zone;
			}
			stack[stack_pointer - 1] = stack[stack_pointer - 1] + stack[stack_pointer];
			stack_pointer -= 1;
		} else if (c == '/') { /* Or */
			if (stack_pointer <= 0) {
				goto debug_zone;
			}
			stack[stack_pointer - 1] = stack[stack_pointer - 1] | stack[stack_pointer];
			stack_pointer -= 1;
		} else if (c == ';') { /* And */
			if (stack_pointer <= 0) {
				goto debug_zone;
			}
			stack[stack_pointer - 1] = stack[stack_pointer - 1] & stack[stack_pointer];
			stack_pointer -= 1;
		} else if (c == '~') { /* Not */
			stack[stack_pointer] = ~stack[stack_pointer];
		} else if (c == '<') { /* Less than */
			if (stack_pointer <= 1) {
				goto debug_zone;
			}
			if (stack[stack_pointer - 1] < stack[stack_pointer]) {
				stack[stack_pointer - 1] = 1;
			} else {
				stack[stack_pointer - 1] = 0;
			}
			stack_pointer -= 2;
		} else if (c == ',') {
			if (stack_pointer <= 0) {
				goto debug_zone;
			}
			stack_pointer -= 1;
		} else if (c == '>') { /* Greater than */
			if (stack_pointer <= 1) {
				goto debug_zone;
			}
			if (stack[stack_pointer - 1] > stack[stack_pointer]) {
				stack[stack_pointer - 1] = 1;
			} else {
				stack[stack_pointer - 1] = 0;
			}
			stack_pointer -= 2;
		} else if (c == '=') { /* Is equal to */
			if (stack_pointer <= 1) {
				goto debug_zone;
			}
			if (stack[stack_pointer - 1] == stack[stack_pointer]) {
				stack[stack_pointer - 1] = 1;
			} else {
				stack[stack_pointer - 1] = 0;
			}
			stack_pointer -= 2;
		} else if (c == '?') { /* Branch */
			if (stack_pointer <= 1) {
				goto debug_zone;
			}
			if (stack[stack_pointer] != 0) {
				pc = stack[stack_pointer - 1] - 1;
			}
			stack_pointer -= 2;
		} else if (c == '_') { /* Swap */
			if (stack_pointer <= 0) {
				goto debug_zone;
			}
			st temp1 = stack[stack_pointer];
			st temp2 = stack[stack_pointer - 1];
			stack[stack_pointer] = temp2;
			stack[stack_pointer - 1] = temp1;
		} else if (c == '%') { /* Duplicate */
			if (stack_pointer >= MAX_VARIABLES) {
				goto debug_zone;
			}
			stack[stack_pointer + 1] = stack[stack_pointer];
			stack_pointer++;
		} else if (c == '&') { /* Dereference label ID */
			stack[stack_pointer] = labels[stack[stack_pointer]];
		} else if (c == '$') { /* Stack base address */
			if (stack_pointer >= MAX_VARIABLES) {
				goto debug_zone;
			}
			stack_pointer += 1;
			stack[stack_pointer] = (st)&stack[0];
		} else if (c == '`') { /* Call */
			if (call_pointer >= MAX_FUNCTIONS) {
				goto debug_zone;
			}
			if (stack_pointer <= 1) {
				goto debug_zone;
			}
			if (stack[stack_pointer] != 0) {
				call_stack[call_pointer] = pc + 1;
				call_pointer += 1;
				pc = stack[stack_pointer - 1] - 1;
			}
			stack_pointer -= 2;
		} else if (c == ':') { /* Return */
			if (call_pointer <= 0) {
				goto debug_zone;
			}
			call_pointer -= 1;
			pc = call_stack[call_pointer];
		} else if (c == '-') { /* Pop from call stack */
			if (call_pointer <= 0) {
				goto debug_zone;
			}
			call_pointer -= 1;
		}
		pc += 1;
	}
	goto skip_debug_zone;
	debug_zone:
		printdebug("[DEBUG] Current token: ");
		printdebugd(to_interpret[pc]);
		printdebug("\n");
		printdebug("[DEBUG] Program counter value: ");
		printdebugd(pc);
		printdebug("\n");
		printdebug("[DEBUG] Call stack pointer value: ");
		printdebugd(call_pointer);
		printdebug("\n");
		printdebug("[DEBUG] Stack pointer value: ");
		printdebugd(stack_pointer);
		printdebug("\n");
		printdebug("[DEBUG] Last construct value: ");
		printdebugd(last_construct);
		printdebug("\n");
		return 1;
	skip_debug_zone:
		return 0;
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		print("Clike - v31 (stable)\n");
		print("| Usage: ");
		print(argv[0]);
		print(" <code> <run/build>\n");
		return 1;
	}
	int byte_pointer = 0;
	while (argv[1][byte_pointer] != '\0') {
		if (eqnext(argv[1], &byte_pointer, "continue") == 1) {
			printv1("LOOP_CONTINUE");
			putcharacterv1('\n');
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "break") == 1) {
			printv1("LOOP_BREAK");
			putcharacterv1('\n');
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "while") == 1) {
			printv1("WHILE_LOOP");
			putcharacterv1('\n');
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "return") == 1) {
			printv1("FUNCTION_RETURN");
			putcharacterv1('\n');
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "if") == 1) {
			printv1("IF_CONDITION");
			putcharacterv1('\n');
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "/*") == 1) {
			get_to_next_string(argv[1], &byte_pointer, "*/");
			continue;
		}
		if (argv[1][byte_pointer] >= (int)'0' && argv[1][byte_pointer] <= (int)'9') {
			printv1("NUMBER ");
			while (argv[1][byte_pointer] >= (int)'0' && argv[1][byte_pointer] <= (int)'9') {
				putcharacterv1(argv[1][byte_pointer]);
				byte_pointer += 1;
			}
			putcharacterv1('\n');
			continue;
		}
		if (argv[1][byte_pointer] == '[') {
			byte_pointer += 1;
			printv1("ARRAY_OPEN");
			putcharacterv1('\n');
			continue;
		}
		if (argv[1][byte_pointer] == ']') {
			byte_pointer += 1;
			printv1("ARRAY_CLOSE");
			putcharacterv1('\n');
			continue;
		}
		if (argv[1][byte_pointer] == '{') {
			byte_pointer += 1;
			printv1("BLOCK_OPEN");
			putcharacterv1('\n');
			continue;
		}
		if (argv[1][byte_pointer] == '}') {
			byte_pointer += 1;
			printv1("BLOCK_CLOSE");
			putcharacterv1('\n');
			continue;
		}
		if (argv[1][byte_pointer] == '(') {
			byte_pointer += 1;
			printv1("PARANTHESES_OPEN");
			putcharacterv1('\n');
			continue;
		}
		if (argv[1][byte_pointer] == ')') {
			byte_pointer += 1;
			printv1("PARANTHESES_CLOSE");
			putcharacterv1('\n');
			continue;
		}
		if (argv[1][byte_pointer] == ',') {
			byte_pointer += 1;
			printv1("COMMA");
			putcharacterv1('\n');
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "==") == 1) {
			printv1("CONDITION_EQUAL");
			putcharacterv1('\n');
			continue;
		}
		if (argv[1][byte_pointer] == '*') {
			byte_pointer += 1;
			printv1("OPERATOR_DEREFERENCE");
			putcharacterv1('\n');
			continue;
		}
		if (argv[1][byte_pointer] == '=') {
			byte_pointer += 1;
			printv1("OPERATOR_ASSIGN");
			putcharacterv1('\n');
			continue;
		}
		if (argv[1][byte_pointer] == '+') {
			byte_pointer += 1;
			printv1("OPERATOR_ADD");
			putcharacterv1('\n');
			continue;
		}
		if (argv[1][byte_pointer] == '-') {
			byte_pointer += 1;
			printv1("OPERATOR_SUBTRACT");
			putcharacterv1('\n');
			continue;
		}
		if (argv[1][byte_pointer] == '&') {
			byte_pointer += 1;
			printv1("OPERATOR_BITWISE_AND");
			putcharacterv1('\n');
			continue;
		}
		if (argv[1][byte_pointer] == '|') {
			byte_pointer += 1;
			printv1("OPERATOR_BITWISE_OR");
			putcharacterv1('\n');
			continue;
		}
		if (argv[1][byte_pointer] == '~') {
			byte_pointer += 1;
			printv1("OPERATOR_BITWISE_NOT");
			putcharacterv1('\n');
			continue;
		}
		if (argv[1][byte_pointer] == '>') {
			byte_pointer += 1;
			printv1("CONDITION_GREATER_THAN");
			putcharacterv1('\n');
			continue;
		}
		if (argv[1][byte_pointer] == '<') {
			byte_pointer += 1;
			printv1("CONDITION_LESS_THAN");
			putcharacterv1('\n');
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "return") == 1) {
			printv1("RETURN");
			putcharacterv1('\n');
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "#stack") == 1) {
			printv1("LATEST");
			putcharacterv1('\n');
		}
		if (argv[1][byte_pointer] == ';') {
			byte_pointer += 1;
			printv1("FLUSH_EXPRESSIONS");
			putcharacterv1('\n');
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "substack") == 1) {
			printv1("CLEAR_STACK");
			putcharacterv1('\n');
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "subcall") == 1) {
			printv1("CLEAR_CALL");
			putcharacterv1('\n');
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "var") == 1) {
			printv1("DEFINE_VARIABLE ");
			byte_pointer += 1;
			while (!((argv[1][byte_pointer] >= 97 && argv[1][byte_pointer] <= 122) || (argv[1][byte_pointer] >= 65 && argv[1][byte_pointer] <= 90) || argv[1][byte_pointer] == '_')) byte_pointer += 1;
			while ((argv[1][byte_pointer] >= 97 && argv[1][byte_pointer] <= 122) || (argv[1][byte_pointer] >= 65 && argv[1][byte_pointer] <= 90) || argv[1][byte_pointer] == '_') {
				putcharacterv1(argv[1][byte_pointer]);
				byte_pointer += 1;
			}
			putcharacterv1('\n');
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "arr") == 1) {
			printv1("DEFINE_ARRAY ");
			byte_pointer += 1;
			while (!((argv[1][byte_pointer] >= 97 && argv[1][byte_pointer] <= 122) || (argv[1][byte_pointer] >= 65 && argv[1][byte_pointer] <= 90) || argv[1][byte_pointer] == '_')) byte_pointer += 1;
			while ((argv[1][byte_pointer] >= 97 && argv[1][byte_pointer] <= 122) || (argv[1][byte_pointer] >= 65 && argv[1][byte_pointer] <= 90) || argv[1][byte_pointer] == '_') {
				putcharacterv1(argv[1][byte_pointer]);
				byte_pointer += 1;
			}
			putcharacterv1('\n');
			while (!(argv[1][byte_pointer] >= '0' && argv[1][byte_pointer] <= '9')) byte_pointer += 1;
			while (argv[1][byte_pointer] >= '0' && argv[1][byte_pointer] <= '9') {
				putcharacterv1(argv[1][byte_pointer]);
				byte_pointer += 1;
			}
			putcharacterv1('\n');
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "fn") == 1) {
			printv1("DEFINE_FUNCTION ");
			byte_pointer += 1;
			while (!((argv[1][byte_pointer] >= 97 && argv[1][byte_pointer] <= 122) || (argv[1][byte_pointer] >= 65 && argv[1][byte_pointer] <= 90) || argv[1][byte_pointer] == '_')) byte_pointer += 1;
			while ((argv[1][byte_pointer] >= 97 && argv[1][byte_pointer] <= 122) || (argv[1][byte_pointer] >= 65 && argv[1][byte_pointer] <= 90) || argv[1][byte_pointer] == '_') {
				putcharacterv1(argv[1][byte_pointer]);
				byte_pointer += 1;
			}
			putcharacterv1('\n');
			continue;
		}
		if ((argv[1][byte_pointer] >= 97 && argv[1][byte_pointer] <= 122) || (argv[1][byte_pointer] >= 65 && argv[1][byte_pointer] <= 90) || argv[1][byte_pointer] == '_') {
			printv1("IDENTIFIER ");
			while ((argv[1][byte_pointer] >= 97 && argv[1][byte_pointer] <= 122) || (argv[1][byte_pointer] >= 65 && argv[1][byte_pointer] <= 90) || argv[1][byte_pointer] == '_') {
				putcharacterv1(argv[1][byte_pointer]);
				byte_pointer += 1;
			}
			putcharacterv1('\n');
			continue;
		}
		byte_pointer += 1;
	}
	byte_pointer = 0;
	char variables[MAX_VARIABLES][MAX_STRING_LENGTH] = {0};
	int variable_pointer = 0;
	char functions[MAX_FUNCTIONS][MAX_STRING_LENGTH] = {0};
	int function_pointer = 0;
	while (tokens[byte_pointer] != '\0') {
		if (eqnext(tokens, &byte_pointer, "DEFINE_VARIABLE ") == 1) {
			strcpy(variables[variable_pointer], get_to_next_char(tokens, &byte_pointer, '\n'));
			variable_pointer += 1;
			continue;
		}
		if (eqnext(tokens, &byte_pointer, "DEFINE_ARRAY ") == 1) {
			strcpy(variables[variable_pointer], get_to_next_char(tokens, &byte_pointer, '\n'));
			variable_pointer += atoi(get_to_next_char(tokens, &byte_pointer, '\n'));
			continue;
		}
		if (eqnext(tokens, &byte_pointer, "DEFINE_FUNCTION ") == 1) {
			strcpy(functions[function_pointer], get_to_next_char(tokens, &byte_pointer, '\n'));
			function_pointer += 2;
			continue;
		}
		byte_pointer += 1;
	}
	byte_pointer = 0;
	char do_add[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int do_add_assign = 0;
	int do_add_if = 0;
	int do_add_store = 0;
	while (tokens[byte_pointer] != '\0') {
		if (eqnext(tokens, &byte_pointer, "DEFINE_FUNCTION ") == 1) {
			char target[MAX_STRING_LENGTH];
			strcpy(target, get_to_next_char(tokens, &byte_pointer, '\n'));
			int j = 0;
			stable_zero = 0;
			while (eqnext(functions[j * 2], &stable_zero, target) == 0 && functions[j * 2][0] != 0) {
				stable_zero = 0;
				j++;
			}
			printdv2(j * 2 + 1);
			printv2("| & 1| ? #");
			putcharacterv2('\n');
			continue;
		}
		if (eqnext(tokens, &byte_pointer, "BLOCK_CLOSE") == 1) {
			putcharacterv2('#');
			putcharacterv2('\n');
			continue;
		}
		if (eqnext(tokens, &byte_pointer, "FLUSH_EXPRESSIONS") == 1) {
			if (do_add_assign == 1) {
				putcharacterv2('_');
				putcharacterv2('!');
				putcharacterv2('\n');
				do_add_assign = 0;
			}
			if (do_add_if == 1) {
				putcharacterv2('_');
				putcharacterv2('`');
				putcharacterv2('\n');
				do_add_if = 0;
			}
			if (do_add_store == 1) {
				putcharacterv2('_');
				putcharacterv2('!');
				do_add_store = 0;
			}
			printv2(v3);
		}
		if (eqnext(tokens, &byte_pointer, "IDENTIFIER ") == 1) {
			int i = 0;
			char target[MAX_STRING_LENGTH];
			strcpy(target, get_to_next_char(tokens, &byte_pointer, '\n'));
			stable_zero = 0;
			while (eqnext(variables[i], &stable_zero, target) == 0 && variables[i][0] != 0) {
				stable_zero = 0;
				i++;
			}
			if (variables[i][0] == 0) {
				int j = 0;
				stable_zero = 0;
				while (eqnext(functions[j * 2], &stable_zero, target) == 0 && functions[j * 2][0] != 0) {
					stable_zero = 0;
					j++;
				}
				printdv3(j);
				printv3("| & 1| `");
				putcharacterv3('\n');
			} else {
				printv2("$ ");
				printdv2(i * 8 + 2048);
				printv2("| +\n");
			}
			continue;
		}
		if (eqnext(tokens, &byte_pointer, "IF_CONDITION") == 1) {
			do_add_if = 1;
			continue;
		}
		if (eqnext(tokens, &byte_pointer, "RETURN") == 1) {
			printv2(":\n");
			continue;
		}
		if (eqnext(tokens, &byte_pointer, "CLEAR_STACK") == 1) {
			printv2(",\n");
			continue;
		}
		if (eqnext(tokens, &byte_pointer, "CLEAR_CALL") == 1) {
			printv2("-\n");
			continue;
		}
		if (eqnext(tokens, &byte_pointer, "LATEST") == 1) {
			printv2("_\n");
			continue;
		}
		if (eqnext(tokens, &byte_pointer, "NUMBER ") == 1) {
			printv2(get_to_next_char(tokens, &byte_pointer, '\n'));
			printv2("|\n");
			while (do_add[0] != '\0') {
				putcharacterv2(do_add[length(do_add) - 1]);
				putcharacterv2('\n');
				do_add[length(do_add) - 1] = '\0';
			}
			putcharacterv2('\n');
			continue;
		}
		if (eqnext(tokens, &byte_pointer, "OPERATOR_DEREFERENCE") == 1) {
			putcharacterv2('@');
			putcharacterv2('\n');
			continue;
		}
		if (eqnext(tokens, &byte_pointer, "OPERATOR_ASSIGN") == 1) {
			do_add_assign = 1;
			continue;
		}
		if (eqnext(tokens, &byte_pointer, "OPERATOR_ADD") == 1) {
			do_add[length(do_add)] = '+';
			continue;
		}
		if (eqnext(tokens, &byte_pointer, "OPERATOR_SUBTRACT") == 1) {
			do_add[length(do_add)] = '+';
			do_add[length(do_add)] = '+';
			do_add[length(do_add)] = '|';
			do_add[length(do_add)] = '1';
			do_add[length(do_add)] = '~';
			continue;
		}
		if (eqnext(tokens, &byte_pointer, "OPERATOR_BITWISE_OR") == 1) {
			do_add[length(do_add)] = '/';
			continue;
		}
		if (eqnext(tokens, &byte_pointer, "OPERATOR_BITWISE_AND") == 1) {
			do_add[length(do_add)] = ';';
			continue;
		}
		if (eqnext(tokens, &byte_pointer, "OPERATOR_BITWISE_NOT") == 1) {
			do_add[length(do_add)] = '~';
			continue;
		}
		if (eqnext(tokens, &byte_pointer, "CONDITION_GREATER_THAN") == 1) {
			do_add[length(do_add)] = '>';
			continue;
		}
		if (eqnext(tokens, &byte_pointer, "CONDITION_LESS_THAN") == 1) {
			do_add[length(do_add)] = '<';
			continue;
		}
		if (eqnext(tokens, &byte_pointer, "CONDITION_EQUAL") == 1) {
			do_add[length(do_add)] = '=';
			continue;
		}
		if (eqnext(tokens, &byte_pointer, "ARRAY_CLOSE") == 1) {
			while (do_add[0] != '\0') {
				putcharacterv2(do_add[length(do_add) - 1]);
				putcharacterv2('\n');
				do_add[length(do_add) - 1] = '\0';
			}
			putcharacterv2('\n');
			printv2("%+%+%++\n");
			continue;
		}
		if (eqnext(tokens, &byte_pointer, "COMMA") == 1) {
			while (do_add[0] != '\0') {
				putcharacterv2(do_add[length(do_add) - 1]);
				putcharacterv2('\n');
				do_add[length(do_add) - 1] = '\0';
			}
			putcharacterv2('\n');
		}
		if (eqnext(tokens, &byte_pointer, "PARANTHESES_CLOSE") == 1) {
			while (do_add[0] != '\0') {
				putcharacterv2(do_add[length(do_add) - 1]);
				putcharacterv2('\n');
				do_add[length(do_add) - 1] = '\0';
			}
			putcharacterv2('\n');
		}
		byte_pointer += 1;
	}
	stable_zero = 0;
	if (eqnext(argv[2], &stable_zero, "run") == 1) {
		interpret();
	}
	return 0;
}