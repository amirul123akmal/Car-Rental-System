# Car Rental System
###### Project from **https://hackr.io/blog/cpp-projects** 

#### 1. What number is this challenge ?
* This `Car Rental System` is at `no. 2`

#### 2. Where to look at the source file ?
* in `Car Rental System\src` , there is `Source.cpp`

#### 3. How its work ?
* Stores your car's `plate` and `time` into `database.txt`
* At checkout, User enter their car's plate, the system will check `database.txt`
* If found : -
  1. Compare `time` right now with the `time` stored
  2. Calculate :-
     * The time difference `deltaTime`
     * Amount of money needed according to the `deltaTime`  
  3. After user entered the correct amount:-
     * The user's car's plate number will be delete from `database.txt`
     * and moved to `history.txt` 
     * ( in the future, after moved, the system will stored the car's plate and the amount paid)

#### 4. Keynote
* This program is `Console Application`
    1. Detailed Information:-
       * Windows 10 Home 
       * Version 10.0.19043 Build 19043
    2. Any linux Distribution have not been tested
* You need to build it yourself by :-
  1. Open `Car Rental System.sln`
  2. Right click the solution and press `build`
* You need to run using `Visual Studio` . Another Solution : -
    1. Redirect the program `start in` :
       * After build, goto `x64\release` or `x64\debug`
       * Make a shortcut of the `executable`
       *  Change `start in` to your absolute path toward the folder that have `res` and `src` 
       *  `<to the path>\Car Rental System\Car Rental System`
    2. Build it yourself
       * Move `Source.cpp` outside `src`
       * Use `g++` compiler to compile and run
