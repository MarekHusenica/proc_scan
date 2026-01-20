import ctypes
import os

class Node(ctypes.Structure):
    pass

Node._fields_ = [
    ("item", ctypes.c_void_p),
    ("next", ctypes.POINTER(Node)),
    ("prev", ctypes.POINTER(Node))
]

class DLList(ctypes.Structure):
    _fields_ = [
        ("first", ctypes.POINTER(Node)),
        ("last", ctypes.POINTER(Node)),
        ("active", ctypes.POINTER(Node))
    ]

lib_path = os.path.join(os.path.dirname(__file__), "liblinkedlist.so")
lib = ctypes.CDLL(lib_path)

lib.linked_list_init.restype = DLList

lib.linked_list_free.argtypes = [ctypes.POINTER(DLList)]


lib.linked_get_first.restype = ctypes.POINTER(Node)
lib.linked_get_first.argtypes = [ctypes.POINTER(DLList)]

lib.linked_get_last.restype = ctypes.POINTER(Node)
lib.linked_get_last.argtypes = [ctypes.POINTER(DLList)]

lib.linked_get_active.restype = ctypes.POINTER(Node)
lib.linked_get_active.argtypes = [ctypes.POINTER(DLList)]


lib.linked_insert_first.argtypes = [ctypes.POINTER(DLList), ctypes.c_void_p]
lib.linked_insert_first.restype = ctypes.c_int

lib.linked_insert_last.argtypes = [ctypes.POINTER(DLList), ctypes.c_void_p]
lib.linked_insert_last.restype = ctypes.c_int

lib.linked_insert_after_active.argtypes = [ctypes.POINTER(DLList), ctypes.c_void_p]
lib.linked_insert_after_active.restype = ctypes.c_int

lib.linked_insert_before_active.argtypes = [ctypes.POINTER(DLList), ctypes.c_void_p]
lib.linked_insert_before_active.restype = ctypes.c_int

lib.linked_set_active_next.argtypes = [ctypes.POINTER(DLList)]
lib.linked_set_active_next.restype = ctypes.c_int

lib.linked_set_active_prev.argtypes = [ctypes.POINTER(DLList)]
lib.linked_set_active_prev.restype = ctypes.c_int

lib.linked_set_active_first.argtypes = [ctypes.POINTER(DLList)]
lib.linked_set_active_first.restype = ctypes.c_int

lib.linked_set_active_last.argtypes = [ctypes.POINTER(DLList)]
lib.linked_set_active_last.restype = ctypes.c_int
