#include "COG_Util.h"

//========================================================================
//
//  Implementation of RNDTraverse
//
//========================================================================
int RndTraverse::primeArray[] = {
	2, 3, 5, 7, 
	11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 
	53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 
	101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 
	151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 
	211, 223, 227, 229, 233, 239, 241,
	251, 257, 263, 269, 271, 277, 281, 283, 293, 
	307, 311, 313, 317, 331, 337, 347, 349, 
	353, 359, 367, 373, 379, 383, 389, 397, 
	401, 409, 419, 421, 431, 433, 439, 443, 449, 
	457, 461, 463, 467, 479, 487, 491, 499, 
	503, 509, 521, 523, 541, 547, 
	557, 563, 569, 571, 577, 587, 593, 599, 
	601, 607, 613, 617, 619, 631, 641, 643, 647, 
	653, 659, 661, 673, 677, 683, 691, 
	701, 709, 719, 727, 733, 739, 743, 
	751, 757, 761, 769, 773, 787, 797, 
	809, 811, 821, 823, 827, 829, 839, 
	853, 857, 859, 863, 877, 881, 883, 887, 
	907, 911, 919, 929, 937, 941, 947, 
	953, 967, 971, 977, 983, 991, 997, 

	1009, 1051, 1103, 1151, 1201, 1259, 1301, 1361, 1409, 1451, 
	1511, 1553, 1601, 1657, 1709, 1753, 1801, 1861, 1901, 1951, 
	2003, 2053, 2111, 2113, 2153, 2203, 2251, 
	2309, 2351, 2411, 2459, 2503, 2551, 2557, 
	2609, 2657, 2707, 2753, 2767, 2801, 2851, 2903, 2953,
	3001, 3061, 3109, 3163, 3203, 3251, 3301, 3359, 3407, 3457, 
	3511, 3557, 3607, 3659, 3701, 3761, 3803, 3851, 3907, 3967, 
	4001, 4051, 4111, 4153, 4201, 4253, 4327, 4357, 4409, 4451, 
	4507, 4561, 4603, 4651, 4703, 4751, 4801, 4861, 4903, 4951, 

	5003, 5101, 5209, 5303, 5407, 5501, 5623, 5701, 5801, 5903, 
	6007, 6101, 6211, 6301, 6421, 6521, 6607, 6701, 6803, 6907, 
	7001, 7103, 7207, 7307, 7411, 7507, 7603, 7703, 7817, 7901, 
	8009, 8101, 8209, 8311, 8419, 8501, 8609, 8707, 8803, 8923, 
	9001, 9103, 9203, 9311, 9403, 9511, 9601, 9719, 9803, 9901, 

	10007, 10501, 11003, 11503, 12007, 12503, 13001, 13513, 14009, 14503, 
	15013, 15511, 16033, 16519, 17011, 17509, 18013, 18503, 19001, 19501, 
	20011, 20507, 21001, 21503, 22003, 22501, 23003, 23509, 24001, 24509


};


RndTraverse::RndTraverse(int elements)
{
	m_maxElements = elements;
	if (elements <= 0) throw "set can't have size 0 or less";

	m_pCurrentPrime = primeArray;

	while(*m_pCurrentPrime < elements) m_pCurrentPrime++;

	generateSkip();


}

int RndTraverse::getNext()
{
	if (done()) return -1;

	int next = m_currentPosition;

	while(1)
	{
		next += m_skip;
		next %= *m_pCurrentPrime;
		if (next < m_maxElements)
		{
			m_currentPosition = next;
			m_searches++;
			return next;
		}
	}

	return -2;
}


void RndTraverse::generateSkip()
{
	int a = rand()%13 + 1, b = rand()%7 + 1, c = rand()%5 + 1;
	m_skip = m_maxElements*m_maxElements*a + m_maxElements*b + c;
	m_skip &= ~0xc0000000;

	if (!(m_skip%*m_pCurrentPrime)) m_skip++;
}




//========================================================================
//
//  Implementation of COGRandom
//
//========================================================================
COGRandom::COGRandom(void)
{
	rseed = 1;
	// safe0 start
	rseed_sp = 0;
	mti=CMATH_N+1;
	// safe0 end
}	
	
// Returns a number from 0 to n (excluding n)
unsigned int COGRandom::Random( unsigned int n )
{
    unsigned long y;
    static unsigned long mag01[2]={0x0, CMATH_MATRIX_A};

	if(n==0)
		return(0);

    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti >= CMATH_N) { /* generate N words at one time */
        int kk;

        if (mti == CMATH_N+1)   /* if sgenrand() has not been called, */
            SetRandomSeed(4357); /* a default initial seed is used   */

        for (kk=0;kk<CMATH_N-CMATH_M;kk++) {
            y = (mt[kk]&CMATH_UPPER_MASK)|(mt[kk+1]&CMATH_LOWER_MASK);
            mt[kk] = mt[kk+CMATH_M] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        for (;kk<CMATH_N-1;kk++) {
            y = (mt[kk]&CMATH_UPPER_MASK)|(mt[kk+1]&CMATH_LOWER_MASK);
            mt[kk] = mt[kk+(CMATH_M-CMATH_N)] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        y = (mt[CMATH_N-1]&CMATH_UPPER_MASK)|(mt[0]&CMATH_LOWER_MASK);
        mt[CMATH_N-1] = mt[CMATH_M-1] ^ (y >> 1) ^ mag01[y & 0x1];

        mti = 0;
    }
  
    y = mt[mti++];
    y ^= CMATH_TEMPERING_SHIFT_U(y);
    y ^= CMATH_TEMPERING_SHIFT_S(y) & CMATH_TEMPERING_MASK_B;
    y ^= CMATH_TEMPERING_SHIFT_T(y) & CMATH_TEMPERING_MASK_C;
    y ^= CMATH_TEMPERING_SHIFT_L(y);

	// ET - old engine added one to the result.
	// We almost NEVER wanted to use this function
	// like this.  So, removed the +1 to return a 
	// range from 0 to n (not including n).
    return (y%n);
}


float COGRandom::Random( )
{
	float r = (float)Random(INT_MAX);
	float divisor = (float)INT_MAX;
	return (r / divisor);
}



void COGRandom::SetRandomSeed(unsigned int n)
{
	/* setting initial seeds to mt[N] using         */
	/* the generator Line 25 of Table 1 in          */
	/* [KNUTH 1981, The Art of Computer Programming */
	/*    Vol. 2 (2nd Ed.), pp102]                  */
	mt[0]= n & 0xffffffff;
	for (mti=1; mti<CMATH_N; mti++)
		mt[mti] = (69069 * mt[mti-1]) & 0xffffffff;

	rseed = n;
}

unsigned int COGRandom::GetRandomSeed(void)
{
	return(rseed);
}

void COGRandom::Randomize(void)
{
	SetRandomSeed((unsigned int)time(NULL));
}




