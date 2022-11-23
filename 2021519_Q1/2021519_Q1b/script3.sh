#!/bin/bash
echo "Starting Compilation Part 3"
cd ~
cd stock_kernel_3/stock_kernel/linux-5.19.8
sudo make -j$(nproc)
sudo make modules
sudo make modules_install
sudo make install
sudo make bzImage
sudo cp -v arch/x86/boot/bzImage /boot/vmlinuz-linux519
sudo mkinitcpio -p linux519
sudo cp System.map /boot/System.map-linux519
sudo ln -sf /boot/System.map-linux519 /boot/System.map