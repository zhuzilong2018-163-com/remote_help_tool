#include <stdio.h>
#include "server.h"
#include "logPrint.h"

int main(int argc, char *argv[])
{
	int a=3;
	SERVE_DEBUG("aaa:%d",a);
	return 0;
}
