// Main functions used here are list.tail and list1.zip(list2) and list.sliding(groupsize, windowsize)

// the only difference from the previous implementation is that now I have to group each 3 which each other

import io.Source._

val data =  fromFile("input.txt").getLines()

@main 
def main(): Unit = {
    val values = data.filterNot(_.trim.isEmpty()).map(_.toInt).toList.sliding(3).map(_.sum).toList
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