[//] <> (note this is a comment i like to comment like this in md)
# simttylogin
`simttylogin` a program to simulate tty login in terminal
![screenscot from tty](simttylogin.png "Picture") 
__Note: this program does not do a login your user won't change after a sucesfull login__
## requirements(only pam is required for method 1)
### ubuntu,debian and distros based on these
`sudo apt update ; sudo apt install pam`
### Arch and distros based on Arch:
`sudo pacman --needed -S core/pambase core/pam`
### Gentoo
`sudo emerge sys-libs/pam`
## installing
## 1.method binary releases
download `simttylogin-bin`,`simttylogin.conf`and `install.sh` from [releases page](https://github.com/dorker6/simttylogin/releases)
run: `chmod +x ./install.sh ; ./install.sh`
## 2.method source code
### requirements
#### ubuntu,debian and distros based on these
`sudo apt update ; sudo apt install gcc pkg-config git`
### Arch and distros based on Arch:
`sudo pacman --needed -S gcc pkgconf git`
## <span style="color:red">color</span> support [//] <> (oh i wish i wish each letter of the word 'color' to be in different color)
run `compile.sh` with `-c` or `--enable-color` option
NOTE: currently only red:on login failures green: on login sucesses
    also color can only be enabled during compile time
## one command to rule them all:
`git clone https://github.com/dorker6/simttylogin ; cd simttylogin ; chmod +x ./compile.sh ./install.sh; ./compile.sh ; sudo ./install.sh`
with colors:`git clone https://github.com/dorker6/simttylogin ; cd simttylogin ; chmod +x ./compile.sh \
./install.sh; ./compile.sh -c ; sudo ./install.sh`
