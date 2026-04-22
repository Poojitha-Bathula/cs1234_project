🚇 City Grid Transit Simulator (C Language Project)

📌 Overview
The City Grid Transit Simulator is a modular C project that models a simplified urban transport system using data structures such as:
2D Grid (Matrix) → for station layout
Graph (Adjacency List) → for connectivity between stations
Linked Lists → for dynamic route creation
Priority Queue → for shortest path computation
File I/O → for persistent data handling
The system allows users to simulate station networks, create routes, compute shortest paths, and manage transport-based travel costs.

🎯 Objective
To simulate a real-world city transport system where:
Stations are arranged in a grid (like a map)
Routes can be dynamically created between stations 
Shortest path between two stations can be computed
Station information can be searched and modified
All operations are controlled via a command file

🧠 Concepts Used

📍 1. 2D Matrix (Grid Representation)
Each cell represents a station with:
Name
Type (BUS / METRO / AUTO etc.)
Coordinates (x, y)

📍 2. Graph Representation
Each station connects to its valid neighbors
Each edge contains:
Distance
Cost
Transport type

📍 3. Linked List (Routes)
Each route is a linked list of stations
Supports:
Add station
Display route
Detect loop
Compute distance & cost

📍 4. Shortest Path Algorithm
Priority queue-based Dijkstra-style traversal
Considers:
Cost
Distance
Transport penalty (mode switching cost)

📍 5. File Handling
Loads station data from file
Executes commands from input file
Exports route data to output file
📁 Project Structure
main.c         → Command interpreter (input handling)
grid.c / grid.h   → Grid & station management
graph.c / graph.h → Graph + shortest path logic
route.c / route.h → Route linked list operations
stations.txt   → Initial grid data
input.txt      → Command script
output_routes.txt → Exported routes
Makefile       → Build system
⚙️ Compilation
Compile the project using Makefile:
make
This generates:
transit   (executable file)
▶️ Running the Program
make run
OR manually:
./transit

📥 Input File Format (input.txt)
The program reads commands line-by-line.
🔹 Supported Commands
📍 Grid Operations
display
search Central
search Airport
rename 0 0 MainHub
📍 Route Operations
create_route R1
add_station R1 0 0
add_station R1 0 1
display_route R1
distance R1
cost R1
detect_loop R1
📍 Shortest Path
shortest 0 0 2 2

📤 Output Features
✔ Station Display
==============================
 AVAILABLE STATIONS
==============================
Central
Egmore
...
✔ Search Output
Found at (0,0)
Station not found
✔ Route Output
(0,0:Central) -> (0,1:Egmore)
Distance: 4
Cost: 20
✔ Shortest Path Output
SHORTEST PATH:
(0,0) -> (0,1) -> (1,1)

Total Cost: 32
✔ Grid Visualization
 *  *  .
 .  *  ..........
       
🚀 Features Implemented
✔ Grid System
Station initialization from file
Station search by name
Rename station support
✔ Route System (Linked List)
Create dynamic routes
Add stations to route
Detect loops in route
Compute:
Distance
Cost
✔ Graph System
Converts grid → adjacency list
Connects valid neighboring stations
Assigns transport-based cost weights
✔ Shortest Path System
Priority queue (min-heap)
Cost-aware shortest path
Path reconstruction
✔ File System
Input-driven execution
Output route export

🛠 Requirements
GCC compiler
Make utility
Linux / macOS / WSL recommended
run commands (for output)
make        # compile project
./transit   # (output is obtained)
