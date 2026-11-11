#!/usr/bin/env bash
# usage: ./run.sh [-t] examples/demo_bst.c
#        ./run.sh [-t] examples/my_folder/
#        ./run.sh [-t] tests/test_bst.c [-- ARGS...]
# -t runs cleanrun/% instead of run/%
# -- ARGS...  passed to the program, e.g. -- --filter=basic
set -euo pipefail

target=run
if [[ ${1:-} == -t ]]; then
    target=cleanrun
    shift
fi

# split off everything after "--"
pos=()
args=()
while (($#)); do
    if [[ $1 == -- ]]; then
        shift
        args=("$@")
        break
    fi
    pos+=("$1")
    shift
done

if ((${#pos[@]} != 1)); then
    echo "usage: $0 [-t] <dir/foo.c | dir/foo/> [-- ARGS...]" >&2
    exit 2
fi

path=${pos[0]#./} # drop leading ./
path=${path%/}    # drop trailing slash (folder examples)
path=${path%.c}   # drop .c for single-file examples

if [[ -z $path ]]; then
    echo "error: empty path" >&2
    exit 1
fi

# Shell-quote the args into one string for make; double $ so make keeps it literal.
prog_args=
if ((${#args[@]})); then
    printf -v prog_args '%q ' "${args[@]}"
    prog_args=${prog_args//\$/\$\$}
fi

exec make "$target/$path" ARGS="$prog_args"
