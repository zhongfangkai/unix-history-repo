/*
 * Copyright (c) 1988 University of Utah.
 * Copyright (c) 1982, 1986, 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: machdep.c 1.6 88/05/24$
 *
 *	@(#)machdep.c	7.1 (Berkeley) %G%
 */

#include "param.h"

/*
 * Copy bytes within kernel
 */
bcopy(from, to, count)
	register caddr_t from, to;
	register unsigned count;
{
	while (count--)
		*to++ = *from++;
}

bzero(to, count)
	register caddr_t to;
	register unsigned count;
{
	while (count--)
		*to++ = 0;
}

bcmp(s1, s2, len)
	register char *s1, *s2;
	register int len;
{
	while (len--)
		if (*s1++ != *s2++)
			return (1);
	return (0);
}

trap(fp)
 struct frame {
	 int dregs[8];
	 int aregs[8];
	 int whoknows;
	 short sr;
	 int pc;
	 short frame;
 } *fp;
{
	static int intrap = 0;

	if (intrap)
		return;
	intrap = 1;
	romprintf("Got unexpected trap, vector = %x, ps = %x, pc = %x\n",
	       fp->frame&0xFFF, fp->sr, fp->pc);
	romprintf("dregs: %x %x %x %x %x %x %x %x\n",
	       fp->dregs[0], fp->dregs[1], fp->dregs[2], fp->dregs[3], 
	       fp->dregs[4], fp->dregs[5], fp->dregs[6], fp->dregs[7]);
	romprintf("aregs: %x %x %x %x %x %x %x %x\n",
	       fp->aregs[0], fp->aregs[1], fp->aregs[2], fp->aregs[3], 
	       fp->aregs[4], fp->aregs[5], fp->aregs[6], fp->aregs[7]);
	intrap = 0;
}

nodev()
{
	return(0);
}

#ifdef ROMPRF
#define ROWS	46
#define COLS	128

romputchar(c)
 register int c;
{
	static char buf[COLS];
	static int col = 0, row = 0;
	register int i;

	switch (c) {
	case '\0':
		break;
	case '\r':
	case '\n':
		for (i = col; i < COLS-1; i++)
			buf[i] = ' ';
		buf[i] = '\0';
		romout(row, buf);
		col = 0;
		if (++row == ROWS)
			row = 0;
		break;

	case '\t':
		do {
			romputchar(' ');
		} while (col & 7);
		break;

	default:
		buf[col] = c;
		if (++col == COLS-1)
			romputchar('\n');
		break;
	}
}
#endif
