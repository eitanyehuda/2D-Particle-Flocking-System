C++ and OpenGL

type make to compile and run program.

![image](https://user-images.githubusercontent.com/23744162/137963417-f924faf8-7023-4507-94aa-dfc7587236bb.png)
![image](https://user-images.githubusercontent.com/23744162/137963709-9a492fe9-4520-40dd-a855-a23ece61ce6b.png)
![image](https://user-images.githubusercontent.com/23744162/137963819-2c4f91f0-e735-4d83-a0ed-57050fb7fb24.png)

I used Windows 10 OS and completed this assignment in VSCode.

I compiled the code in MSYS2 MINGW-64 using the Makefile. Simply type make to remove past exe, compile program, and run.

List of commands:
- press or hold LMB to attract particles within range of mouse cursor
- press or hold RMB to repel particles within range of mouse cursor
- press "a" to add new particle at current cursor position
- press "d" to remove a particle closest to cursor position
- press "+" to globally increase the range of all particles 
- press "-" to globally decrease the range of all particles 
- press "up" arrow key to globally increase movment speed of particles
- press "down" arrow key to globally decrease movment speed of particles
- press "space bar" to stop/run annimation if it it running/stopped
- press "r" to wipe screen and re-generate a new set of particles
- press "q" or "Esc" to exit the program

Additional features:
- Improved particle physics with momuntum
- Particles bounce off the screen edges
- Press "f" to toggle friction on/off: particles will slow down if no force is applied to them 
- Press "e" to toggle evacuation on/off: predefined animation of particles evacuating to the bottom-left corner of the screen
- Press "h" to gather particles and create a heart: the more particles in range, the more detailed it will be :)
