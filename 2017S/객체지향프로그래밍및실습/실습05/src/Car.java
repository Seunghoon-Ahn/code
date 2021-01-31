
public class Car {
	int maxSpeed;
	int speed;
	
	Car(int maxSpeed){
		this.maxSpeed = maxSpeed;
	}
	void speedUp() {
		speed+=5;
		speedprint();
	}
	void speedUp(int spd){
		if(spd < 0) {
			System.out.print("ȣ�� : ���� : �ӵ��� ������ 0���� ���� : ");
			spd = 0;
			speedUp(spd);
		}
		else if((this.speed+spd)>maxSpeed){
			System.out.print("ȣ�� : �ִ�ӵ����� ���� �ִ�ӵ��� ���� : ");
			this.speed = maxSpeed;
			speedprint();
		}
		else{
			speed+=spd;
			speedprint();
		}
		
	}
	void speedDown() {
		speed-=5;
		speedprint();
	}
	void speedDown(int spd){
		if(spd < 0) {
			System.out.print("ȣ�� : ���� : �ӵ��� ������ 0���� ���� : ");
			spd = 0;
			speedDown(spd);
		}
		else if((this.speed-spd)<0){
			System.out.print("ȣ�� : �ӵ��� 0���� ������ 0���� ���� : ");
			this.speed = 0;
			speedprint();
		}
		else{
			speed-=spd;
			speedprint();
		}
		
	}
	
	void speedprint(){
		System.out.println("ȣ�� : �ִ�ӵ� : "+this.maxSpeed+", ����ӵ� : "+this.speed);
	}
	
	public static void main(String[] args) {
		Car mycar = new Car(300);
		mycar.speedUp();
		mycar.speedUp();
		mycar.speedUp(-50);
		mycar.speedUp(50);
		mycar.speedDown(-30);
		mycar.speedDown(30);
		mycar.speedDown(30);
		mycar.speedDown(30);
		mycar.speedUp(100);
		mycar.speedUp(300);
		mycar.speedDown();
	}
}
