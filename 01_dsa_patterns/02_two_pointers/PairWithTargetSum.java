public class PairWithTargetSum {
    public static int[] search(int[] arr, int targetSum) {
        int l = 0, r = arr.length - 1;

        while (l < r) {
            int s = arr[l] + arr[r];
            if (s == targetSum) {
                return new int[] { l, r };
            } else if (s > targetSum) {
                r--;
            } else {
                l++;
            }
        }

        return new int[] { -1, -1 };
    }
}
