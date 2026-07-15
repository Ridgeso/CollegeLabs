import java.time.LocalDate;
import java.util.UUID;

/**
 * Record representing data of the movie from shop
 * @param movie: Movie abstraction
 * @param returnDate: date when movie was returned to the shop
 * @param uuid: id of the movie
 * @param rentalDate: day when movie was rented
 * @see Movie
 */
public record VHS(Movie movie, LocalDate returnDate, UUID uuid, LocalDate rentalDate) {

    /**
     * @return Format of the String is "uuid,movie,rentalDate,returnDate"
     */
    @Override
    public String toString() {
        return uuid + "," + movie + "," + rentalDate + "," + returnDate;
    }
}
