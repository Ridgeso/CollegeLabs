import scala.util.Random

object ex8 {

    def comp(v: Any): String = v match {
        case h: Int => "Int(" + h.toString + ") "
        case h: String => "String(" + h.toString + ") "
        case h: Double => "Double(" + h.toString + ") "
        case None => ""
    }
    
    def stream(data: Iterable[Any]): String = {
        @scala.annotation.tailrec
        def pars(oldData: Iterable[Any], output: String): String = {
            oldData.headOption match {
                case Some(h) => pars(oldData.tail, output + comp(h))
                case None => output
            }
        }
        return pars(data, "");
    }

    def main(args: Array[String]): Unit = {

        val l = List(1, "hello", 2.56, 0x45, "key") 
        val a = Array(1, "hello", 2.56, 0x45, "key") 

        val s = stream(l)
        println(s)
        
        val sa = stream(a)
        println(sa)
    }
}