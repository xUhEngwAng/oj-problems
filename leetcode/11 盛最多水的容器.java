/*
 * 唉，我再次写了暴力解......遍历了所有可能的组合，时间复杂度
 * 为 O(n^2)，最优解只需要 O(n) 即可。
 *
 * 最优解本质上是做了充分的剪枝。设当前的左右边界分别是 l 和
 * r，更新规则是更低的一边向内收缩。不妨设
 * height[l] < height[r]，容器的容器为 S(l, r)，
 * 则 S(l, r-1), ..., S(l, l+1) 都不可能是最大容积。因为更长
 * 的一边向内收缩后，容器的长度减小，而有效高度不会增加（有效
 * 高度由短边决定），因此容积一定会减小。将这些情况忽略并不会
 * 妨碍我们找到最优解，却可以显著地降低时间复杂度。
 */

class Solution{
	public int maxArea_v1(int[] height) {
		int ret = 0, curr;
		for(int ix = 0; ix != height.length; ++ix)
			for(int jx = ix + 1; jx != height.length; ++jx){
				curr = (jx - ix) * Math.min(height[ix], height[jx]);
				if(ret < curr) ret = curr;
			}
		return ret;
    }

    public int maxArea(int[] height){
    	int l = 0, r = height.length - 1;
    	int max = 0, curr;
    	do{
    		curr = (r - l) * Math.min(height[l], height[r]);
    		if(max < curr) max = curr;
    		if(height[l] < height[r]) l++;
    		else r--;
    	}while(l != r);
    	return max;
    }
}