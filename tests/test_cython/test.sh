#!/bin/bash

if python3 -c "import cython" 2>/dev/null; then
    echo "this test is not running without Cython installed"
    exit 0
fi

str="verificarlo"

export CC=$str
export FC=$str
export LDSHARED="$str -shared"

# Build library
python3 setup.py build_ext --inplace

num=200
# Test build
python3 -c "from test import test_function as f; f($num)"