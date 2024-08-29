/*
Use Ubuntu LTS (WSL) for pipe() & fork() process execution
*/

#include <iostream>
#include <unistd.h>
using namespace std;

void pipeline(const char* process1, const char* process2) {
    int fd[2];
    pipe(fd);
    int id = fork();
    if (id != 0) { // non-zero means  Parent Process
        close(fd[0]); // read end
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]); // write end

        execlp("/bin/cat", "cat", "systemCall-parentChild.cpp", nullptr);
        std::cerr <<"Failed to execute"<<process1<<std::endl;
    } else { // zero means Child Process
        close(fd[1]); // write end
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]); // read end 

        execlp("/bin/grep", "grep", "hello", nullptr);
        std::cerr <<"Failed to execute"<<process2<<std::endl;
    }
}

int main() {
    pipeline("cat systemCall-parentChild.cpp", "grep hello");
    return 0;
}