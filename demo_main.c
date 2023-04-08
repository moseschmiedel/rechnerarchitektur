#include "demo.h"

int main(int argc, char **argv)
{
	int retval = 0;
	struct handle_struct h;

	retval = pre_process(argc, argv, &h);
	if (0 > retval)
		return retval;
	retval = sort(&h);
	if (0 > retval)
		return retval;
	retval = post_process(&h);

	return retval;
}
