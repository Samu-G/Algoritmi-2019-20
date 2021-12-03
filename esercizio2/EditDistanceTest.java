import org.junit.Test;

import static org.junit.Assert.*;

/**
 * This class is used for the unit test of the class EditDistance
 * 
 * @author Marius Berinde
 * @author Samuel Girardello
 */

public class EditDistanceTest {

  @Test
  public void editDistanceGreaterLengthTest() {
    int expected, result;

    String s1 = "casa", s2 = "cassa";
    expected = 1;
    result = EditDistanceLibrary.editDistance(s1, s2);
    assertEquals(expected, result);

  }

  @Test
  public void editDistanceLesserLengthTest() {
    int expected, result;

    String s5 = "vinaio", s6 = "vino";
    expected = 2;
    result = EditDistanceLibrary.editDistance(s5, s6);
    assertEquals(expected, result);

  }

  @Test
  public void editDistanceEqualLengthTest() {
    int expected, result;

    String s3 = "casa", s4 = "cara";
    expected = 2;
    result = EditDistanceLibrary.editDistance(s3, s4);
    assertEquals(expected, result);

  }

  @Test
  public void editDistanceEqualWordTest() {
    int expected, result;

    String s9 = "pioppo", s10 = "pioppo";
    expected = 0;
    result = EditDistanceLibrary.editDistance(s9, s10);
    assertEquals(expected, result);

  }

  @Test
  public void editDistanceS1EmptyTest() {
    int expected, result;

    String s1 = "", s2 = "teststring";
    expected = s2.length();
    result = EditDistanceLibrary.editDistance(s1, s2);
    assertEquals(expected, result);

  }

  @Test
  public void editDistanceS2EmptyTest() {
    int expected, result;

    String s3 = "teststring", s4 = "";
    expected = s3.length();
    result = EditDistanceLibrary.editDistance(s3, s4);
    assertEquals(expected, result);

  }

  @Test
  public void editDistanceS1nullTest() {
    int expected, result;

    String s1 = null, s2 = "";
    expected = -1;
    result = EditDistanceLibrary.editDistance(s1, s2);
    assertEquals(expected, result);

  }

  @Test
  public void editDistanceS2nullTest() {
    int expected, result;

    String s1 = "", s2 = null;
    expected = -1;
    result = EditDistanceLibrary.editDistance(s1, s2);
    assertEquals(expected, result);

  }

  @Test
  public void editDistanceSubstringTest() {
    int expected, result;

    String s1 = "TEST", s2 = "stringTESTstring";
    expected = "string".length() * 2;
    result = EditDistanceLibrary.editDistance(s1, s2);
    assertEquals(expected, result);

  }

  @Test
  public void editDistanceBothEmptyStringTest() {
    int expected, result;

    String s5 = "", s6 = "";
    expected = 0;
    result = EditDistanceLibrary.editDistance(s5, s6);
    assertEquals(expected, result);

  }

  @Test
  public void editDistanceDynamicGreaterLengthTest() {
    int expected, result;

    String s1 = "casa", s2 = "cassa";
    expected = 1;
    result = EditDistanceLibrary.editDistanceApp(s1, s2);
    assertEquals(expected, result);

  }

  @Test
  public void editDistanceDynamicLesserLengthTest() {
    int expected, result;

    String s5 = "vinaio", s6 = "vino";
    expected = 2;
    result = EditDistanceLibrary.editDistanceApp(s5, s6);
    assertEquals(expected, result);

  }

  @Test
  public void editDistanceDynamicEqualLengthTest() {
    int expected, result;

    String s3 = "casa", s4 = "cara";
    expected = 2;
    result = EditDistanceLibrary.editDistanceApp(s3, s4);
    assertEquals(expected, result);

  }

  @Test
  public void editDistanceDynamicEqualWordTest() {
    int expected, result;

    String s9 = "pioppo", s10 = "pioppo";
    expected = 0;
    result = EditDistanceLibrary.editDistanceApp(s9, s10);
    assertEquals(expected, result);

  }

  @Test
  public void editDistanceDynamicS1EmptyTest() {
    int expected, result;

    String s1 = "", s2 = "teststring";
    expected = s2.length();
    result = EditDistanceLibrary.editDistanceApp(s1, s2);
    assertEquals(expected, result);

  }

  @Test
  public void editDistanceDynamicS2EmptyTest() {
    int expected, result;

    String s3 = "teststring", s4 = "";
    expected = s3.length();
    result = EditDistanceLibrary.editDistanceApp(s3, s4);
    assertEquals(expected, result);

  }

  @Test
  public void editDistanceDynamicS1nullTest() {
    int expected, result;

    String s1 = null, s2 = "";
    expected = -1;
    result = EditDistanceLibrary.editDistanceApp(s1, s2);
    assertEquals(expected, result);

  }

  @Test
  public void editDistanceDynamicS2nullTest() {
    int expected, result;

    String s1 = "", s2 = null;
    expected = -1;
    result = EditDistanceLibrary.editDistanceApp(s1, s2);
    assertEquals(expected, result);

  }

  @Test
  public void editDistanceDynamicSubstringTest() {
    int expected, result;

    String s3 = "TE", s4 = "aTEa";
    expected = EditDistanceLibrary.editDistance(s3, s4);
    result = EditDistanceLibrary.editDistanceApp(s3, s4);
    assertEquals(expected, result);

    String s1 = "TESTA", s2 = "stringTESTAstring";
    expected = "string".length() * 2;
    result = EditDistanceLibrary.editDistanceApp(s1, s2);
    assertEquals(expected, result);

  }

  @Test
  public void editDistanceDynamicBothEmptyStringTest() {
    int expected, result;

    String s5 = "", s6 = "";
    expected = 0;
    result = EditDistanceLibrary.editDistanceApp(s5, s6);
    assertEquals(expected, result);

  }
}
