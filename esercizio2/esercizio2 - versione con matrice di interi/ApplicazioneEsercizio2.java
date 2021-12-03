import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Collections;

/**
 * This class is an application of how the editDistance function can be used to find, 
 * given a lexically incorrect text, a pool of words that come closest to the incorrect word, 
 * using a vocabulary given as input to the program.
 * Created by the developers Samuel Girardello & Marius Berinde.
 */
class ApplicazioneEsercizio2 {
  public static void main(String [] args) throws FileNotFoundException {
    System.out.println("\n\n\n\n|| Edit distance application ||\n|| Created by S.G. and M.B.  ||\n\n\n\n");
    System.out.println("Please insert the name of .txt file with contain the text: ");

    Scanner pathReader = new Scanner(System.in);
    String pathNameFile = pathReader.nextLine();
    
    System.out.println("Now insert the name of .txt file with contain the dictionary:");
    String pathNameDictionary = pathReader.nextLine();

    System.out.println("\n\n---------------------------------");
    System.out.print("initialization in progress...");
    
    File textFile = new File(pathNameFile);
    File dictionaryFile = new File(pathNameDictionary);

    Scanner textReader = new Scanner(textFile);
    Scanner dictionaryReader = new Scanner(dictionaryFile);

    textReader.useDelimiter("[^A-Za-z]+");
    dictionaryReader.useDelimiter("[^A-Za-z]+");
    
    ArrayList<String> sentenceList = new ArrayList<String>();
    ArrayList<String> dictionaryList = new ArrayList<String>();
    
    while (textReader.hasNextLine() && textReader.hasNext())
      sentenceList.add(textReader.next().toLowerCase());  
    
    while (dictionaryReader.hasNextLine() && dictionaryReader.hasNext())
      dictionaryList.add(dictionaryReader.next().toLowerCase());

    ArrayList<Integer> editDistance = new ArrayList<Integer>();

    System.out.print("DONE\n");
    System.out.println("---------------------------------\n\n");

    long startTime = System.nanoTime();

    for(int i=0; i<sentenceList.size(); i++) {
      for(int j=0; j<dictionaryList.size(); j++)
        editDistance.add(EditDistanceLibrary.editDistanceApp(sentenceList.get(i), dictionaryList.get(j)));

      int minEditDistance = Collections.min(editDistance);
      
      if(minEditDistance == 0) {
        System.out.println("The word <" + sentenceList.get(i) + "> appears in the vocabulary\n");
      } else {
        System.out.print("List of words with minor editDistance (equal to " + minEditDistance + ") for the word <" + sentenceList.get(i) + ">:");
        for(int z = 0; z < editDistance.size(); z++) {
          if(editDistance.get(z) == minEditDistance) {
            System.out.print("\n  -> " + dictionaryList.get(z));
          }
        }
        System.out.println("\n");
      }

      editDistance.clear();
    }
    long endTime = System.nanoTime();
    long elapsedTime = endTime - startTime;

    pathReader.close();
    textReader.close();
    dictionaryReader.close();

    System.out.println("\n\n----------------------------------------------------------------------------------------------");
    System.out.println("Analyzed a text of "+ sentenceList.size() +" words referring to a dictionary of "+ dictionaryList.size() +" words in a time of "+ elapsedTime/1000000000 +" seconds");
    System.out.println("----------------------------------------------------------------------------------------------\n\n");
    sentenceList.clear();
    dictionaryList.clear();

    System.out.println("\n\n||    CORRECTION COMPLETE    ||\n|| Created by S.G. and M.B.  ||\n\n\n\n\n");

  }

}
