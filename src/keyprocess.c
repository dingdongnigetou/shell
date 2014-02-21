/*
 * src/keyprocess.c
 *
 * (C) 2014 HuangJingDong
 *
 * deal with some keys
 *
 */

#include "keyprocess.h"

void keyprocess(char ch)
{
	switch(ch)
	{
	case 72:fprintf(stdout,"up\n");
		break;
	case 80:fprintf(stdout,"down\n");
		break;
	case 75:fprintf(stdout, "left\n");
		break;
	case 77:fprintf(stdout, "right\n");
		break;
	default:
		break;
	}
}

