//
// Created by Sadegh on 12/20/17.
//
#include "fake_io.h"

#include <string.h>
#include <debug.h>
#include <stdio.h>
#include "devices/timer.h"
#include "threads/malloc.h"

void io_init(const char* name);
void io_down(const char* name, const int64_t ticks);
struct io_device* _find_io_device_by_name(const char* name);

void
io_init(const char* name)
{
    struct io_device *io_device = malloc (sizeof *io_device);
    if (io_device == NULL)
        PANIC ("Failed to allocate memory for io_device descriptor");

    list_push_back (&io_devices, &io_device->list_elem);
    strlcpy (io_device->name, name, sizeof io_device->name);
    sema_init(&io_device->in_use, 1);
}

struct io_device*
_find_io_device_by_name(const char* name)
{
    struct list_elem *e;

    for(e = list_begin (&io_devices);
        e != list_end (&io_devices);
        e = list_next (e)) {
        struct io_device *io_device = list_entry (e, struct io_device, list_elem);
        if (!strcmp (name, io_device->name))
            return io_device;
    }

    return NULL;
}


void
io_down(const char* name, const int64_t ticks)
{
    struct io_device *io_device = _find_io_device_by_name(name);
    if(io_device == NULL)
        goto error;

    // get lock for N ticks
    sema_down(&io_device->in_use);
    timer_sleep(ticks);
    sema_up(&io_device->in_use);

error:
    printf("Device not found!");
    return;
}