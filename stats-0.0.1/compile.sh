# $SRC: source files
# $CFLAGS: compiler options
# $LDFLAGS: linking options
# $CC: compiler

CC="gcc"
CFLAGS="-std=c11 -O2 -Winline -g -Wall -Werror -Wextra -Wconversion"
SRC="misc.c file.c table.c stats.c main.c"
LDFLAGS="-lm"

$CC $CFLAGS $SRC -o stats $LDFLAGS
