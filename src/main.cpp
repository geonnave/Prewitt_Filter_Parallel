#include <stdio.h>
#include <stdlib.h>
#include "prewitt.h"
#include "string.h"



int main(int argc, char* argv[]) {
	int i = 0, t = 10;
	double s=0, pv1=0, pv2=0;
	if (argv[1] != NULL && argv[2] != NULL) {
		if (argv[3] != NULL)
			t = atoi(argv[3]);
		else
			t = 10;
		init(argv[1], atoi(argv[2]));
		for (i = 0; i < t; ++i)
		{
			printf("exec %d...\n", i+1);
			s += prewitt();
			pv1 += prewitt_parallel_v1();
			pv2 += prewitt_parallel_v2();
		}
		printf("\n\n\n");
		print("single", s/(double)i);
		print("parallel_v1", pv1/(double)i);
		print("parallel_v2", pv2/(double)i);
	} else if (argv[1] != NULL ) {
		printf("====================================================================\n");
		init(argv[1], 2);
		prewitt();
		prewitt_parallel_v1();
		prewitt_parallel_v2();
		printf("====================================================================\n");
		set_threads(4);
		prewitt();
		prewitt_parallel_v1();
		prewitt_parallel_v2();
		printf("====================================================================\n");
		set_threads(8);
		prewitt();
		prewitt_parallel_v1();
		prewitt_parallel_v2();
	} else {
		init("images/duck.jpg", 2);
		prewitt();
		prewitt_parallel_v1();
		prewitt_parallel_v2();
		// set_threads(2);
		// prewitt_parallel_v1();
		// prewitt_parallel_v2();
	}
}
