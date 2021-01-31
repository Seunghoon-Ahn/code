
public class Complex {
	double a;
	double b;
	Complex() {
		this.a = 0;
		this.b = 0;
	}
	
	Complex(double a, double b) {
		this.a=a;
		this.b=b;
	}
	static Complex add(Complex c1, Complex c2) {
		Complex res = new Complex(c1.a+c2.a, c1.b+c2.b);
		return res;
	}
	static Complex sub(Complex c1, Complex c2) {
		Complex res = new Complex(c1.a-c2.a, c1.b-c2.b);
		return res;
	}
	double abs() {
		return Math.sqrt((this.a)*(this.a)+(this.b)*(this.b));
	}
	void print() {
		System.out.println(this.a+" + "+this.b+" i");
	}
	public static void main(String[] args) {
		Complex x = new Complex(3.4, 4.5);
		Complex y = new Complex(5.2, -2.4);
		System.out.print("x ���Ҽ� : ");		
		x.print();
		System.out.print("y ���Ҽ� : ");
		y.print();
		double abs1, abs2;
		System.out.print("���Ҽ��� �� : ");
		Complex.add(x, y).print();
		System.out.print("���Ҽ��� �� : ");
		Complex.sub(x, y).print();
		System.out.print("x�� y�� ���� : ");
		abs1 = x.abs();
		abs2 = y.abs();
		System.out.print(abs1 + ",  "+abs2);		
	}
}
