Embry-Riddle Aeronautical University - CS125
Final Project: Programming Pong in C
Authors: Xander Lee and Thomas Silva
Date of Submission: 4/6/2026

NOTE***
This project requires the external library Raylib to function
- https://www.raylib.com/ 

References:

Raylib External Library
- This includes numerous tutorials, examples, and coding cheatsheets. 

ChatGPT
- Helped to organize code and fix integration errors, most notably when we added the gameplay function to
the main game loop. We had to turn the game play portion from a .c file into a function to add to a header file, which meant stripping it
of a lot of specific functions that it relied on for testing. These extra portions that were already created in the main 
game loop were causing glitches and crashes, for example, the window initialization. The original gameplay program did 
not match the play area of the main window as well, and needed fine-tuning. ChatGPT helped to combine the different
programs we used in construction and building into one coherent and steady game. 
