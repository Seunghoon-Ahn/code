public class no5 {

		public static void main ( String args [] )
		{
			String str [] = { " 박수 한 번" , " 박수 두 번" } ;
			int iRes = 0 ;
			int iNum = 0 ;
			int iNumberOf369 = 0 ;
			
			
			for ( int i = 1 ; i < 100 ; ++i )
			{
				iNum = i ;
				
				
				for ( iRes = iNum % 10 ; iNum > 0 ; iRes = iNum )
				{
					if (  ( 3 == iRes ) || ( 6 == iRes ) || ( 9 == iRes ) )
						++ iNumberOf369 ;
					
					iNum /= 10 ;
				}
				if ( iNumberOf369 > 0 )
				{
					System.out.println ( i + str [ iNumberOf369 - 1 ] ) ;
				}
				
				iNumberOf369 = 0 ;
			}
		}
	}