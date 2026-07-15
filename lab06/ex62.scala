object ex62 {

    def main(args: Array[String]): Unit = {
        val autors = List("Agnieszka Osiecka", "Sławomir Mrozek", "Joachim Lelevel", "Maria Kownacka", "Maria Rodziewiczowna",
                     "Ewa Stadtmuller", "Julian Tuwim", "Tadeusz Boy-Zelenski", "Stefan Zeromski", "Joseph Conrad")



        // 1
        println(autors.filter(_.split(" ")(0).last == 'a'))

        // 2
        println(autors.filter(_.split(" ")(0).last != 'a').sortBy(_.split(" ")(1)))

        // 3
        println(autors.map(_.split(" ")(0)).toSet)
    
        // 4
        val names = autors.map(_.split(" ")(0))
        println(names.filter(a => names.count(_ == a) > 1).toSet)

        // 5
        println(autors.map(_.split(" ")(1).length).sum)

        // 6
        val groupSexes = autors.groupBy(_.split(" ")(0).last != 'a')
        println(groupSexes(false) ::: groupSexes(true))
    }
}