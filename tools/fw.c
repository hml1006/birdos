#include <stdio.h>
//本程序的功能是写软盘扇区
int main(int argc, char **argv)
{
	if(argc == 1) {
		printf("fw inputfile outputfile start_of_output\n");
		return 0;
	}

	if(argc != 4) {
		printf("arguments error!\n");
		return -1;
	}

	FILE *input = fopen(argv[1], "r");
	if (input == NULL) {
		printf("input file open error!\n");
		return -1;
	}
	FILE *output = fopen(argv[1], "a+");
	if (output == NULL) {
		printf("output file open error!\n");
		fclose(input);
		return -1;
	}
	fclose(input);
	fclose(output);
}
