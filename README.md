# MarsEngine - Physics Engine with Graphics Rendering

This project is a physics engine with graphics rendering capabilities, implemented in C++. It allows for realistic simulations of physical properties and provides a visual representation using the SDL2 graphics library.

## Features

- Accurate physics calculations: The physics engine is designed to handle heavy calculations and provides reliable simulation of various physical properties, such as collision detection, gravity, forces, and motion.

- Real-time rendering: The SDL2 graphics library is utilized to render the simulated physics objects onto a window in real-time. This provides a visual representation of the physics simulations and enhances the user experience.

- Smooth performance: The project is implemented in C++, taking advantage of its efficiency and low-level control. This ensures smooth handling of heavy physics calculations, resulting in optimal performance.

## Requirements

- C++ compiler: The project requires a C++ compiler that supports C++11 or higher.

- SDL2 library: SDL2 is used for graphics rendering. Make sure to have SDL2 installed on your system. You can find more information and installation instructions on the [SDL2 website](https://www.libsdl.org/).

## Getting Started

1. Clone the repository:

   ```
   git clone https://github.com/your-username/physics-engine.git 
   ```
   
2. Compile the code using a C++ compiler:

   ```
   g++ -std=c++11 -o physics_engine main.cpp physics.cpp -lSDL2 
   ```
3. Make sure to link against the SDL2 library using the -lSDL2 flag.
   Run the compiled executable:
   ```
   ./physics_engine
   ```
   
## Usage
- Customize physics simulations: Modify the code in main.cpp or physics.cpp to create your own simulations or incorporate additional physical properties.

- Adjust rendering settings: You can modify the graphics rendering settings in the code to change the visual representation of the physics simulations.

## Screenshots

<img width="961" alt="0" src="https://github.com/marsian83/MarsEngine-with-physics-simulations/assets/114365550/ad402e0b-64d9-4713-9222-6ddd95d22af2">



<img width="963" alt="1" src="https://github.com/marsian83/MarsEngine-with-physics-simulations/assets/114365550/f3afe882-3a13-4c97-9952-7d4ab97637a2">



<img width="1120" alt="2" src="https://github.com/marsian83/MarsEngine-with-physics-simulations/assets/114365550/d82a01c5-a8c8-4055-a615-8741a8a2d32c">




