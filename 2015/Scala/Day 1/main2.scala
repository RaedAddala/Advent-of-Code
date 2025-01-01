import io.Source

@main
def main(filename : String) = 
{    
    println(calculateFloor(Source.fromFile(filename).mkString))
}
def  calculateFloor(movements : String): Int = 
{
    var x = 0
    var index: Int = -1
    for( i <- 0 until movements.length ){
        if( movements(i) == '(') then x +=1 
        else if( movements(i) == ')') then x-=1
        if( x < 0 && index == -1 ) then index = i
    }
    index + 1
}
