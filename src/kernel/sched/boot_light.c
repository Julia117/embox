/**
 * @file
 * @brief Pseudo thread as boot thread. It cannot use sync functions.
 *
 * @author  Vita Loginova
 * @date    08.12.2014
 */

#include <kernel/panic.h>

#include <kernel/sched/schedee.h>
#include <kernel/lthread/lthread_priority.h>

struct schedee boot_schedee;

static void *boot_stub(void *arg) {
	panic("Entering boot_stub");
}

static struct schedee *boot_process(struct schedee *prev, struct schedee *next) {
	assert(prev == next);
	assert(next == &boot_schedee);

	schedee_set_current(next);
	ipl_enable();

	return &boot_schedee;
}

struct schedee *boot_thread_create(void)
{
	schedee_init(&boot_schedee, LTHREAD_PRIORITY_DEFAULT, boot_process,
		boot_stub, NULL);
	return &boot_schedee;
};
