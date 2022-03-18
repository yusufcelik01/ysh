# ysh
This is a ysh a simple shell that is being developed for educational purposes. It is still fresh and incomplete so don't expect too much.

##Features
For now ysh only supports 2 built-in commands which are cd and exit and uses /bin/ as binary files' directory.

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
Classic shell change directory command
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


