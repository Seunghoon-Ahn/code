import java.io.*;


public class no2 {

	public static void main(String[] args) {
		InputStreamReader rd = new InputStreamReader(System.in);
		char c = 0;
		int i, j = 0;
		System.out.println("Input one alphabet : ");
		try{
			c =(char)rd.read();
		}catch (IOException e) {
			System.out.println("Ű���� �Է� �� ������ �߻��߽��ϴ�\n");
		}
		for(char cLow = 'a';cLow <= c;--c) {
			for(char cTmp = cLow; cTmp <= c;cTmp++) {
				System.out.print(cTmp);
			}
			System.out.println();
		}
	}
}
