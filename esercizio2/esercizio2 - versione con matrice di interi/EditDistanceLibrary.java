public class EditDistanceLibrary {
  
  /**
   * returns the least number of operations necessary 
   * to transform the string s2 into the string s1.
   * Warning: This function is not optimized to solve problems 
   * with strings longer than 5 characters, for this reason 
   * it is highly recommended to use the EditDistanceApp function
   * @return Integer
   */
  public static int editDistance(final String s1, final String s2) {
    int dNoOp, dInsertion, dDelete;
    String restS1, restS2;
    
    if(s1==null || s2==null) return -1;
    if (s1.length() == 0) return s2.length();
    else if (s2.length() == 0) return s1.length();
    
    restS1 = s1.substring(1);
    restS2 = s2.substring(1);

    if (s2.charAt(0) == s1.charAt(0))
      dNoOp = editDistance(restS1, restS2);
    else
      dNoOp = Integer.MAX_VALUE;
    dInsertion = 1 + editDistance(restS1, s2);
    dDelete = 1 + editDistance(s1, restS2);

    return Integer.min(Integer.min(dNoOp, dInsertion), dDelete);
  }
  
  /**
   * returns the least number of operations necessary 
   * to transform the string s2 into the string s1.
   * it needs an int matrix sized like this, [s1.length () + 1] [s2.length () + 1]. 
   * The function uses this matrix to derive the result previously saved by other 
   * recursive method calls on the same arguments.
   * @return Integer
   */
  public static int editDistanceDyn(final String s1, final String s2, int [][] memory) {
    int dNoOp, dInsertion, dDelete;
    String restS1, restS2;
    
    if (s1.length() == 0) return s2.length();
    else if (s2.length() == 0) return s1.length();
    
    restS1 = s1.substring(1);
    restS2 = s2.substring(1);

    if (s2.charAt(0) == s1.charAt(0)) 
    {
      if(memory[restS1.length()][restS2.length()] == -1) 
        memory[restS1.length()][restS2.length()] = editDistanceDyn(restS1, restS2, memory);
      
      dNoOp =memory[restS1.length()][restS2.length()];
    } 
    else
    {
      dNoOp = Integer.MAX_VALUE;
    }
    
    if(memory[restS1.length()][s2.length()] == -1) 
      memory[restS1.length()][s2.length()] = 1 + editDistanceDyn(restS1, s2, memory);

    dInsertion = memory[restS1.length()][s2.length()]; 

    if(memory[s1.length()][restS2.length()] == -1)
      memory[s1.length()][restS2.length()] = 1 + editDistanceDyn(s1, restS2, memory);
    
    dDelete = memory[s1.length()][restS2.length()];

    return Integer.min(Integer.min(dNoOp, dInsertion), dDelete);
  }

  /**
   * returns the least number of operations necessary 
   * to transform the string s2 into the string s1.
   * @return Integer
   */
  public static int editDistanceApp(String s1, String s2) {
    int retvalue;

    if(s1==null || s2==null) return -1;
    else if (s1.length() == 0) return s2.length();
    else if (s2.length() == 0) return s1.length();
    else {
      int[][] memory = new int[s1.length()+1][s2.length()+1];
  
      for(int i=0; i<=s1.length(); i++)
        for(int j=0; j<=s2.length(); j++)
        {
          memory[i][j] = -1;
        }        
      
      retvalue = editDistanceDyn(s1, s2, memory);
  
      return retvalue;
    }
  }
 
}
