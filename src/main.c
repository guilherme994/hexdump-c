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
	bool c_flag = false;
	
	long int n_bytes = -1;
	long int s_soffset = 0;
	size_t offset = 0;
	
	uint8_t buffer[16];
	uint8_t v_buffer[16];

	char ascii[17];

	char *p_soffset;
	char *p_nbytes;

	int opt;
	bool equal = false;
	size_t f_read_copy = 0;
	bool first_print = true;

	while((opt = getopt(argc, argv,"n:s:c"))!= -1){
		switch (opt) {
			case 'n':
				n_flag = true;
				n_bytes = strtol(optarg, &p_nbytes, 10);
				if(optarg == p_nbytes) {
					fprintf(stderr, "Invalid value for -n\n");
					return 1;
				}
				break;
			case 's':
				s_flag = true;
				s_soffset = strtol(optarg, &p_soffset, 10);
				offset += s_soffset;
				if(optarg == p_soffset) {
					fprintf(stderr, "Invalid value for -s\n");
					return 1;
				}
				break;
			case 'c':
				c_flag = true;
				break;
			default:
				fprintf(stderr, "Use: %s [-n N] [-s OFFSET] [-c] [file]\n", argv[0]);
				break;
		}
	}

	if(optind >= argc) f_bin = stdin;
	else f_bin = fopen(argv[optind], "rb");

	if(f_bin == NULL) {
		perror("fopen");
		return 1;
	}

	if(s_flag && fseek(f_bin, s_soffset, SEEK_SET) != 0) {
		fprintf(stderr, "%s: -s ignored with stdin (non-seekable stream).\n", argv[0]);
		offset = 0;
	}

	while(1) {
		int str_size = 16;

		if(n_flag) {
			if(n_bytes == 0) break;
			if(n_bytes < str_size) str_size = n_bytes;
		}

		size_t f_read = fread(buffer, 1, str_size, f_bin);
		
		memset(ascii, '.', 16);

		int concise = (f_read == 16 && f_read_copy == 16 && c_flag && memcmp(v_buffer, buffer, sizeof(buffer)) == 0 && !first_print);

		if(!concise) {
			if(f_read == 0 && !first_print) {
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
				offset += f_read;
				break;
			}

			equal = false;
		}
		else if (!equal) {
			printf("*\n");
			equal = true;
		}
	
		offset += f_read;
		first_print = false;
		
		if(c_flag) {
			memcpy(v_buffer, buffer, sizeof(buffer));
			f_read_copy = f_read;
		}
		if(n_bytes > str_size) n_bytes -= str_size;
	}

	printf("%08lx\n", offset);
	
	if(f_bin != stdin) { 
		fclose(f_bin);
	}
	return 0 ;
}
