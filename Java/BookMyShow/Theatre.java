package Java.BookMyShow;
import java.util.ArrayList;
import java.util.List;

import Java.BookMyShow.Enums.City;

public class Theatre {
    City city;
    List<Screen> screens;
    List<Show> shows;
    String name;

    public Theatre(City city,String name)
    {
        this.city = city;
        this.name = name;
    }
    void addShow(Show show)
    {   
        if(shows == null)
        {
            shows = new ArrayList<>();
        }
        shows.add(show);
    }
    void addScreen(Screen screen)
    {   
        if(screens == null)
        {
            screens = new ArrayList<>();
        }
        screens.add(screen);
    }
    void removeShow(Show show)
    {
        if(shows!=null && shows.contains(show))
        {
            shows.remove(show);
        }
    }
    List<Show> getAllShows(){ return shows;}
    City getCity(){ return city;}
    public void printTheatreDetails()
    {   
        String cityString = city.getCityString();
        System.out.println("The theatre name is " + name + " in the city " + cityString);
    }
}
