# bin/bash
gcc -I/usr/include/postgresql  -L/usr/local/pgsql/lib "$1.c" -o program -lpq



# ecpg "$1.pcg"
# gcc -g -I/usr/include/postgresql "$1.c" -o program -lecpg



./program
