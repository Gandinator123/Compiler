#!/bin/bash

# Try to find a portable way of getting rid of
# any stray carriage returns
if which dos2unix ; then
    DOS2UNIX="dos2unix"
elif which fromdos ; then
    DOS2UNIX="fromdos"
else
    >&2 echo "warning: dos2unix is not installed."
    # This should work on Linux and MacOS, it matches all the carriage returns with sed and removes
    # them.  `tr` is used instead of `sed` because some versions of `sed` don't recognize the
    # carriage return symbol.  Something similar could be implemented with `sed` if necessary or
    # worst case it could be disabled by substituting it with `cat`.  One other thing to note is
    # that there are no quotes around the \r, which is so that it gets converted by bash.
    DOS2UNIX="tr -d \r"
    # DOS2UNIX="sed -e s/\r//g"
    # DOS2UNIX="cat"
fi


echo "=================================================="
echo "clean"
make clean
echo "Building c_compiler"
make bin/c_compiler -B
if [[ "$?" -ne 0 ]]; then
    echo "Build failed.";
fi
echo""
echo "Enter filepath: " 
read filepath
echo $filepath
file=$(basename -s .c $filepath)
echo $file
driverfile="${filepath}_driver"
echo "Running"
bin/c_compiler -S compiler_tests/$filepath.c -o output/$file.s
mips-linux-gnu-gcc -mfp32 -o output/$file.o -c output/$file.s
mips-linux-gnu-gcc -mfp32 -static -o output/$file output/$file.o compiler_tests/$driverfile.c
qemu-mips output/$file
echo "Result: $?"
