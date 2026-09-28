arr a 5;
var global_return_value;
fn _start {
	main;
}
fn main { /* Any function called such as main(a, b) will have a stack looking like RET, A, B where B is the #stack value and can be cleared with "clear". Of course, in this case, there are no arguments (hopefully), so we run "clear" on the return value so that it wouldn't stack overflow once it starts recursing. We also make sure main gets called rather than just implicitly executed, as "clear" would cause a stack underflow because we'd be clearing nothing on the first recursion */
	clear;
	add(2, 3);
	a[0] = global_return_value;
	main;
}

fn add { /* RET, ARG1, ARG2 */
	arr mtp_arguments 2; /* Allocates the base (0) and two additional values */
	mtp_arguments[0] = #stack;
	clear;
	mtp_arguments[1] = #stack;
	clear;
	mtp_arguments[0] = mtp_arguments[0]* + mtp_arguments[1]*;
	global_return_value = mtp_arguments[0]*;
	return;
}