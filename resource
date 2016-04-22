http://unix.stackexchange.com/questions/94322/is-it-possible-for-a-daemon-i-e-background-process-to-look-for-key-presses-fr

cat /proc/bus/input/devices
ls -l  /dev/input/by-{path,id}/


http://askubuntu.com/questions/26056/where-are-gnome-keyboard-shortcuts-stored/217310#217310

gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom$customcount/ name \"$name\"

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
http://askubuntu.com/questions/597395/how-to-set-custom-keyboard-shortcuts-from-terminal
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!