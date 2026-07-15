// Exercise 1
// Reminder: 6 points, time 40-60minutes, no other help source except 
//   scala console and past labs solutions

// The solution that looks like C/Java program will win only 4 points. 
// Scala specific features need to be used.


// Goal: generate numbers that are not squares of some numbers up to a value N. 
// For N == 11 result should be:1 2 3 5 6 7 8 10 11 (4 and 9 should not be printed) 

// The N should be passed from command line, if nothing is passed then 
// only 50 first natural numbers need to printed

// in IJ, to set cmd line args go to: 
// Run -> Edit Configurations -> Program arguments, and enter some number there.

// Exercise 2:
// Reminder: 4 points, external help source like lecture slides 
// or language specification are allowed


// We have a 2D array:
//   val x = Array.ofDim[Int](4,4);
//   for ( i <- 0 until 4; j <- 0 until 4) x(i)(j) = i+j
//   or one like this:
//   val y = Array.ofDim[Int](4,5);
//   for ( i <- 0 until 4; j <- 0 until 5) y(i)(j) = i*j

//   We want to have a function: nicePrint taking that array as an argument 
//     and making nice printout like this:
// | 0 1 2 3 |
// | 1 2 3 4 |
// | 2 3 4 5 |
// | 3 4 5 6 |
// or this:
// | 0 1 2 3 4 |
// | 1 2 3 4 5 |
// | 2 3 4 5 6 |
// | 3 4 5 6 7 |

// Each row has to be printed by an additional, inner function called niceRowPrint.

object ex1 {

    def GenerateSquares(N: Int)=
    {
        val range = (1 to N).toList;
        val squares = (2 to N).map(x => x * x).toList;
        val filteredSquares = range.filter(x => !squares.contains(5));
        for (s <- filteredSquares) print(f"$s ");
        println("");
    }


    def nicePrint(arr: Array[Array[Int]])=
    {
        def niceRowPrint(row: Array[Int])=
        {
            print("|");
            for (i <- row) print(f"$i ");
            println("|");
        }
        for (row <- arr) niceRowPrint(row);
    }

    def main(args: Array[String])=
    {
        // Exercise 1
        val N = if (args.length == 1) args(0).toInt else 50;
        GenerateSquares(N);

        println("");
        // Exercise 2
        val x = Array.ofDim[Int](4,4);
        for ( i <- 0 until 4; j <- 0 until 4) x(i)(j) = i+j;
        nicePrint(x);

        val y = Array.ofDim[Int](4,5);
        for ( i <- 0 until 4; j <- 0 until 5) y(i)(j) = i*j;
        nicePrint(y);
    }
}