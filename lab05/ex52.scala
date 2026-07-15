object ex52 {

    class Person(val name: String, val surname: String, val age: Int, val sex: String) {
        def +(other: Person): Int = return age + other.age

    }
    object Person {
        def apply(name: String, surname: String, age: Int, sex: String) = new Person(name, surname, age, sex)
    }

    def main(args: Array[String]): Unit = {
        val people = List(
            Person("John", "Doe", 23, "male"),
            Person("Joan", "Doe", 23, "female"),
            Person("Steve", "Jenkins", 24, "male"),
            Person("Eva", "Robinson", 25, "female"),
            Person("Ben", "Who", 22, "male"),
            Person("Janet", "Reed", 21, "female"),
            Person("Rob", "Jenkins", 26, "male"),
            Person("Ella", "Dawson", 27, "female")
        )

        // people.foreach(p => println((if (p.male == "male") "M" else "F") + s" | " p.name + " " +p.surname))
        people.foreach(p => println((if (p.sex == "male") "M" else "F") + " | " + p.name + " " + p.surname))
        println("Males: " + people.count(p => p.sex == "male") + " | Females: " + people.count(p => p.sex == "female"))
        println(people.map(p => p.age).sum / people.length)
        println("Males avrage: " + people.map(p => if (p.sex == "male") p.age else 0).sum / people.count(p => p.sex == "male"))
        println("Females avrage: " + people.map(p => if (p.sex == "female") p.age else 0).sum / people.count(p => p.sex == "female"))
    }
}