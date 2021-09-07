#include <stdio.h>

int main()
{
   int arg1=51, arg2=15,temp;
    //store variables in register
    __asm__ ( "movl %0, %%eax;"
              "movl %1, %%ebx;"
            :
            : "g"(arg1), "g"(arg2));
    //store eax in temp variable        
    __asm__ ("mov %%eax,%0" 
            :"=a" ( temp ) 
            : );
    //Move ebx to eax        
    __asm__("mov %ebx, %eax");
    //Move temp to ebx
    __asm__("movl %0, %%ebx"
            :
            : "g"(temp));
    
    //Copy content of registers back to arg1 and arg2
    __asm__ ("mov %%eax,%0" 
            :"=a" ( arg1 ) 
            : );
            
    __asm__ ("mov %%ebx,%0" 
            :"=b" ( arg2 ) 
            : );
    
    printf("arg1 = %d\narg2 = %d",arg1,arg2);
    return 0;
    
}