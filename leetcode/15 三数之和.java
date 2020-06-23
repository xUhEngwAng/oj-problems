import java.util.List;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

/*
 * 这题本身是非常有趣的，学到了不少内容。
 *
 * 首先是 java 多态性的部分，此题是要求返回 List<List<Integer>>
 * 其中 List 是一个 interface，显然是不可实例化的。解决方案是
 *
 * List<List<Interger>> ret = new ArrayList<>();
 * List<Integer> curr = new ArrayList<>();
 *
 * 由于 ArrayList 中的相关函数都是 implement List 类中的接口，
 * 因此直接调用 ret.add 实际上是调用了 ArrayList 中的实现。此外，
 * 由于 ArrayList IS A List，因此可以直接将 ArrayList 添加到
 * ret 中，所以下面这种定义方式也是可以的：
 *
 * ArrayList<Integer> curr = new ArrayList<>();
 * ret.add(curr)//legal
 *
 * 其次是算法本身的问题。我使用了一个 HashMap 用以记录数组中存
 * 的元素及它们出现的次数，主循环是枚举前两个数，利用散列查看第
 * 三个数是否存在，时间复杂度是 O(n^2)，空间复杂度是 O(n)。然而
 * 我这种做法似乎很慢（「打败了 20% 的 java 程序」。我不禁怀疑
 * 我的复杂度不是最优。
 *
 * 然而看了题解发现，最优解其实也是 O(n^2) 的复杂度。它的思想是
 * 确定第一个位置 ix，然后利用两个指针分别指向 ix + 1 和 n - 1。
 * 如果三个元素之和大于零，则右侧指针左移；如果和小于零，则左指针
 * 右移；如果恰好为零，则左右指针同时移过重复位置。
 *
 * 使用了这种算法后，尽管时间复杂度没有变化，却不再需要额外空间。
 * 实际运行时间也相较于第一版快了一倍，依我想来还是 HashMap 操作
 * 常数太大了。
 */

class Solution{
	public static void main(String[] argv){
		Scanner sc = new Scanner(System.in);
		Solution solution = new Solution();
		int len;
		len = sc.nextInt();
		int[] arr = new int[len];
		for(int ix = 0; ix != len; ++ix)
			arr[ix] = sc.nextInt();
		System.out.println(solution.threeSum(arr));
	}

	public List<List<Integer>> threeSum_v1(int[] nums){
		Arrays.sort(nums);
		HashMap<Integer, Integer> map = new HashMap<Integer, Integer>();
		for(int ix = 0; ix != nums.length; ++ix){
			if(map.containsKey(nums[ix]))
				map.put(nums[ix], map.get(nums[ix]) + 1);
			else
				map.put(nums[ix], 1);
		}
		int target;
		ArrayList<Integer> curr;
		List<List<Integer>> ret = new ArrayList<>();
		for(int ix = 0; ix != nums.length; ++ix){
			if(ix > 0 && nums[ix] == nums[ix-1]) continue;
			if(nums[ix] > 0) break;
			for(int jx = ix + 1; jx != nums.length; ++jx){
				if(jx > ix + 1 && nums[jx] == nums[jx-1]) continue;
				target = - nums[ix] - nums[jx];
				if(target < nums[jx]) break;
				if((target == nums[jx] && target != nums[ix] && map.get(target) >= 2) ||
				   (target == nums[jx] && target == nums[ix] && map.get(target) >= 3) ||
				   (target >  nums[jx] && map.containsKey(target))){
				   	curr = new ArrayList<>();
				   	curr.add(nums[ix]);
				   	curr.add(nums[jx]);
				   	curr.add(target);
				   	ret.add(curr);
				}
			}
		}
		return ret;
	}

	public List<List<Integer>> threeSum(int[] nums){
		Arrays.sort(nums);
		List<List<Integer>> ret = new ArrayList<>();
		ArrayList<Integer> curr;
		int left, right;
		for(int ix = 0; ix != nums.length; ++ix){
			if(nums[ix] > 0) break;
			if(ix > 0 && nums[ix] == nums[ix-1]) continue;
			left = ix + 1; right = nums.length - 1;
			while(left < right){
				if(nums[ix] + nums[left] + nums[right] == 0){
					curr = new ArrayList<>();
					curr.add(nums[ix]);
					curr.add(nums[left]);
					curr.add(nums[right]);
					ret.add(curr);
					//ret.add(Arrays.asList(nums[ix], nums[left], nums[right]));
					++left; --right;
					while(left < right && nums[left-1] == nums[left]) ++left;
					while(left < right && nums[right+1]== nums[right]) --right;
				}
				else
				if(nums[ix] + nums[left] + nums[right] < 0) ++left;
				else --right;
			}
		}
		return ret;
	}
}