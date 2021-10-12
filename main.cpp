#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

pid_t createChildProcess() {
    pid_t child_pid = fork(); // creating child process
    
    if (child_pid == -1) { // process error
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (child_pid > 0) {
        // child_pid = fork() returns the child PID to the parent
        return child_pid;
    } else {
        exit(EXIT_FAILURE); 
    }
}

int main()
{
    // Create 4 child processes
    for (int i = 0; i < 4; i++) {
        int processID = createChildProcess();
        //  After creating each child process the parent process prints a list of child processes.
        cout << "Child: [PID: " << processID << "] CREATED" << endl;
    }
    
    pid_t child_pid;

    // terminate children after every 4 seconds
    while((child_pid = wait(nullptr)) > 0) {
        sleep(4);
        cout << " Child: [PID:" << child_pid << "] TERMINATED " << endl;
    }

    return EXIT_SUCCESS;
}

/* OUTPUT:
Child: [PID: 6801] CREATED
Child: [PID: 6802] CREATED
Child: [PID: 6803] CREATED
Child: [PID: 6804] CREATED
 Child: [PID:6801] TERMINATED 
 Child: [PID:6802] TERMINATED 
 Child: [PID:6803] TERMINATED 
 Child: [PID:6804] TERMINATED 
*/