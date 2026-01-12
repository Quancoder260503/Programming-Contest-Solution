#!/bin/bash

TEST_DIR="./TimDance_Data"

pass=0
total=0

for infile in "$TEST_DIR"/*.in; do
    testname="${infile%.in}"
    outfile="out.txt"
    ansfile="${testname}.out"

    echo "Running test: $testname"
    ((total++))

    ./tim < "$infile" > "$outfile"

    # Normalize both files to ensure they end with a newline
    printf '\n' >> "$outfile"
    printf '\n' >> "$ansfile"

    # Compare while ignoring differences in whitespace and newlines
    if diff -q -bB "$outfile" "$ansfile" > /dev/null; then
        echo -e "✅ Accepted"
        ((pass++))
    else
        echo -e "❌ Wrong Answer"
        diff -y -bB "$outfile" "$ansfile"
    fi

    echo "--------------------------------------"
done

echo "Summary: $pass / $total tests passed ✅"
