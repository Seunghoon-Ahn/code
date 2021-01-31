import java.util.*;

public class no4 {
	public static void main(String[] args) {
		int[] ary1 = new int [10];
		int tmp = 0;
		int i, j = 0;
		Scanner s = new Scanner(System.in);
		System.out.println("Input : ");
		for(i=0;i<10;i++)
			ary1[i] = s.nextInt();
		tmp = ary1[0];
		j = 9;
		Arrays.sort(ary1);
		/*while((0 != j)&&(ary1[j-1]>tmp)) {
			ary1[j] = ary1[j-1];
			--j;
		}
		ary1[j]=tmp;
	*/
	for(i = 0; i<10;i++)
		System.out.print(ary1[i]+" ");
	}
}
