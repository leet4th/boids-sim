#! /bin/bash

# enable color support of ls and also add handy aliases
if [ -x /usr/bin/dircolors ]; then
    test -r ~/.dircolors && eval "$(dircolors -b ~/.dircolors)" || eval "$(dircolors -b)"
    alias ls='ls --color=auto'
    alias dir='dir --color=auto'
    alias vdir='vdir --color=auto'
    alias grep='grep --color=auto'
    alias fgrep='fgrep --color=auto'
    alias egrep='egrep --color=auto'
fi

# ls
alias ll="ls -lh"
alias la="ll -A"  # ll showing hidden files
alias lk="ll -Sr" # sort by size
alias lc="ll -cr" # sort by change time
alias lu="ll -ur" # sort by access time
alias lt="ll -tr" # sort by date
alias lf="ll | grep -v '^d'" # files only
alias ld="ll | grep '^d'" # directories only
alias llt="lt" # habit

# Find command in your history
alias gh='history | grep'

# Aliasing python to force python3 usage
alias python=python3
alias pip=pip3

# Prints out the python executable path
alias whichpy='python -c "import sys; print(sys.executable)"'

# Prints out python version information, including pyenv versions
alias pv='python --version; whichpy; pyenv versions'

# tree
alias tree='tree --dirsfirst -I "venv*|__pycache__"'
