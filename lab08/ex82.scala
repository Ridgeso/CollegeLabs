object ex82 {

    
    val FAILED = 0;
    val WORKS = 1;

    class MyMaybe(val v: Double, s: Int) {
        def flatMap(f: Double => MyMaybe): MyMaybe = {
            s match {
                case WORKS => f(v)
                case FAILED => MyMaybe(v)
            }
        }

        override def toString(): String = "MyMaybe(" + v.toString + ")"
    }
    object MyMaybe {
        def apply(d: Double) = new MyMaybe(d, WORKS)
        def apply(d: Double, s: Int) = new MyMaybe(d, s)
    }
    
    def fail(arg: Double) : MyMaybe = MyMaybe(arg, FAILED)

    def main(args: Array[String]): Unit = {
        val a = MyMaybe(9.0)

        val failing_calculation = a
            .flatMap((x: Double) => {println("multiplying"); MyMaybe(x*2)})
            .flatMap(fail)
            .flatMap((x: Double) => {println("multiplying again"); MyMaybe(x*2)})


        val successful_calculation = a
            .flatMap((x: Double) => MyMaybe(x * 2))
            .flatMap((x: Double) => MyMaybe(x + 2))
        
        println(failing_calculation)
        println(successful_calculation)
    }

}