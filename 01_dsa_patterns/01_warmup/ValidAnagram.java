public class ValidAnagram {

    public boolean isAnagram(String s, String t) {
        if (s.length() != t.length()) {
            return false;
        }

        int[] characters = new int[26];

        for (int i = 0; i < s.length(); i++) {
            int ch1 = s.charAt(i) - 'a';
            int ch2 = t.charAt(i) - 'a';

            characters[ch1]++;
            characters[ch2]--;
        }

        for (int val : characters) {
            if (val != 0) {
                return false;
            }
        }

        return true;
    }
}
