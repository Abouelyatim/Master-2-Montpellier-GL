public class main {

    public static void main(String[]args){
        //@Override
        //    public String toString() {
        //        return "Legs( legsNumber = "+legsNumber+" legSize = "+legSize+" )";
        //    }
        Animal cat = new Cat("cat","mammal",4,5);

        Chair chair = new Chair(4,2);

        System.out.println(cat.toString());
        System.out.println(chair.toString());
    }
}
