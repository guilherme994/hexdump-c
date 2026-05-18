#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

int main() {
	FILE* f = fopen("hexdump", "rb");
	if(f == NULL) {
		perror("fopen");
		return 1;
	}
	
	size_t offset = 0;
	uint8_t buffer[16];
	char ascii[17];

	while(1) {
		size_t read = fread(buffer, 1, 16, f);
		if(read == 0) break;

		printf("%08zx: ", offset);
		
		for(size_t i = 0; i < read; i++) {	
			printf("%02x ", buffer[i]);
			if(buffer[i] >= 0x20 && buffer[i] <= 0x7E) ascii[i] = (char)buffer[i];
			else ascii[i] = '.';
 		}
		ascii[read] = '\0';
 
		for(size_t i = read; i < 16; i++){
			printf("   ");
		}

		printf("|%s|\n",ascii);

		if(read < 16) break;

		offset += read;
	}
	fclose(f);
	return 0 ;
}
