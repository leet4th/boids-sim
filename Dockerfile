FROM ubuntu:22.04 as base
# FROM nvidia/cuda:11.8.0-runtime-ubuntu22.04 as base

ENV DEBIAN_FRONTEND=noninteractive

# Setup non-root user
ARG USERNAME=lee
ARG USER_UID=1000
ARG USER_GID=$USER_UID

# Create the user
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && usermod --shell /bin/bash ${USERNAME} \
    #
    # [Optional] Add sudo support. Omit if you don't need to install software after connecting.
    && apt-get update \
    && apt-get install -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME

WORKDIR /home/${USERNAME}


# install required packages
RUN apt-get update && apt-get install -y \
    git \
    build-essential \
    curl \
    wget \
    python3 \
    python3-pip \
    python3-dev \
    python3-venv


# install additional packages
RUN apt-get update && apt-get install -y \
    fzf \
    htop \
    tree \
    parallel \
    dos2unix \
    cmake \
    strace \
    valgrind \
    bsdmainutils\
    net-tools \
    jq \
    kcachegrind \
    google-perftools \
    libgoogle-perftools-dev \
    graphviz \
    linux-tools-generic \
    && rm -rf /var/lib/apt/lists/*

# dotfiles
ADD dotfiles /home/${USERNAME}/

# User owns everything in home dir
RUN chown -R ${USERNAME}:${USERNAME} /home/${USERNAME}

# Set the default user
USER $USERNAME

CMD /bin/bash