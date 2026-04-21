#!/bin/bash

TEMP_FILE="temp_experiment.txt"

echo "Creating file as $USER..."
echo "Sensitive data" > "$TEMP_FILE"
ls -l "$TEMP_FILE"

echo ""
echo "Changing ownership to ROOT and setting permissions to 600 (Owner only)..."
sudo chown root:root "$TEMP_FILE"
sudo chmod 600 "$TEMP_FILE"
ls -l "$TEMP_FILE"

echo ""
echo "Attempting to READ as $USER:"
if cat "$TEMP_FILE" 2>/dev/null; then
    echo "Read: Success"
else
    echo "Read: Access denied"
fi

echo ""
echo "Attempting to WRITE as $USER:"
if echo "New data" >> "$TEMP_FILE" 2>/dev/null; then
    echo "Write: Success"
else
    echo "Write: Access denied"
fi

echo ""
echo "Changing permissions to 644 (Read-only for others)..."
sudo chmod 644 "$TEMP_FILE"
ls -l "$TEMP_FILE"

echo ""
echo "Attempting to READ again:"
if cat "$TEMP_FILE" 2>/dev/null; then
    echo "Read: Success"
else
    echo "Read: Access denied"
fi

sudo rm "$TEMP_FILE"
