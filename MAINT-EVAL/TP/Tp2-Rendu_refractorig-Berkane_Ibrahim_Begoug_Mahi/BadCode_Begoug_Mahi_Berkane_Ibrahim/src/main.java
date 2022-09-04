public class main {

    public static void main(String[]args){
        Animal cat = new Cat("cat","mammal",4,5);

        Chair chair = new Chair("none","none",4,2);

        System.out.println(cat.toString());
        System.out.println(chair.toString());
    }
}
