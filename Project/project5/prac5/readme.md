#Part 1 - Basic Programs   (4 points)
In this part you'll be familiarise yourself with Hack assembly by writing a basic arithmetic program.

You'll also need to write your own tests. Take a look at the sample test file provided to see how to write your own test cases.


Task 1.1 - Add and Subtract  (4 points)
Write a program in Hack assembly to calculate 

Complete the code in AddSub.asm

 

Inputs:

R1 contains the value for a
R2 contains the value for b
R3 contains the value for c
Outputs:

Write your final answer to R0
 

Test Cases:

Write at least 2 test cases.
A sample test case is provided in AddSub00.tst
Each test case should be in a file named AddSubXX.tst where XX is a number starting at 01.
You should also submit any supporting files such as CMP files.
Your mark for this task may be scaled down for poor/missing testing.



#Part 2 - Conditionals & Loops  (24 points)
In this part you'll be writing more complex programs that involve jumps.

##Task 2.1 - Absolute Value (8 points)
Write a program in Hack assembly to calculate the absolute valueLinks to an external site. of a given number.

Complete the code in Abs.asm


Inputs:

R1 contains the number
Outputs:

Write your final answer to R0
 
Test Cases:

Write at least 3 test cases.
A sample test case is provided in Abs00.tst
Each test case should be in a file named AbsXX.tst where XX is a number starting at 01.
You should also submit any supporting files such as CMP files.
Your mark for this task may be scaled down for poor/missing testing.

##Task 2.2 - Multiply (16 points)
Write a program in Hack assembly to multiply 2 numbers.

Complete the code in Mult.asm

Inputs:

R1 contains the first number
R2 contains the second number
Outputs:

Write your final answer to R0
 
Test Cases:

Write at least 5 test cases.
A sample test case is provided in Mult00.tst
Each test case should be in a file named MultXX.tst where XX is a number starting at 01.
You should also submit any supporting files such as CMP files.
Your mark for this task may be scaled down for poor/missing testing.

#Part 3 - Arrays  (28 points)
It's time to apply your knowledge of Memory to work with array data structures.

Your solutions to this part will also be evaluated on efficiency; number of instructions used, with bonus points available.

##Task 3.1 - Array Smallest (12 points)
Write a program in Hack assembly to calculate the minimal value in a given array.

Complete the code in ArrMin.asm

 

Inputs:

R1 contains the RAM address of the first element in the array
R2 contains the length of the array
Outputs:

Write your final answer to R0
 

Test Cases:

Write at least 5 test cases.
A sample test case is provided in ArrMin00.tst
Each test case should be in a file named ArrMinXX.tst where XX is a number starting at 01.
You should also submit any supporting files such as CMP files.
Your mark for this task may be scaled down for poor/missing testing.
Efficiency:

Your code runs, but how efficient is it? Your code will be tested on a large data set to measure its performance compared to a basic solution.
You will gain/lose as much as 2 points depending on the efficiency of your code.
Make sure you have a working solution before trying to optimise!

##Task 3.2 - Array Sort (16 points)
Write a program in Hack assembly to sort a given array in-place in ascending order (smallest to largest).

You may implement any sorting algorithm but should aim for a complexity of O(n2) or better.

Complete the code in ArrSort.asm

Inputs:

R1 contains the RAM address of the first element in the array
R2 contains the length of the array
Outputs:

Write your True (-1) to R0 when your program finishes.
The correctly sorted array should replace the original array in its location.
 
Test Cases:

Write at least 5 test cases.
A sample test case is provided in ArrSort00.tst
Each test case should be in a file named ArrSortXX.tst where XX is a number starting at 01.
You should also submit any supporting files such as CMP files.
Your mark for this task may be scaled down for poor/missing testing.
Efficiency:

Your code runs, but how efficient is it? Your code will be tested on a large data set to measure its performance compared to a basic solution.
You will gain/lose as much as 3 points depending on the efficiency of your code.
Make sure you have a working solution before trying to optimise!
