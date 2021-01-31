import java.util.*;
class Conduction {
	String[][] seat = new String[3][10];
	public Conduction() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 10; j++) {
				seat[i][j] = "---";
			}
		}
	}
	public void reserve() {

		int check = 1;
		while (check == 1) {
				System.out.println("�̸��� �Է��ϼ��� : ");
				Scanner s = new Scanner(System.in);
				String name = s.next();
				
				for(int i = 0; i < 3;i++){
					for( int j = 0; j < 10; j++){
						if(seat[i][j].equals(name)){
							System.out.println("�̹� ����� ����Դϴ�");
							check = 0;
							break;
						}
					}
				}
				if(check == 0) break;
				
				System.out.println("�¼����� ����   1) S��  2) A��  3) B��   ");
				s = new Scanner(System.in);
				int seattype = s.nextInt();
				if (seattype == 1) { // S��
					while (true) {
						try {
							System.out.println("�¼���ȣ�� �����ϼ���.");
							System.out.print("[S��]");
							for (int i = 0; i < 10; i++) {
								System.out.print("[" + (i + 1) + "]" + seat[0][i]);
							}
							System.out.println(" ");
							s = new Scanner(System.in);
							int seatpos = s.nextInt();
							if (seat[0][seatpos - 1] == "---") {
								seat[0][seatpos - 1] = name;
								System.out.println("���� �Ϸ�");
								check = 0;
								break;
							} else {
								System.out.println("����Ұ����� �ڸ��Դϴ�. �ٽ� �����ϼ���.");
							}
						} catch (ArrayIndexOutOfBoundsException e) {
							System.out.println("�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.");
						}
					}
				} else if (seattype == 2) {
					while (true) {// A��
						try {
							System.out.println("�¼���ȣ�� �����ϼ���.");
							System.out.print("[A��]");
							for (int i = 0; i < 10; i++) {
								System.out.print("[" + (i + 1) + "]" + seat[1][i]);
							}
							s = new Scanner(System.in);
							int seatpos = s.nextInt();
							if (seat[1][seatpos - 1] == "---") {
								seat[1][seatpos - 1] = name;
								System.out.println("���� �Ϸ�");
								check = 0;
								break;
							} else {
								System.out.println("����Ұ����� �ڸ��Դϴ�. �ٽ� �����ϼ���.");
							}
						} catch (ArrayIndexOutOfBoundsException e) {
							System.out.println("�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.");
						}
					}
				} else if (seattype == 3) { // B��
					while (true) {
						try {
							System.out.println("�¼���ȣ�� �����ϼ���.");
							System.out.print("[B��]");
							for (int i = 0; i < 10; i++) {
								System.out.print("[" + (i + 1) + "]" + seat[2][i]);
							}
							s = new Scanner(System.in);
							int seatpos = s.nextInt();
							if (seat[2][seatpos - 1] == "---") {
								seat[2][seatpos - 1] = name;
								System.out.println("���� �Ϸ�");
								check = 0;
								break;
							} else {
								System.out.println("����Ұ����� �ڸ��Դϴ�. �ٽ� �����ϼ���.");
							}
						} catch (ArrayIndexOutOfBoundsException e) {
							System.out.println("�߸��� �Է� \t �ٽ� �Է��ϼ���");
						}
					}
				} 
				else System.out.println("�ٽ� �Է�");
			} 
		}

	public void confirm() { // ��ȸ
		for (int i = 0; i < 3; i++) {
			if (i == 0) {
				System.out.print("[S��] ");
			}
			else if (i == 1) {
				System.out.print("[A��] ");
			}
			else if (i == 2) {
				System.out.print("[B��] ");
			}
			for (int j = 0; j < 10; j++) {
				System.out.print( "  " + seat[i][j] + "  ");
			}
			System.out.println(" ");
		}
	}

	public void cancel() { // ���
		while (true) {
			try {
				System.out.println("����� �¼�Ÿ���� �����ϼ���.  1) S��  2) A��  3) B��");
				Scanner s = new Scanner(System.in);
				int seattype = s.nextInt();
				for (int i = 0; i < 10; i++) {
					System.out.print("  " + seat[seattype - 1][i] + "  ");
				}
				System.out.println(" ");
				System.out.println("����� �̸��� �����ϼ���.");

				s = new Scanner(System.in);
				String seatname = s.next();
				int seatpos = 0;
				for(int i = 0;i < seat[seattype - 1].length;i++){
					if(seat[seattype - 1][i].equals(seatname))
						seatpos = i+1;
				}
				if (seatpos >= 1 && seatpos <= 10) {
					if (seat[seattype - 1][seatpos - 1] != "---") {
						seat[seattype - 1][seatpos - 1] = "---";
						System.out.println("��� �Ϸ�");
						break;
					}
					else {
						System.out.println("�̹� �� �ڸ� �Դϴ�.");
						continue;
					}
				}
				else {
					System.out.println("�߸��� �Է��Դϴ�.");
				}
			} 
			catch (ArrayIndexOutOfBoundsException e) {
				System.out.println("�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.");
			}
		}
	}

	boolean checkName(String name) { // �Է¹��� �̸����� ����� �¼��� �ִ��� Ȯ��
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 10; j++) {
				if (seat[i][j].equals(name)) {
					return false;
				} else {
					return true;
				}
			}
		}
		return true;
	}
}

public class reservation {
	public static void main(String[] args) {
		Conduction c = new Conduction();
		int menuNum;

		while (true) {
			System.out.println("1) ���� 2) ��ȸ 3) ��� 4) ����");
			Scanner main_s = new Scanner(System.in);
			menuNum = main_s.nextInt();
			if (menuNum == 1 || menuNum == 2 || menuNum == 3) {
				switch (menuNum) {
				case 1:
					c.reserve();
					break;
				case 2:
					c.confirm();
					break;
				case 3:
					c.cancel();
					break;
				}
			} else if (menuNum == 4) {
				System.out.println("����");
				System.exit(0);
			} else {
				System.out.println("�߸��Է��ϼ̽��ϴ�.");
			}
		}
	}
}
