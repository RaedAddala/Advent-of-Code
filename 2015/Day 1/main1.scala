import io.Source

@main
def main(filename : String) = 
{    
    println(calculateFloor(Source.fromFile(filename).mkString))
}
def  calculateFloor(movements : String): Int = 
{
    var x = 0
    for( c <- movements){
        if( c == '(') then x +=1 
        else if( c == ')') then x-=1
    }
    x
}