import io.Source._

val data =  fromFile("input.txt").getLines()

@main
def main():Unit = {
    val values = data.map(_.filter(_.isDigit))
    val temp = values.map((x) => x.head.asDigit*10 + x.last.asDigit).toList
    print(temp.sum)
}