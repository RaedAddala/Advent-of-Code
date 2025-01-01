import io.Source._

val data =  fromFile("input.txt").getLines()

@main
def main():Unit = {
    val limits = Map(
        "blue" -> 14,
        "green" -> 13,
        "red" -> 12
    )
    val games = data.map(_.split(":").last.split(";").map(_.split(","))).toList
    
    // debugging purposes
    //games.foreach((arr) => arr.foreach((f)=> println(s"Array Num ${games.indexOf(arr)} $f")))
    
}