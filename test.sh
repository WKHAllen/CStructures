./build.sh
gcc -L./bin -Wl,-rpath=./bin -o bin/test-$1 test/test-$1.c -lcstructures
chmod +x ./bin/test-$1
./bin/test-$1
