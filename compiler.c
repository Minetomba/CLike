/* Includes */
#include <stdio.h>

// Example
/*
#main {
	v1& 3 =
	v2& 5 =
	#loop:
	v1 v2 < {
		v1& 1 +
		$loop
	}
	$exit
}

#exit {
	$exit % this just loops forever %
}
*/

/* Global variables*/
int byte_pointer = 0;
int skip_label = 0;
int skip_stack[256];
int stack_top = 0;
int variable_toggle = 0;
int if_id = 0;

/* Helpers */
int llen(char buf[]) {
	int i = 0;
	while (buf[i] != '\0') i++;
	return i;
}

/* Very helpful helpers */
int exec(char code[]) {
	while (code[byte_pointer] != '\0') {
		if (code[byte_pointer] == '#') {
			char label[256];
			label[0] = '\0';
			byte_pointer++;
			while (code[byte_pointer] != ':' && code[byte_pointer] != '{') {
				int target = llen(label);
				if ((code[byte_pointer] >= 48 && code[byte_pointer] <= 57) || (code[byte_pointer] >= 65 && code[byte_pointer] <= 90) || (code[byte_pointer] >= 97 && code[byte_pointer] <= 122) || (code[byte_pointer] == 95)) {
					label[target] = code[byte_pointer];
					label[target + 1] = '\0';
				}
				byte_pointer++;
			}
			if (code[byte_pointer] == ':') {
				printf("%s:\n", label);
				byte_pointer++;
			} else if (code[byte_pointer] == '{') {
				int lbl = skip_label++;
				printf("jmp skip%d\n", lbl);
				skip_stack[stack_top++] = lbl;
				printf("global %s\n", label);
				printf("%s:\n", label);
				byte_pointer++;
			}
		}
		if (code[byte_pointer] == '{') {
			int lbl = skip_label++;
			printf("jmp skip%d\n", lbl);
			skip_stack[stack_top++] = lbl;
		}
		if (code[byte_pointer] == '}') {
			int lbl = skip_stack[--stack_top];
			printf("skip%d:\n", lbl);
		}
		if (code[byte_pointer] == '$') {
			char label[256];
			label[0] = '\0';
			byte_pointer++;
			while (code[byte_pointer] != ' ' && code[byte_pointer] != '\n' && code[byte_pointer] != '\r' && code[byte_pointer] != '\t') {
				int target = llen(label);
				if ((code[byte_pointer] >= 48 && code[byte_pointer] <= 57) || (code[byte_pointer] >= 65 && code[byte_pointer] <= 90) || (code[byte_pointer] >= 97 && code[byte_pointer] <= 122)) {
					label[target] = code[byte_pointer];
					label[target + 1] = '\0';
				}
				byte_pointer++;
			}
			printf("jmp %s\n", label);
		}
		if (code[byte_pointer] == 'v') {
			byte_pointer++;
			int variable = 0;
			while (code[byte_pointer] >= '0' && code[byte_pointer] <= '9') {
				int digit = (int)code[byte_pointer] - (int)'0';
				variable *= 10;
				variable += digit;
				byte_pointer++;
			}
			if (variable_toggle == 0) {
				if (code[byte_pointer] == '&') {
					printf("mov rax, r13\nadd rax, 64\nadd rax, %d\n", variable * 8);
				} else if (code[byte_pointer] == '*') {
					printf("mov rax, r13\nadd rax, 64\nadd rax, %d\nmov rax, [rax]\nmov rax, [rax]\n", variable * 8);
				} else {
					printf("mov rax, r13\nadd rax, 64\nadd rax, %d\nmov rax, [rax]\n", variable * 8);
				}
				variable_toggle = 1;
			} else if (variable_toggle == 1) {
				if (code[byte_pointer] == '&') {
					printf("mov rdi, r13\nadd rdi, 64\nadd rdi, %d\n", variable * 8);
				} else if (code[byte_pointer] == '*') {
					printf("mov rdi, r13\nadd rdi, 64\nadd rdi, %d\nmov rdi, [rdi]\nmov rdi, [rdi]\n", variable * 8);
				} else {
					printf("mov rdi, r13\nadd rdi, 64\nadd rdi, %d\nmov rdi, [rdi]\n", variable * 8);
				}
				variable_toggle = 0;
			}
		}
		if (code[byte_pointer] >= '0' && code[byte_pointer] <= '9') {
			int number = code[byte_pointer] - '0';
			byte_pointer++;
			while (code[byte_pointer] >= '0' && code[byte_pointer] <= '9') {
				number *= 10;
				number += code[byte_pointer] - '0';
				byte_pointer++;
			}
			if (variable_toggle == 0) {
				printf("mov rax, %d\n", number);
				variable_toggle = 1;
			} else if (variable_toggle == 1) {
				printf("mov rdi, %d\n", number);
				variable_toggle = 0;
			}
			byte_pointer++;
		}
		if (code[byte_pointer] == '=' && code[byte_pointer + 1] != '=') {
			printf("mov [rax], rdi\n");
		}
		if (code[byte_pointer] == '+') {
			printf("add [rax], rdi\n");
		}
		if (code[byte_pointer] == '|') {
			printf("or [rax], rdi\nnot [rax]\n");
		}
		if (code[byte_pointer] == '=' && code[byte_pointer + 1] == '=') {
			printf("cmp rax, rdi\n");
			printf("je if%d\n", if_id);
			int lbl = skip_label++;
			printf("jmp skip%d\n", lbl);
			skip_stack[stack_top++] = lbl;
			printf("if%d:\n", if_id);
			byte_pointer += 3;
			if_id += 1;
		}
		if (code[byte_pointer] == '>') {
			printf("cmp rax, rdi\n");
			printf("jg if%d\n", if_id);
			int lbl = skip_label++;
			printf("jmp skip%d\n", lbl);
			skip_stack[stack_top++] = lbl;
			printf("if%d:\n", if_id);
			byte_pointer += 2;
			if_id += 1;
		}
		if (code[byte_pointer] == '<') {
			printf("cmp rax, rdi\n");
			printf("jl if%d\n", if_id);
			int lbl = skip_label++;
			printf("jmp skip%d\n", lbl);
			skip_stack[stack_top++] = lbl;
			printf("if%d:\n", if_id);
			byte_pointer += 2;
			if_id += 1;
		}
		byte_pointer += 1;
	}
	return 0;
}

/* Main logic */
int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Usage: %s <code>\n", argv[0]);
		return 1;
	}
	printf("global _start\n_start:\nmov r13, rsp\njmp main\n");
	exec(argv[1]);
	return 0;
}