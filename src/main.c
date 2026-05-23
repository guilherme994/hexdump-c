#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char* argv[]) {
	FILE* f_bin;
	
	bool n_flag = false;
	bool s_flag = false;
	bool v_flag = false;
	
	long int n_bytes = 0;
	long int s_soffset = 0;
	size_t offset = 0;
	
	uint8_t buffer[16];
	uint8_t v_buffer[16];

	char ascii[17];

	char *p_soffset;
	char *p_nbytes;

	int opt;
	bool squeeze = false;
	size_t f_read_copy = 0;
	bool first_print = true;

	while((opt = getopt(argc, argv,"n:s:v"))!= -1){
		switch (opt) {
			case 'n':
				n_flag = true;
				n_bytes = strtol(optarg, &p_nbytes, 10);
				if(optarg == p_nbytes) {
					printf("Invalid value for -n\n");
					return 1;
				}
				break;
			case 's':
				s_flag = true;
				s_soffset = strtol(optarg, &p_soffset, 10);
				if(optarg == p_soffset) {
					printf("Invalid value for -s\n");
					return 1;
				}
				break;
			case 'v':
				v_flag = true;
				break;
		}
	}

	if(argc < 2) f_bin = stdin;
	else f_bin = fopen(argv[optind], "rb");

	if(f_bin == NULL) {
		perror("fopen");
		return 1;
	}

	if(s_flag) fseek(f_bin, s_soffset, SEEK_SET);

	while(1) {
		int str_size = 16;
		if(n_flag || n_bytes > 16) {
			if(n_bytes < str_size) str_size = n_bytes;
		}

		size_t f_read = fread(buffer, 1, str_size, f_bin);

		int verbose = (f_read == 16 && f_read_copy == 16 && v_flag && memcmp(v_buffer, buffer, sizeof(buffer)) == 0 && !first_print);

		if(!verbose) {
			if(f_read == 0 && !first_print) {
				printf("%08lx\n", (offset + f_read + (s_flag ? s_soffset : 0)));
				break;
			}
			printf("%08lx  ", offset);
		
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
		
			if(f_read < 8) printf(" ");
			
			for(size_t i = f_read; i < 16; i++){
				printf("   ");
			}

			ascii[f_read] = '\0';
			printf(" |%s|\n",ascii);
			
			if(f_read < 16) {
				printf("%08lx\n", (offset + f_read + (s_flag ? s_soffset : 0)));
				break;
			}

			squeeze = false;
		}
		else if (!squeeze) {
			printf("*\n");
			squeeze = true;
		}
	
		offset += f_read;
		f_read_copy = f_read;
		first_print = false;
		
		if(v_flag) memcpy(v_buffer, buffer, sizeof(buffer));
		if(n_bytes > str_size) n_bytes -= str_size;
	}

	if(f_bin != stdin) { 
		fclose(f_bin);
	}
	return 0 ;
}
