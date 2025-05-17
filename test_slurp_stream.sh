
#!/bin/bash
set -e

# Build jq
make

# Test cases from issue description
echo "Test 1: With newline (should be ok)"
printf "[1]\n" | ./jq -c -s --stream .
echo "Test 2: Without newline (should now match Test 1)"
printf "[1]" | ./jq -c -s --stream .

# Additional test cases
echo "Test 3: Multiple values with newline"
printf "[1]\n[2]\n" | ./jq -c -s --stream .
echo "Test 4: Multiple values without newline"
printf "[1][2]" | ./jq -c -s --stream .
