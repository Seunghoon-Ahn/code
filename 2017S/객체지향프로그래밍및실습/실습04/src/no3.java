public class no3 {
	public static void main(String[] args) {
		int ary[][];
		ary = new int[10][];
		for(int i = 1; i <= 10;i++) {
			ary[i-1] = new int[i]; 
		}
		for(int i = 0; i < 10;i++) {
			for(int j = 0; j <= i;j++) {
				ary[i][j] = fact(i)/(fact(j)*fact(i-j));
			}
		}
		
		for(int i = 0; i < 10; i++) {
			for(int j = 0; j<=i;j++) {
				System.out.printf("%5d",ary[i][j]);
			}
			System.out.println();
		}
	}

	public static int fact(int n) {
		if (n <= 1)
			return 1;
		else 
			return fact(n-1) * n;
	}
}
