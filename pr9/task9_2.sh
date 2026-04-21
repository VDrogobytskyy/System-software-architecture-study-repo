#!/bin/bash

echo ""
echo "Try to read /etc/shadow like admin"

echo ""
sudo cat /etc/shadow

if [ $? -eq 0 ]; then
    echo "Success: File /etc/shadow accessed successfully."
else
    echo "Error: Failed to obtain administrative access."
fi

echo ""
