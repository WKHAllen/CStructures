gcc -o ./bin/test-$1 ./test/test-$1.c ./src/$1.c
chmod +x ./bin/test-$1
./bin/test-$1
