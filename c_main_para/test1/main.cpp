#include <stdio.h>


void main(int argc, char **argv)
{
    printf("number of input paras: %d\n", argc);
    printf("the exe path is %s\n", argv[0]);

    printf("the 1st para is %s\n", argv[1]);
    printf("the 2st para is %s\n", argv[2]);
}

/*

PS C : \Users\hongfei\Documents\Visual Studio 2015\Projects\test1\Debug> .\test1.exe "ok" OK2
number of input paras : 3
the exe path is C : \Users\hongfei\Documents\Visual Studio 2015\Projects\test1\Debug\test1.exe
the 1st para is ok
the 2st para is OK2
PS C : \Users\hongfei\Documents\Visual Studio 2015\Projects\test1\Debug> .\test1.exe "ok"
number of input paras : 2
the exe path is C : \Users\hongfei\Documents\Visual Studio 2015\Projects\test1\Debug\test1.exe
the 1st para is ok
the 2st para is(null)
PS C : \Users\hongfei\Documents\Visual Studio 2015\Projects\test1\Debug>

*/