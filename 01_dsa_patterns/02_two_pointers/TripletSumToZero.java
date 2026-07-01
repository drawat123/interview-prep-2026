import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class TripletSumToZero {

    public static List<List<Integer>> searchTriplets(int[] arr) {
        List<List<Integer>> triplets = new ArrayList<>();
        Arrays.sort(arr); // -3.-2.-1,0,1,1,2

        for (int i = 0; i < arr.length - 2; i++) {
            if (i > 0 && arr[i] == arr[i - 1]) {
                continue;
            }

            int j = i + 1, k = arr.length - 1;
            while (j < k) {
                int currSum = arr[i] + arr[j] + arr[k];
                if (currSum == 0) {
                    triplets.add(List.of(arr[i], arr[j], arr[k]));
                    j++;
                    k--;
                    // Skip duplicates for both pointers to save CPU cycles
                    while (j < k && arr[j] == arr[j - 1]) {
                        j++;
                    }
                    while (j < k && arr[k] == arr[k + 1]) {
                        k--;
                    }
                } else if (currSum < 0) {
                    j++;
                } else {
                    k--;
                }
            }
        }

        return triplets;
    }

    public static void main(String[] args) {
        System.out.println(searchTriplets(new int[] { -4, -2, -2, 0, 2, 2, 4 }));
    }
}