#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char* argv[]) {
	FILE* f_bin;

	bool c_flag = false;
	
	long int n_bytes = -1;
	long int s_soffset = 0;
	size_t offset = 0;
	
	uint8_t buffer[16] = {0};
	uint8_t v_buffer[16] = {0};

	char ascii[17];

	int opt;
	bool equal = false;
	size_t f_read_copy = 0;
	bool first_print = true;

	while((opt = getopt(argc, argv,"n:s:c"))!= -1){
		switch (opt) {
			case 'n': {
				char *p_nbytes;
				n_bytes = strtol(optarg, &p_nbytes, 10);
				if(optarg == p_nbytes) {
					fprintf(stderr, "%s: Invalid value for -n\n",argv[0]);
					return 1;
				}
				break;
			}
			case 's': {
				char *p_soffset;
				s_soffset = strtol(optarg, &p_soffset, 10);
				if(optarg == p_soffset) {
					fprintf(stderr, "%s: Invalid value for -s\n", argv[0]);
					return 1;
				}
				offset += s_soffset;
				break;
			}
			case 'c':
				c_flag = true;
				break;
			default:
				fprintf(stderr, "Usage: %s [-n N] [-s OFFSET] [-c] [file]\n", argv[0]);
				return 1;
		}
	}

	if(optind >= argc) f_bin = stdin;
	else f_bin = fopen(argv[optind], "rb");

	if(f_bin == NULL) {
		perror("fopen");
		return 1;
	}

	if(s_soffset > 0 && fseek(f_bin, s_soffset, SEEK_SET) != 0) {
		fprintf(stderr, "%s: -s requires a seekable file (not stdin).\n", argv[0]);
		return 1;
	}

	while(1) {
		size_t str_size = 16;

		if(n_bytes >= 0) {
			if(n_bytes == 0) break;
			if(n_bytes < (long)str_size) str_size = (size_t)n_bytes;
		}

		size_t f_read = fread(buffer, 1, str_size, f_bin);
		
		memset(ascii, '.', 16);

		bool concise = (f_read == 16 && f_read_copy == 16 && c_flag && memcmp(v_buffer, buffer, sizeof(buffer)) == 0 && !first_print);

		if(!concise) {
			if(f_read == 0 && !first_print) {
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
			/* Se a linha tem menos de 8 bytes, o loop nao imprimiu o espaço duplo do meio
			   - compensa aqui para manter alinhamento da coluna ASCII*/
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
		if(n_bytes >= (long)f_read) n_bytes -= (long)f_read;
	}

	printf("%08zx\n", offset);
	
	if(f_bin != stdin) { 
		fclose(f_bin);
	}
	return 0 ;
}
