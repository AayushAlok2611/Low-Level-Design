package Java.BookMyShow.Utils;

import Java.BookMyShow.Movie;
import Java.BookMyShow.Screen;
import Java.BookMyShow.Show;

public class CreateShow {
    public Show createShow(Screen screen, Movie movie, int showStartTime) {
        Show show = new Show(movie,showStartTime,screen);
        return show;
    }

}
