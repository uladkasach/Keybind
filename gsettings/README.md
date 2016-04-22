This is a C implementation of this answer http://askubuntu.com/a/597414/357970 of how to set custom key bindings through the terminal
It creates a new custom-keybinding, with a unique name/key, and sets the name, binding, and command of this new keybinding.

Note: this works for *Ubuntu 13+ Only*, as 12 and below still store keybindings in XML format. See the xml keybinding folder for a possible solution.
Also note: this does *NOT* work for Xubuntu for sure untill 14.04, as they also still store keybindings in XML format. the xml folder has a solution for Xubuntu XFCE4 systems.

/////////////////////////
// Usage 
/////////////////////////
./binary '<name>' '<command>' '<binding>'
/////////////////////////

compile the binary, ie:
gcc -o keybinder keybind.c

use it, ie:
"./keybind 'test' 'gedit' '<Control><Alt>7'"

//////////////////////////
// Example Bindings
//////////////////////////
Super key:                 <Super>
Control key:               <Primary> or <Control>
Alt key:                   <Alt>
Shift key:                 <Shift>
numbers:                   1 (just the number)
Spacebar:                  space
Slash key:                 slash
Asterisk key:              asterisk (so it would need `<Shift>` as well)
Ampersand key:             ampersand (so it would need <Shift> as well)

a few numpad keys:
Numpad divide key (`/`):   KP_Divide
Numpad multiply (Asterisk):KP_Multiply
Numpad number key(s):      KP_1
Numpad `-`:                KP_Subtract


This is a C implementation of the solution from this answer : http://askubuntu.com/a/597414/357970