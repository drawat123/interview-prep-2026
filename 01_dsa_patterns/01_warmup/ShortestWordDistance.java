public class ShortestWordDistance {

    public int shortestDistance(String[] words, String word1, String word2) {
        int shortestDistance = words.length;
        int position1 = -1, position2 = -1; // Initialize the positions of word1 and word2 with -1

        for (int i = 0; i < words.length; i++) {
            if (words[i].equals(word1)) {
                position1 = i;
                if (position2 != -1) {
                    shortestDistance = Math.min(shortestDistance, i - position2);
                }
            } else if (words[i].equals(word2)) {
                position2 = i;
                if (position1 != -1) {
                    shortestDistance = Math.min(shortestDistance, i - position1);
                }
            }
        }

        return shortestDistance;
    }
}