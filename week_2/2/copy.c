/*

    Read file using fgetc()
    Write to another file using fprintf()

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        printf("Too few arguments. Usage: ./copy SOURCE DEST\n");
        exit(0);
    }
    FILE *fpRead  = NULL;
    FILE *fpWrite = NULL;
    char ch;

    // Source file
    fpRead = fopen(argv[1], "r");

    // Check if file exists
    if(fpRead == NULL)
    {
        printf("%s does not exist\n", argv[1]);
        exit(0);
    }

    // Destination file
    fpWrite = fopen(argv[2], "w");

    // Copy one char at a time
    while(1)
    {
        ch = fgetc(fpRead);
        if (feof(fpRead))
            break;
        fprintf(fpWrite, "%c", ch);
    }

    fclose(fpRead);
    fclose(fpWrite);

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
