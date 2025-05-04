#include "task.h"
#include "memory_manager.h"
#include "vga.h"

#define STACK_SIZE 4096

task_t* current_task = 0;
task_t* task_queue_head = 0;

static uint32_t next_task_id = 1;

extern void context_switch(uint32_t eip, uint32_t esp, uint32_t ebp);

void create_task(void (*entry_point)()) {
    task_t* new_task = (task_t*)alloc_memory(sizeof(task_t));
    if (!new_task) {
        vga_write("[!] Failed to allocate memory for task\n");
        return;
    }

    new_task->stack = (uint32_t*)alloc_memory(STACK_SIZE);
    if (!new_task->stack) {
        vga_write("[!] Failed to allocate stack\n");
        return;
    }

    new_task->id = next_task_id++;
    new_task->state = TASK_READY;
    new_task->esp = (uint32_t)(new_task->stack + STACK_SIZE - 1);
    new_task->ebp = new_task->esp;
    new_task->eip = (uint32_t)entry_point;
    new_task->next = 0;

    // Add to queue
    if (!task_queue_head) {
        task_queue_head = new_task;
        current_task = new_task;
        new_task->next = new_task;
    } else {
        task_t* temp = task_queue_head;
        while (temp->next != task_queue_head) temp = temp->next;
        temp->next = new_task;
        new_task->next = task_queue_head;
    }

    vga_write("[+] Task created.\n");
}

void run_next_task() {
    if (!current_task) {
        vga_write("[!] No tasks to run.\n");
        return;
    }

    current_task->state = TASK_RUNNING;
    context_switch(current_task->eip, current_task->esp, current_task->ebp);
    __builtin_unreachable();  // Should never return here after a context switch
}

void task_yield() {
    if (!current_task || !current_task->next) {
        vga_write("[!] No other task to switch to.\n");
        return;
    }

    // Save current task context (placeholder: use inline asm if needed later)
    task_t* prev = current_task;
    current_task = current_task->next;
    current_task->state = TASK_RUNNING;

    context_switch(current_task->eip, current_task->esp, current_task->ebp);
    __builtin_unreachable();  // Should never return here after yielding
}

void task_trampoline(void (*task_func)()) {
    task_func();
    vga_write("[!] Task returned — halting!\n");
    while (1);  // Panic or halt
}

void context_switch(uint32_t eip, uint32_t esp, uint32_t ebp) {
    asm volatile (
        "mov %0, %%esp\n"
        "mov %1, %%ebp\n"
        "jmp *%2\n"
        :
        : "r" (esp), "r" (ebp), "r" (eip)
    );
    __builtin_unreachable();  // We should never return here after context switch
}
