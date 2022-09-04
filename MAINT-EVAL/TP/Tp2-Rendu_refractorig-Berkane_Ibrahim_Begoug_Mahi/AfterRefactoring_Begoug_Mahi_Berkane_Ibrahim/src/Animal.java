public abstract class Animal {
    final Legs legs = new Legs();
    String name;
    String type;

    public Animal(String name, String type, int legsNumber, int legSize) {
        this.name = name;
        this.type = type;
        this.legs.legsNumber = legsNumber;
        this.legs.legSize = legSize;
    }
}


