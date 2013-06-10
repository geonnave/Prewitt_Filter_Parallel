#include "prewitt.h"
#include "string.h"



int main(int argc, char* argv[]) {
	if (argv[1] != NULL && argv[2] != NULL) {
		init(argv[1], atoi(argv[2]));
		prewitt();
		prewitt_parallel_v1();
		prewitt_parallel_v2();
		prewitt_parallel_v3();
	} else {
		init("images/duck.jpg", 2);
		// gauss_blur();
		prewitt();
		prewitt_parallel_v1();
		prewitt_parallel_v2();
		prewitt_parallel_v3();
		// set_threads(2);
		// prewitt_parallel_v1();
		// prewitt_parallel_v2();
	}
}
