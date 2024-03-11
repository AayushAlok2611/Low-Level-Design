package Java.BookMyShow;

import Java.BookMyShow.Enums.SeatType;

public class Seat {
    int seatId;
    int seatCost;
    SeatType seatType;

    public Seat(int seatId,int seatCost,SeatType seatType){
        this.seatId = seatId;
        this.seatCost = seatCost;
        this.seatType = seatType;
    }
}
