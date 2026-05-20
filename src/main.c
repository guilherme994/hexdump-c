#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	FILE* f_bin;
	
	if(argc < 2) f_bin = stdin;
	else f_bin = fopen(argv[1], "rb");
	
	if(f_bin == NULL) {
		perror("fopen");
		return 1;
	}
	int n_flag = 0;
	int n_bytes = 0;
	size_t offset = 0;
	uint8_t buffer[16];
	char ascii[17];

	int opt = getopt(argc, argv, "nsv:");

	printf("%d\n",argc);

	while(opt != -1){

		switch (opt) {
			case 'n':
				break;

			case 's':
				break;

			case 'v':
				break;
		}
	}

	while(1) {
		size_t f_read = fread(buffer, 1, n_flag ? n_bytes : 16, f_bin);
		if(f_read == 0) {
			if(offset > 0) printf("%08zx\n", offset);
			break;
		}
		printf("%08zx  ", offset);
		
		for(size_t i = 0; i < f_read; i++) {	
			printf("%02x ", buffer[i]);
			if(buffer[i] >= 0x20 && buffer[i] <= 0x7E) {
				ascii[i] = (char)buffer[i];
			}
			else { 
				ascii[i] = '.';
			}
			if(i == 7) printf(" ");
 		}
		ascii[f_read] = '\0';
 
		for(size_t i = f_read; i < 16; i++){
			printf("   ");
		}

		printf(" |%s|\n",ascii);

		if(f_read < 16) break;

		offset += f_read;
	}
	if(f_bin != stdin) { 
		fclose(f_bin);
	}
	return 0 ;
}
