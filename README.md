# probarlib
probarlib is a library that allows you to create a simple progress bar in the terminal.
You can customize the text in front of the bar the bar filling character (indicator) and the size of the entire bar.
If you want to use it in your own project you need to know the width of the terminal or enter a static width.
I chose not to get the terminal width dynamically because it could cause some unnecessary calculations for example:
You already have a project that collects the width of the terminal so it is unnecessary to collect it again.
Another example:
You want the bar only to take half of the terminal.
And dynamically collecting the terminal size would result in a dependency like ncurses.

BTW probarlib is C89 compatible but not windows

If any questions come up dont hesitate to open an issue or if you want to contribute just open a pull request.

# Description
This is a library that allows you to diplay a progress bar that shows the exact percentage (examples/BasicProgressBar)
or you can use the progress indicator circle that doesnt show a exact percentage (examples/ProgressIndicationCircle).

BasicProgressBar:
![BasicProgressBar](images/BasicProgressBar.png)

ProgressIndicationCircle:
![ProgressIndicationCircle](images/ProgressIndicationCircle.png)

## Test the different bars

There are examples and usefull documentations in the `examples/` directory for both of the progress bars.
