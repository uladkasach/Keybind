This is a C implementation for keybinding custom commands in XFCE4, Xubuntu systems.

------------

Where keybinding shortcuts are stored in XFCE4: `$ gedit ~/.config/xfce4/xfconf/xfce-perchannel-xml/xfce4-keyboard-shortcuts.xml`

Underlying Schema:
xfconf-query --reset --channel xfce4-keyboard-shortcuts --property "/commands/custom/<Control><Alt>Down"
xfconf-query --reset --channel xfce4-keyboard-shortcuts --property "/xfwm4/custom/<Control><Alt>Down"
xfconf-query --create --channel xfce4-keyboard-shortcuts --property "/commands/custom/<Control><Alt>Down" --type string --set 'gedit'

Note, you must clear the active bindings to both commands and xfwm4 in order for your new custom command to work.

------------
See example key bindings in main README.md 