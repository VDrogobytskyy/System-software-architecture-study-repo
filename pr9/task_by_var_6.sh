#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 <username>"
    exit 1
fi

USER_NAME=$1

if ! id "$USER_NAME" >/dev/null 2>&1; then
    echo "Error: User '$USER_NAME' not found."
    exit 1
fi

echo "Analyzing user: $USER_NAME"

USER_SHELL=$(grep "^$USER_NAME:" /etc/passwd | cut -d: -f7)

USER_HOME=$(grep "^$USER_NAME:" /etc/passwd | cut -d: -f6)

USER_PASS_STATUS=$(sudo passwd -S "$USER_NAME" | awk '{print $2}')

echo ""
echo "Shell      : $USER_SHELL"
echo "Home       : $USER_HOME"
echo "Password   : $USER_PASS_STATUS (L=Locked, P=Passable)"
echo ""

IS_SYSTEM=0

if [[ "$USER_SHELL" == *"/nologin"* || "$USER_SHELL" == *"/false"* ]]; then
    IS_SYSTEM=$((IS_SYSTEM + 1))
fi

if [[ "$USER_HOME" != "/home/"* ]]; then
    IS_SYSTEM=$((IS_SYSTEM + 1))
fi

if [[ "$USER_PASS_STATUS" == "L" ]]; then
    IS_SYSTEM=$((IS_SYSTEM + 1))
fi

if [ $IS_SYSTEM -ge 2 ]; then
    echo "Result: This is a SYSTEM user (based on non-UID criteria)."
else
    echo "Result: This is a REGULAR user."
fi
