#!/bin/bash

INPUT_FILE="$1"

if [ -z "$INPUT_FILE" ] || [ ! -f "$INPUT_FILE" ]; then
    echo "Usage: $0 <minion_file>"
    exit 1
fi

# Create temporary files
TMP_VARS=$(mktemp)
TMP_CONS=$(mktemp)
NEW_BOUNDS=$(mktemp)

# 1. Extract just the variable names from the **VARIABLES** block
awk '/^\*\*VARIABLES\*\*/{flag=1; next} /^\*\*CONSTRAINTS\*\*/{flag=0; next} flag && /^BOUND/ {print $2}' "$INPUT_FILE" > "$TMP_VARS"

# 2. Extract just the constraints into a separate file
awk '/^\*\*CONSTRAINTS\*\*/{flag=1; next} /^\*\*/{if(flag) flag=0} flag' "$INPUT_FILE" > "$TMP_CONS"

# 3. Iterate through each variable and write to NEW_BOUNDS
while read -r var; do
    # - grep ONLY "sumleq" constraints from TMP_CONS for this variable
    # - extract the trailing number, keep only digits, and sort for the minimum
    min_val=$(grep "sumleq" "$TMP_CONS" | grep "$var" | grep -oE ',-?[0-9]+\)[[:space:]]*$' | tr -dc '0-9-\n' | sort -n | head -n 1)

    if [ -n "$min_val" ]; then
        echo "BOUND $var {0..$min_val}"
    else
        # Fallback if a variable exists but has no sumleq constraints
        echo "BOUND $var {0..60}"
    fi
done < "$TMP_VARS" > "$NEW_BOUNDS"

# 4. Replace the old bounds in the original file in-place
awk -v nb="$NEW_BOUNDS" '
BEGIN { print_line = 1 }
/^\*\*VARIABLES\*\*/ { 
    print; 
    system("cat " nb); 
    print_line = 0; 
    next 
}
/^\*\*CONSTRAINTS\*\*/ { 
    print_line = 1 
}
print_line
' "$INPUT_FILE" > "${INPUT_FILE}.tmp"

# Safely overwrite the original file
mv "${INPUT_FILE}.tmp" "$INPUT_FILE"

# Cleanup
rm -f "$TMP_VARS" "$TMP_CONS" "$NEW_BOUNDS"
