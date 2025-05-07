#!/bin/bash

# Step 1: Verify if required files exist
echo "Checking for necessary files..."
if [ ! -f "aion.iso" ]; then
    echo "Error: aion.iso not found!"
    exit 1
fi

# Step 2: Clean and build
echo "Running make clean and make..."
make clean && make

# Step 3: Prompt user to plug in USB drive
echo "Please plug in your USB drive and press Enter to continue..."
read -p "Press Enter when done."

# Step 4: List removable devices
echo "Detecting removable devices..."
# List all removable devices (you can use `lsblk` or `fdisk` to find the devices)
removable_devices=$(lsblk -o NAME,SIZE,TYPE,MOUNTPOINT | grep "disk" | grep -v "sr0")  # Excluding CD drives like 'sr0'

echo "Removable devices detected:"
echo "$removable_devices"

# Step 5: Ask the user to select a device
echo "Please select the device you want to format (e.g., sdb, sdc):"
read device

# Ensure that the user input is valid
if [[ -z "$device" || ! -b "/dev/$device" ]]; then
    echo "Invalid device selected or device does not exist!"
    exit 1
fi

# Step 6: Confirm the formatting operation
echo "You are about to format /dev/$device. This will erase all data on the drive."
read -p "Are you sure you want to continue? (y/n): " confirmation

if [[ "$confirmation" != "y" && "$confirmation" != "Y" ]]; then
    echo "Operation canceled."
    exit 0
fi

# Step 7: Format the USB drive
echo "Formatting /dev/$device..."
# You can use mkfs or any other method to format the drive, here it's assumed to be ext4 for simplicity
sudo mkfs.ext4 -F /dev/$device

# Step 8: Write the ISO image to the USB drive
echo "Writing the aion.iso to /dev/$device..."
# Be very careful with dd, as it can overwrite any drive without warning.
sudo dd if=aion.iso of=/dev/$device bs=4M status=progress && sync

echo "USB drive is now bootable."

# End of script
