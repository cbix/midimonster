#include <sys/types.h>

#include "midimonster.h"

/*
 * This provides read-write access to the Linux kernel evdev subsystem
 * via libevdev. On systems where uinput is not supported, output can be
 * disabled by building with -DEVDEV_NO_UINPUT
 */

int init();
static int evdev_configure(char* option, char* value);
static int evdev_configure_instance(instance* instance, char* option, char* value);
static instance* evdev_instance();
static channel* evdev_channel(instance* instance, char* spec);
static int evdev_set(instance* inst, size_t num, channel** c, channel_value* v);
static int evdev_handle(size_t num, managed_fd* fds);
static int evdev_start();
static int evdev_shutdown();

typedef struct /*_evdev_instance_model*/ {
	int input_fd;
	struct libevdev* input_ev;
	int exclusive;

	int output_enabled;
#ifndef EVDEV_NO_UINPUT
	struct libevdev* output_proto;
	struct libevdev_uinput* output_ev;
#endif
} evdev_instance_data;
