import java.util.HashMap;
import java.util.Scanner;

/*
 * 此题很容易想出一种暴力解，即遍历每个位置开始的字符串，利用
 * HashSet 保存出现过的字符，从而找到每个位置的最长子串。整体
 * 时间复杂度为 O(n^2)。
 *
 * 我在此基础上做出了一些改进，使用了 HashMap 存储出现过的字符
 * 以及出现的位置。如果某个位置 pos 的字符在前面已经出现过了，
 * 则更长的子串只有可能出现在以 hash.get(s.chatAt(pos)) + 1
 * 开始及其后的子串。我的做法是清空 HashMap，从这个新的位置继续
 * 遍历。尽管做了优化，避免了某些不必要的遍历，最坏时间复杂度仍
 * 是 O(n^2)。
 *
 * 实际上我的想法已经非常接近最优解了，只是一些细节的处理不够细
 * 致。在最优解中，即使出现了重复字符也没有清空 HashMap，而是简
 * 单地将该字符的位置更新为当前出现重复的位置。在后续的循环中，
 * 是判断重复位置是否在滑动窗口内来确定是否更新左边界的，由于只
 * 需要一次循环，时间复杂度仅为 O(n)。
 *
 * 回顾我的做法，是把时间浪费在了重新建立 HashMap 上面了。
 */

class Solution{
	public static void main(String[] argv){
		Scanner sc = new Scanner(System.in);
		String input = sc.next();
		Solution solu = new Solution();
		System.out.println(solu.lengthOfLongestSubstring(input));
	}

	public int lengthOfLongestSubstring_v1(String s) {
		HashMap<Character, Integer> hash = new HashMap<Character, Integer>();
		int ret = 0, len = s.length();
		for(int ix = 0, pos; ix < len; ){
			hash.clear();
			for(pos = ix; pos < len; pos++){
				if(hash.containsKey(s.charAt(pos))){
					if(ret < pos - ix) ret = pos - ix;
					ix = hash.get(s.charAt(pos)) + 1;
					break;
				}
				hash.put(s.charAt(pos), pos);
			}
			if(pos == len){
				if(ret < pos - ix) ret = pos - ix;
				ix = pos;
			}
		}
		return ret;
    }

    public int lengthOfLongestSubstring(String s) {
		HashMap<Character, Integer> hash = new HashMap<Character, Integer>();
		int ret = 0, len = s.length(), left = 0;
		for(int pos = 0; pos != len; ++pos){
			if(hash.containsKey(s.charAt(pos)))
				left = Math.max(left, hash.get(s.charAt(pos)) + 1);
			hash.put(s.charAt(pos), pos);
			if(ret < pos - left + 1) ret = pos - left + 1;
		}
		return ret;
    }
}
