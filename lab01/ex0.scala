/*
 
 1) Write a program that generates a sequence of integers given the command line arguments.
    eg. > scala s0 12 
    should output numbers: 0 1 2 3 4 5 6 7 8 9 10 11
    > scala s0 12 16
    should output 12 13 14 15

 You need to read number of parameters passed to the scala program. Once you know how many of them there is they need to be converted to an integer and used to generate the range.

  2) Write a program that uses  List of tuples to store the inventory (like in a flower shop):
   eg. - to denote the name of the flower  and how many of there is in the stock
   "rose while star", 12 
   "sunflower", 3
   "orchid", 7
   "carnation white", 30
   "carnation red", 25

   Add code to print it nicely (e.g.: fixed size fields like below).
 rose while star           12
 sunflower                 3
 orchid                    7
 carnation white           30
 carnation red             25

   Write a generator that filters all flowers for which we need to set order (say have less than 10) and print resulting list again.
   
 If time permits think of wrapping the printing code in a function.

 */


object ex0 {
    
    def FlowerFilter(flowers : List[Tuple2[String, Int]])= 
    {
        val filteredFlowers = flowers.filter(_._2 >= 10);
        for (filteredFlower <- filteredFlowers)
            yield filteredFlower
    }

    def PrintFlowers(flowers : List[Tuple2[String, Int]])=
    {
        val fixedSize = 30;
        println("-" * (fixedSize / 2) + "FLOWERS" + "-" * (fixedSize / 2));
        for (flower <- flowers)
        {
            val flowerFormat = " " * (fixedSize - flower._1.size);
            println(flower._1 + flowerFormat + flower._2.toString);
        }
    }

    def main(args: Array[String])=
    {
        val start: Int = if (args.length == 1) 0 else args(0).toInt;
        val end: Int = if (args.length == 1) args(0).toInt else args(1).toInt;

        for (i <- start until end)
        {
            print(s"$i ");
        }
        println("");


        val flowers = List(
            ("rose while star", 12),
            ("sunflower", 3),
            ("orchid", 7),
            ("carnation white", 30),
            ("carnation red", 25)
        );

        PrintFlowers(flowers)

        val soledFlowers = FlowerFilter(flowers);
        PrintFlowers(soledFlowers)
    }

}
