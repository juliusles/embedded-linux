/*

    Read file using fgetc()
    Print to terminal
    Usage:
        ./read file.txt

*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    char ch;

    fp = fopen(argv[1], "r");

    while(1)
    {
        ch = fgetc(fp);
        if (feof(fp))
            break;
        printf("%c", ch);
    }

    //fprintf(fp, "Hello world\n");
    //fwrite("Hello world\n", sizeof(char), sizeof("Hello world\n"), fp);

    fclose(fp);

    return 0;
}

/*
  r   read
  w   write, erase if exists
  a   append
  r+  read and write, file must exist
  w+  create empty file for writing and reading
  a+  open for reading and appending
*/
