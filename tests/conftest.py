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
        print("Compilation succesful.\n")
    except subprocess.CalledProcessError as e:
        pytest.exit(f"Compilation failed with: {e}\n")

def pytest_sessionfinish(session, exitstatus):
    if exitstatus == 0:
        print(f"\n\n--- Running Memory Leak Check ---")
        
        valgrind_cmd = [
            "valgrind",
            "--leak-check=full",
            "--error-exitcode=1",
            "--errors-for-leak-kinds=definite",
            "python3", "test_list_mem.py"
        ]
        
        result = subprocess.run(valgrind_cmd, capture_output=True, text=True)
        
        if result.returncode != 0:
            print(result.stderr)
            pytest.exit("Memory Leak Detected!", returncode=1)
        else:
            print("Memory Check Passed: No definite leaks found.")

    if os.path.exists(LIB_NAME):
        print(f"\n--- Removing {LIB_NAME} ---")
        os.remove(LIB_NAME)