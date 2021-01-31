class CPoint {
	int a, b;
	public CPoint(int a, int b) {
		this.a = a;
		this.b = b;
	}
	void show() {
		System.out.println( "(" + a + " , " + b + ")" );
	}
	public String toString() {
		return "(" + a + " , " + b + ") ¿‘¥œ¥Ÿ."; 
	}
}
class CColorPoint extends CPoint {
	String color;
	public CColorPoint(int a, int b, String color) {
		super(a, b);
		this.color = color;
	}
	void show() {
		System.out.println("(" + a + " , " + b + " , " + color + ")");
	}
}

public class no2 {
	public static void main(String[] args) {
		CPoint a, b;
		a = new CPoint(2, 3);
		b = new CColorPoint(3, 4, "red");
		a.show();
		b.show();
		System.out.println(a);
		System.out.println(b);
	}
}