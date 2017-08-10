#include "stdint.h"
#include "global.h"
#include "thread.h"
#include "string.h"
#include "memory.h"

static void kernel_thread(thread_func *function, void *func_arg)
{
	function(func_arg);
}

void thread_create(struct task_struct *pthread, thread_func *function, void *func_arg)
{
	pthread->self_kstack -= sizeof(struct intr_stack);
	pthread->self_kstack -= sizeof(struct thread_stack);

	struct thread_stack *kthread_stack = (struct thread_stack *)pthread->self_kstack;
	kthread_stack->eip = kernel_thread;
	kernel_thread->function = function;
	kernel_thread->func_arg = func_arg;
	kernel_thread->ebp = kernel_thread->ebx = kernel_thread->esi = kernel_thread->edi = 0;
}

void init_thread(struct task_struct *pthread, char *name, int prio)
{
	memset(pthread, 0, sizeof(*pthread));
	strcpy(pthread->name, name);
	pthread->status = TASK_RUNNING;
	pthread->priority = prio;
	pthread->self_kstack = (uint32_t *)((uint32_t)pthread + PAGE_SIZE);
	pthread->stack_magic = 0x19870916;
}

struct task_struct *thread_start(char *name, int prio, thread_func *function, void *func_arg)
{
	struct task_struct *thread = get_kernel_pages(1);
	init_thread(thread, name, prio);
	thread_create(thread, function, func_arg);

	asm volatile ("movl %0, %%esp;
				   pop %%ebp;
				   pop %%ebx;
				   pop %%edi;
				   pop %%esi;" : : "g"(thread->self_kstack) : "memory");
	return thread;
}


