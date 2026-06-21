
public class Pangram {

    public boolean checkIfPangram(String sentence) {
        if (sentence == null || sentence.length() < 26) {
            return false;
        }

        boolean[] arr = new boolean[26];
        int cnt = 0;

        for (int i = 0; i < sentence.length(); i++) {
            int val = Character.toLowerCase(sentence.charAt(i)) - 'a';
            if (val >= 0 && val <= 25 && !arr[val]) {
                cnt++;
                arr[val] = true;
            }

            if (cnt == 26) {
                return true;
            }
        }
        return false;
    }
}
