#include <unistd.h> /* for the syscall() function */

#define MAX_STRING_LENGTH 4096 /* configurable number specifying the total maximum amount of allowed characters in a single string */

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

int length(char buffer[]) { /* returns the amount of items in a string before a null terminator */
	int i = 0;
	while (buffer[i] != '\0') i += 1;
	return i;
}

int eqnext(char string[], int* start_index, char compare[]) { /* returns 1 if equal, returns 0 if not */
	int current_index = 0;
	while (string[current_index + *start_index] != '\0' && compare[current_index] != '\0') {
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
	while (string[*start_index + string_pointer] != end) {
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
		print(" <code>");
		putchar('\n');
		return 1;
	}
	int byte_pointer = 0;
	while (argv[1][byte_pointer] != '\0') {
		if (eqnext(argv[1], &byte_pointer, "continue") == 1) {
			print("LOOP_CONTINUE");
			putchar('\n');
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "break") == 1) {
			print("LOOP_BREAK");
			putchar('\n');
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "while") == 1) {
			print("WHILE_LOOP");
			putchar('\n');
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "return") == 1) {
			print("FUNCTION_RETURN");
			putchar('\n');
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "if") == 1) {
			print("IF_CONDITION");
			putchar('\n');
			continue;
		}
		// if (argv[1][byte_pointer] == '"') {
		// 	byte_pointer += 1;
		// 	print("STRING ");
		// 	print(get_to_next_char(argv[1], &byte_pointer, '"'));
		// 	putchar('\n');
		// 	continue;
		// }
		// if (argv[1][byte_pointer] == 39) {
		// 	byte_pointer += 1;
		// 	print("CHARACTER ");
		// 	print(get_to_next_char(argv[1], &byte_pointer, 39));
		// 	putchar('\n');
		// 	continue;
		// }
		if (eqnext(argv[1], &byte_pointer, "/*") == 1) {
			get_to_next_string(argv[1], &byte_pointer, "*/");
			continue;
		}
		if (argv[1][byte_pointer] >= (int)'0' && argv[1][byte_pointer] <= (int)'9') {
			print("NUMBER ");
			while (argv[1][byte_pointer] >= (int)'0' && argv[1][byte_pointer] <= (int)'9') {
				putchar(argv[1][byte_pointer]);
				byte_pointer += 1;
			}
			putchar('\n');
			continue;
		}
		if (argv[1][byte_pointer] == '[') {
			byte_pointer += 1;
			print("ARRAY_OPEN");
			putchar('\n');
			continue;
		}
		if (argv[1][byte_pointer] == ']') {
			byte_pointer += 1;
			print("ARRAY_CLOSE");
			putchar('\n');
			continue;
		}
		if (argv[1][byte_pointer] == '{') {
			byte_pointer += 1;
			print("BLOCK_OPEN");
			putchar('\n');
			continue;
		}
		if (argv[1][byte_pointer] == '}') {
			byte_pointer += 1;
			print("BLOCK_CLOSE");
			putchar('\n');
			continue;
		}
		if (argv[1][byte_pointer] == '(') {
			byte_pointer += 1;
			print("PARANTHESES_OPEN");
			putchar('\n');
			continue;
		}
		if (argv[1][byte_pointer] == ')') {
			byte_pointer += 1;
			print("PARANTHESES_CLOSE");
			putchar('\n');
			continue;
		}
		if (argv[1][byte_pointer] == ';') {
			byte_pointer += 1;
			print("LINE_END");
			putchar('\n');
			continue;
		}
		if (argv[1][byte_pointer] == ',') {
			byte_pointer += 1;
			print("COMMA");
			putchar('\n');
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "==") == 1) {
			print("CONDITION_EQUAL");
			putchar('\n');
			continue;
		}
		// if (eqnext(argv[1], &byte_pointer, ">>") == 1) {
		// 	print("OPERATOR_SHIFT_RIGHT");
		// 	putchar('\n');
		// 	continue;
		// }
		// if (eqnext(argv[1], &byte_pointer, "<<") == 1) {
		// 	print("OPERATOR_SHIFT_LEFT");
		// 	putchar('\n');
		// 	continue;
		// }
		if (argv[1][byte_pointer] == '*') {
			byte_pointer += 1;
			print("OPERATOR_DEREFERENCE");
			putchar('\n');
			continue;
		}
		if (argv[1][byte_pointer] == '=') {
			byte_pointer += 1;
			print("OPERATOR_ASSIGN");
			putchar('\n');
			continue;
		}
		if (argv[1][byte_pointer] == '+') {
			byte_pointer += 1;
			print("OPERATOR_ADD");
			putchar('\n');
			continue;
		}
		if (argv[1][byte_pointer] == '-') {
			byte_pointer += 1;
			print("OPERATOR_SUBTRACT");
			putchar('\n');
			continue;
		}
		if (argv[1][byte_pointer] == '&') {
			byte_pointer += 1;
			print("OPERATOR_BITWISE_AND");
			putchar('\n');
			continue;
		}
		if (argv[1][byte_pointer] == '|') {
			byte_pointer += 1;
			print("OPERATOR_BITWISE_OR");
			putchar('\n');
			continue;
		}
		if (argv[1][byte_pointer] == '~') {
			byte_pointer += 1;
			print("OPERATOR_BITWISE_NOT");
			putchar('\n');
			continue;
		}
		if (argv[1][byte_pointer] == '>') {
			byte_pointer += 1;
			print("CONDITION_GREATER_THAN");
			putchar('\n');
			continue;
		}
		if (argv[1][byte_pointer] == '<') {
			byte_pointer += 1;
			print("CONDITION_LESS_THAN");
			putchar('\n');
			continue;
		}
		if (argv[1][byte_pointer] == ':') {
			byte_pointer += 1;
			print("LABEL_DEFINITION");
			putchar('\n');
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "goto") == 1) {
			print("LABEL_GOTO");
			putchar('\n');
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "var") == 1) {
			print("DEFINE_VARIABLE ");
			byte_pointer += 1;
			while (!((argv[1][byte_pointer] >= 97 && argv[1][byte_pointer] <= 122) || (argv[1][byte_pointer] >= 65 && argv[1][byte_pointer] <= 90) || argv[1][byte_pointer] == '_')) byte_pointer += 1;
			while ((argv[1][byte_pointer] >= 97 && argv[1][byte_pointer] <= 122) || (argv[1][byte_pointer] >= 65 && argv[1][byte_pointer] <= 90) || argv[1][byte_pointer] == '_') {
				putchar(argv[1][byte_pointer]);
				byte_pointer += 1;
			}
			putchar('\n');
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "arr") == 1) {
			print("DEFINE_ARRAY ");
			byte_pointer += 1;
			while (!((argv[1][byte_pointer] >= 97 && argv[1][byte_pointer] <= 122) || (argv[1][byte_pointer] >= 65 && argv[1][byte_pointer] <= 90) || argv[1][byte_pointer] == '_')) byte_pointer += 1;
			while ((argv[1][byte_pointer] >= 97 && argv[1][byte_pointer] <= 122) || (argv[1][byte_pointer] >= 65 && argv[1][byte_pointer] <= 90) || argv[1][byte_pointer] == '_') {
				putchar(argv[1][byte_pointer]);
				byte_pointer += 1;
			}
			putchar('\n');
			while (!(argv[1][byte_pointer] >= '0' && argv[1][byte_pointer] <= '9')) byte_pointer += 1;
			while (argv[1][byte_pointer] >= '0' && argv[1][byte_pointer] <= '9') {
				putchar(argv[1][byte_pointer] - '0');
				byte_pointer += 1;
			}
			putchar('\n');
			continue;
		}
		if (eqnext(argv[1], &byte_pointer, "fn") == 1) {
			print("DEFINE_FUNCTION ");
			byte_pointer += 1;
			while (!((argv[1][byte_pointer] >= 97 && argv[1][byte_pointer] <= 122) || (argv[1][byte_pointer] >= 65 && argv[1][byte_pointer] <= 90) || argv[1][byte_pointer] == '_')) byte_pointer += 1;
			while ((argv[1][byte_pointer] >= 97 && argv[1][byte_pointer] <= 122) || (argv[1][byte_pointer] >= 65 && argv[1][byte_pointer] <= 90) || argv[1][byte_pointer] == '_') {
				putchar(argv[1][byte_pointer]);
				byte_pointer += 1;
			}
			putchar('\n');
			continue;
		}
		if ((argv[1][byte_pointer] >= 97 && argv[1][byte_pointer] <= 122) || (argv[1][byte_pointer] >= 65 && argv[1][byte_pointer] <= 90) || argv[1][byte_pointer] == '_') {
			print("IDENTIFIER ");
			while ((argv[1][byte_pointer] >= 97 && argv[1][byte_pointer] <= 122) || (argv[1][byte_pointer] >= 65 && argv[1][byte_pointer] <= 90) || argv[1][byte_pointer] == '_') {
				putchar(argv[1][byte_pointer]);
				byte_pointer += 1;
			}
			putchar('\n');
			continue;
		}
		byte_pointer += 1;
	}
	return 0;
}