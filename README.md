# python_launcher
A simple windows executable that install python quietly on the client's machine if it is not installed and start your script so that you don't have to compile

You juste have to put the launcher.exe file at your main python file root with a "launcher.conf" file containing only one line specifying the python command to start your script like ```python main.py```. If python is already installed, the launcher will just execute your command. 
