#!/bin/bash

input_file="./build/Testing/Temporary/LastTest.log"
output_file="output.log"

# Clear the output file if it already exists
> "$output_file"

pass_count=0
fail_count=0

# Read the input file line by line
while IFS= read -r line; do
  # Check if the line starts with "PASS" or "FAIL" and matches the pattern
  if [[ $line =~ ^(PASS|FAIL):\ vast-test-cxx\ ::\ (.+\.cpp) ]]; then
    # Extract the status and filename
    status=${BASH_REMATCH[1]}
    filename=${BASH_REMATCH[2]}

    if [[ $status == "FAIL" ]]; then
      echo "$status $filename" >> "$output_file"
    fi

    if [[ $status == "PASS" ]]; then
      ((pass_count++))
    fi
    if [[ $status == "FAIL" ]]; then
      ((fail_count++))
    fi

  fi
done < "$input_file"

# Write the total number of tests passed to the output file
total_count=$((pass_count + fail_count))
result="${fail_count}/${total_count} tests failed"
sed -i "1i$result" "$output_file"

echo "Processing completed. Output written to $output_file."

awk '
/\/\/ -----\/\/ .*\/\/----- \/\// {
    skip = 1
    next
}
/^$/ {
    skip = 0
}
!skip
' build/Testing/Temporary/LastTest.log > test.log

sed -i '/^PASS: vast-test-cxx/d' test.log
