public class ArrayUtility2 {
	static int[] concat(int[] s1, int[] s2) {
		int[] concatAry = new int[s1.length + s2.length];
		for (int i = 0; i < s1.length; i++)
			concatAry[i] = s1[i];
		for (int i = 0; i < s2.length; i++)
			concatAry[s1.length + i] = s2[i];
		return concatAry;
	}

	static int[] remove(int[] s1, int[] s2) {
		int [] temp = new int[s1.length];
		boolean btemp = false;
		int num = 0;
		for(int i=0; i<s1.length; i++){
			for(int j=0; j<s2.length; j++){
				if(s1[i]==s2[j]) {
					btemp = false;
					break;
				}
				else {
					btemp = true;
				}
			}
			if(btemp == true) {
				temp[num++] = s1[i];
				btemp = false;
			}
		}
		int []ary = new int[num];
		for(int i=0; i<ary.length; i++)
			ary[i] = temp[i];
		return ary;
	}

	public static void main(String[] args) {
		int[] ary1 = { 2, 2, 3, 1, 7 };
		int[] ary2 = { 2, 5, 1, 8};
		int [] aryConcat = new int [ary1.length + ary2.length];
		
		System.out.println("초기의 배열 2개 : ");
		System.out.print("배열 1 : ");
		for(int i=0; i<ary1.length; i++)
			System.out.print(ary1[i]+"    ");
		System.out.print("\n배열 2 : ");
		for(int i=0; i<ary2.length; i++)
			System.out.print(ary2[i]+"    ");
		System.out.println();
		aryConcat = ArrayUtility2.concat(ary1, ary2);
		System.out.println("concat 메소드 테스트");
		for(int i=0; i<aryConcat.length; i++)
			System.out.print(aryConcat[i]+"    ");
		System.out.println();
		
		int len = ArrayUtility2.remove(ary1, ary2).length;
		int [] aryRemove = new int [len];
		aryRemove =  ArrayUtility2.remove(ary1, ary2);
		System.out.println("remove 함수 테스트");
		for(int i=0; i<aryRemove.length; i++)
			System.out.print(aryRemove[i]+"    ");
	}
}
