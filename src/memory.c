#include "memory.h"

PageMap *create_paging_structures(uint64_t base_address)
{
  memset((void *)base_address, 0, 0x4000);
  PageMap *page_map = (PageMap *)base_address;
  page_map->page_directory_pointers = (PageDirectoryPointer *)(base_address+0x1003);

  PageDirectoryPointer *page_directory_pointer = (PageDirectoryPointer *)(base_address+0x1000);
  page_directory_pointer->page_directories = (PageDirectory *)(base_address+0x2003);

  PageDirectory *page_directory = (PageDirectory *)(base_address+0x2000);
  page_directory->page_tables = (PageTable *)(base_address+0x3003);

  PageTable *page_table = (PageTable *)(base_address+0x3000);
  uint64_t entry = 0x03;
  // Loop through the page table
  for (int i = 0; i < 512; ++i)
  {
    page_table->entries[i] = entry;
    entry += 0x1000;
  }

  return page_map;
}

void load_paging_structure(PageMap *address)
{
  asm volatile("mov %0, %%cr3" : : "r"(address));
}
