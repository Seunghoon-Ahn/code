public class no1 {
	public static void main(String[] args) {
		int i[][];
		i = new int [4][];
		i[0] = new int[4];
		i[1] = new int[2];
		i[2] = new int[3];
		i[3] = new int[4];
		
		i[0][0] = 78;
		i[0][1] = 48;
		i[0][2] = 78;
		i[0][3] = 98;
		i[1][0] = 99;
		i[1][1] = 92;
		i[2][0] = 29;
		i[2][1] = 64;
		i[2][2] = 83;
		i[3][0] = 34;
		i[3][1] = 78;
		i[3][2] = 92;
		i[3][3] = 56;
		
		for(int s = 0;s < i.length;s++) {
			int sum = 0;
			for (int k = 0;k < i[s].length; k++) {
				sum += i[s][k];
				System.out.print(i[s][k] + " ");
			}
			int avg = sum / i[s].length;
			System.out.println("        Sum : "+sum+"     Average : "+avg);
		}
	}
}
