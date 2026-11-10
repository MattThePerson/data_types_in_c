#!/usr/bin/env bash
# usage: ./run.sh [-t] examples/demo_bst.c
#        ./run.sh [-t] examples/my_folder/
# -t runs tidyrun-% instead of run-%
set -euo pipefail

EXDIR=${EXDIR:-examples}

target=run
if [[ ${1:-} == -t ]]; then
    target=tidyrun
    shift
fi

if [[ $# -ne 1 ]]; then
    echo "usage: $0 [-t] <$EXDIR/foo.c | $EXDIR/foo/>" >&2
    exit 2
fi

path=${1#./}          # drop leading ./
rel=${path#"$EXDIR"/} # path relative to the examples dir
if [[ $rel == "$path" || -z $rel ]]; then
    echo "error: '$1' is not inside $EXDIR/" >&2
    exit 1
fi

name=${rel%%/*} # first path component: foo.c or foo
name=${name%.c} # strip .c for single-file examples

exec make "$target-$name"
