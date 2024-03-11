package Java.BookMyShow;
import java.util.List;

public class Booking {
    User user;
    Show show;
    List<Integer> bookedSeatIds;
    int bookingCost;

    Booking(User user,Show show,List<Integer> bookedSeatIds,int bookingCost)
    {
        this.user = user;
        this.show = show;
        this.bookedSeatIds = bookedSeatIds;
        this.bookingCost = bookingCost;
    }
}
