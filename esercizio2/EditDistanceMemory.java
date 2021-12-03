public class EditDistanceMemory {
  int dNoOp, dInsertion, dDelete;

  public EditDistanceMemory(int dNoOp, int dInsertion, int dDelete) {
    this.dNoOp = dNoOp;
    this.dInsertion = dInsertion;
    this.dDelete = dDelete;
  }
}