
# tty-pong-clock

## What is clock?

A work in progress!

A tty clock that shows an animated pong game

![](https://raw.githubusercontent.com/pcharest2000/ttyPongClock/master/screenshots/screen01.png)
![](https://raw.githubusercontent.com/pcharest2000/ttyPongClock/master/screenshots/screen02.png)
![](https://raw.githubusercontent.com/pcharest2000/ttyPongClock/master/screenshots/screen03.png)


## Known issues

When resizing the terminal sometimes it cores dump or screen is corrupted working on it!

## How do I install tty-pong-clock

Requirements:

A terminal with color support an unicode charaters, should be the case if you are not running a VT-100 from 1982. 

Build requirements:

* lib ncurses


* Clone the repo:  git clone https://github.com/pcharest2000/ttyPongClock.git 
* cd ttyPongClone
* make
* Copy in the build directory tty-pong-clock somewhere in your path/

## Where can I get help?

For support & all other kinds of questions open an issue ticket.  Comments negative or postive are welcomed!

## Configuration
Notes: Colors are indexes of your tty. The higher the frame rate the higer is cpu usage and ball is faster!

<pre>
usage : tty-pong-clock [-B [0-7] -C [0-7] -F [1-60] ]            
    -C            Set forground color                            
    -B            Set background color                           
    -F            Set frame rate default 30                      
    -b            Set big font                  
</pre>
