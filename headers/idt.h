#include "common.h"
#include "io.h"
#include "terminal.h"

// A struct describing an interrupt gate.
struct idt_entry_struct
{
   uint16_t offset_1;
   uint16_t selector;
   uint8_t ist;
   uint8_t type_attr;
   uint16_t offset_2;
   uint32_t offset_3;
   uint32_t zero;
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;

// A struct describing a pointer to an array of interrupt handlers.
// This is in a format suitable for giving to 'lidt'.
struct idt_ptr_struct
{
   uint16_t limit;
   uint64_t base;
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
extern void isr32();
extern void isr33();
extern void isr34();
extern void isr35();
extern void isr36();
extern void isr37();
extern void isr38();
extern void isr39();
extern void isr40();

idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;

void idt_flush(uint64_t pointer);
void init_idt();
void isr_handler(uint64_t n, uint64_t error);
