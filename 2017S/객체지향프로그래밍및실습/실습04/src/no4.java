import java.util.*;

public class no4 {
	public static void main(String[] args) {
		String[] h2b = {"0000", "0001", "0010", "0011", 
				"0100", "0101", "0110", "0111", 
				"1000", "1001", "1010", "1011", 
				"1100", "1101", "1110", "1111"};
		Scanner s = new Scanner(System.in);
		char cHex[] = null;
		String stmp;
		System.out.println("16���� ���ڿ� �Է� : ");
		stmp = s.nextLine();
		cHex = stmp.toCharArray();
		System.out.println(stmp + "�� ��������");
		
		for(int i = 0;i < cHex.length;i++) {
			if((cHex[i] >= '0') && (cHex[i] <= '9'))
				System.out.printf("%5s", h2b[cHex[i] - '0']);
			else if ((cHex[i] >= 'a')&&(cHex[i] <= 'f'))
				System.out.printf("%5s", h2b[cHex[i] - 'a'+10]);
			else
				System.out.print("Error!!");
		}
	}
}
