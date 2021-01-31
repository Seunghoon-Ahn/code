public class Rectangle {
	int x1, y1, x2, y2;
	Rectangle() {
		this.x1 = 0;
		this.y1 = 0;
		this.x2 = 0;
		this.y2 = 0;
	}
	Rectangle(int x1, int y1, int x2, int y2){
		this.x1 = x1;
		this.y1 = y1;
		this.x2 = x2;
		this.y2 = y2;
	}
	void set(int x1, int y1, int x2, int y2) {
		this.x1 = x1;
		this.y1 = y1;
		this.x2 = x2;
		this.y2 = y2;
	}
	int square() {
		int row, column;
		row = Math.abs(x2 - x1);
		column = Math.abs(y2 - y1);
		return row * column;
	}
	void show() {
		System.out.println("대각선 두 점의 좌표 : ("+x1+","+y1+") ("+x2+","+y2+")");
		System.out.println("넓이 : "+square());
	}
	boolean equals(Rectangle r) {
		if(r.square()==this.square())
			return true;
		else
			return false;
	}
	public static void main(String[] args) {
		Rectangle r = new Rectangle();
		Rectangle s = new Rectangle(1, 1, 2, 3);
		
		r.show();
		s.show();
		System.out.println(s.square());
		r.set(-2, 2, -1, 4);
		r.show();
		System.out.println(r.square());
		if(r.equals(s))
			System.out.println("두 사각형은 같습니다.");
	}
}
