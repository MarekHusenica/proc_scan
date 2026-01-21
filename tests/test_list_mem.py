import ctypes
from list_wrapper import lib, libc

def leak_check():
    l_list = lib.linked_list_init()
    l_ptr = ctypes.pointer(l_list)

    for i in range(100):
        item = libc.malloc(16)

        lib.linked_insert_first(l_ptr, item)
        first = lib.linked_get_first(l_ptr)
        item_to_free = first.contents.item
        lib.linked_delete_first(l_ptr)
        libc.free(item_to_free)

    lib.linked_list_free(l_ptr)

if __name__ == "__main__":
    leak_check()