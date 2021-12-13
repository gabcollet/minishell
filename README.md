# Minishell
My own shell made in C!<br/>
I made this little shell based on bash in partnership with Justine Badia.<br/>

# What can it do? :
- Show a prompt when waiting for a new command.<br/>
- Have a working History.<br/>
- Search and launch the right executable (based on the PATH variable or by using relative or absolute path)<br/>
- The builtins:<br/>
  - echo with option -n<br/>
  - cd with only a relative or absolute path<br/>
  - pwd with no options<br/>
  - export with no options<br/>
  - unset with no options<br/>
  - env with no options or arguments<br/>
  - exit with no options<br/>
- ’ inhibit all interpretation of a sequence of characters.<br/>
- " inhibit all interpretation of a sequence of characters except for $.<br/>
- Redirections:<br/>
  - < redirect input.<br/>
  - \> redirect output.<br/>
  - “<<” read input from the current source until a line containing only the delimiter is seen.<br/>
  - “>>” redirect output with append mode.<br/>
- Pipes | The output of each command in the pipeline is connected via a pipe to the input of the next command.<br/>
- Environment variables ($ followed by characters) expand to their values.<br/>
- $? expand to the exit status of the most recently executed foreground pipeline.<br/>
- ctrl-C ctrl-D ctrl-\ work like in bash.<br/>

# How to install and launch :

Mac :
```
git clone git@github.com:gabcollet/minishell.git; cd minishell; make; ./minishell
```
Linux : 
```
git clone git@github.com:gabcollet/minishell.git; cd minishell; make linux; ./minishell
```

Enjoy!
