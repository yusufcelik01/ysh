# ysh
This is a ysh a simple shell that is being developed for educational purposes. It is still fresh and incomplete so don't expect too much.

## Features
For now ysh only supports 3 built-in commands and executing binaries that exist under the directories speciefied in the path command. /bin/ is the default directory for searching binary executables for ysh if path command is never executed.

## Usage
In order to use ysh 
First clone the repo:
```
git clone https://github.com/yusufcelik01/ysh.git
```

Compile it:
```
make ysh
```

Lastly run the executable:
```
./ysh
```
which shoul give you a prompt

## Built-in commands

### Change directory cd
Classic change directory command in shells
```
$ cd </path/to/new/working/directory>
```

### Exit 
Exits the shell session
```
$ exit
```

### Path command
Updates the path/paths to search executable files
```
$ path <path1> <path2>
```

Example usage:
```
$ path /bin /usr/bin/
```
### Executing binaries
Just like any other shell, ysh searches for binaries in directories specified with path command and executes them with given arguments.


