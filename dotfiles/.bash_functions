#! /bin/bash

# print paths, new line for each path
function printpath() {
    sed 's/:/\n/g' <<< "$PATH"
}

# cd to venv project dir
function proj() {
    if [ -z "$VIRTUAL_ENV" ]; then
        echo "venv not set"
    else
        cd $VIRTUAL_ENV/../
    fi
}

# Uninstalls all currently installed pip packages, only works for virutal envs
function pipua() {
    if [ -z "$VIRTUAL_ENV" ]; then
        echo "venv not set"
    else
        pip uninstall -y -r<(pip freeze)
    fi
}

function parse_git_branch () {
    git symbolic-ref --short -q HEAD 2> /dev/null
}

function _ps1_git_branch () {
    if git rev-parse --git-dir > /dev/null 2>&1; then
        echo "$(parse_git_branch) "
    fi
}

function parse_git_hash() {
    git log -1 --pretty=oneline 2> /dev/null | cut -c -8
}

# Used to set the bash prompt dynamically
function set_bash_prompt () {

    # More colors
    # https://michurin.github.io/xterm256-color-picker/
    # https://robotmoon.com/bash-prompt-generator/

    # Regular Colors
    Black='0;30'        # Black
    Red='0;31'          # Red
    Green='0;32'        # Green
    Yellow='0;33'       # Yellow
    Blue='0;34'         # Blue
    Purple='0;35'       # Purple
    Cyan='0;36'         # Cyan
    White='0;37'        # White

    # Bold
    BBlack='1;30'       # Black
    BRed='1;31'         # Red
    BGreen='1;32'       # Green
    BYellow='1;33'      # Yellow
    BBlue='1;34'        # Blue
    BPurple='1;35'      # Purple
    BCyan='1;36'        # Cyan
    BWhite='1;37'       # White

    # High Intensity
    IBlack='0;90'       # Black
    IRed='0;91'         # Red
    IGreen='0;92'       # Green
    IYellow='0;93'      # Yellow
    IBlue='0;94'        # Blue
    IPurple='0;95'      # Purple
    ICyan='0;96'        # Cyan
    IWhite='0;97'       # White

    # Bold High Intensity
    BIBlack='1;90'      # Black
    BIRed='1;91'        # Red
    BIGreen='1;92'      # Green
    BIYellow='1;93'     # Yellow
    BIBlue='1;94'       # Blue
    BIPurple='1;95'     # Purple
    BICyan='1;96'       # Cyan
    BIWhite='1;97'      # White

    # Chosen colors
    C_VENV=$IBlue
    C_BRANCH=$Yellow
    C_PATH=$Purple
    C_USER=$IGreen
    C_NONE="\[\e[00m\]"

    # Color formatting
    C_START="\[\e["
    C_END="m\]"
    C_VENV=$C_START$C_VENV$C_END
    C_BRANCH=$C_START$C_BRANCH$C_END
    C_PATH=$C_START$C_PATH$C_END
    C_USER=$C_START$C_USER$C_END

    # Build ps1
    PS1=""

    # venv
    if ! [ -z $VIRTUAL_ENV_PROMPT ] ; then
        PS1="$C_VENV$VIRTUAL_ENV_PROMPT"
    fi

    # Add git info to prompt when inside a git repo
    if git rev-parse --git-dir > /dev/null 2>&1; then
        GIT_REPO_DIR=$(basename `git rev-parse --show-toplevel`)
        GIT_BRANCH=$(git symbolic-ref --short -q HEAD)
        PS1+="$C_BRANCH$GIT_BRANCH$C_NONE "
    fi

    # Path and user@hostname
    PS1+="$C_PATH\w\n"
    PS1+="$C_USER\u@\h$C_NONE\$ "
}
