object ex6 {
    // @scala.annotation.tailrec

    def liftToSequence[T, U](funktor: T => U): Iterable[T] => Iterable[U] = {
        def workOnSequence(seq: Iterable[T]): Iterable[U] = seq.map(funktor(_));
        return workOnSequence;
    }

    // def liftToSequence[T, U](funktor: T => U): Iterable[T] => Iterable[U] = (seq: Iterable[T]) => seq.map(funktor);

    def main(args: Array[String]): Unit = {
        // example functions
        // first 3 letters
        def f3(x: String) =  x.substring(0, if (x.size >3) 3 else x.size)

        // count of characters alphabetically before e
        def becount(x: String) =  x.filter(_ < 'e').size

        // // specific string representation
        def str6(x: Double) = f"$x%2.6f".replace(',', '.')

        val l_f3 = liftToSequence(f3)
        val l_becount = liftToSequence(becount)
        val l_str6 = liftToSequence(str6)

        val message = List("Hello", "there", "humans.", "AI", "is", "watching", "you")
        println(l_f3(message).mkString(","))
        println(l_becount(message).mkString(","))
        println(l_str6(Vector[Double](3.14, 7.8778, 1.3434, 6.23)).mkString(" "))
    }
}