object ex4 {

    class Expense(val amount: Int, val name: String, val category: String) {

        override def toString(): String = "Expense(" + amount + ", " + name + ", " + category + ")"

    }
    object Expense {
        def apply(a: Int, n: String, c: String) = new Expense(a, n, c)
    }

    class ExpensesList {
        var expenses = List[Expense]();

        def +=(expense: Expense): ExpensesList = { expenses = expenses :+ expense; return this; };

        def printList() = {
            println("Expenses List(")
            for (exp <- expenses) {
                println("- " + exp)
            }
            println(")")
        }

        def sum(): Int = {
            @scala.annotation.tailrec
            def getSum(sum: Int, exp: List[Expense]): Int = {
                if (exp.length == 0) return sum;
                return getSum(sum + exp(0).amount, exp.tail);
            }
            return getSum(0, expenses);
        }

        def max(): Int = {
            @scala.annotation.tailrec
            def getMax(max: Int, exp: List[Expense]): Int = {
                if (exp.length == 0) return max;
                if (exp(0).amount > max)
                    return getMax(exp(0).amount, exp.tail);
                else
                    return getMax(max, exp.tail);
            }
            return getMax(0, expenses);
        }

    }
    object ExpensesList {
        def apply() = new ExpensesList()
    }

    def main(args: Array[String]): Unit = {
        val ex = Expense(1, "S", "c");
        val el = ExpensesList();
        el += ex;
        el += ex;
        el += ex;
        el += Expense(1, "Gear", "Car");
        el += Expense(2, "Cheese", "Milk");

        el.printList();
        println(el.sum);
        println(el.max);
    }
}