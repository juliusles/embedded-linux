/*

    Testing the fopen(), fprintff() and fwrite()

*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *fp;

    fp = fopen("test.txt", "w+");

    fprintf(fp, "Hello world\n");
    fwrite("Hello world\n", sizeof(char), sizeof("Hello world\n"), fp);

    fclose(fp);

    return 0;
}
