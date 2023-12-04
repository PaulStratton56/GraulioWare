# GraulioWare

### CSE165 Project: Paul S. Gabriel L.

#### GraulioWare | 12/3/23

#### (Note: For best results, it is recommended to open, build, and run this project via Qt Creator.)

  GraulioWare is a simple take on the minigame-rush genre, with the goal of surviving microgames and accumulating as many points as possible. There are three microgames, titled “Hyper Typer”, “Chaser Cube”, and “Simon Says”. Winning a microgame rewards a point, while losing (by letting time run out or otherwise) removes a life. If the player is in Normal Mode, the game is won when the player reaches 10 points. In survival mode, the game becomes increasingly difficult, with the goal being to get as many points as possible. Losing all lives results in a Game Over. The game was programmed using Qt Widgets, along with several objects being drawn through OpenGL interfaces. Additionally, Git version control allowed for a smooth progression of project creation, and GitHub provided a means of collaboration between the two partners.
  
  Hyper Typer provides a series of keys to be pressed sequentially within a given time frame. These keys are drawn using custom OpenGL graphics, and are separated into two classes (CapitalKey and LowercaseKey) that inherit from an abstract Key class. Pointers to these keys are upcasted to be stored in a Key pointer array. As the keys are pressed, they are removed from the screen and the array, and CapitalKeys and LowercaseKeys are handled differently via dynamic casting, providing elements of polymorphism. When all keys are removed, the microgame is won, and the player returns to the “Hub” to prepare for the next microgame.
  
  Chaser Cube is an OpenGL drawn game using QOpenGLWidget classes. The enemy red cube will continuously chase after the blue player, who must use the arrow keys to avoid the enemy until a timer expires. If the enemy touches the player, OpenGL detects this and the microgame is lost. Additional checks were made to ensure the player and the enemy cannot go outside the boundary of the arena they move in.
  
  Simon Says is a minigame that uses OpenGL to render an arrow on the screen. The player must press the arrow key that is in the direction of the on-screen arrow several times before the minigame is considered complete. If the player presses the wrong direction or time runs out, the game is lost. These arrows are stored in an array as their corresponding key (“Qt::Key_Up”, etc.), and dynamically show up as the player presses the correct buttons.

The game satisfies the following requirements:
> Controllable Object: player object in Cube Chaser, destroyable keys in Hyper Typer
> 
> Autonomous Object: enemy in Cube Chaser, arrow directions in Simon Says, etc.
> 
> Interaction: enemy can touch the player in Cube Chaser, etc.
> 
> Classes: Used heavily for every rendered item in the game.
> 
> Inheritance: CapitalKey and LowercaseKey inherit from the abstract class Key
> 
> Upcasting: Done to store the Capital and Lowercase keys in a Key array
> 
> Polymorphism: CapitalKey and LowercaseKey have different definitions of Key functions, and are handled differently on creation and destruction.
> 
> GitHub Usage: Used from the very start (initial commit was project creation)
> 
> OpenGL: Keys in Hyper Typer, arrows in Simon Says, arena/characters in Cube Chaser
> 
> Qt: Game logic, heavy use of Qt Widgets, Signals, and Slots

Gabe contributed the base navigational logic of the game, along with the bulk of Cube Chaser and Simon Says. 

Paul cleaned up elements of the code and was in charge of the UI design, along with creating Hyper Typer. 

Both members contributed to the project’s repository, each with several commits throughout the process of its creation.
