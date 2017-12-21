#include "userprog/syscall.h"

#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "userprog/pagedir.h"
#include "devices/fake_io.h"
#include "../lib/syscall-nr.h"

#define MAX_ARGS 3
void syscall_init (void);
static void syscall_handler (struct intr_frame *);
void get_arg (struct intr_frame *f, int *arg, int n);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
    int arg[MAX_ARGS];
    switch (*(int *) f->esp) {
        case SYS_HALT:
        case SYS_EXEC:
        case SYS_WAIT:
        case SYS_CREATE:
        case SYS_REMOVE:
        case SYS_OPEN:
        case SYS_FILESIZE:
        case SYS_READ:
        case SYS_WRITE:
        case SYS_SEEK:
        case SYS_TELL:
        case SYS_CLOSE:
        case SYS_MMAP:
        case SYS_MUNMAP:
        case SYS_CHDIR:
        case SYS_MKDIR:
        case SYS_READDIR:
        case SYS_ISDIR:
        case SYS_INUMBER:
            printf ("not implemented syscall! (%d)\n", (*(int *) f->esp));
            thread_exit();
            break;

        case SYS_EXIT:
            printf ("Exit\n");
            thread_exit();
            break;

        case SYS_IONEED:
            get_arg(f, arg, 2);
            printf ("I/O need (%d, %d)\n", arg[0], arg[1]);
            thread_current()->io_need += arg[1];
            printf ("I/O need thread: (%d)\n", thread_current()->io_need);
            break;

        case SYS_IODOWN:
            get_arg(f, arg, 2);
            printf ("I/O down (%d, %d)\n", arg[0], arg[1]);
            io_down(arg[0], arg[1]);
            break;
    }
}

void get_arg (struct intr_frame *f, int *arg, int n)
{
    int i;
    int *ptr;
    for (i = 0; i < n; i++)
    {
        ptr = (int *) f->esp + i + 1;
        arg[i] = *ptr;
    }
}
