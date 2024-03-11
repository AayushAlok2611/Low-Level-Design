package Java.BookMyShow.Enums;

public enum City {
    Bangalore("Bangalore"),
    Delhi("Delhi"),
    Mumbai("Mumbai");
    

    private String cityString;

    // Constructor to associate string values with enum constants
    City(String cityString) {
        this.cityString = cityString;
    }

    // Getter method to retrieve the associated string value
    public String getCityString() {
        return cityString;
    }
}