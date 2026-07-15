object ex42 {
    class Point {
        var x = 0;
        var y = 0;

        override def toString(): String = "Position(" + x + ", " + y + ")"
    }

    trait Color {
        // var R = 0;
        // var G = 0;
        // var B = 0;

        private def selfCheck() = {
            if (getR < 0) setR 0;
            else if (getR > 255) setR 255;
            if (getG < 0) setG 0;
            else if (getG > 255) setG 255;
            if (getB < 0) setB 0;
            else if (getB > 255) setB 255;
        }

        def increaseRedBy(v: Int) = { setR(R + v); selfCheck; }
        def increaseGreenBy(v: Int) = { setG(G + v); selfCheck; }
        def increaseBlueBy(v: Int) = { setB(B + v); selfCheck; }
        def decreaseRedBy(v: Int) = { setR(R - v); selfCheck; }
        def decreaseGreenBy(v: Int) = { setG(G - v); selfCheck; }
        def decreaseBlueBy(v: Int) = { setB(B - v); selfCheck; }
        def darkerBy(v: Int) = {
            decreaseRedBy(v);
            decreaseGreenBy(v);
            decreaseBlueBy(v);
            selfCheck;
        }
        def inverseColor() = {
            setColor(255 - getR, 255 - getG, 255 - getB)
        }

        def blackWhite() = {
            val Y = (0.299 * getR + 0.587 * getG + 0.114 * getB).toInt;
            setColor(Y, Y, Y);
        }
    }

    class ColorPoint extends Point {
        var R = 0;
        var G = 0;
        var B = 0;

        override def toString(): String = "Color(" + R + ", " + G + ", " + B + ") at " + super.toString;

        def setColor(r: Int, g: Int, b: Int) = {
            R = r;
            G = g;
            B = b;
            selfCheck;
        }
        def getR() = R;
        def getG() = G;
        def getB() = B;
        def setR(v: Int) = { R = v; };
        def setG(v: Int) = { G = v; };
        def setB(v: Int) = { B = v; };
    }
    
    def main(args: Array[String]): Unit = {
        val pc = new ColorPoint with Color
        pc.setColor(56, 0, 120)
        pc.increaseRedBy( 20 )
        pc.decreaseBlueBy( 10 )
        println(pc)
        pc.inverseColor()
        println(pc)
        pc.blackWhite()
        println(pc)
    }
}