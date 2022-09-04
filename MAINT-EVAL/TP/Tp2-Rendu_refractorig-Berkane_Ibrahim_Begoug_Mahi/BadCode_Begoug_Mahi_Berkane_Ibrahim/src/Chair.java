public class Chair extends Animal {//nous attendons elimination de l'héritage avec la classeAnimal


    public Chair(String name, String type, int legsNumber, int legSize) {
        super(name, type, legsNumber, legSize);
    }

    @Override
    public String toString() {
        return "Chair ( "+"name = "+name+" "+"type = "+type+" "+" "+"legsNumber = "+legsNumber+" legSize = "+legSize+" )";
    }
}
