public abstract class Animal {
    String name;
    String type;

    //nous attendons l'extraction de ces deux propriété a une nouvelle classe
    int legsNumber;
    int legSize;

    public Animal(String name, String type, int legsNumber, int legSize) {
        this.name = name;
        this.type = type;
        this.legsNumber = legsNumber;
        this.legSize = legSize;
    }
}
