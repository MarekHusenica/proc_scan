import subprocess
import pytest

TEST_TARGET="./proc_scan"

def test_compare_to_py():
    result = subprocess.run([TEST_TARGET], capture_output=True, text=True)

    lines = result.stdout.strip().split(None)
    
    assert "proc_scan" in lines
    assert "1" in lines



