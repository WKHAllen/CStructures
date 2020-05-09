mkdir bin/obj 2>/dev/null
gcc -c -fpic src/*.c
mv ./*.o bin/obj/
gcc -shared -o bin/libcstructures.so bin/obj/*.o
mkdir bin/include 2>/dev/null
cp src/*.h bin/include/
