import java.util.Scanner;
public class no3 {

	public static void main(String[] args) {
		int val1,val2;
        int GCD=1;
        
        Scanner sc = new Scanner(System.in);
        
        System.out.print("첫번째 수를 입력하시오 : ");
        val1 = sc.nextInt();
        System.out.print("두번째 수를 입력하시오 : ");
        val2 = sc.nextInt();
        
        int tmp1=val1,tmp2=val2;
        if(val1<val2){ 
            val1 = tmp2;
            val2 = tmp1;
         }
 
         while(GCD>0){
             GCD = val1 % val2;
             val1 = val2;
             val2 = GCD;
          }
         System.out.println("최대공약수 : "+ val1);
    }
}