// Main functions used here are list.tail and list1.zip(list2)

import io.Source._

val data =  fromFile("input.txt").getLines()

@main 
def main(): Unit = {
    val values = data.filterNot(_.trim.isEmpty()).map(_.toInt).toList
    /*
     * Here I will use the zip function which 
     * given two lists would match each element of the first 
     * with the equivalent element in the second
     * 
     * list.tail is a method that returns the list except for the first element
     * 
     * 
    */
    val num = values.zip(values.tail).count{ case (first,second) => second > first}
    println(num)
}