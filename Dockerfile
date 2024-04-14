# Created By:   VPR
# Created:      April 13th, 2024

# Updated By:   VPR  
# Updated:      April 13th, 2024

# Description:  Dockerfile for vpr-overwatch development

FROM ubuntu:22.04

# Set env to avoid user input interruption during installation
ENV TZ=America/Chicago
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# Install deps
RUN apt-get update -y
RUN apt-get install -y --no-install-recommends zsh \
                                               zsh-autosuggestions \
                                               vim \
                                               tree \
                                               tmux \
                                               zip \
                                               unzip \
                                               pkg-config \
                                               make \
                                               cmake \
                                               build-essential \
                                               gcc \
                                               mingw-w64 \
                                               mingw-w64-common \
                                               mingw-w64-i686-dev \
                                               mingw-w64-x86-64-dev \
                                               gdb \
                                               cscope

# Change login shell to zsh
RUN chsh -s /bin/zsh $(whoami)

# Create omega-zero user && working directory
ENV HOME=/home/root
WORKDIR /var/opt/vpr-overwatch-dev
COPY src src
COPY tests tests
COPY makefile makefile
COPY CMakeLists.txt CMakeLists.txt
