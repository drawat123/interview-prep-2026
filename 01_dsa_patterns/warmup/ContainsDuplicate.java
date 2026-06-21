
import java.util.HashSet;
import java.util.Set;

public class ContainsDuplicate {

    public boolean containsDuplicate(int[] nums) {
        Set<Integer> hashSet = new HashSet<>();
        for (int num : nums) {
            if (!hashSet.add(num)) {
                return true;
            }
        }

        return false;
    }
}
