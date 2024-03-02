# 01 - Introduction

## Linux Basic Commands

## Navigate Directories

- ```pwd```: print working directory

- ```ls```: list directory

- ```cd```: change directory

- ```cd /```: take you to the root directory

- ```cd ~```: take you to the user home directory

- ```cd ./another_folder```: navigate from current directory to another_folder

- ```cd ..```: navigate from current directory to parent directory

- ```cd -```: go back to the previous working directory
  - ```cd /```: going to the root directory
  - ```cd ~/```: going to the home directory
  - ```cd -```: going back to the root directory


- ```cd "my work"``` or ```cd 'my work'``` or ```cd my\ work```: going to a folder with space

## ls Options

- ```ls```: List files by alphabetic order

- ```ls -a```: This will show all the files (-a == all files) in your current directory, including hidden files

- ```ls -l```: Long listing of all files in the directory and some important information.

- ```ls -al```: listing of all files in the directory including hidden files.

- ```ls -li```: Long listing + show inode ids

- ```ls -lia```: Long listing + show inode ids + hidden files

- ```ls -R```: Show current directory content plus any children/sub directory content as well

- ```ls -Ra```: Show current directory content plus any children/sub directory content as well + including hidden files

- ```ls -aLR```: Show all files in the user account including thos in sub directories

## Touch Command (Create a file)

- Touch is used to create empty files

  - ```touch file_name```: Create a file called file_name
  - ```touch file_name1 file_name2 file_name3```: Creates 3 files
  - ```touch 'my file'``` or ```touch "my file"``` or ```touch my\ \ file```: create a file with a name containing spaces
    - ```\``` is a scape sequence


- Touch is also used to update a current files timestamp (modification dade)

  - ```touch newFile```
  - ```echo "test" > newFile```
  - ```touch newFile```: this will update the file timestamp and keep the content

## MKDIR (Make directory) and RMDIR (Remove directory) Commands

- If you want to create a directory, then you use ```mkdir``` command as follow:

  ```
  mkdir directory_name
  mkdir directory_name1 directory_name2 directory_name3
  ```

- To remove **empty** directories you can use ```rmdir``` command as follows:

  ```
  mkdir empty_dir
  rmdir empty_dir
  ```

  - In case you do ```rmdir``` in one directory that has files and another that is empty, it will only delete the empty one.


- To create a directory with a name containing spaces, you can do ```mkdir 'my directory'``` or ```mkdir "my directory"```


## RM (Remove) Command

  - To delete non-empty-directory files, or just normal files you just do:
    ```
    touch fileToDelete
    rm fileToDelete
    mkdir folder
    cd folder
    touch file
    cd ..
    ```
    - ```rm -R folder``` or ```rm -r folder```

    - In case of non-empty-directory you need to run ```rm``` with the recursive flag ```-R```. Otherwise it will fail
    - Also, the ```-R``` flag can be lowercase since it is not case sensitive for ```rm``` (although it is case sensitive for ```ls```)


  - ```rm``` options:

    - ```rm -i```: Prompt you before removing any existing file. the ```-i``` means interactive mode

    - ```rm -R``` or ```rm -r```: Recursively delete files. If the file is a directory, remove the entire directory and all its contents, including subdirectories.


## CP (Copy) Command

- The ```cp``` command copies files or directories. It can be used in two different ways:
  - Copy a file: ```cp file file2```
  - Make a copy of a directory: ```cp -R dir dir2```: ```dir2``` does not need to exist
    - This will make a copy of dir1 named dir2 (Assuming that dir2 didn't exist)

  -  In case you copy many files using the following syntax:
    - ```cp file1 file2 file3 dir```: ```dir``` must exist in this case.
    - Same case for directories: ```cp -R dir1 dir2 dir3```


  ## MV (Move) Command

- The ```mv``` command can be used in two different ways.
  - Renaming files

    - ```mv file1 file2```: This will rename file1 to file2
    - ```mv dir1 dir2```: If your file is a directory, this will rename the directory
    - **You do not need to use the -R option with ```mv```**

  - Moving files

    - ```mv file1 file2 dir1```: This will move file1 and file2 to dir1. However, dir1 must exist
    - ```mv dir1 dir2 dir3```: This will move dir1 and dir2 to dir3. Again, dir3 must exist

## FILE (File) Command

  - Filenames are case sensitive in just like the commands are.

  - Linux has no concept of  `file extension` like Windows. You can have files without any extension.
    - It checks the file content to identify what kind is it.


  - The command ```file filename``` will give us information about the file type.

  - ```file LS -L OUTPUT.png```: LS -L OUTPUT.png: PNG image data, 1968 x 488, 8-bit/color RGBA, non-interlaced

## Command Line History

  - ```history```: Show all the commands executed in the cmd
  - ```history 10```: Show last 10 commands
  - ```history -c```: Clear history
    - Your history is stored at ```~/.bash_history```
  - ```!number```: Runs a command from history

  ## View text files (less, cat, tac, head, tail) Commands

  - ```less file1```: View the content of the file ```file1```
    - Press ```q``` to quit

  - ```cat file1 file2```: View the content of the file ```file1```concatenated with ```file2```
    - ```cat``` lets you see two files output concatenated

  - ```tac file```: Shows the content of file, but reversed
  - ```head -n 20 file```: Show first 20 lines of file
  - ```tail -n 20 file```: Show last 20 lines of file

  ## Streams and Pipes

### Stream 

* `>` operator 
  * e.g. `grep "text" . > output.txt`
  * Writing to a file (overwrite)
  * e.g `head -n1 < /etc/passwd`
    * Using operator as input to an app

* `>>` operator 
  * e.g. `grep "text" . >> output.txt`
  * Append to a file 

### Pipes

* `ls | cowsay`
  * pipe the results from `ls` to the program `cowsay`

* `ls -l *.conf | wc -l | cowsay`

## Users, Groups and Permissions

* `adduser danielmapar`
  * Only root may add a user or group to the system.
  * `sudo`: `super user do`
    * `sudo -i`: login as `root`

* `sudo adduser danielmapar`
  * Executing command with root credentials 

* `sudo login danielmapar`
  * `cat /etc/passwd | grep "^danielmapar"`

  * user = file owner
  * group = the group of the file owner
  * others = other users / groups
  * The first char can be `-` (for file), `d` for directory of `l` for link.

* `chmod +x file`
  * You can change the `user` and `group` permission to include `x` (execute).

* `chmod 755 file`
  * each number represents a sequence of 3 bits. In the case of 7 it represents 111 (read, write and execute). Another example is 5 (read, dont write, execute).
    * In this case, 7 changes the `user` permissions (`rwx`), the second and third numbers (5's) will change the `group` and `other` permissions respectively.

  * Anothe way to achieve this (`755`) is by running: `chmod u=rwx,g=rw,o=rw file`
