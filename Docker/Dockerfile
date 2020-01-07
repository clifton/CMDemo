FROM nvidia/opengl:1.0-glvnd-devel-ubuntu18.04

# Add a sentinel label so we can easily identify all derived images, including intermediate images
LABEL ue4.sentinel="1"

# Disable interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install our build prerequisites
USER root
RUN apt-get update && apt-get install -y --no-install-recommends --no-install-suggests \
    build-essential \
    ca-certificates \
    curl \
    git \
    python3 \
    python3-pip \
    shared-mime-info \
    tzdata \
    unzip \
    xdg-user-dirs \
    wget \
    zip \
    netcat \
    && apt-get clean autoclean \
    && apt-get autoremove -y \
    && rm -rf /var/lib/apt/lists/* 

# Since UE4 refuses to build or run as the root user under Linux, create a non-root user
RUN useradd --create-home --home /home/ue4 --shell /bin/bash --uid 1000 ue4 \
    && usermod -a -G audio,video ue4

# Install SteamCMD
USER ue4
ENV STEAMCMDDIR=/home/ue4/steamcmd
RUN mkdir -p ${STEAMCMDDIR} && cd ${STEAMCMDDIR} \
    && wget -qO- 'https://steamcdn-a.akamaihd.net/client/installer/steamcmd_linux.tar.gz' | tar zxf -

EXPOSE 27016/tcp
EXPOSE 27016/udp
EXPOSE 7777/tcp
EXPOSE 7777/udp