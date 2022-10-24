import java.util.Random;

public class ShellSort{
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

    private static void shellSort(int [] array){
        int n = array.length;
        
        int buff;
        for(int gap = n/2; gap > 0; gap /= 2){
            for(int i = gap; i < n; i++){
                for(int j = i - gap; (j > -1) && (array[j] > array[j + gap]); j--){
                    buff = array[j];
                    array[j] = array[j + gap];
                    array[j + gap] = buff;
                }
            }
        }
    }

    public static void main(String [] args){
        int [] array = generateArray(50000);
        System.out.print("Before sorting: ");
        printArray(array);
        System.out.println();

        long start = System.currentTimeMillis();
        shellSort(array);
        long stop = System.currentTimeMillis();

        System.out.print("After sorting: ");
        printArray(array);
        System.out.println();

        System.out.println("Elapsed time: " + (stop - start) + "ms.");
    }
}