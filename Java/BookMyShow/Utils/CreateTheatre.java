package Java.BookMyShow.Utils;

import java.util.ArrayList;
import java.util.List;

import Java.BookMyShow.Theatre;
import Java.BookMyShow.Enums.City;

public class CreateTheatre {
    public List<Theatre> create(){
        List<Theatre> theatres = new ArrayList<>();

        Theatre t1 = new Theatre(City.Bangalore,"PVR");
        Theatre t2 = new Theatre(City.Delhi,"INOX");

        theatres.add(t1);
        theatres.add(t2);
        return theatres;
    }
}
