ARG STEAM_USERNAME
ARG STEAM_PASSWORD
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
RUN groupadd --gid 999 ue4 \
    && useradd --create-home --home /home/ue4 --shell /bin/bash --uid 999 --gid ue4 ue4 \
    && usermod --append --groups audio,video ue4
WORKDIR /home/ue4
USER ue4

ENV GAMEDIR /home/ue4/CrimsonMirror
ENV STEAMCMDDIR /home/ue4/steamcmd

# mount in the linux server
ADD --chown=ue4:ue4 LinuxServer ${GAMEDIR}

# install steam runtimes  ${STEAM_USERNAME} ${STEAM_PASSWORD} \
RUN mkdir -p ${STEAMCMDDIR} && cd ${STEAMCMDDIR} \
    && wget -qO- 'https://steamcdn-a.akamaihd.net/client/installer/steamcmd_linux.tar.gz' | tar zxf -
RUN ${STEAMCMDDIR}/steamcmd.sh \
    +login anonymous \
    +force_install_dir /home/ue4/.steam \
    validate +quit
RUN mkdir -p /home/ue4/.steam/sdk64 \
    && cp ${STEAMCMDDIR}/linux64/steamclient.so /home/ue4/.steam/sdk64 \
    && mkdir -p ${GAMEDIR}/CrimsonMirror/Saved/SaveGames

EXPOSE 27016/tcp
EXPOSE 27016/udp
EXPOSE 7777/tcp
EXPOSE 7777/udp