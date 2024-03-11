package Java.BookMyShow.Utils;

import java.util.ArrayList;
import java.util.List;
import Java.BookMyShow.Screen;
import Java.BookMyShow.Seat;

public class CreateScreens {
    public List<Screen> create()
    {
        List<Seat> seats = new CreateSeats().create();
        List<Screen> screens = new ArrayList<>();

        Screen screen1 = new Screen(1,seats);
        Screen screen2 = new Screen(2,seats);
        screens.add(screen1);
        screens.add(screen2);

        return screens;
    }   
}
