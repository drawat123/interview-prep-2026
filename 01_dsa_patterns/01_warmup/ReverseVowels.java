public class ReverseVowels {
    private static boolean isVowel(char c) {
        return switch (c) {
            case 'a', 'e', 'i', 'o', 'u',
                    'A', 'E', 'I', 'O', 'U' ->
                true;
            default -> false;
        };
    }

    public String reverseVowels(String s) {
        char[] arr = s.toCharArray();

        int l = 0, r = arr.length - 1;

        while (l < r) {
            while (l < r && !isVowel(arr[l])) {
                l++;
            }
            while (l < r && !isVowel(arr[r])) {
                r--;
            }

            char t = arr[l];
            arr[l] = arr[r];
            arr[r] = t;

            l++;
            r--;
        }

        return new String(arr);
    }
}