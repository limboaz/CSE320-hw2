#include "helper.h"
#define MEM_MAX 1024

int checkFlag(void * ptr){}
int checkID(void * ptr, int id){}
int checkSize(void * ptr){}


int main(int argc, char** argv) {
    if (*(argv + 1) == NULL) {
        printf("You should provide name of the test file.\n");
        return 1;
    }
    void* ram = cse320_init(*(argv + 1));
    void* tmp_buf = cse320_tmp_buffer_init();
    int ret = 0;
    void * cursor = ram;
    /*
     * You code goes below. Do not modify provided parts
     * of the code.
     */
    int id;
    int af;
    uint64_t size;
    int mem_cnt = 0;
    int add_flag = 0;
    int tmp_size = 0;
    printf("ram: %p\n", ram);
    printf("tmp_buffer: %p\n", tmp_buf);
    printf("seg fault: %lu\n", *((uint64_t *)ram + 256));

    while(mem_cnt < MEM_MAX){
	    //Check if ID is valid
	for (id = 1; id < 4; id++){
		add_flag = checkID(cursor, id);	//Match the current id loop
		if(add_flag == 1)
			add_flag = checkFlag(cursor);	//If add-flag is 0 at this point, this will just be skipped
		if (add_flag == 1)
			add_flag = checkSize(cursor, tmp_size);	//Same here

	}
    }
	

    /*
     * Do not modify code below.
     */
    cse320_check();
    cse320_free();
    return ret;
}
