#!/bin/bash

DIRS=("$HOME" "/usr/bin" "/etc")

for DIR in "${DIRS[@]}"; do
    echo "Directory: $DIR"
    
    ls -l "$DIR" 2>/dev/null | head -n 4
    echo ""

    TEST_FILE=$(ls -p "$DIR" 2>/dev/null | grep -v / | head -n 1)
    FULL_PATH="$DIR/$TEST_FILE"

    if [ -z "$TEST_FILE" ]; then
        echo "No test file found."
        echo ""
        continue
    fi

    echo "Testing file access: $FULL_PATH"

    if cat "$FULL_PATH" > /dev/null 2>&1; then
        echo "Read    : Success"
    else
        echo "Read    : Access Denied"
    fi

    if echo "test" >> "$FULL_PATH" 2>/dev/null; then
        echo "Write   : Success"
    else
        echo "Write   : Access Denied"
    fi

    if [ -x "$FULL_PATH" ]; then
        echo "Execute : Success"
    else
        echo "Execute : Access Denied"
    fi
    echo ""
done
