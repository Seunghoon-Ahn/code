import java.util.Scanner;
public class no3 {

	public static void main(String[] args) {
		int val1,val2;
        int GCD=1;
        
        Scanner sc = new Scanner(System.in);
        
        System.out.print("ù��° ���� �Է��Ͻÿ� : ");
        val1 = sc.nextInt();
        System.out.print("�ι�° ���� �Է��Ͻÿ� : ");
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
         System.out.println("�ִ����� : "+ val1);
    }
}