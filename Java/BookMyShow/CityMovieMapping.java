package Java.BookMyShow;

import java.util.Map;

import Java.BookMyShow.Enums.City;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class CityMovieMapping {
    Map<City,List<Movie>> cityToMovieMap;
    
    CityMovieMapping(){
        cityToMovieMap = new HashMap<>();
    }
    List<Movie> getAllMoviesInCity(City city) throws Exception
    {
        if(!cityToMovieMap.containsKey(city))
        {
            throw new Exception("Unknown city");
        }
        return cityToMovieMap.get(city);
    }
    void addMovieToCity(Movie movie,City city)
    {   
        List<Movie> movieList;
        if(!cityToMovieMap.containsKey(city))
        {   
            movieList = new ArrayList<>();
            movieList.add(movie);
        }
        else{
            movieList = cityToMovieMap.get(city);
            movieList.add(movie);
        }
        cityToMovieMap.put(city,movieList);
    }
}
