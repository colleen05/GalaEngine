<p align="center">
    <img src="Images/logo.png">
    <br>
    GalaEngine is a C++17 game engine for 2D games, built with the <a href="https://www.raylib.com">raylib</a> library.
</p>

## PLEASE NOTE
GalaEngine is in a very early development stage. Expect bugs and lack of documentation and cross-platform support. If you run into a bug, please report it in the issues section of the GitHub repository.

## Compiling
### Linux
Before compiling on linux, make sure you have the clang compiler, with C++17 supported. GalaEngine should compile with g++, however it has not been tested.
To compile, simply execute the ``build_demo_linux64.sh`` file. Please note that ``build_engine_linux64.sh`` will produce a standalone library in the future, however this is not supported at the moment.

### Windows
GalaEngine does not have an official Windows build script yet, but feel free to check out the linux build scripts to create your own build.

## Documentation
Documentation for GalaEngine exists within each header, formatted with Doxygen comments, and within the ``Docs/`` folder. Although these can be read manually, it is recommended you build the documentation using Doxygen.

### Installing Doxygen
If you **do not have Doxygen installed**, you may download and install it [here](https://www.doxygen.nl/download.html). If you are **on Ubuntu**, you can simply install it by running ``sudo apt-get install doxygen``.

### Building Documentation
To build the documentation, simply open the directory you have cloned GalaEngine to, and run the following command:
``doxygen Doxyfile``. This will generate the appropriate HTML in the ``Docs/html/`` directory. To view the documentation, simply locate and open the ``Docs/html/index.html`` file in your web browser of choice.

## Contributing
If you'd like to contribute to GalaEngine (firstly, thank you!), there are a few guidelines expected. Following these guidelines makes managing and maintaining GalaEngine cooperatively muchc easier.

### Reporting Bugs & Issues
If you've found a bug while using GalaEngine, creating a report in the "Issues" section of this GitHub repository is recommended. Creating a well-structured bug report is appreciated, as it makes the process of communicating and fixing the bug as easy as possible. A good bug report should:
- **Be well-titled.** A good title structure is as follows: ``<Subject|Object>: ([<Issue> "when"] <Action>) | (<Summary>).``. Examples of **good** titles are: ``Entity: Crash when changing sprites.``, ``InputManager: Fails to recognise bluetooth controllers.``, and ``Docs: Scene.hpp has outdated TODO.``. Examples of **bad** titles are: ``Entities crash the game.``, ``Scenes are too confusing.``, or ``How do I change the colour of a sprite?``.
- **Have a good explanation in comment.** The comment of your issue should explain the expected behaviour, the actual behaviour, how to reproduce the bug, and the platform you are using GalaEngine on (are you using Windows or macOS? what GPU do you have?). If your bug or issue does not require such details (as in the case of a documentation error), it's fine to simply suggest an edit or clarification.
- **Be properly tagged.** Properly tagging your issue can help maintainers and newcommers understand the current issues within GalaEngine. You can tag your issue by selecting a "label" when creating it.

### Forks & Pull Requests
If you wish to contribute to the source code of GalaEngine, you may do so by forking the repository and creating a pull request. It is recommended to commit to your fork in small steps, and properly comment your changes. 

When you are ready to make a **pull request,** make sure to include some information about your changes. A good title for a pull request is as follows: ``<Verb>: <Object>: <Action>.``, or ``<Verb|Cat>: <Action>`` for simpler changes. Examples of good pull request titles are:
- ``Fixed: Scene: Stale-pointer deletion on RemoveLayer().``
- ``Implemented: Debug::Logger class.``
- ``Docs: Updated "Scene.hpp".``

In addition to the title, it is a good idea to supply further infromation in the comment. Here's some useful information that is appreciated to include in a pull request comment:
- Recap the problem as described in the title.
- What caused the problem?
- How did you solve the problem?
- Has this been reported before? (Include a link to an Issue if you have one!)
- Provide an example of how your solution works in practice, versus the result before the fix. (Such as a code example, or screenshots.)