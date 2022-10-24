import java.util.Random;

public class BubbleSort{
    private static void printArray(int [] array){
        int n = array.length;
        System.out.print("[ ");
        if(n < 21){
            for(int i=0; i < n; i++){
                System.out.print(array[i] + " ");
            }
        }else{
            for(int i=0; i < 10; i++){
                System.out.print(array[i] + " ");
            }
            System.out.print("(...) ");
            for(int i=n - 10; i < n; i++){
                System.out.print(array[i] + " ");
            }
        }
        System.out.print("]");        
    }


    private static int [] generateArray(int size){
        int [] output_array = new int[size];
        Random rd = new Random();

        for(int i = 0; i < size; i++){
            output_array[i] = rd.nextInt() % 100;
        }

        return output_array;
    }

    private static void bubbleSort(int [] array){
        int n = array.length - 1;
        for(int i = n; i > -1; i--){
            for(int j=0; j < n; j++){
                if(array[j] > array[j + 1]){
                    int aux = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = aux;
                }
            }
        }
    }

    public static void main(String[] args){
        int size = 50000;
        int [] array = generateArray(size);
        System.out.print("Before sorting: ");
        printArray(array);
        long start = System.currentTimeMillis();
        bubbleSort(array);
        long stop = System.currentTimeMillis();
        System.out.println();
        System.out.print("After sorting: ");
        printArray(array);
        System.out.println();
        System.out.println("Time elapsed: " + (stop - start) + "ms.");

    }
}