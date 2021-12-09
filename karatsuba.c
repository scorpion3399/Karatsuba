#include <stdlib.h>
#include <stdio.h>

#define mytype_t signed long long

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

static const char err_msg[32] = "Wrong number of arguments!!!\n";

typedef struct hilo {
	mytype_t hi;
	mytype_t lo;
} hilo;

int sz_base2(type_t x)
{
	int sz = 0;
	while (x != 0)
	{
		x = x>>1;
		sz++;
	}
	return sz;
}

hilo split_at(mytype_t num, int m)
{
	hilo temp;
	mytype_t mask = 0xFFFFFFFFFFFFFFFF<<m;
	temp.lo = num & (~mask);
	temp.hi = num>>m;
	return temp;
}

type_t karatsuba(mytype_t num1, mytype_t num2)
{
	if ( num1 < 2 || num2 < 2)
		return num1 * num2; /* fall back to traditional multiplication */

	/* Calculates the size of the numbers. */
	int m = MIN(sz_base2(num1), sz_base2(num2));
	int m2 = m>>1;
	
	/* Split the digit sequences in the middle. */
	hilo H1L1 = split_at(num1, m2);
	hilo H2L2 = split_at(num2, m2);


	/* 3 recursive calls made to numbers approximately half the size. */
	type_t z0 = karatsuba(H1L1.lo, H2L2.lo);
	type_t z1 = karatsuba(H1L1.lo + H1L1.hi, H2L2.lo + H2L2.hi);
	type_t z2 = karatsuba(H1L1.hi, H2L2.hi);

	return (z2<<(m2*2)) + ((z1 - z2 - z0)<<m2) + z0; // alt way, prob faster
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, err_msg);
		return -1;
	}

	mytype_t x = atol(argv[1]);
	mytype_t y = atol(argv[2]);

	long long res = karatsuba(x, y);
	printf("%s x %s = %lld\n", argv[1], argv[2], res);

	return 0;
}
