package Java.BookMyShow.Utils;

import java.util.ArrayList;
import java.util.List;

import Java.BookMyShow.Seat;
import Java.BookMyShow.Enums.SeatType;

public class CreateSeats {
    public List<Seat> create()
    {
        //creating 100 seats for testing purpose, this can be generalised
        List<Seat> seats = new ArrayList<>();

        //1 to 40 : SILVER
        for (int i = 0; i < 40; i++) {
            Seat seat = new Seat(i,10,SeatType.SILVER);
            seats.add(seat);
        }

        //41 to 70 : GOLD
        for (int i = 40; i < 70; i++) {
            Seat seat = new Seat(i,20,SeatType.GOLD);
            seats.add(seat);
        }

        //1 to 40 : PLATINUM
        for (int i = 70; i < 100; i++) {
            Seat seat = new Seat(i,30,SeatType.PLATINUM);
            seats.add(seat);
        }

        return seats;
    }   
}
