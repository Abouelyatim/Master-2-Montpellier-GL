public class Cat extends Animal {


    public Cat(String name, String type, int legsNumber, int legSize) {
        super(name, type, legsNumber, legSize);
    }

    @Override
    public String toString() {
        return "Cat ( "+"name = "+name+" "+"type = "+type+" "+" "+"legsNumber = "+ legs.legsNumber +" legSize = "+ legs.legSize +" )";
    }
}
