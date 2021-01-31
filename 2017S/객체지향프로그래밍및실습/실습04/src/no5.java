import java.util.*;

public class no5 {
	public static void main(String[] args) {
		
		int[][] ary = new int [4][4];
			
		for(int cnt = 0; cnt< 10 ; cnt++) {
		int i = (int)Math.round(Math.random()* 3);
		int j = (int)Math.round(Math.random() * 3);
		int num = (int)Math.round(Math.random() * 9 + 1);
		ary[i][j] = num;
		}
		for( int i = 0; i<4;i++) {
			for (int j = 0; j < 4; j++) {
				System.out.print(ary[i][j]+" ");
			}
			System.out.println();
		}
		
	}
}
