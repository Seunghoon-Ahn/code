public class Cylinder {
	Circle circle;
	double h;
	
	public Cylinder(Circle circle, double h)
	{
		this.circle = circle;
		this.h = h;
	}
	
	public Cylinder(double radius, double h)
	{
		this.circle = new Circle(radius);
		this.h = h;
	}
	
	public double getVolume()
	{
		return circle.getArea() * this.h;
	}
	
	public static void main(String[] args) {
		Circle ci = new Circle(2.8);
		Cylinder cy1 = new Cylinder(ci, 5.6);
		System.out.println("생성자 1 사용 : 실린더 1 부피 : " + cy1.getVolume());
		
		Cylinder cy2 = new Cylinder(2.8, 5.6);
		System.out.println("생성자 2 사용 : 실린더 2 부피 : " + cy2.getVolume());
		
	}

}

