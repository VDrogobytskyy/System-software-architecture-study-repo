#!/bin/bash

FILE_NAME="ordinary_file.txt"
COPY_NAME="root_owned.txt"

echo "Creating a file as $USER..."
echo "Regular user data" > "$FILE_NAME"
ls -l "$FILE_NAME"

echo ""
echo "Copying to home folder as ROOT..."
sudo cp "$FILE_NAME" "$HOME/$COPY_NAME"
sudo chmod 644 "$HOME/$COPY_NAME"
ls -l "$HOME/$COPY_NAME"

echo ""
echo "Trying to modify the file..."

if sudo -u "$USER" bash -c "echo 'New data' >> '$HOME/$COPY_NAME'" 2>/dev/null; then
    echo "Result: Success."
else
    echo "Result: Access denied. I cannot edit root's file."
fi

echo ""
echo "Trying to delete the file..."
if rm "$HOME/$COPY_NAME" 2>/dev/null; then
    echo "Result: Success! The file was deleted."
    echo "Explanation: I can delete it because I own the directory."
else
    echo "Result: Failed to delete."
fi

rm "$FILE_NAME" 2>/dev/null
echo ""
