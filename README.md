# Falling sand simulation

Falling sand simulation made for testing capabilities of Apus - 2d rendering engine(repo: https://github.com/CodeForBeauty/Apus)

All of the calculations and sand rendering work on CPU using OMP parallelism for speeding up loops.


# Screenshots of work
![alt text](https://github.com/CodeForBeauty/FallingSand/blob/master/Apus/testing/Render1.png)
![alt text](https://github.com/CodeForBeauty/FallingSand/blob/master/Apus/testing/Render2.png)
![alt text](https://github.com/CodeForBeauty/FallingSand/blob/master/Apus/testing/Render.png)

# How to use
To only test out program you can get it here: https://github.com/CodeForBeauty/FallingSand/releases/tag/Testing

On launch program expects user to input width and height of a canvas.
After inputing width and height app window unfreezes and is free to use or resize.

Pressing left mouse button spawns sand in a circle around cursor. That circle can be resized by pressing [-]/[=] on the keyboard.

Screenshot of a current state of a canvas can be taken by pressing [R] on the keyboard. Screenshot is saved in folder "testing" as "Render.png". Resolution of a taken screenshot is dependent on window size.

# Conclusion
ApusCore has become very powerful rendering engine. And is being worked on. More of the similar projects will come in the near future.
