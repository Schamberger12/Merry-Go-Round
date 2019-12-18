# Author

Gregory Schamberger, netid - gscham2

Made to fulfill requirements of CS425 - Computer Graphics I
at University of Illinois at Chicago

# Spooky Merry-Go-Round

Spooky Merry-Go-Round is a c++/opengl program that shows you some rides for an
amusement park! There are some cars moving around and a merry-go-round ride.
A ghost has been included for the Spooky version of Merry-Go-Round. 
You can move this ghost around, and if it comes into contact with either of the rides,
it turns part of, or the whole ride, transparent. 


# Ghost Implementation
 
    I made a ghost with a sphere and cylinder and allowed for its x, y, z transform to change
    based upon movement via I, J, K, L, U, P. Then I created a range of x,y,z coordinates that 'contained'
    the amusment park ride. Now when the ghost 'collides' with the amusement ride,
    the material of the ride is changed to a transparent version of the material. For all the transparent versions,
    I just changed the alpha from 1.0 to 0.5.

# Instructions

Windows:
    In order to use Merry-Go-Round on Windows, have Visual Studio downloaded and
    open MerryGoRound.sln, which you'll find in the Merry-Go-Round folder.

Linux:
    Have glut dev downloaded on your linux machine, navigate to the folder
    titled "UbuntuBuild", type in g++ Source.cpp -lglut -lGLU -lGL

    In the terminal type ./a.out in order to use Merry-Go-Round.


Controls:

   W-Move camera forward
   A-pan left
   S-Camera backward
   D-Pan right
   R-Reset camera
   I-Ghost forward
   J-Ghost Left
   K-Ghost backward
   L-Ghost right
   U-Ghost Down
   O-Ghost Up

# Contributions


I used the tree_and_teapot.cpp provided by Ja Eun Yu as a base. 


