#include <string.h> /* for the strcpy() function */
#include <unistd.h> /* for the syscall() function */

#define MAX_STRING_LENGTH 4096 /* configurable number specifying the total maximum amount of allowed characters in a single string */
#define MAX_VARIABLES 64
#define MAX_FUNCTIONS 64

int putchar(char character) { /* prints a character */
	syscall(1, 1, &character, 1);
	return 0;
}

int print(char string[]) { /* prints a list of characters until the function hits a null terminator */
	int i = 0;
	while (string[i] != '\0') {
		putchar(string[i]);
		i += 1;
	}
	return 0;
}

int printd(int input_number) {
	char number[MAX_STRING_LENGTH];
	if (input_number == 0) {
		putchar('0');
		return 0;
	}
	if (input_number < 0) {
		putchar('-');
		input_number = -input_number;
	}
	int i = 0;
	while (input_number > 0) {
		number[i++] = '0' + input_number % 10;
		input_number /= 10;
	}
	while (i--) {
		putchar(number[i]);
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

int main(int argc, char* argv[]) {
	if (argc != 2) {
		print("Usage: ");
		print(argv[0]);
		print(" <tokens>");
		putchar('\n');
		return 1;
	}
	int byte_pointer = 0;
	char variables[MAX_VARIABLES][MAX_STRING_LENGTH];
	int variable_pointer = 0;
	char functions[MAX_FUNCTIONS][MAX_STRING_LENGTH];
	int function_pointer = 0;
	while (argv[1][byte_pointer] != '\0') {
		if (eqnext(argv[1], &byte_pointer, "DEFINE_VARIABLE ") == 1) {
			strcpy(variables[variable_pointer], get_to_next_char(argv[1], &byte_pointer, '\n'));
			variable_pointer += 1;
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "DEFINE_FUNCTION ") == 1) {
			strcpy(functions[function_pointer], get_to_next_char(argv[1], &byte_pointer, '\n'));
			function_pointer += 1;
			continue;
		}
		byte_pointer += 1;
	}
	byte_pointer = 0;
	char do_add[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int do_add_assign = 0;
	while (argv[1][byte_pointer] != '\0') {
		if (eqnext(argv[1], &byte_pointer, "DEFINE_FUNCTION ") == 1) {
			putchar('#');
			putchar('\n');
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "LINE_END")) { // Flush expression
			while (do_add[0] != '\0') {
				putchar(do_add[length(do_add) - 1]);
				putchar('\n');
				do_add[length(do_add) - 1] = '\0';
			}
			if (do_add_assign == 1) {
				putchar('`');
				putchar('\n');
				do_add_assign = 0;
			}
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "IDENTIFIER ") == 1) {
			int i = 0;
			int stable_zero = 0;
			char target[MAX_STRING_LENGTH];
			strcpy(target, get_to_next_char(argv[1], &byte_pointer, '\n'));
			while (eqnext(variables[i], &stable_zero, target) == 0 && variables[i][0] != 0) {
				stable_zero = 0;
				i++;
			}
			if (variables[i][0] == 0) {
				int j = 0;
				stable_zero = 0;
				while (eqnext(functions[j], &stable_zero, target) == 0 && functions[j][0] != 0) {
					stable_zero = 0;
					j++;
				}
				printd(j);
				print("| 1| & _");
				putchar('\n');
			} else {
				print("$ ");
				printd(i * 8 + 2048);
				print("| +\n");
			}
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "NUMBER ") == 1) {
			print(get_to_next_char(argv[1], &byte_pointer, '\n'));
			print("|\n");
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "CHARACTER ") == 1) {
			print(get_to_next_char(argv[1], &byte_pointer, '\n'));
			print("|\n");
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "OPERATOR_DEREFERENCE") == 1) {
			putchar('@');
			putchar('\n');
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "OPERATOR_ASSIGN") == 1) {
			do_add_assign = 1;
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "OPERATOR_ADD") == 1) {
			do_add[length(do_add)] = '+';
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "OPERATOR_SUBTRACT") == 1) {
			do_add[length(do_add)] = '-';
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "OPERATOR_BITWISE_OR") == 1) {
			do_add[length(do_add)] = '/';
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "OPERATOR_BITWISE_AND") == 1) {
			do_add[length(do_add)] = ';';
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "OPERATOR_BITWISE_NOT") == 1) {
			do_add[length(do_add)] = '~';
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "CONDITION_GREATER_THAN") == 1) {
			do_add[length(do_add)] = '>';
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "CONDITION_LESS_THAN") == 1) {
			do_add[length(do_add)] = '<';
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "CONDITION_EQUAL") == 1) {
			do_add[length(do_add)] = '=';
			continue;
		}
		byte_pointer += 1;
	}
	return 0;
}