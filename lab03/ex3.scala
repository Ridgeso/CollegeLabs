
import math.Pi

object ex3 {

    def a(x: Int, y: String) {
        println("a " + x + " " + y)
    }

    def b(x:Int)(y:String) {
        println("b " + x + " " + y)
    }

    def curryIt(toCurry: (Int, String)=Unit) = (Int)=>(String)=>Unit {
        def curryed(x: Int)(y: String)=Unit = toCurry(x, y);
        return curryed;
    }

    def uncurryIt(toUnCurry: (Int)=>(String)=Unit) = (Int, String)=>Unit {
        def uncurryed(x: Int, y: String)=Unit = toUnCurry(x)(y);
        return uncurryed;
    }

    // def reverseList[T](toReverse: List[T]) = List[T] {
    //     @scala.annotation.tailrec
    //     def recRev(reversing: List[T], n: Int) = List[T] {
    //         if (n != 0) {
    //             return recRev(reversing + toReverse.head, n - 1)
    //         }
    //     }

    //     val reversed = List[T]();
    //     return reverseList(reversed, toReverse.lenght);
    // }

    class Angle(ang: Double) {
        val angle = ang;
        def +(a: Angle) = new Angle(angle + a.angle);
    }
    object Angle {
        def apply(ang: Double) = Angle {
            
            return new Angle(ang);
        }

        val right = 12;
        val stright = 12;
        val full = 12;

        def +(a: Angle, s: String) = "Angle=" + a.angle + s;
        def +(s: String, a: Angle) = s + "Angle=" + a.angle;
    }

    def main(args: Array[String])=
    {
        // Exercise 1
        // A
        // val ca = curryIt(a);
        // ca(7)("trying curryIt");
     
        // val ub = uncurryIt(b);
        // ub(9, "trying uncurrIt");

        //B


        // Exercise 2
        val fil1 = Angle(1.5);
        val fil2 = Angle(2.5);
        val r = Angle.right;
        val fil3 = fil1 + fil2;
        println(fil1.angle + " "+ fil2.angle +" "+fil3.angle)
    }
}