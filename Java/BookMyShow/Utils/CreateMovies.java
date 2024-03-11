package Java.BookMyShow.Utils;
import java.util.ArrayList;
import java.util.List;

import Java.BookMyShow.Movie;

public class CreateMovies {
    public List<Movie> create(){
        List<Movie> movieList = new ArrayList<>();

        // Avengers movie
        Movie avengersMovie = new Movie("Avengers",120,1);

        // Avengers 2 movie
        Movie avengers2Movie = new Movie("Avengers 2",120,2);

        movieList.add(avengersMovie);
        movieList.add(avengers2Movie);

        return movieList;
    }
}
