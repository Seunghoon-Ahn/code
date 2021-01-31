
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
			System.out.print("호출 : 오류 : 속도가 음수라 0으로 지정 : ");
			spd = 0;
			speedUp(spd);
		}
		else if((this.speed+spd)>maxSpeed){
			System.out.print("호출 : 최대속도보다 높아 최대속도로 지정 : ");
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
			System.out.print("호출 : 오류 : 속도가 음수라 0으로 지정 : ");
			spd = 0;
			speedDown(spd);
		}
		else if((this.speed-spd)<0){
			System.out.print("호출 : 속도가 0보다 낮아져 0으로 지정 : ");
			this.speed = 0;
			speedprint();
		}
		else{
			speed-=spd;
			speedprint();
		}
		
	}
	
	void speedprint(){
		System.out.println("호출 : 최대속도 : "+this.maxSpeed+", 현재속도 : "+this.speed);
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
