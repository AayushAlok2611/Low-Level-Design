package Java.BookMyShow;
import java.util.Map;

import Java.BookMyShow.Enums.City;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class CityTheatreMapping {
    Map<City,List<Theatre>> cityToTheatreMap;

    CityTheatreMapping()
    {
        cityToTheatreMap = new HashMap<>();
    }
    void addTheatreToCity(Theatre theatre,City city)
    {
        List<Theatre> theatreList;
        if(!cityToTheatreMap.containsKey(city))
        {   
            theatreList = new ArrayList<>();
            theatreList.add(theatre);
        }
        else{
            theatreList = cityToTheatreMap.get(city);
            theatreList.add(theatre);
        }
        cityToTheatreMap.put(city,theatreList);
    }
    List<Theatre> getAllTheatresInCity(City city) throws Exception
    {
        if(!cityToTheatreMap.containsKey(city))
        {
            throw new Exception("Unknown City");
        }
        return cityToTheatreMap.get(city);
    }
}
