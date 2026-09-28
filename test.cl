arr a 5;
var global_return_value;
fn _start {
	main;
}
fn main {
	subcall;
	add(2, 3);
	a[0] = global_return_value;
	main;
}

fn add { /* RET, ARG1, ARG2 */
	arr mtp_arguments 2; /* Allocates the base (0) and two additional values */
	mtp_arguments[0] = #stack;
	substack;
	mtp_arguments[1] = #stack;
	substack;
	mtp_arguments[0] = mtp_arguments[0]* + mtp_arguments[1]*;
	global_return_value = mtp_arguments[0]*;
	return;
}