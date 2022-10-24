import java.util.Random;

public class SelectionSort{
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

    private static void selectionSort(int [] array){
        int n = array.length;

        int aux; int buff;
        for(int i = 0; i < n; i++){
            aux = i;
            for(int j = i + 1; j < n; j++){
                if(array[j] < array[aux]){
                    aux = j;
                }
            }

            buff = array[i];
            array[i] = array[aux];
            array[aux] = buff;
        }
    }

    public static void main(String [] args){
        int [] array = generateArray(5000);

        System.out.print("Before sorting: ");
        printArray(array);
        System.out.println();

        long start = System.currentTimeMillis();
        selectionSort(array);
        long stop = System.currentTimeMillis();

        System.out.print("After sorting: ");
        printArray(array);
        System.out.println();
        System.out.println("Time elapsed: " + (stop - start) + "ms.");
    }
}