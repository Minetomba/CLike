typedef __INTPTR_TYPE__ st; /* Standard type */

int main(int argc, char *argv[]) {
	st stack[4096];
	st stack_pointer = 0;
	st labels[4096];
	st label_pointer = 0;
	st pc = 0;
	st last_construct = 0;
	while (argv[1][pc] != '\0') {
		if (argv[1][pc] == '#') {
			labels[label_pointer] = pc + 1;
			label_pointer += 1;
		}
		pc += 1;
	}
	pc = 0;
	while (argv[1][pc] != '\0') {
		st c = argv[1][pc];
		if (c == '|') { /* Pushing the constructed number */
			stack_pointer += 1;
			stack[stack_pointer] = last_construct;
			last_construct = 0;
		} else if (c >= '0' && c <= '9') { /* Constructing the number */
			last_construct = last_construct + last_construct + last_construct + last_construct + last_construct + last_construct + last_construct + last_construct + last_construct + last_construct + ((int)c) + -48;
		} else if (c == '@') { /* Get */
			stack[stack_pointer] = *(st*)stack[stack_pointer];
		} else if (c == '!') { /* Store */
			*(st*)stack[stack_pointer] = stack[stack_pointer + ~1 + 1];
			stack_pointer += ~2 + 1;
		} else if (c == '+') { /* Add */
			stack[stack_pointer + ~1 + 1] = stack[stack_pointer + ~1 + 1] + stack[stack_pointer];
			stack_pointer += ~1 + 1;
		} else if (c == '~') { /* Nor */
			stack[stack_pointer + ~1 + 1] = ~(stack[stack_pointer + ~1 + 1] | stack[stack_pointer]);
			stack_pointer += ~1 + 1;
		} else if (c == '<') { /* Less than */
			if (stack[stack_pointer + ~1 + 1] < stack[stack_pointer]) {
				stack[stack_pointer + ~1 + 1] = 1;
			} else {
				stack[stack_pointer + ~1 + 1] = 0;
			}
			stack_pointer += ~1 + 1;
		} else if (c == '>') { /* Greater than */
			if (stack[stack_pointer + ~1 + 1] > stack[stack_pointer]) {
				stack[stack_pointer + ~1 + 1] = 1;
			} else {
				stack[stack_pointer + ~1 + 1] = 0;
			}
			stack_pointer += ~1 + 1;
		} else if (c == '=') { /* Is equal to */
			if (stack[stack_pointer + ~1 + 1] == stack[stack_pointer]) {
				stack[stack_pointer + ~1 + 1] = 1;
			} else {
				stack[stack_pointer + ~1 + 1] = 0;
			}
			stack_pointer += ~1 + 1;
		} else if (c == '?') { /* Branch */
			if (stack[stack_pointer] != 0) {
				pc = stack[stack_pointer + ~1 + 1] + ~1 + 1;
			}
			stack_pointer += ~2 + 1;
		} else if (c == '&') { /* Dereference label ID */
			stack[stack_pointer] = labels[stack[stack_pointer]];
		} else if (c == '$') { /* Stack base address */
			stack_pointer += 1;
			stack[stack_pointer] = (st)&stack[0];
		} else if (c == '.') { /* Output */
			char out = (char)stack[stack_pointer];
			__asm__ volatile ("syscall" :: "a"(1), "D"(1), "S"(&out), "d"(1) : "rcx", "r11", "memory");
			stack_pointer -= 1;
		} else if (c == ',') { /* Recover */
			stack_pointer += 1;
		} else if (c == '^') { /* Program counter */
			stack_pointer += 1;
			stack[stack_pointer] = pc;
		}
		pc += 1;
	}
}

__attribute__((naked, noreturn))
void _start() {
	__asm__ volatile (
		"mov (%rsp), %rdi\n"
		"lea 8(%rsp), %rsi\n"
		"and $-16, %rsp\n"
		"call main\n"
		"mov %eax, %edi\n"
		"mov $60, %eax\n"
		"syscall"
	);
}