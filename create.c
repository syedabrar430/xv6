#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

#define size_of_block 512

// Function to print the contents of a block
void blockprint(char *buf) {
    int i;
    for (i = 0; i < size_of_block; i++) {
        if (buf[i] == '\0') break;
        fprintf(1, "%c", buf[i]);
    }
    fprintf(1, "\n");
}

int main(int argc, char *argv[]) {
    // Check if the correct number of arguments are provided
    if (argc != 4) {
        fprintf(1, "Usage: create <fileName> <fileSize> <rollNo>\n");
        exit(0);
    }

    // Extract the necessary information from arguments
    char *nameoffile = argv[1];
    int sizeoffile = atoi(argv[2]);
    char *iithrollnumber = argv[3];
    int fd = open(nameoffile, O_CREATE | O_RDWR);
   
    // Allocate disk blocks and write rollNo in each block
    int i;
    char buf[size_of_block];
    for (i = 0; i < sizeoffile; i += size_of_block) {
        memset(buf, '\0', size_of_block);  
        strcpy(buf, iithrollnumber);
        write(fd, buf, size_of_block);
    }
    close(fd);
 
    // Open the file to get inode number and print block numbers and contents
    fd = open(nameoffile, O_RDWR);
  
    // Get the inode number 
    struct stat st;
    if (fstat(fd, &st) < 0) {
        fprintf(1, "Cannot get the necessary information\n");
        exit(0);
    }
    fprintf(1, "Inode number: %d\n", st.ino);

    // Print block numbers and contents
    for (i = 0; i < sizeoffile; i += size_of_block) {
        fprintf(1, "Block number: %d\n", i / size_of_block);
        memset(buf, '\0', size_of_block);
        read(fd, buf, size_of_block);
        fprintf(1, "Block contents: ");
        blockprint(buf);
    }
    close(fd);
    exit(0);
}
