import os
import subprocess
import pytest

LIB_NAME = "liblinkedlist.so"

def pytest_sessionstart(session):
    print(f"\n--- Compiling {LIB_NAME} ---")

    compile_cmd = [
        "gcc", "-fPIC", "-shared",
        "-o", LIB_NAME,
        "../src/d_linked_list.c"
    ]

    try:
        subprocess.run(compile_cmd, check=True)
        print("Compilation succesful.")
    except subprocess.CalledProcessError as e:
        pytest.exit(f"Compilation failed with: {e}")

def pytest_sessionfinish(session, exitstatus):
    if os.path.exists(LIB_NAME):
        print(f"\n--- Removing {LIB_NAME} ---")
        os.remove(LIB_NAME)