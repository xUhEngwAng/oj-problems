import java.util.HashMap;
import java.util.Scanner;

class Solution{
	public static void main(String[] argv){
		Scanner sc = new Scanner(System.in);
		int target, len;
		len = sc.nextInt();
		target = sc.nextInt();
		int[] nums = new int[len];
		for(int ix = 0; ix != len; ++ix)
			nums[ix] = sc.nextInt();

		int[] res = twoSum(nums, target);
		System.out.println(String.format("%d %d", res[0], res[1]));
	}

	public static int[] twoSum(int[] nums, int target){
		HashMap<Integer, Integer> hash = new HashMap<Integer, Integer>();
		int[] ret = new int[2];
		int key;
		for(int ix = 0; ix != nums.length; ++ix){
			key = nums[ix];
			if(hash.containsKey(key)){
				ret[0] = hash.get(key);
				ret[1] = ix;
				break;
			}
			hash.put(target - key, ix);
		}
		int tmp;
		if(ret[0] > ret[1]){
			tmp = ret[0];
			ret[0] = ret[1];
			ret[1] = tmp;
		}
		return ret;
	}
}
