public class Pizza {
    String name;
    Double price;

    public Pizza(String name, Double price) {
        this.name = name;
        this.price = price;
    }

    public Double geTotal(){
        return price*0.10 + price;
    }

    public String getName(){
        return this.name;
    }

    @Override
    public String toString() {
        return name+" "+price.toString();
    }
}
