import java.util.Timer;

/**
 * Movie record containing data representing:
 * @param duration: int, movie length in minutes
 * @param title: string, name of the movie
 * @param director: string, Director of the movie
 */
public record Movie(int duration, String title, String director)
{
    /**
     * @return Format of the Movie is "splited-title,duration,director-fullname"
     */
    @Override
    public String toString() {
        return String.join("-", title.split(" ")) + "," + duration + "," + director;
    }
}
