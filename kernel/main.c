#include "print.h"
#include "init.h"

int main(void)
{
    put_str("          Welcome using\n");
    put_str("          This is tiny operator system by CJS\n");
    
    init_all();
    asm volatile ("sti");
    while(1);
    return 0;
}