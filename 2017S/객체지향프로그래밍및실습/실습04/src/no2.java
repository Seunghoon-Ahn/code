public class no2 {
	public static void main(String[] args) {
		int[] prime = new int[1001];
		int cnt = 0;
		for( int i = 2;i<1001;i++) {
			prime[i-1] = 1;
		}
		for( int i = 2; i <=Math.sqrt(1000);i++) {
			for(int j = i+i ; j< 1000 ; j += i) {
				prime[j-1] = 0;
			}
		}
		for(int i = 1;i < 1000;i++)
		if(prime[i] == 1){
			System.out.print((i+1)+" ");
			cnt++;
			if(cnt % 20 == 0)
				System.out.println();
		}
	}
}
