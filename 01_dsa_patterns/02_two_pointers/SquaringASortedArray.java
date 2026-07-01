import java.util.Arrays;

public class SquaringASortedArray {
    public static int[] makeSquares(int[] arr) {
        int n = arr.length;
        int[] squares = new int[n];
        int l = 0, r = n - 1;
        int writeIdx = n - 1;

        while (l <= r) {
            int leftSquare = arr[l] * arr[l];
            int rightSquare = arr[r] * arr[r];

            if (leftSquare > rightSquare) {
                squares[writeIdx--] = leftSquare;
                l++;
            } else {
                squares[writeIdx--] = rightSquare;
                r--;
            }
        }
        return squares;
    }

    public static void main(String[] args) {
        int[] arr = { -2, -1, 1, 2, 3 };
        System.out.println(Arrays.toString(makeSquares(arr)));
    }
}
// -2,-1,1,2,3