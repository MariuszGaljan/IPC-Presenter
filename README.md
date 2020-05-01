# IPC Presenter

This is a simple program that demonstrates the Inter Process Communication (IPC) mechanisms in Linux and their usage.

**NOTE: At the time of writing this, Windows Subsystem for Linux does not have support for the message queue. Therefore, to run this program you need either an installed Linux distribution or a Linux VM**

The program utilizes such IPC mechanisms as:
- forks
- signals
- message queues
- shared memory
- semaphores



## How does it work?

1. Run the **ipcPresenter** program from your terminal (see *Compilation* for details on creating).

2. The program launches **three** additional terminal windows, one for each process. To show the communication between them, every one of them prints out the PIDs of the processes.

    ![Starting state image](README_img\ipcPresenter_begin.png)

3. Process 1 reads the **input text** and sends it to process2.

4. Process 2 counts the **number of characters** in the string and sends it to process 3.

5. Process 3 prints out the number. Simple as that.

    ![After input image](README_img\ipcPresenter_insert.png)

6. To exit, send **SIGINT signal (Ctrl + C)**. The programs wait for any character, so the terminals don't close immediately

    ![Finished state image](README_img\ipcPresenter_end.png)



At any time, you can **send signals** to any one of the processes and they will **all respond**.
You can do it either via keyboard shortcuts or another terminal using the printed PIDs.

Signals the processes react to:
 -  SIGINT  -   exits the programs
 -  SIGUSR2 -   pauses the running of the programs
 -  SIGCONT -   continues the running of the programs

## Compilation

Just run **make** in your terminal.
Run **make clean** if you want to delete the compiled files.
