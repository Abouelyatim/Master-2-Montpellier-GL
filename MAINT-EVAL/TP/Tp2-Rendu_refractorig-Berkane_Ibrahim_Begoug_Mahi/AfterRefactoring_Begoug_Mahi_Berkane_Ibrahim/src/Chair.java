public class Chair {

    final Legs legs = new Legs();


    public Chair(int legsNumber, int legSize) {
        this.legs.legsNumber = legsNumber;
        this.legs.legSize = legSize;
    }

    @Override
    public String toString() {
        return "Chair ( "+"legsNumber = "+ legs.legsNumber +" legSize = "+ legs.legSize +" )";
    }
}


