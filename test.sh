#!/usr/bin/env bash
# usage: ./test.sh [-l|--list] [pattern]
#   no pattern  -> all tests in tests/
#   pattern     -> substring glob on file name (case-insensitive)
#   -l, --list  -> print matching tests instead of running them
shopt -s nocaseglob

list=0
if [[ ${1:-} == -l || ${1:-} == --list ]]; then
    list=1
    shift
fi

pattern=${1:-}

files=(tests/*${pattern}*.c)
if [[ ! -e ${files[0]} ]]; then
    echo "no tests match '$pattern'" >&2
    exit 2
fi

if ((list)); then
    for f in "${files[@]}"; do
        echo "${f%.c}"
    done
    exit 0
fi

pass=0
fail=0
failed=()
err=$(mktemp)
trap 'rm -f "$err"' EXIT

out=$(mktemp)
for f in "${files[@]}"; do
    name=${f%.c}
    if make -s "cleanrun/$name" >"$out" 2>"$err"; then
        echo "PASS  $name"
        ((pass++))
    else
        echo "FAIL  $name"
        ((fail++))
        failed+=("$name")
    fi
    sed 's/^/    /' "$out" "$err"
done
rm -f "$out"

echo "$pass passed, $fail failed"
((fail == 0))
