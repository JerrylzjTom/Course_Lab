/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  return ~(~x & ~y) & ~(x & y);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  /*Convert unsigned int to two's complement int*/
  return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
    int y = x + 1;
    x = x + y;  // x now holds the result of x + (x + 1) which should be 0xFFFFFFFF if x was 0x7FFFFFFF
    x = ~x;     // Invert bits, so 0xFFFFFFFF becomes 0x00000000
    return !x & !!(y);  // Return 1 if x is 0 and y is not 0,because -1 also be 0xFFFFFFFF.
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  int mask = 0xAAAAAAAA; // 1010101010...
  return !((x & mask) ^ mask);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
    // 0x30 = 110000
    // 0x39 = 111001
    int a = (x >> 4) ^ 0x3; //If this returns 0, then we know x is valid. Otherwise, it is not. 
    int b = ((x >> 3) & 1); //If the 8's place is 1, this returns 1. 
    int c = !((x >> 1) & 0x3); //If the returns 0, either the 2's or the 3's place is 1. So this isn't valid if b is als 1. 

    return(!a & !(b & !c));
}

/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int x_bool = !!x;
  int mask = ~x_bool + 1; //! The bitwise NOT (~) of 1 is 0xFFFFFFFE (all bits set to 1 except the least significant bit). 

  return (y & mask) | (z & ~mask);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    // Extract sign bits: 1 if negative, 0 if positive
    int sign_x = x >> 31 & 1;
    int sign_y = y >> 31 & 1;

    int differentSigns = sign_x & !sign_y;

    // Calculate whether `x` and `y` have the same sign 
    int sameSigns = !(sign_x ^ sign_y);

    int diffSign = ((y + (~x + 1)) >> 31 & 1); //! for two's complement integer, -x = ~x + 1 

    return differentSigns | (sameSigns & !diffSign);
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
    // Compute -x
    int neg_x = ~x + 1;

    // Combine x and -x
    int combined = x | neg_x;

    // Shift the sign bit to the least significant bit.if x is no-zero, then the sign bit is -1, otherwise 0.
    int sign_bit = combined >> 31;

    // Add 1 to the negated sign bit to get the logical negation result
    return (sign_bit + 1) & 1;
}

/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
    int sign = x >> 31;
    // If x is negative, we use ~x; if x is positive, we use x itself
    x = (sign & ~x) | (~sign & x);

    //! Use binary search method to find the position of the highest set bit
    int b16, b8, b4, b2, b1, b0;
    b16 = !!(x >> 16) << 4; 
    x >>= b16;              
    b8 = !!(x >> 8) << 3;   
    x >>= b8;               
    b4 = !!(x >> 4) << 2;  
    x >>= b4;               
    b2 = !!(x >> 2) << 1;   
    x >>= b2;               
    b1 = !!(x >> 1);        
    x >>= b1;              
    b0 = x;                

    // Sum up the bit shifts and add 1 for the sign bit
    return b16 + b8 + b4 + b2 + b1 + b0 + 1;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf & 0x80000000;   // Extract sign bit
    unsigned exponent = uf & 0x7F800000; // Extract exponent bits
    unsigned fraction = uf & 0x007FFFFF; // Extract fraction bits

    // Special cases: NaN or infinity
    if (exponent == 0x7F800000) {
        return uf; // NaN or infinity, return uf
    }

    // Denormalized number
    if (exponent == 0) {
        fraction <<= 1; // Shift fraction left by 1
    } else {
        exponent += 0x00800000; // Increment exponent to multiply by 2
        if (exponent >= 0x7F800000) {
            // Handle overflow: set to infinity
            exponent = 0x7F800000;
            fraction = 0;
        }
    }

    return sign | exponent | fraction; // Combine sign, exponent, and fraction
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
    unsigned sign = (uf >> 31) & 1;   // Extract sign bit
    int exp = (uf >> 23) & 0xFF;      // Extract exponent bits
    unsigned frac = uf & 0x007FFFFF;  // Extract fraction bits

    if (exp == 0xFF) {
        // NaN or infinity
        return 0x80000000u;
    }

    int e = exp - 127;  // Calculate the actual exponent

    if (e < 0) {
        // Exponent is negative, result is less than 1
        return 0;
    }

    if (e > 31) {
        // Out of range for int
        return 0x80000000u;
    }

    // Normalized number, add the implicit leading 1
    unsigned mantissa = frac | 0x00800000;

    // Shift the mantissa based on the exponent
    if (e > 23) {
        mantissa <<= (e - 23);
    } else {
        mantissa >>= (23 - e);
    }

    // Apply the sign
    if (sign) {
        mantissa = -mantissa;
    }

    return (int)mantissa;
}

/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    int result;
    int inf_limit = 0x7F800000; 
    int denorm_limit = 0x00800000;  // Minimum denormal in IEEE 754 single precision

    if (x < -126) {
      return 0;
    }
     // Calculate biased exponent
    int biased_exp = x + 127;
    if (biased_exp > 255) {
      return inf_limit;
    }
    
    result = biased_exp << 23;

    return result;
}
