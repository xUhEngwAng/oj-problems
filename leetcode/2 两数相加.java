/*
 * 不过是链表版本的大数加法，可是我却 debug 了半天，究其原因还
 * 是对 java 的指针（reference variable）操作不熟悉。
 *
 * 我是定义了一个结果链表 ret，以及当前的工作指针 curr，并且令
 * curr = ret.next，表示下一位数的位置。在计算出它的值后，通过
 * curr = new ListNode(res) 为其分配存储空间，出错也就是在这里。
 * 该操作确实使得 curr 变量指向了新分配的对象，然而 ret.next 
 * 仍然是一个空指针。
 *
 * 解决方案是，初始化 curr = ret，通过
 * curr.next = new ListNode(res) 添加每一位数，可以使得每个节
 * 点被成功链接起来，最后返回 ret.next 即可。
 */

public class ListNode{
	int val;
	ListNode next;
	ListNode(int x){ val = x;}
}

public Solution{
	public ListNode addTwoNumbers(ListNode l1, ListNode l2){
		int one, two;
		int carry = 0, res;
		ListNode ret = new ListNode(0), curr = ret;
		while(l1 != null || l2 != null){
			if(l1 == null) one = 0;
			else one = l1.val;
			if(l2 == null) two = 0;
			else two = l2.val;
			res = one + two + carry;
			carry = res / 10;
			res = res - 10 * carry;
			curr.next = new ListNode(res);
			if(l1 != null) l1 = l1.next;
			if(l2 != null) l2 = l2.next;
			curr = curr.next;
		}
		if(carry == 1) curr.next = new ListNode(carry);
		return ret.next;
	}
}
