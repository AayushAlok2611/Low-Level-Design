package Java.BookMyShow;
import java.util.List;


public class Show {
    Movie movie;
    int startTime;
    Screen screen;
    List<Integer> bookedSeatIds;

    public Show(Movie movie,int startTime,Screen screen)
    {
        this.movie = movie;
        this.startTime = startTime;
        this.screen = screen;
    }
    public void print()
    {   
        String printString = movie.getName() + " is showing on screen no. " + screen.getScreenId() + " at " + Integer.toString(startTime);
        System.out.println(printString);
    }
}
