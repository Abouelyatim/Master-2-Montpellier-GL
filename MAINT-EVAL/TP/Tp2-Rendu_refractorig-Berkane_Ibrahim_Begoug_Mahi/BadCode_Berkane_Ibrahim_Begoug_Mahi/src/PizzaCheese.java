public class PizzaCheese {// nous attendons de regrouper les méthodes et propriétés commune dans une super classe
    String name;
    Double price;

    public PizzaCheese(String name, Double price) {
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




