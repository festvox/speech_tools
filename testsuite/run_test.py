#!/usr/bin/env python3

import os
import sys
from subprocess import run, PIPE
from difflib import unified_diff

TESTNAME=sys.argv[1]
TESTBIN=sys.argv[2]
CORRECTDIR=sys.argv[3]
TESTARGS=sys.argv[4:]


os.makedirs("tmp", exist_ok = True)
test_result = run([TESTBIN] + TESTARGS, stdout = PIPE)

if test_result.returncode != 0:
    print(TESTNAME + " status: FAILED")
    sys.exit(1)

print(TESTNAME + " completed")
test_output = test_result.stdout.decode("utf-8")

# load expected result:
with open(os.path.join(CORRECTDIR, TESTNAME + ".out")) as fh:
    test_output_correct = fh.read()

# paths and newlines in windows and unix are different
test_output_correct = test_output_correct.replace("\\", "/").replace("\r\n", "\n")
test_output_patched = test_output.replace("\\", "/").replace("\r\n", "\n")

output_diff = unified_diff(test_output_patched.splitlines(keepends=True),
                           test_output_correct.splitlines(keepends=True))
output_diff_str = "".join(output_diff)

if output_diff_str == "":
    print(TESTNAME + " status: CORRECT")
    sys.exit(0)
else:
    print(TESTNAME + " status: INCORRECT")
    print(output_diff_str)
    sys.exit(1)

