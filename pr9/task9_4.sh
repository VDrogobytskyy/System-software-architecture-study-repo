#!/bin/bash

echo "Current user identity:"
whoami

echo ""
echo "Full account details (UID, GID, and Groups):"
id

echo ""
echo "List of all groups you belong to:"
id -Gn

echo ""
echo "Summary:"
echo "User $USER is currently active and belongs to $(id -Gn | wc -w) groups."
