#include "helper.h"
#define MEM_MAX 1024
#define WSIZE 8

int checkFlag(void * ptr, int flag){
	int check = *((uint64_t *)ptr) % 2;
	return check == flag ? 1 : 0;
}

int checkID(void * ptr, int id){
	int check = (*((uint64_t *)ptr) >> 1) & 3;
	return check == id ? 1 : 0;		
}

int checkSize(void * ptr, int* tmp_size){
	int check = *((uint64_t *)ptr) & -8;
	if (check < *tmp_size) {
		*tmp_size = check;
		return 1;
	} else return 0;
}


int main(int argc, char** argv) {
    if (*(argv + 1) == NULL) {
        printf("You should provide name of the test file.\n");
        return 1;
    }
    void* ram = cse320_init(*(argv + 1));
    void* tmp_buf = cse320_tmp_buffer_init();
    int ret = 0;
    void * cursor = ram;
    void * buffer = tmp_buf + 128;
    /*
     * You code goes below. Do not modify provided parts
     * of the code.
     */
    int id, j;
    int af;
    uint64_t size;
    int mem_cnt = 0;
    int add_flag = 1;
    int tmp_size = 1024;
	int buffer_size = 0;
	void * min;
    printf("ram: %p\n", ram);
    printf("tmp_buffer: %p\n", tmp_buf);
    printf("seg fault: %lu\n", *((uint64_t *)ram + 256));

	    //Check if ID is valid
	for (id = 1; id < 4; id++){
		for (j = 1; j >= 0; j--){
			while( add_flag != 0 ){
				while(mem_cnt < MEM_MAX){
					size = *((uint64_t *)cursor) & -8;
					add_flag = checkID(cursor, id);	// Match the current id loop
					if(add_flag == 1)
						add_flag = checkFlag(cursor, j);	// If add-flag is 0 at this point, this will just be skipped
					if (add_flag == 1)
						add_flag = checkSize(cursor, &tmp_size);	// Same here
					if (add_flag == 1){
						min = cursor;
					}
					mem_cnt += (size == 0) ? 1 : size;
				}
				if ( min != NULL ){
					if(cse320_sbrk(tmp_size)){
						memcpy(min, buffer, tmp_size);
						int m;
						for (m = 0; m < tmp_size; m += WSIZE){
							*((uint64_t *)min) = 0;
							min += WSIZE;
						}
						buffer += tmp_size;
						buffer_size += tmp_size;
						min = NULL;
						tmp_size = 1024;
					} else {
						printf("SBRK_ERROR");
						exit(errno);
					}
				}
				mem_cnt = 0;
			}
			add_flag = 1;
		}
	}

	// Add the last empty block
	cse320_sbrk(16);
	*((uint64_t *)buffer) = 16;
	buffer += 8;
	*((uint64_t *)buffer) = 16;
	memcpy(tmp_buf + 128, ram, buffer_size + 16);

    /*
     * Do not modify code below.   
     */
    cse320_check();
    cse320_free();
    return ret;
}
