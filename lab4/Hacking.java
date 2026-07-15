import java.util.Objects;

public class Hacking {
    public static void main(String[] args) {
        // TODO
        Time.ONE_SECOND.setDays(999);
        Time.ONE_SECOND.setHours(23);
        Time.ONE_SECOND.setMinutes(59);
        Time.ONE_SECOND.setSeconds(59);

        System.out.println(Time.ONE_SECOND);
    }
}

/**
 * Klasa Time (przykładowa implementacja z zeszłego tygodnia)
 * W tej klasie niczego nie zmieniamy!
 */
class Time {
    public static final int SECONDS_PER_MINUTE = 60;
    public static final int MINUTES_PER_HOUR = 60;
    public static final int HOURS_PER_DAY = 24;
    public static final Time ZERO = new Time();
    public static final Time ONE_SECOND = new Time(0, 0, 0, 1);
    public static final Time ONE_MINUTE = new Time(0, 0, 1, 0);
    public static final Time ONE_HOUR = new Time(0, 1, 0, 0);
    public static final Time ONE_DAY = new Time(1, 0, 0, 0);
    public static final Time ONE_YEAR = new Time(365, 0, 0, 0);
    private int days = 0;
    private int hours = 0;
    private int minutes = 0;
    private int seconds = 0;

    public Time() {
    }

    public Time(int days, int hours, int minutes, int seconds) {
        this.setDays(days);
        this.setHours(hours);
        this.setMinutes(minutes);
        this.setSeconds(seconds);
    }

    public int getDays() {
        return days;
    }

    public int getHours() {
        return hours;
    }

    public int getMinutes() {
        return minutes;
    }

    public int getSeconds() {
        return seconds;
    }

    public void setDays(int days) {
        if (testRange(days, 0, Integer.MAX_VALUE, "dni")) return;
        this.days = days;
    }

    public void setHours(int hours) {
        if (testRange(hours, 0, HOURS_PER_DAY, "godzin")) return;
        this.hours = hours;
    }

    private static boolean testRange(int variable, int variableMin, int variableMax, String description) {
        if (variable < variableMin || variable >= variableMax) {
            System.out.println("Liczba " + description + ": " + variable + " spoza przedzialu [" + variableMin + ", " + variableMax + ")!");
            return true;
        }
        return false;
    }

    public void setMinutes(int minutes) {
        if (testRange(minutes, 0, MINUTES_PER_HOUR, "minut")) return;
        this.minutes = minutes;
    }

    public void setSeconds(int seconds) {
        if (testRange(seconds, 0, SECONDS_PER_MINUTE, "sekund")) return;
        this.seconds = seconds;
    }

    public void addDays(int days) {
        this.setDays(this.days + days);
    }

    public void addHours(int hours) {
        int allHours = this.hours + hours;
        this.setHours(allHours % HOURS_PER_DAY);
        this.addDays(allHours / HOURS_PER_DAY);
    }

    public void addMinutes(int minutes) {
        int allMinutes = this.minutes + minutes;
        this.setMinutes(allMinutes % MINUTES_PER_HOUR);
        this.addHours(allMinutes / MINUTES_PER_HOUR);
    }

    public void addSeconds(int seconds) {
        int allSeconds = this.seconds + seconds;
        this.setSeconds(allSeconds % SECONDS_PER_MINUTE);
        this.addMinutes(allSeconds / SECONDS_PER_MINUTE);
    }

    public static Time plusTime(Time t1, Time t2) {
        Time time = Time.copyOf(t1);
        time.addDays(t2.days);
        time.addHours(t2.hours);
        time.addMinutes(t2.minutes);
        time.addSeconds(t2.seconds);
        return time;
    }

    public static Time times(Time t1, int times) {
        Time time = new Time();
        time.addDays(t1.days * times);
        time.addHours(t1.hours * times);
        time.addMinutes(t1.minutes * times);
        time.addSeconds(t1.seconds * times);
        return time;
    }

    public static Time timeOf(String timeString) {
        String[] splitted = timeString.split(":");
        Time time = new Time(Integer.parseInt(splitted[0]),
                Integer.parseInt(splitted[1]),
                Integer.parseInt(splitted[2]),
                Integer.parseInt(splitted[3]));
        return time;
    }

    public static Time copyOf(Time t3) {
        Time time = new Time(t3.days, t3.hours, t3.minutes, t3.seconds);
        return time;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Time time = (Time) o;
        return days == time.days && hours == time.hours && minutes == time.minutes && seconds == time.seconds;
    }

    @Override
    public int hashCode() {
        return Objects.hash(days, hours, minutes, seconds);
    }

    @Override
    public String toString() {
        return String.format("%d:%02d:%02d:%02d", days, hours, minutes, seconds);
    }
}
