#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf(1, "helloname_test <name>\n");
        exit();
    }

    hello_name(argv[1]);
    exit();
}
