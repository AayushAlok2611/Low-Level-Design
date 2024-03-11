package Java.BookMyShow;

import java.util.List;

import Java.BookMyShow.Enums.City;
import Java.BookMyShow.Utils.CreateMovies;
import Java.BookMyShow.Utils.CreateScreens;
import Java.BookMyShow.Utils.CreateShow;
import Java.BookMyShow.Utils.CreateTheatre;

public class App {
    CityMovieMapping cityToMovieMapping;
    CityTheatreMapping cityToTheatreMapping;

    public static void main(String[] args){
        App bmsApp = new App();
        bmsApp.initializeApp();

    }
    private void initializeApp(){
        cityToMovieMapping = new CityMovieMapping();
        cityToTheatreMapping = new CityTheatreMapping();

        List<Theatre> theatres = new CreateTheatre().create();
        List<Movie> movies = new CreateMovies().create();
        List<Screen> screens  = new CreateScreens().create();

        for(Theatre t:theatres)
        {   
            City city = t.getCity();
            cityToTheatreMapping.addTheatreToCity(t, city);
            for(Movie m:movies)
            {
                cityToMovieMapping.addMovieToCity(m, city);
                int showStartTime = 10;
                for(Screen s:screens)
                {
                    Show show = new CreateShow().createShow(s, m, showStartTime);
                    t.addShow(show);
                    showStartTime += 4;
                }
            }
            printScheduleForTheatre(t);
        }
        
    }
    private void printScheduleForTheatre(Theatre theatre)
    {   
        System.out.println("==========================================");
        theatre.printTheatreDetails();
        List<Show> showsInTheatre = theatre.getAllShows();
        for(Show s:showsInTheatre) s.print();
        System.out.println("==========================================");
    }
}
