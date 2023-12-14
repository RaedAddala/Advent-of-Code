import io.Source._

@main
def main(): Unit = {
  def firstAndLastNumbers = (x: String) => {
    val first = x.find(_.isDigit).get
    val last = x.findLast(_.isDigit).get
    ((x.indexOf(first), first), (x.lastIndexOf(last), last))
  }
  val datax = fromFile("input.txt").getLines()

  // Only 4 & 6 don't produce prolems after converting them
  val data = datax.map(_.replaceAll("six", "6").replaceAll("four", "4"))

  val data1 =
    data.map(_.replaceAll("one", "1")).map(firstAndLastNumbers).toArray
  val data2 =
    data.map(_.replaceAll("two", "2")).map(firstAndLastNumbers).toArray
  val data3 =
    data.map(_.replaceAll("three", "3")).map(firstAndLastNumbers).toArray
  val data5 =
    data.map(_.replaceAll("five", "5")).map(firstAndLastNumbers).toArray
  val data7 =
    data.map(_.replaceAll("seven", "7")).map(firstAndLastNumbers).toArray
  val data8 =
    data.map(_.replaceAll("eight", "8")).map(firstAndLastNumbers).toArray
  val data9 =
    data.map(_.replaceAll("nine", "9")).map(firstAndLastNumbers).toArray

  val x = Array(data1, data2, data3, data5, data7, data8, data9).transpose
  
  val reducedX = x.map(list => {
    val smallestfirst = list.minBy(_._1._1)._1
    val biggestsecond = list.maxBy(_._2._1)._2
    (smallestfirst, biggestsecond)
})

  val temp = reducedX.map((x) => x._1._2.asDigit * 10 + x._2._2.asDigit).toList
  print(temp.sum)
}
