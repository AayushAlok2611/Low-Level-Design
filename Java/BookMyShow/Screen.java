package Java.BookMyShow;
import java.util.List;

public class Screen {
    int screenId;
    List<Seat> seats;

    public Screen(int screenId,List<Seat> seats)
    {   
        this.screenId = screenId;
        this.seats = seats;
    }
    public String getScreenId()
    {
        return Integer.toString(screenId);
    }
}
