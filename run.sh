#!/usr/bin/env bash
# usage: ./run.sh [-t] examples/demo_bst.c
#        ./run.sh [-t] examples/my_folder/
#        ./run.sh [-t] tests/test_bst.c
# -t runs tidyrun/% instead of run/%
set -euo pipefail

target=run
if [[ ${1:-} == -t ]]; then
    target=cleanrun
    shift
fi

if [[ $# -ne 1 ]]; then
    echo "usage: $0 [-t] <dir/foo.c | dir/foo/>" >&2
    exit 2
fi

path=${1#./}    # drop leading ./
path=${path%/}  # drop trailing slash (folder examples)
path=${path%.c} # drop .c for single-file examples

if [[ -z $path ]]; then
    echo "error: empty path" >&2
    exit 1
fi

exec make "$target/$path"
