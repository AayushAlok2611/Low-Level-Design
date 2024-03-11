package Java.BookMyShow;

public class Movie {
    String name;
    int durationInMinutes;
    int movieId;

    public Movie(String name,int durationInMinutes,int movieId){
        this.name = name;
        this.durationInMinutes = durationInMinutes;
        this.movieId = movieId;
    }
    public String getName(){return name;}

}
