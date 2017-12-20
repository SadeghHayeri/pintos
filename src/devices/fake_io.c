//
// Created by Sadegh on 12/20/17.
//
#include "fake_io.h"

#include <string.h>
#include <debug.h>
#include <stdio.h>
#include "devices/timer.h"
#include "threads/malloc.h"

void io_init(const unsigned id);
void io_down(const unsigned id, const unsigned ticks);
struct io_device* _find_io_device_by_id(const unsigned id);

void
io_init(const unsigned id)
{
    struct io_device *io_device = malloc (sizeof *io_device);
    if (io_device == NULL)
        PANIC ("Failed to allocate memory for io_device descriptor");

    list_push_back (&io_devices, &io_device->list_elem);
    io_device->id = id;
    sema_init(&io_device->in_use, 1);
}

struct io_device*
_find_io_device_by_id(const unsigned id)
{
    struct list_elem *e;

    for(e = list_begin (&io_devices);
        e != list_end (&io_devices);
        e = list_next (e)) {
        struct io_device *io_device = list_entry (e, struct io_device, list_elem);
        if (id == io_device->id)
            return io_device;
    }

    return NULL;
}


void
io_down(const unsigned id, const unsigned ticks)
{
    struct io_device *io_device = _find_io_device_by_id(id);
    if(io_device == NULL) {
        printf("Device not found!");
        return;
    }

    sema_down(&io_device->in_use);
    timer_sleep(ticks);
    sema_up(&io_device->in_use);
}