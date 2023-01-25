#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "decoder.h"
#include "memory.h"
#include "memory_system.h"
#include "bit_functions.h"
#include "cpu.h"
#include "compiler.h"

void my_memory_dump(int start_address, int num_bytes) {
    int start_boundary = start_address - (start_address % 8);
    int boundary_bytes = num_bytes + (start_address - start_boundary);
    printf("start_boundary: %d 0x%04x\n", start_boundary, start_boundary);
    for (int i = start_boundary; i < start_boundary+boundary_bytes; i+=8) {
        printf("0x%04x (0d%04d) 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x \n", 
               i, i,
               memory_fetch(i),   memory_fetch(i+1), memory_fetch(i+2), memory_fetch(i+3),
               memory_fetch(i+4), memory_fetch(i+5), memory_fetch(i+6), memory_fetch(i+7));
    }
}

void my_step_n(int n){
    for(int i = 0; i < n; i++){
        step();
    }
}

void my_show_regs(void){
    for(int i = 0; i < 15; i++){
        printf("register[%02d]: %x\n",i, get_reg(i));
    }
    printf("register[%02d]: %x\n",PC, get_reg(PC));
}


int main(int argc, char **argv) {
    programInfo *progInfo;
    if (argc == 2)
    {
        progInfo = compileProg(argv[1]);
    }
    else
    {
        //load_memory("program1.txt");
        progInfo = compileProg("hello_world.dasm");
    }
    load_memory(progInfo->progName);
    set_reg(PC, progInfo->progStart);
    //my_step_n(75);
    int stopped = 0;
    int count = 0;
    while (!stopped)
    {
        stopped = step();
        if (count > 75)
            stopped = 1;
    }
        
        
    my_memory_dump(progInfo->memStart, 200);
    my_show_regs();
}
