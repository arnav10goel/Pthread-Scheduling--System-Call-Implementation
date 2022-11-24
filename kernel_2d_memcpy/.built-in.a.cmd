cmd_kernel_2d_memcpy/built-in.a := rm -f kernel_2d_memcpy/built-in.a; echo kernel_2d_memcpy.o | sed -E 's:([^ ]+):kernel_2d_memcpy/\1:g' | xargs ar cDPrST kernel_2d_memcpy/built-in.a
