import pytest
import ctypes
from list_wrapper import lib, DLList, Node

@pytest.fixture
def empty_list():
    l_list = lib.linked_list_init()
    l_ptr = ctypes.pointer(l_list)
    yield l_ptr
    lib.linked_list_free(l_ptr)

def test_insertion_logic(empty_list):
    item1 = ctypes.c_void_p(101)
    item2 = ctypes.c_void_p(202)

    lib.linked_insert_first(empty_list, item1)
    lib.linked_insert_last(empty_list, item2)

    first_node = lib.linked_get_first(empty_list)
    last_node = lib.linked_get_last(empty_list)

    assert first_node.contents.item == 101
    assert last_node.contents.item == 202

    assert ctypes.addressof(first_node.contents.next.contents) == ctypes.addressof(last_node.contents)
    assert ctypes.addressof(last_node.contents.prev.contents) == ctypes.addressof(first_node.contents)

def test_active_movement(empty_list):
    lib.linked_insert_first(empty_list, ctypes.c_void_p(10))
    lib.linked_set_active_first(empty_list)

    lib.linked_insert_after_active(empty_list, ctypes.c_void_p(20))

    active = lib.linked_get_active(empty_list)
    assert active.contents.item == 10

    lib.linked_set_active_next(empty_list)
    active = lib.linked_get_active(empty_list)
    assert active.contents.item == 20
    # TODO: Add a third element and check get_active_last