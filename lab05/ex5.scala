object ex5 {
    // @scala.annotation.tailrec

    abstract class Fuel(val fuel: Int)
    case class EletricCharges(val charge: Int) extends Fuel(charge)
    case class Oil(val petrol: Int) extends Fuel(petrol)
    case class HGas(val gas: Int) extends Fuel(gas)

    trait Engine {
        type KindeOfFuel <: Fuel
        def addFuel(f: KindeOfFuel): Unit
    }

    trait ElectricMotor extends Engine {
        type KindeOfFuel = EletricCharges

        def addFuel(f : KindeOfFuel) = println("added " + f.charge + " Ah")
    }

    trait Diesel extends Engine {
        type KindeOfFuel = Oil
        
        def addFuel(f : KindeOfFuel) = println("added " + f.petrol + " Liter")
    }
    
    trait Hydro extends Engine {
        type KindeOfFuel = HGas
        
        def addFuel(f : KindeOfFuel) = println("added " + f.gas + " H2 Liter")
    }


    class Car {

    }

    class SUV extends Car {
    
    }


    def main(args: Array[String]): Unit = {
        val tesla = new Car with ElectricMotor;
        val vw    = new Car with Diesel;
        val honda = new SUV with Hydro;

        tesla.addFuel(new EletricCharges(100))
        vw.addFuel(new Oil(300))
        honda.addFuel(new HGas(10))

        // honda.addFuel(new Oil(100))
    }
}