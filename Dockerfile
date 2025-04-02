# Created By:   VPR
# Created:      April 13th, 2024

# Updated By:   VPR
# Updated:      April 1st, 2025

# Description:  Dockerfile for vpr-overwatch development

FROM gcc:latest

# Set env to avoid user input interruption during installation
ENV TZ=America/New_York
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# Install normal goodies
RUN apt update && apt-get install -y --no-install-recommends \
make \
cmake

# Create working environment
ENV HOME=/root
WORKDIR /opt/overwatch-dev/
