#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <fcntl.h>
#include "main.h"

#define BUFFERSIZE 100

int main() {
    char* 	filename = "testdir/testfile.txt";
    char* 	text = "Lorem ipsum dolor sit amet, consectetuer adipiscing...\n";
    char 	buffer[BUFFERSIZE];
    int file_handle = creat(filename, S_IWRITE);
    int byte_written = write(file_handle, text, strlen(text));
    cout<<("byte written in file", byte_written, filename)<<endl;
    close(file_handle);
    file_handle = open(filename, O_RDONLY);
    int bytes_read = read(file_handle, &buffer, BUFFERSIZE-1);
    buffer[bytes_read] = '\0';
    cout<<("Read from file", filename, buffer)<<endl;
    close(file_handle);
}
}