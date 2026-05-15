 #include <stdio.h>

 int main (){
    fopen("hello.txt", "r");
    perror("Error opening file");
    return 0;

 } 