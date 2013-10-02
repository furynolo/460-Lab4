#ifndef TYPE_H
#define TYPE_H

#define NPROC    9
#define SSIZE 1024
#define NULL     0
#define NFD     10

/******* PROC status ********/
#define FREE     0
#define READY    1
#define RUNNING  2
#define STOPPED  3
#define SLEEP    4
#define ZOMBIE   5


typedef unsigned char   u8;
typedef unsigned short  u16;
typedef unsigned long   u32;

/*typedef struct pipe
{
    char buf[PSIZE];
    int head, tail, data, room;
    int nreader, nwriter;
    int busy;
}PIPE;

typedef struct OFT
{
    int mode;
    int refCount;
    PIPE *pipe_ptr;//struct pipe *pipe_ptr;
}OFT;*/

//extern typedef struct proc;
typedef struct proc
{
    struct proc *next;
    int    *ksp;               // at offset 2
    int    uss, usp;           // at offsets 4,6
    int    pid;                // add pid for identify the proc
    int    status;             // status = FREE|READY|RUNNING|SLEEP|ZOMBIE    

    int    ppid;               // parent pid
    struct proc *parent;
    int    priority;
    int    event;
    int    exitCode;
    char   name[32];

//    OFT    *fd[NFD];
    int    kstack[SSIZE];      // per proc stack area
}PROC;

extern PROC proc[NPROC];
extern PROC *running;
extern PROC *freeList;
extern PROC *readyQueue;
extern PROC *sleepList;

/****************** int.c ******************/
int kcinth();

/**************** kernel.c *****************/
PROC *getproc();
int copy_image(u16 child_segment);
int do_fork();
int do_exec(int b);
int kfork(char *filename);
int body();
int do_tswitch();
int do_kfork();
int do_wait();
int do_exit();
int do_ps();
int kmode();
int chname();

/******************* t.c *******************/
int init();
int scheduler();
int int80h();
int set_vec(u16 vector, u16 handler);
main();

/****************** wait.c *****************/
PROC *findZombieChild(int processid);
int enterWait();
int kwait(int *status);
int enterSleepEvent();
int enterWakeupEvent();
int ksleep(int event);
int kwakeup(int event);
int hasChild(int processid);
int printQueue (PROC **queue);
int enqueue(PROC **queue, PROC *added);
PROC *dequeue (PROC **queue);
int dequeueSleep(PROC **queue, PROC *sleepyProc);
int enterExit();
int kexit(int value);
int giveChildrenAway(int parent);

#endif