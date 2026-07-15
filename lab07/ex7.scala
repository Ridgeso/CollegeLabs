import scala.util.Random

object ex7 {
    // @scala.annotation.tailrec

    def GetRandomRange(start: Int, end: Int): Int = new Random().nextInt(end - start) + start

    def main(args: Array[String]): Unit = {

        val rand = new Random();

        val randomSeq: Seq[Int] = Seq(GetRandomRange(0, 20), GetRandomRange(0, 20), GetRandomRange(0, 20)) 

        println("Sequence " + randomSeq)
        println()


        // Exercieses
        println(randomSeq.sum) // sum
        
        // avrage
        val avrage = randomSeq.tail.fold(randomSeq(0))({ case (s, l) => s + l / 2 })
        println(avrage)
        println(randomSeq.sum / randomSeq.length)

        println(randomSeq.take(10)) // w/o first 10
        println(randomSeq.takeWhile(_ > 10)) // grater than 10


        println(randomSeq.map(el => (el - randomSeq.sum / randomSeq.length) / randomSeq.length).sum) // variance

        println(randomSeq.groupBy(el => el < randomSeq.sum / randomSeq.length)) //above and below

        println(randomSeq.zip(randomSeq.tail).filter({case (l, r) => l > r}).map({case (l, r) => l})) // grater than next

        // sum of products
        val x: Seq[Int] = Seq(GetRandomRange(0, 20), GetRandomRange(0, 20), GetRandomRange(0, 20)) 
        val y: Seq[Int] = Seq(GetRandomRange(0, 20), GetRandomRange(0, 20), GetRandomRange(0, 20)) 
        println(x.zip(y).map({ case (l, r) => l * r }).sum)
    }
}