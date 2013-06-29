
#include <stdlib.h>
#include <time.h>
#include <functional>
#define _USE_MATH_DEFINES
#include <math.h>
#include <limits>



/* Period parameters */  
#define CMATH_N 624
#define CMATH_M 397
#define CMATH_MATRIX_A 0x9908b0df   /* constant vector a */
#define CMATH_UPPER_MASK 0x80000000 /* most significant w-r bits */
#define CMATH_LOWER_MASK 0x7fffffff /* least significant r bits */

/* Tempering parameters */   
#define CMATH_TEMPERING_MASK_B 0x9d2c5680
#define CMATH_TEMPERING_MASK_C 0xefc60000
#define CMATH_TEMPERING_SHIFT_U(y)  (y >> 11)
#define CMATH_TEMPERING_SHIFT_S(y)  (y << 7)
#define CMATH_TEMPERING_SHIFT_T(y)  (y << 15)
#define CMATH_TEMPERING_SHIFT_L(y)  (y >> 18)

#define RADIANS_TO_DEGREES(x) ((x) * 180.0f / M_PI)
#define DEGREES_TO_RADIANS(x) ((x) * M_PI / 180.0f)

//========================================================================
//
//  Purpose: This class allows the traversing of a range of integers without 
//           traversing the same integer twice.
//
//========================================================================
class RndTraverse
{
	private:
		static int primeArray[]; 
		int m_currentPosition, m_skip, m_searches, *m_pCurrentPrime, m_maxElements;
		void generateSkip();
	public:
		RndTraverse(int elements); //Define the range to be traversed, it ranges between [0-elements)
		int getNext(); //Gets the next randomly generated integer in the range
		bool done(){return m_searches == m_maxElements;}//Whether all integers have been traversed
		void restart(){m_currentPosition=0; m_searches = 0;generateSkip();} //Start all over

};


//========================================================================
//
//  Purpose: Random number generator
//
//========================================================================
class COGRandom
{
private:
	// DATA
	unsigned int		rseed;
	unsigned int		rseed_sp;
	unsigned long mt[CMATH_N]; /* the array for the state vector  */
	int mti; /* mti==N+1 means mt[N] is not initialized */

	// FUNCTIONS
public:
	COGRandom(void);	

	unsigned int	Random( unsigned int n ); //Generate an integer in the range [0, n)
	float			Random( ); // generate a float in the range [0-1)
	void			SetRandomSeed(unsigned int n); //sets a custom seed
	unsigned int	GetRandomSeed(void); // returns the current seed
	void			Randomize(void); //Randomize the seed
};