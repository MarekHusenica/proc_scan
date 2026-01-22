import pytest
import ctypes
from .list_wrapper import lib, DLList, Node

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

    lib.linked_insert_last(empty_list, ctypes.c_void_p(30))

    active = lib.linked_get_active(empty_list)
    assert active.contents.item == 10

    lib.linked_set_active_next(empty_list)
    active = lib.linked_get_active(empty_list)
    assert active.contents.item == 20

    lib.linked_set_active_prev(empty_list)
    active = lib.linked_get_active(empty_list)
    assert active.contents.item == 10

    lib.linked_set_active_last(empty_list)
    active = lib.linked_get_active(empty_list)
    assert active.contents.item == 30

def test_deletion_logic(empty_list):
    lib.linked_insert_first(empty_list, ctypes.c_void_p(50))
    lib.linked_insert_first(empty_list, ctypes.c_void_p(40))
    lib.linked_insert_first(empty_list, ctypes.c_void_p(30))
    lib.linked_insert_first(empty_list, ctypes.c_void_p(20))
    lib.linked_insert_first(empty_list, ctypes.c_void_p(10))

    lib.linked_set_active_last(empty_list)
    lib.linked_set_active_prev(empty_list)

    delete_ret = lib.linked_delete_active(empty_list)
    active = lib.linked_get_active(empty_list)
    assert delete_ret == 1
    assert not active

    active = lib.linked_get_last(empty_list)
    assert active.contents.item == 50

    lib.linked_set_active_last(empty_list)
    lib.linked_set_active_prev(empty_list)
    active = lib.linked_get_active(empty_list)
    assert active.contents.item == 30
    assert active.contents.next.contents.item == 50
    assert active.contents.prev.contents.item == 20

    lib.linked_delete_last(empty_list)
    active = lib.linked_get_last(empty_list)
    assert active.contents.item == 30
    assert not active.contents.next
    assert active.contents.prev.contents.item == 20

    lib.linked_delete_first(empty_list)
    active = lib.linked_get_first(empty_list)
    assert active.contents.item == 20
    assert not active.contents.prev
    assert active.contents.next.contents.item == 30