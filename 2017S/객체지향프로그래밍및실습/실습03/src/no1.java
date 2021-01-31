import java.util.Scanner;

public class no1 {

	public static void main(String[] args) {
		final int px1 = 50;
		final int py1 = 50;
		final int px2 = 100;
		final int py2 = 100;
		
		int x1, y1, x2, y2 = 0;
		System.out.println("(x1, y1), (x2, y2)의 좌표를 입력하시오 :");
		Scanner num = new Scanner(System.in);
		x1 = num.nextInt();
		y1 = num.nextInt();
		x2 = num.nextInt();
		y2 = num.nextInt();
		
		if((x1<=px1)&&(y1<= py1)&&(x2>=px1)&&((y2>=py1)&&(y2<=py2)))
			System.out.println("사각형이 겹칩니다\n");
		else if((x1>=px1)&&(y1<=py1)&&(x2>=px1)&&(y2>=py1))
			System.out.println("사각형이 겹칩니다\n");
		else if((x1>=px1&&x1<=px2)&&(y1>=py1&&y1<=py2)&&(x2<=px1&&x2>=px2)&&(y2<=py1&&y2>=py2))
			System.out.println("사각형이 겹칩니다\n");
		else if((x1>=px1&&x1<=px2)&&(y1>=py1&&y2<=py2)&&(x2>=px1))
			System.out.println("사각형이 겹칩니다\n");
		else
			System.out.println("사각형이 겹치지 않습니다\n");	
		}
	}
