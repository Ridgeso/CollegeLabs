object ex72 {

    abstract class DiWord
    case class Person(val name: String, val fname: String, val age: Int) extends DiWord
    case class Company(val name: String, val origin: String) extends DiWord

    def extr(data: List[Iterable[String]]): List[DiWord] = data.map(el => el match {
        case Person(n, f, a) => Person(n, f, a);
        case Company(n, o) => Company(n, o);
        case _ => Person("InValid", "Person", -1)
    })

    def main(args: Array[String]): Unit = {
        val data = List(
            Map("name" -> "Jan", "fname" -> "Kowalski", "age" -> "45"),
            Map("company" -> "ABB", "origin" -> "Sweden"),
            Map("name" -> "Katarzyna", "fname" -> "Nowak", "age" -> "45"),
            Map("company" -> "F4", "origin" -> "Poland"),
            List("Cos", "innego"), // a different type here
            Map("company" -> "Salina Bochnia", "origin" -> "Poland"),
            Map("company" -> "AGH", "origin" -> "Poland"),
            Map("name" -> "Krzysztof", "fname" -> "Krol", "age" -> "14")
        )
    }

    object Person {
        def unapply(info: Map[String, String]): Option[Person] = {
            // if (info.keySet.contains("name"))
            if (info.get("name"))
                return Some(Person(info.get("name"), info.get("fname"), info.get("age")))
            return None;
        }
    }

    object Company {
        def unapply(info: Map[String, String]): Option[Company] = {
            // if (info.keySet.contains("company"))
            if (info.get("company"))
                return Some(Company(info.get("company"), info.get("origin")))
            return None;
        }
    }
}