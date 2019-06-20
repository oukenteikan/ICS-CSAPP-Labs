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
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

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
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
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
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 8.0.0.  Version 8.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2014, plus Amendment 1 (published
   2015-05-15).  */
/* We do not support C11 <threads.h>.  */
/*
 * changeHigh : if low 16-bit of x == y, then let high 16-bit of z = x, otherwise let
 *     high 16-bit of z = y. return z.
 *   Example: changeHigh(0xaaaabbbb, 0xbbbbaaaa, 0xcccccccc) = 0xbbbbcccc,
 *   changeHigh(0xaaaabbbb, 0xddddbbbb, 0xcccccccc) = 0xaaaacccc
 *   Legal ops: ! ~ & ^ | << >>
 *   Max ops: 24
 *   Rating: 1
 */
int changeHigh(int x, int y, int z) {
  int p1;
  int p2;
  int p3;
  int p4;
  int p5 = 0xff;
  p5 = p5|(p5<<8);
  p1 = !((x^y) << 16);
  p2 = p1 << 31;
  p3 = (!p1) << 31;
  p3 = p3 >> 15;
  p2 = p2 >> 15;
  //printf("%02x %02x %02x\n", p1, p2, p3);
  p2 = x&p2;
  p3 = y&p3;
  p4 = p5&z;
  z = p4 | p2 | p3;
  return z;
}
/* 
 * newOp - define a new bit-wise opertor PKU : 1PKU1 = 1, 1PKU0 = 1, 0PKU1 = 0, 0PKU0 = 1
 *   input int x, y return xPKUy(bit-wise)
 *   Legal ops: ! ~ & ^ |
 *   Max ops: 6
 *   Rating: 1
 */
int newOp(int x, int y) {
  int z;
  z = (~(x^y))|x;
  return z;
}
/* 
 * onlyOne - input x, y return 1 if only one bit of the two numbers is different, return 0 otherwise
 *   Examples onlyOne(12, 14) = 1, onlyOne(12, 15) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int onlyOne(int x, int y) {
  int p1;
  int p2;
  p2 = x^y;
  p1 = ~p2;
  p2 = !!p2;
  p1 = !(~(p1|(p1+1)));
  p1 = p1 & p2;
  return p1;
}
/*
 * truncAvg - Compute the average of the two numbers rounded toward 0
 *          without causing overflow
 *   Example: truncAvg(1, 10) = 5,
 *            truncAvg(-3, 6) = 1,
 *            truncAvg(-3, -4) = -3,
 *            truncAvg(0x7fffffff, 0x7fffffff) = 0x7fffffff
 *   Legal ops: ! ~ & | ^ + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int truncAvg(int x, int y) {
    int p1;
    int p2;
    p1 = (x>>1) + (y>>1);
    p2 = p1 >> 31;
    p1 += (p2|x)&(p2|y)&(x|y)&1;
    return p1;
}
/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 2
 */
int absVal(int x) {
  int p1;
  int p2;
  int p3;
  p2 = x>>31;
  p1 = (~x)+1;
  p3 = (~p2)&x;
  p3 += p3;
  p1 += p3;
  return p1;
}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 2
 */
int subOK(int x, int y) {
  int p1;
  int p2;
  int p3;
  p2 = (~y) + 1;
  p1 = x + p2;
  p3 = ((x^p1)&(y^x))>>31;
  return !p3;
}
/*
 * fullAdd - 4-bits add using bit-wise operations only.
 *   (0 <= x, y < 16) 
 *   Example: fullAdd(12, 7) = 3,
 *            fullAdd(7, 8) = 15,
 *   Legal ops: ~ | ^ & << >>
 *   Max ops: 30
 *   Rating: 2
 */
int fullAdd(int x, int y) {
    int p1;
    int p2;
    int p3;
    int p4;
    int p5;
    int p6;
    int p7;
    p1 = x ^ y;
    p2 = (x & y) << 1;
    p3 = p1 ^ p2;
    p4 = (p1 & p2) << 1;
    p5 = p3 ^ p4;
    p6 = (p3 & p4) << 1;
    p7 = p5 ^ p6;
    p7 = p7 & 0x0000000f;
    return p7;
}
/* 
 * theMax - the same as max(x, y) 
 *   Example: max(4,5) = 5, max(6,3) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 28
 *   Rating: 3
 */
int theMax(int x, int y) {
  int p1, p2, p3, p4, p5, p6, p7;
  p1 = ~y;
  p2 = p1 + 1;
  p3 = (x + p2) & (x ^ p1);
  p4 = x & p1;
  p5 = p3 | p4;
  p5 = (p5 >> 31) & 1;
  p6 = ~p5 + 1;
  p7 = (x&(~p6))|(y&p6);
  return p7;
}
/*
 * palindrome - return 1 if x is palindrome in binary form,
 *   return 0 otherwise
 *   A number is palindrome if it is the same when reversed
 *   YOU MAY USE BIG CONST IN THIS PROBLEM, LIKE 0xFFFF0000
 *   YOU MAY USE BIG CONST IN THIS PROBLEM, LIKE 0xFFFF0000
 *   YOU MAY USE BIG CONST IN THIS PROBLEM, LIKE 0xFFFF0000
 *   Example: palindrome(0xff0000ff) = 1,
 *            palindrome(0xff00ff00) = 0
 *   Legal ops: ~ ! | ^ & << >> +
 *   Max ops: 40
 *   Rating: 4
 */
int palindrome(int x) {
    int p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p16;
    int y;
    y = x>>16;
    y = y&0x0000ffff;
    x = x&0x0000ffff;
    p1 = y&0xaaaaaaaa;
    p1 = p1>>1; 
    p2 = y&0x55555555;
    p2 = p2<<1;
    p3 = p1 | p2;
    p4 = p3&0xcccccccc;
    p4 = p4>>2;
    p5 = p3&0x33333333;
    p5 = p5<<2;
    p6 = p4 | p5;
    p7 = p6&0xf0f0f0f0;
    p7 = p7>>4;
    p8 = p6&0x0f0f0f0f;
    p8 = p8<<4;
    p9 = p7 | p8;
    p10 = p9&0xff00ff00;
    p10 = p10>>8;
    p11 = p9&0x00ff00ff;
    p11 = p11<<8;
    p12 = p10 | p11;
    p16 = x^p12;
    return (!p16);
}
/*
 * distance - calculate how many bits are different between x and y
 *   Example: distance(0xabcdabcd, 0xabcddcba) = 12,
 *            distance(0x0000ffff, 0xffff0000) = 32,
 *   Legal ops: ~ ! | ^ & << >> +
 *   Max ops: 40
 *   Rating: 4
 */
int distance(int x, int y) {
  int p1, p2, p3, p4, p5, p6;
  int t1=0x55, t2=0x33, t3=0x0f, t4=0xff, t5=0xff;
  p1 = x^y;
  t1 = (t1<<16)|t1;
  t1 = (t1<<8)|t1;
  t2 = (t2<<16)|t2;
  t2 = (t2<<8)|t2;
  t3 = (t3<<16)|t3;
  t3 = (t3<<8)|t3;
  t4 = (t4<<16)|t4;
  t5 = (t5<<8)|t5;
  p2 = ((p1>>1)&t1) + ((p1&t1));
  p3 = ((p2>>2)&t2) + ((p2&t2));
  p4 = ((p3>>4)&t3) + ((p3&t3));
  p5 = ((p4>>8)&t4) + ((p4&t4));
  p6 = ((p5>>16)&t5) + ((p5&t5));
  return p6;
}
/*
 * divSix - calculate x / 6 without using /
 *   Example: divSix(6) = 1,
 *            divSix(2147483647) = 357913941,
 *   Legal ops: ~ ! | ^ & << >> +
 *   Max ops: 40
 *   Rating: 4
 */
int divSix(int x) {
    int p2, p3, p4, p5;
    x += (x>>31) & 5;
    p2 = (x >> 1) + (x >> 3);
    p2 += (p2 >> 4);
    p2 += (p2 >> 8);
    p2 += (p2 >> 16);
    p2 = p2 >> 2;
    p5 = (p2<<1) + (p2<<2);
    p5 = (~p5)+1;
    p3 = x + p5;
    p4 = p2 + ((p3+2) >> 3);
    return p4;
}
/*
 * modThree - calculate x mod 3 without using %.
	 *    Example: modThree(12) = 0,
 *            modThree(2147483647) = 1,
 *            modThree(-8) = -2,
 *   Legal ops: ~ ! | ^ & << >> +
 *   Max ops: 60
 *   Rating: 4
 */
int modThree(int x) {
    int p1, p2;
    int t1;
    int t2 = 0x33;
    int t3 = 0x07;
    int t4 = 0xf;
    int t5, t6;
    t1 = ~0;
    t5 = t1;
    t1 = t1^0x2;
    t6 = t5^(1<<31);

    t2 = (t2<<16)|t2;
    t2 = (t2<<8)|t2;
    
    t3 = (t3<<16)|t3;
    t3 = (t3<<8)|t3;

    t4 = (t4<<16)|t4;

    p1 = x&t6;
    p2 = (x>>31)&1;
    p1 += p2;
   
    p1 = ((p1>>2)&t2) + (p1&t2);
    p1 = ((p1>>4)&t3) + (p1&t3);
    p1 = ((p1>>8)&t4) + (p1&t4);
    p1 = ((p1>>16)&0x1f) + (p1&0x1f);
    p1 = ((p1>>2)&t2) + (p1&t2);
    p1 = ((p1>>4)) + (p1&t3);
    p1 = ((p1>>2)) + (p1&t2);

    //p1 += (-3)&(~(!p2));
    p1 += ((p1+1)>>2)&0x00000001;
    p1 = p1&0x00000003;
    p1 += (t1)&((!p2)+(t5))&((!p1)+(t5));
    return p1;
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
    Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 3
 */
int float_f2i(unsigned uf) {
  unsigned p1, p2;
  int p3;
  p1 = (uf>>23)&0xff;
  p2 = uf>>31;
  p3 = uf&0x007fffff;
  if (p1 < 127) return 0;
  p1 -= 127;
  if (p1 >= 31) return 0x80000000u;
  p3 = ((p3<<7)+0x40000000)>>(30-p1);
  if (p2) return -p3;
  else return p3;
}
/* 
 * float_half - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 3
 */
unsigned float_half(unsigned uf) {
  unsigned p1, p2;
  p1 = uf&0x7f800000;
  p2 = uf&0x80000000;
  if (p1 == 0x7f800000) return uf;
  if (p1 <= 0x00800000) return (((uf^p2)+((uf&0x00000003)==0x00000003))>>1)|p2;
  return uf-0x00800000;
}
/* 
 * float_construct - Return bit-level equivalent of expression float(x*2^y),
 *   you should treat the input as integers: if x = 2, y = 3, you should return a float value of 16  
 *   we ensure the constructed number can be represented in float: X[-65535, 65535], y[-160, 60]
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 90
 *   Rating: 4
 */
unsigned float_construct(int x, int y) {
  unsigned p1, p2, p3, p7, p8, p9, p10;
  int p4 = -1, p5, p6;
  if (!x) return 0;
  p1 = x&0x80000000;
  if (p1) p2 = (~x) + 1;
  else p2 = x;
  p3 = p2;
  while (p3) {
    p3 = p3 >> 1;
    p4 += 1;
  }
  p5 = p4 + 127 + y;
  if (p5 > 0)
    p6 = 31 - p4;
  else
  {  p6 = 30 - p4 + p5;
     p5 = 0;
  }
  if (p6 >= 0) {
  p7 = p2 << p6;
  p8 = p7 & 0x000000ff;
  p7 = (p7 >> 8) & 0x007fffff;

  p9 = p8&0x00000080;
  p10 = p8&0x0000007f;
	}
  else
  {
	  p7 = p2 >> (8-p6);
	  p8 = p2&((1<<(8-p6))-1);
	  p9 = p8&(1<<(8-p6-1));
	  p10 = p8&((1<<(8-p6-1))-1);
  }
  p7 += ((p9&&p10) || (p9&&(p7&0x00000001)));
 // printf("%02x %02x %02x %d %d %d %02x %02x %02x %02x \n", p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
  return p1 | (p5<<23) | p7;
}
