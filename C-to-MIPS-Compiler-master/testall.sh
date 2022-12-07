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

echo "=================================================="

PASSED=0
CHECKED=0
for j in compiler_tests/*; do
    prefix="compiler_tests/"
    suffix="/"
    string=${j#$prefix}; #Remove prefix
    string=${string%$suffix}; #Remove suffix
    echo $string
    for i in compiler_tests/$string/*; do
        b=$(basename -s .c ${i});
        echo $b
        if [[ $b == *_driver ]]; then 
            echo ""
        else 
            echo $b
            driverfile="${b}_driver"
            bin/c_compiler -S compiler_tests/$string/$b.c -o output/$b.s
            mips-linux-gnu-gcc -mfp32 -o output/$b.o -c output/$b.s
            mips-linux-gnu-gcc -mfp32 -static -o output/$b output/$b.o compiler_tests/$string/$driverfile.c
            qemu-mips output/$b

            # #getting the qemu output
            GOT_RESULT=$?;

            if [[ "$GOT_RESULT" -eq "0" ]]; then
                PASSED=$(( ${PASSED}+1 ));
                echo "Passed: ${b} test"
            else
                echo "Failed: ${b} test"
            fi

            CHECKED=$(( ${CHECKED}+1 ));
            echo ""

        fi
    done
done
echo "########################################"
echo "Passed ${PASSED} out of ${CHECKED}".
echo ""