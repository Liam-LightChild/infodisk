#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

off_t fsize(const char *filename) {
    struct stat st; 

    if (stat(filename, &st) == 0)
        return st.st_size;

    return -1; 
}

int main(int argc, char const *argv[])
{
    if(fsize(argv[1]) == -1) {
        fprintf(stderr, "IOERR: File does not exist!\n");
        exit(1);
    }

    printf("Seeing info for %s\n\n", argv[1]);
    FILE *disk = fopen(argv[1], "r");
    fseek(disk, 0, SEEK_END);
    off_t *size = malloc(sizeof(off_t));
    fpos_t *pos = malloc(sizeof(fpos_t));
    fgetpos(disk, pos);
    size = &pos->__pos;
    printf("Disk size: %ld bytes\n", *size);
    
    char *name = malloc(11);
    char *type = malloc(8);
    fseek(disk, 0x2B, SEEK_SET);
    fread(name, 1, 11, disk);
    fread(type, 1, 8, disk);
    printf("     name: %s\n     type: %s\n", name, type);

    fseek(disk, 3, SEEK_SET);
    char *by = malloc(8);
    fread(by, 1, 9, disk);
    printf("      oem: %s\n", by);

    fseek(disk, 0xE, SEEK_SET);
    short *reserved = malloc(sizeof(short));
    fread(reserved, 2, 1, disk);
    printf("Reserved sectors: %i (%iB)\n", (int)*reserved, *reserved * 512);

    fclose(disk);
    return 0;
}