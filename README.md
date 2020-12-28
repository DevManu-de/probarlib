# probarlib
probarlib is a library that allows you to create a simple progress bar in the terminal.
You can customize the text in front of the bar the bar filling character (indicator) and the size of the entire bar.
Currently there are 3 bars BasicProgressBar, ComplexProgressBar and ProgressIndicationCircle.

BasicProgressBar:
> Only requires a text the rest of the bar like resize and apprearence is done automatically.
> This allows the programmer to implement a progress bar fast with preset values.
>

ComplexProgressBar:
> This allows the programmer to have a much deeper control over the bar thus may take longer to
> implement in the project.
>

IMPORTANT: Both BasicProgressBar and ComplexProgressBar are technically the same everything that can be done with
the ComplexProgressBar can also be done with the BasicProgressBar only that the BasicProgressBar doesnt have functions
to set those variables but they can be changed by editing the structure manually. Optionallly you can use ComplexProgressBar
functions on a BasicProgressBar but its neither recommended nor officially supported.

ProgressIndicationCircle:
> This can display a text and shows a circular animation until it is stopped.
>

BTW probarlib is C89 compatible but not windows only linux is tested and supported

If any questions come up dont hesitate to open an issue or if you want to contribute just open a pull request.

# Description
This is a library that allows you to diplay a progress bar that shows the exact percentage (examples/BasicProgressBar)
or you can use the progress indicator circle that doesnt show a exact percentage (examples/ProgressIndicationCircle).

BasicProgressBar / ComplexProgressBar:
![BasicProgressBar](images/BasicProgressBar.png)

ProgressIndicationCircle:
![ProgressIndicationCircle](images/ProgressIndicationCircle.png)

# Universal function for both bars

## get_term_width()
> 
> Return value
> is the width of the current terminal.

# Test the different bars

There are examples and usefull documentations in the `examples/` directory for both of the progress bars.
