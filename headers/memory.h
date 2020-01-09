#include "common.h"
#include "string.h"

struct __attribute__((__packed__)) PageTable
{
  uint64_t entries[512];
};
typedef struct PageTable PageTable;

struct __attribute__((__packed__)) PageDirectory
{
  PageTable *page_tables;
};
typedef struct PageDirectory PageDirectory;

struct __attribute__((__packed__)) PageDirectoryPointer
{
  PageDirectory *page_directories;
};
typedef struct PageDirectoryPointer PageDirectoryPointer;

struct __attribute__((__packed__)) PageMap
{
  PageDirectoryPointer *page_directory_pointers;
};
typedef struct PageMap PageMap;

PageMap *create_paging_structures(uint64_t base_address);
void load_paging_structure(PageMap *address);
