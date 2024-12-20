#ifndef HELLO1_H
#define HELLO1_H

#include <linux/ktime.h>
#include <linux/list.h>

// Структура для збереження даних друку
struct hello_entry {
	struct list_head list;
	ktime_t time_before;
	ktime_t time_after;
};

void print_hello(void);

#endif // HELLO1_H

