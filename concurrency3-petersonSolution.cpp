// Con - for 2 process/thread only 
//          Not for Multiprocessors


#include <iostream>
#include <thread>

#define TRUE 1
#define FALSE 0
#define N 2

int turn =0;
int interested[N];
int x=0;

void enter_section(int process) {
    int other = 1-process; // other = 1-0 => 1
    interested[process] = TRUE; // for process 0 set turn true  [1,0]
    turn = process; // turn =0;
    while(turn==process && interested[other] == TRUE); // loop is false => No wait    i.e. Can instantly enter critical section bcoz other is not interested
}

void leave_section(int process) {
    interested[process] = FALSE;
}

class thread_object {
public:
    void operator()(int process) {
        for (int i=0; i<10000; ++i) {
            enter_section(process);
            x += 1;
            std::cout<<"Thread"<<process<<" "<<x<<std::endl;
            leave_section(process);
        }
    }
};

int main(int argc, char *argv[]) {
    thread_object obj;
    std::thread th1(obj, 0);
    std::thread th2(obj, 1);
    th1.join();
    th2.join();
    return 0;
}