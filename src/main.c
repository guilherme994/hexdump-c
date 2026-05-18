#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

int main() {
	FILE* f = fopen("src/teste", "rb");
	if(f == NULL) {
		perror("fopen");
		return 1;
	}
	int count = 0;
	uint8_t buffer[16];

	while(1) {
		size_t read = fread(buffer, 1, 16, f);
		printf("%07x0: ", count);
		for(int i = 0; i <= 16; i+= 2) {	
			printf("%02X%02X ",buffer[i],buffer[i+1]);
		}
		for(int i= 0; i <= 16; i++) {	
			if(buffer[i] >= 0x20 && buffer[i] <= 0x7E) {
				printf("%c",(char)buffer[i]);
			}
			else {
				printf(".");
			}
		}
		printf("\n");
		if(read < 16) break;
		count++;
	}
	fclose(f);
	return 0 ;
}
