# Go
notes on the Go language: a personal reference not a guide

## packages
- every program is made of packages
- programs start running from the main package
- by convention, the package name is the same as the last element of the import path
## exported names
- a member is exported when its name starts with a capitalized letter
- only exported names are available from imported packages
## factored blocks
```
import (
        "fmt"
        "net"
       )
```
## functions
### parameters
- func <funcName>(<arg0> <arg0Type>, ...) {}
- parameters with the same type may omit the type on all but the last arg
### return results
- may return any number of values
### named return values
- may name return values and use them as declared variables
- "naked return" automatically returns the values if named (only use in short funcs)
```
func split(sum int) (x, y int) {
    x = sum * 4 / 9
    y = sum - x
    return
}
```
## variables
- var <name0> <type0>, <name1> <type1>, ... = <initializer1>, ...
- may omit type (if same) until last variable
- type may be ommitted if initializer present
- may be package or function level
- <name> := <initializer> // shorthand can use within functions
- outside of a func, every statement begins with a keyword
- may factored into blocks like with imports
### types
```
bool
string
int  int8  int16  int32  int64
uint uint8 uint16 uint32 uint64 uintptr
byte // alias for uint8
rune // alias for int32
     // represents a Unicode code point
float32 float64
complex64 complex128
```
- int, uint, uintptr are usually size n for n-bit systems
- Printf(): %T will print type of the var provided
### zero values
- variables declared without an explicit initial value are given their zero value
- numeric     0
- bool        false
- string      "" (empty string)
- pointer     nil
### type conversion
- type(<var>)
- explicitely required when an assignment has different types
### constants
- ```const <name> = <value>```
### numeric constants
- are values and take on a type best for the sitution it is used in
## loops
### for loop
- the only looping construct
```
for <init>; <condition>; <post> {
} // for
```
- init, and post are optional: exclude them and the semicolons for a while loop
### while
- ```for <condition> {}```
### forever
- ```for {}```
### range form of a for loop
```
for <index>, <copyOfElement> := range <slice/map> {
    ... 
} // for
```
- iterates over a slice or a map
- may skip index or copyOfElement by replacing with '_'
- ```for _, <e> := range ...```
- ```for <i>, _ := range ...```
- ```for <i> := range ...```
  - or just omit e if only wanting i
## control flow
### if
- if <optional_init;> <condition> {}
### switch
```
switch <init;> <variable> {
    case <>:
    case <>:
    default:
} // switch
```
- cases need not be constants or ints
    - may be values, vars, expressions
- cases do not fallthrough unless 'fallthrough' statement
    - ie implicit break
- cases are evaluated top-to-bottom and stop executing once one succeeds
- may use switch {} to condense long if-else chains
## defer
- ```defer <func()>```
- ```defer func() { <statements> }()```
- runs at func's return in last-in-first-out order (stack)
- deferred func's args are evaluated immediately though
- deferred functions may read and assign to the returning function's named return values
    - executes after the surrounding statement returns
    - eg: returns 2
    ```
    func c() (i int) {
        defer func() { i++ }()
        return 1
    } // c()
    ```
## exceptions
### panic()
- stops execution of the current func, deferred funcs are executed, the current func returns
- causes the current func's surrounding func to panic as well
    - propogates up the stack all funcs in the current goroutine have returned then crashes
- Go convention is that packages in libs using panic still presents explicit error ret val
### recover()
- regains control of a panicking goroutine
- only useful inside a defferred func
## pointer
- ```var <name> *<type>```
- ```*<var>``` dereference/indirect
- ```&<var>``` generates a pointer
- no pointer arithmetic
## struct
- collection of fields
```
type <name> struct {
    <fieldi> <typei>
}
```
- initializing
    - ```s := <name>{<vali>}```
    - ```s := <structName>{<Fieldi>: <val>}``` // to init a subset of fields
- fields accessed using .
    - ```s.Fieldi```
- ```*struct pointer```
    - may use structPtr.Field without explicitely dereferencing
## arrays
- ```[n]T```    an n-valued array of type T
- ```arr := [n]T{1, 2, ... , n}```
- length is part of the type so arrays cannot be resized
## slices
- []T             a slice with elements of type T
- arr[low:high]   // [low,high)
- dynamically sized flexible view into elements of an array
- make
    - ```make([]T, <len>)```
    - ```make([]T, <len>, <cap>)```
    - allocates a zeroed array and returns a slice refering to that array
- changing elements of a slice changes the elements of the array
- may omit high and or low bounds which default to len and 0 
- len(s): elements in the slice
- cap(s): elements in the underlying array counting from the first of the slice
- slice literal
    - ```[]T{1, 2, ... , n}```
    - creates an array then builds a slice that references it
- zero value of nil
    - has len(s) and cap(s) of 0 and no underlying array
- slices may contain other slices
```
sliceOfSlices := [][]T{
    []T{...},
        ...     
}
```
- appending
    - ```append(s []T, vs ...T)```
    - a slice and variable length of parameters of type T to append
    - if the backing array is too small, a new array will be allocated
        - the returned slice will refer to the new array
## map
- ```var m map[<keyType>]<valueType>```
    - nil: no keys nor can they be added
- ```m = make(map[<keyType>]<valueType>)```
    - returns initialized map 
- eg:
- m[key] = v
- v = m[key]
- v, ok =/:= m[key]
    ```
    if (m contains key) {
        ok = true
        v  = value
    } else {
        ok = false
        v  = (nil of v's type)
    } // if
    ```
- delete(m, key)
- map literals
    ```
    var m = map[<kT>]<vT>{
        k0: v0,
        ...
    } // map m
    ```
- if top level type is just a type name, may omit it from elements of the literals
    ```
    var m = map[string]Vertex{
        "Bell Labs": Vertex{
            40.68433, -74.39967,
        },
        "Google": Vertex{
            37.42202, -122.08408,
        },
    }
    // vvv instead vvv
    var m = map[string]Vertex{
        "Bell Labs": {40.68433, -74.39967},
        "Google":    {37.42202, -122.08408},
    }
    ```
## function values
- functions themselves are values and can be passed around
- eg:
    ```
    func compute(fn func(float64, float64) float64) float64 {
        return fn(3, 4)
    }
    
    func main() {
        hypot := func(x, y float64) float64 {
            return math.Sqrt(x*x + y*y)
        }
        fmt.Println(hypot(5, 12))
    
        fmt.Println(compute(hypot))
        fmt.Println(compute(math.Pow))
    }
    ```
## function closures
- a closure is a function value that references variables outside its body
- may access and assign to the variables: essentially bound to them
- ~static variables in C?
- eg: pos and neg each get their own sum variable: they are changed independently
    ```
    func adder() func(int) int {
        sum := 0
        return func(x int) int {
            sum += x
            return sum
        }
    }
    
    func main() {
        pos, neg := adder(), adder()
        for i := 0; i < 10; i++ {
            fmt.Println(
                pos(i),
                neg(-2*i),
            )
        }
    }
    ```
## method
- ```func (t Type) funcName() {}```
    - may use t in the method body
- a function with a receiver
- t can be struct or non struct type
- must be declared in the same package as the type
- pointer receivers allow the values of the type to be changed
    - most common to use pointer receivers so you can modify values
    - non-ptr doesn't since functions are all pass by value
        - ie it will make an entire copy of the type (even though it's being called on and not a parameter itself)
    - generally: type's methods should be all ptr or all non-ptr
        - can't make methods with the same name for t and *t
- go automatically calls pointer receiver methods when calling on actual types
    - and conversly calls receiver methods for pointer types
    - specifically for receiver methods not for arguments
- eg:
    ```
    type Vertex struct {
        X, Y float64
    }
    // type MyFloat float64     // non struct type

    func (v Vertex) Abs() float64 {
        return math.Sqrt(v.X*v.X + v.Y*v.Y)
    }
        
    v.Abs() // usable method
    ```
## interfaces, interface type
    ```
    type <Name> interface {
        <MethodName> <methodType>
    }
    func (<t> *<ImplementingType>) <MethodName> () {
        ...
    }
    ```
- a set of method signatures
- implicitly implemented: don't declare that an interface is implemented
- a value of interface type can hold any value that implements those methods
- if defined on *type, type can not be held by the interface type
- interface type can hold *type if type implements the methods
- under the hood: interface types are like a tuple of value and concrete type
    - (value, type)
    - calling a method on the value executes the method of the same name on the type
- if the underlying value is nil, the method is still called
    - common to write methods which gracefully handle nil receivers
    - an interface value is non-nil if it holds a concrete value even if that value is nil
## empty interface
- ```interface{}```
- eg:
    ```
    var i interface{}
    func def(i interface{}) { fmt.Printf("(%v, %T)\n", i, i) }
    ```
- holds value of any type
- used when the code handles values of unknown type
## type assertions
    foo := <InterfaceType>.(<SomeType>)     // panic assertion
    foo, ok := <InterfaceType>.(<SomeType>) // non panic assertion
    eg
        var i interface{}
        s := i.(int)
    allows access to interfaces undelying value if it matches the argument
    panics if the arg is not that type unless ask for boolean return type too
## type switches
    switch <varName> := <interfaceVar>.(type) {
    case <Type0>:
    case <Type1>:
    default:
    } // switch










oop map
1: static var in C# class => global var in Golang package
2: enum in C# => new package with enum name and const type of enum elements
3: class in OOP => struct type
4: class methods => struct with receiver methods
5: C#/Java abstract methods(pure virtual functions in C++) => interface methods like io.Reader
6: public => first letter Upper case Name
7: private => first letter lower case name
8: namespace => package name
9: inheritance => embedded struct and embedded interface
10: Thread => Go routines
11: lock => sync.Mutex
