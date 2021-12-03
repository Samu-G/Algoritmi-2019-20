import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
public class usoScanner {
  public static void main(String[] args) {
    String nome_file="dictionary.txt";
    int nr_righe=count_rows(nome_file);
    String[] file=new String[nr_righe];
    file=read_file(nome_file);
    String nome_file1="correctme.txt";
    int nr_righe1=count_rows(nome_file1);
    String[] sentence=new String[nr_righe1];
    sentence=read_file(nome_file1);
    String[] errori=wrong_words(sentence[0],file);
    System.out.println("lista parole errate grammaticalmente:");
    for(int i=0;i<errori.length;System.out.println(errori[i]),i++);
  }

  /**
   * 
   * @param file_name il nome del file in cui contare le righe
   * @return il numero di righe di file_name
   */

  public static int count_rows(String file_name){
    Scanner inputStream=null;
    String riga;
    int i=0;
   // System.out.println("tento di aprire e leggere il file");
    try {
      inputStream=new Scanner(new File(file_name));
    } catch (FileNotFoundException e) {

      System.out.println("errorre nell'apertura di mini.txt");
      System.exit(0);
    }
    while (inputStream.hasNextLine()) {
      riga=inputStream.nextLine();
      i++;
    }
    inputStream.close();
    return i;
  }
  
  /**
   *  
   * @param file_name the name of the file that you want to read
   * @return 
   */
  public static String[] read_file(String file_name){
    Scanner inputStream=null;
    String[] riga=new String[count_rows(file_name)];
    int i=0;
    System.out.println("tento di aprire e leggere il file");
    try {
      inputStream=new Scanner(new File(file_name));
    } catch (FileNotFoundException e) {

      System.out.println("errorre nell'apertura di mini.txt");
      System.exit(0);
    }
    while (inputStream.hasNextLine()) {
      riga[i++]=inputStream.nextLine();
    }
    inputStream.close();
    return riga;
  }
  /**
   * 
   * @param sentence   contains the sentence that you nedd you analize
   * @param dictionary
   * @return the errors of the sentence
   */
  public static String[] wrong_words(String sentence,String[] dictionary){
    sentence=sentence.replaceAll(",","");
    sentence=sentence.replaceAll(":","");
    sentence=sentence.replaceAll("\\.","");
    sentence=sentence.toLowerCase();
    String[] words=sentence.split(" ");
    int nr_error_word=0;
    for(int i=0;i<words.length;i++){
      if(Arrays.binarySearch(dictionary,words[i])<0)
        nr_error_word++;
      } 
    String[] errors=new String[nr_error_word];
    for(int i=0,j=0;i<words.length;i++){
      if(Arrays.binarySearch(dictionary,words[i])<0){
        errors[j]=words[i];
        j++;
      }
    }
    return errors;

  }
}