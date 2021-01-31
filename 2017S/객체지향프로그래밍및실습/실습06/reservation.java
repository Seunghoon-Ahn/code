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
				System.out.println("이름을 입력하세요 : ");
				Scanner s = new Scanner(System.in);
				String name = s.next();
				
				for(int i = 0; i < 3;i++){
					for( int j = 0; j < 10; j++){
						if(seat[i][j].equals(name)){
							System.out.println("이미 예약된 사람입니다");
							check = 0;
							break;
						}
					}
				}
				if(check == 0) break;
				
				System.out.println("좌석유형 선택   1) S석  2) A석  3) B석   ");
				s = new Scanner(System.in);
				int seattype = s.nextInt();
				if (seattype == 1) { // S석
					while (true) {
						try {
							System.out.println("좌석번호를 선택하세요.");
							System.out.print("[S석]");
							for (int i = 0; i < 10; i++) {
								System.out.print("[" + (i + 1) + "]" + seat[0][i]);
							}
							System.out.println(" ");
							s = new Scanner(System.in);
							int seatpos = s.nextInt();
							if (seat[0][seatpos - 1] == "---") {
								seat[0][seatpos - 1] = name;
								System.out.println("예약 완료");
								check = 0;
								break;
							} else {
								System.out.println("예약불가능한 자리입니다. 다시 선택하세요.");
							}
						} catch (ArrayIndexOutOfBoundsException e) {
							System.out.println("잘못된 입력입니다. 다시 입력하세요.");
						}
					}
				} else if (seattype == 2) {
					while (true) {// A석
						try {
							System.out.println("좌석번호를 선택하세요.");
							System.out.print("[A석]");
							for (int i = 0; i < 10; i++) {
								System.out.print("[" + (i + 1) + "]" + seat[1][i]);
							}
							s = new Scanner(System.in);
							int seatpos = s.nextInt();
							if (seat[1][seatpos - 1] == "---") {
								seat[1][seatpos - 1] = name;
								System.out.println("예약 완료");
								check = 0;
								break;
							} else {
								System.out.println("예약불가능한 자리입니다. 다시 선택하세요.");
							}
						} catch (ArrayIndexOutOfBoundsException e) {
							System.out.println("잘못된 입력입니다. 다시 입력하세요.");
						}
					}
				} else if (seattype == 3) { // B석
					while (true) {
						try {
							System.out.println("좌석번호를 선택하세요.");
							System.out.print("[B석]");
							for (int i = 0; i < 10; i++) {
								System.out.print("[" + (i + 1) + "]" + seat[2][i]);
							}
							s = new Scanner(System.in);
							int seatpos = s.nextInt();
							if (seat[2][seatpos - 1] == "---") {
								seat[2][seatpos - 1] = name;
								System.out.println("예약 완료");
								check = 0;
								break;
							} else {
								System.out.println("예약불가능한 자리입니다. 다시 선택하세요.");
							}
						} catch (ArrayIndexOutOfBoundsException e) {
							System.out.println("잘못된 입력 \t 다시 입력하세요");
						}
					}
				} 
				else System.out.println("다시 입력");
			} 
		}

	public void confirm() { // 조회
		for (int i = 0; i < 3; i++) {
			if (i == 0) {
				System.out.print("[S석] ");
			}
			else if (i == 1) {
				System.out.print("[A석] ");
			}
			else if (i == 2) {
				System.out.print("[B석] ");
			}
			for (int j = 0; j < 10; j++) {
				System.out.print( "  " + seat[i][j] + "  ");
			}
			System.out.println(" ");
		}
	}

	public void cancel() { // 취소
		while (true) {
			try {
				System.out.println("취소할 좌석타입을 선택하세요.  1) S석  2) A석  3) B석");
				Scanner s = new Scanner(System.in);
				int seattype = s.nextInt();
				for (int i = 0; i < 10; i++) {
					System.out.print("  " + seat[seattype - 1][i] + "  ");
				}
				System.out.println(" ");
				System.out.println("취소할 이름를 선택하세요.");

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
						System.out.println("취소 완료");
						break;
					}
					else {
						System.out.println("이미 빈 자리 입니다.");
						continue;
					}
				}
				else {
					System.out.println("잘못된 입력입니다.");
				}
			} 
			catch (ArrayIndexOutOfBoundsException e) {
				System.out.println("잘못된 입력입니다. 다시 입력하세요.");
			}
		}
	}

	boolean checkName(String name) { // 입력받은 이름으로 예약된 좌석이 있는지 확인
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
			System.out.println("1) 예약 2) 조회 3) 취소 4) 종료");
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
				System.out.println("종료");
				System.exit(0);
			} else {
				System.out.println("잘못입력하셨습니다.");
			}
		}
	}
}
