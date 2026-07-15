import java.util.Arrays;
import java.util.Objects;

public class BigInt {

    public static final BigInt ZERO = new BigInt("0");
    public static final BigInt ONE = new BigInt("1");
    public static final BigInt TWO = new BigInt("2");
    public static final BigInt TEN = new BigInt("10");
    
    public static void main(String[] args)
    {
        BigInt test1 = new BigInt("-1235");
        System.out.println(test1);

        BigInt test2 = new BigInt(new byte[]{1, 4 , 5, 2, 3}, true);
        System.out.println(test2);

        System.out.println(BigInt.TWO);

        BigInt test3 = BigInt.valueOf("10");
        System.out.println(test3);

        byte[] n = test1.getNumber();
        System.out.println(Arrays.toString(n));
        System.out.println("Znak w test1: " + test1.getSign());

        System.out.println("Czy test1 == test2 [expected false]: " + test1.equals(test2));
        System.out.println("Czy test3 == BigInt.TEN [expected true]: " + test3.equals(BigInt.TEN));
    }

    public BigInt(byte[] n, boolean s)
    {
        number = Arrays.copyOf(n, n.length);
        sign = s;
    }

    public BigInt(String n)
    {
        int s = 0;
        sign = !n.startsWith("-");
        if (!sign)
            s = 1;

        number = new byte[n.length() - s];
        for (int i = 0; i < n.length() - s; i++)
            number[i] = (byte)(n.charAt(i + s) - '0');
    }

    public static BigInt valueOf(String val)
    {
        return switch (val) {
            case "0" -> BigInt.ZERO;
            case "1" -> BigInt.ONE;
            case "2" -> BigInt.TWO;
            case "10" -> BigInt.TEN;
            default -> new BigInt(val);
        };
    }

    private BigInt(BigInt flipSign)
    {
        number = flipSign.number;
        sign = !flipSign.sign;
        hashval = flipSign.hashval;
        isHash = flipSign.isHash;
    }

    @Override
    public String toString()
    {
        StringBuilder sb = new StringBuilder();
        sb.append(sign ? "" : "-");
        for (byte b : number)
            sb.append((char)(b + '0'));
        return sb.toString();
    }

    @Override
    public boolean equals(Object other)
    {
        if (this == other) return true;
        if (!(other instanceof BigInt bigOther)) return false;
        return hashCode() == bigOther.hashCode();
    }

    @Override
    public int hashCode() {
        if (!isHash)
        {
            hashval = Objects.hash((Object) number);
        }
        return hashval;
    }

    public BigInt negate()
    {
        return new BigInt(this);
    }

    public byte[] getNumber()
    {
        return Arrays.copyOf(number, number.length);
    }

    public char getSign()
    {
        return sign ? '\0' : '-';
    }

    final private byte[] number;
    final private boolean sign;

    private int hashval = 0;
    private boolean isHash = false;
}
