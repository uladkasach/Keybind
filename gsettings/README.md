This is a C implementation for keybinding custom commands in **Ubuntu 13+** systems. Implementation was fully based on this answer http://askubuntu.com/a/597414/357970.

Note: For Ubuntu 12 and below, see the answer linked above (feel free to add your implementation to the repo if you create it). For Xubuntu systems, please visit Keybind/xml/xfce4.


------------
##Usage 
./binary '<name>' '<command>' '<binding>'

For example
compile the binary : `gcc -o keybinder keybind.c`

use it : `./keybind 'test' 'gedit' '<Control><Alt>7'`
------------

See example key bindings in main README.md 
