# Cleaning Robot Documentation

## Team Members
- Naumenko Kateryna
- Nitkiewicz Jakub
- Świderska Ada

---

## Project Overview
The Cleaning Robot project implements a robot capable of navigating a user-defined room to clean it efficiently. The project includes the following features:
1. Selection of room size.
2. Addition of walls and obstacles.
3. Execution of a cleaning algorithm that ensures the robot navigates through all accessible spaces.

### Key Algorithm
- The robot follows a "right-hand" rule, always keeping a wall, obstacle, or cleaned area to its right side.
- When no adjacent areas need cleaning, the robot calculates the shortest path to the nearest uncleaned area and resumes cleaning from there.

---

## Project Workflow
### Terminal Application
Initially, the project was implemented as a terminal-based application, where obstacles were represented as `||` and numbers indicated the robot’s path.

### Graphical Application
To improve usability, a graphical interface was developed using **SFML (Simple and Fast Multimedia Library)**. The graphical representation includes:
- **Purple areas:** Walls and obstacles.
- **Pink circle:** The robot.
- **Gray areas:** Dirty surfaces.
- **White areas:** Cleaned surfaces.

---

## Tools Used
- **SFML (Simple and Fast Multimedia Library):** Used for real-time visualization of the robot's movement.
- **TDD (Test-Driven Development):** Ensured reliability and correctness during development.

---

## Architecture

### Classes
1. **`Map`**
   - Handles map-related functionalities such as:
     - Adding walls and obstacles.
     - Checking if the entire map is cleaned.

2. **`Track`**
   - Implements the robot’s navigation algorithm.
   - Ensures the robot maintains a wall, obstacle, or cleaned area to its right side.
   - Utilizes the `Direction` class to determine movement (Left, Right, Up, Down, Unknown).
   - When no adjacent areas are unclean, the robot identifies the closest unclean cell and navigates to it.

3. **`DrawnMap`**
   - Visualizes the map and the robot's movement.
   - Uses SFML to render the 2D vector-based map as an image, with real-time robot tracking.

4. **`Robot`**
   - Handles the robot's position on the map.
   - Includes methods for setting and retrieving the robot's coordinates.

5. **`Point`**
   - A structure for storing coordinates.

6. **`Direction`**
   - Enumerates possible movement directions (Left, Right, Up, Down, Unknown).

---
