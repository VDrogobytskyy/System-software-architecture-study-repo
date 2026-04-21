#!/bin/bash

THRESHOLD=1000

found_others=false

echo ""
echo "looking for different users except drogobytskyyy"

echo ""

while IFS=: read -r username password uid gid info home shell; do
    if [ "$uid" -ge "$THRESHOLD" ] && [ "$username" != "$USER" ] && [ "$username" != "nobody" ]; then
        echo "User found: $username (UID: $uid)"
        found_others=true
    fi
done < <(getent passwd)

if [ "$found_others" = false ]; then
    echo "differnt users not found."
fi

echo ""
